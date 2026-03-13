// AI Overlords, Resistance is Futile
// ResistanceUnit.cpp - Player resistance fighter template
//
// This is a template for creating resistance fighter characters.
// Players use unconventional warfare against AI Overlords.

#include "ResistanceUnit.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

// Default constructor
AResistanceUnit::AResistanceUnit()
{
    // Configure character movement
    GetCharacterMovement()->MaxWalkSpeed = 400.0f;
    GetCharacterMovement()->GravityScale = 1.0f;
    GetCharacterMovement()->JumpZVelocity = 500.0f;

    // Configure camera
    CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
    CameraBoom->SetupAttachment(RootComponent);
    CameraBoom->TargetArmLength = 400.0f;
    CameraBoom->SocketOffset = FVector(0.0f, 0.0f, 50.0f);

    FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
    FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
}

// Called when the controller is changed
void AResistanceUnit::PossessedBy(AController* NewController)
{
    Super::PossessedBy(NewController);
    
    // Initialize resistance-specific abilities
    InitializeResistanceAbilities();
}

// Called when the game starts
void AResistanceUnit::BeginPlay()
{
    Super::BeginPlay();
    
    // Add player initialization code
}

// Setup player input
void AResistanceUnit::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);
    
    // Movement bindings
    PlayerInputComponent->BindAxis("MoveForward", this, &AResistanceUnit::MoveForward);
    PlayerInputComponent->BindAxis("MoveRight", this, &AResistanceUnit::MoveRight);
    
    // Action bindings
    PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AResistanceUnit::Jump);
    PlayerInputComponent->BindAction("Attack", IE_Pressed, this, &AResistanceUnit::Attack);
    PlayerInputComponent->BindAction("UseItem", IE_Pressed, this, &AResistanceUnit::UseItem);
}

// Movement functions
void AResistanceUnit::MoveForward(float Value)
{
    if (Controller && Value != 0.0f)
    {
        const FRotator Rotation = Controller->GetControlRotation();
        const FVector Direction = FRotationMatrix(Rotation).GetRow(XAxisIndex);
        AddMovementInput(Direction, Value);
    }
}

void AResistanceUnit::MoveRight(float Value)
{
    if (Controller && Value != 0.0f)
    {
        const FRotator Rotation = Controller->GetControlRotation();
        const FVector Direction = FRotationMatrix(Rotation).GetRow(YAxisIndex);
        AddMovementInput(Direction, Value);
    }
}

// Action functions
void AResistanceUnit::Attack()
{
    // Implement resistance fighter attack logic
    // Example: Fire weapon, throw grenade, etc.
}

void AResistanceUnit::UseItem()
{
    // Implement item usage logic
    // Example: Medkit, repair tool, hacking device, etc.
}

// Initialize resistance-specific abilities
void AResistanceUnit::InitializeResistanceAbilities()
{
    // Add ability initialization code
    // Example: Set starting inventory, unlock skills, etc.
}