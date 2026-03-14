// Copyright Epic Games, Inc. All Rights Reserved.

#include "AIOverlordsCharacter.h"
#include "AIOverlordsPlayerController.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "InputMappingContext.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Engine/World.h"

AAIOverlordsCharacter::AAIOverlordsCharacter()
{
	// Create camera boom
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(GetMesh());
	CameraBoom->SetRelativeLocation(FVector(0.0f, 0.0f, 50.0f));
	CameraBoom->SetRelativeRotation(FRotator(-45.0f, 0.0f, 0.0f));
	CameraBoom->TargetArmLength = 600.0f;
	CameraBoom->bEnableCameraLag = true;
	CameraBoom->CameraLagSpeed = 3.0f;
	CameraBoom->bUsePawnControlRotation = false;

	// Create follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	// Configure character mesh
	CharacterMesh = GetMesh();
	CharacterMesh->SetupAttachment(GetRootComponent());
	CharacterMesh->SetRelativeLocation(FVector(0.0f, 0.0f, -90.0f));
	CharacterMesh->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));

	// Set default mouse sensitivity
	MouseSensitivity = 1.0f;
}

void AAIOverlordsCharacter::BeginPlay()
{
	Super::BeginPlay();

	// Get player controller
	if (AAIOverlordsPlayerController* PlayerController = Cast<AAIOverlordsPlayerController>(GetController()))
	{
		// Set up camera manager
		PlayerController->SetFollowCamera(FollowCamera);
	}
}

void AAIOverlordsCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// Get player controller
		AAIOverlordsPlayerController* PlayerController = Cast<AAIOverlordsPlayerController>(GetController());

		if (PlayerController && PlayerController->GetInputMappingContext())
		{
			// Movement bindings
			EnhancedInputComponent->BindAction(PlayerController->GetMoveAction(), ETriggerEvent::Triggered, this, &AAIOverlordsCharacter::MoveForward, PlayerController->GetMoveAction());
			EnhancedInputComponent->BindAction(PlayerController->GetMoveAction(), ETriggerEvent::Triggered, this, &AAIOverlordsCharacter::MoveRight, PlayerController->GetMoveAction());

			// Look bindings
			EnhancedInputComponent->BindAction(PlayerController->GetLookAction(), ETriggerEvent::Triggered, this, &AAIOverlordsCharacter::LookUp, PlayerController->GetLookAction());
			EnhancedInputComponent->BindAction(PlayerController->GetLookAction(), ETriggerEvent::Triggered, this, &AAIOverlordsCharacter::LookRight, PlayerController->GetLookAction());

			// Action bindings
			EnhancedInputComponent->BindAction(PlayerController->GetJumpAction(), ETriggerEvent::Started, this, &AAIOverlordsCharacter::JumpInput, true);
			EnhancedInputComponent->BindAction(PlayerController->GetJumpAction(), ETriggerEvent::Completed, this, &AAIOverlordsCharacter::JumpInput, false);

			EnhancedInputComponent->BindAction(PlayerController->GetFireAction(), ETriggerEvent::Started, this, &AAIOverlordsCharacter::FireInput, true);
			EnhancedInputComponent->BindAction(PlayerController->GetFireAction(), ETriggerEvent::Completed, this, &AAIOverlordsCharacter::FireInput, false);

			EnhancedInputComponent->BindAction(PlayerController->GetReloadAction(), ETriggerEvent::Started, this, &AAIOverlordsCharacter::ReloadInput, true);
			EnhancedInputComponent->BindAction(PlayerController->GetReloadAction(), ETriggerEvent::Completed, this, &AAIOverlordsCharacter::ReloadInput, false);
		}
	}
}

void AAIOverlordsCharacter::MoveForward(float Value)
{
	if (Value != 0.0f)
	{
		// Get control rotation (ignoring pitch)
		const FRotator Rotation = GetControlRotation();
		const FRotator YawRotation(0.0f, Rotation.Yaw, 0.0f);

		// Calculate forward vector
		const FVector Forward = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		
		// Add movement
		AddMovementInput(Forward, Value);
	}
}

void AAIOverlordsCharacter::MoveRight(float Value)
{
	if (Value != 0.0f)
	{
		// Get control rotation (ignoring pitch)
		const FRotator Rotation = GetControlRotation();
		const FRotator YawRotation(0.0f, Rotation.Yaw, 0.0f);

		// Calculate right vector
		const FVector Right = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		
		// Add movement
		AddMovementInput(Right, Value);
	}
}

void AAIOverlordsCharacter::LookUp(float Value)
{
	if (Value != 0.0f)
	{
		// Add pitch input (vertical look)
		AddControllerPitchInput(Value * MouseSensitivity);
	}
}

void AAIOverlordsCharacter::LookRight(float Value)
{
	if (Value != 0.0f)
	{
		// Add yaw input (horizontal look)
		AddControllerYawInput(Value * MouseSensitivity);
	}
}

void AAIOverlordsCharacter::JumpInput(bool bPressed)
{
	if (bPressed)
	{
		// Trigger jump
		Jump();
	}
	else
	{
		// Stop jump
		StopJumping();
	}
}

void AAIOverlordsCharacter::FireInput(bool bPressed)
{
	if (bPressed && IsAlive())
	{
		// Fire weapon
		FireWeapon();
	}
}

void AAIOverlordsCharacter::ReloadInput(bool bPressed)
{
	if (bPressed)
	{
		// Reload weapon
		ReloadWeapon();
	}
}