// Copyright Epic Games, Inc. All Rights Reserved.

#include "AIOverlordsCameraManager.h"
#include "AIOverlordsPlayerController.h"
#include "Engine/World.h"
#include "Math/UnrealMathUtility.h"

AAIOverlordsCameraManager::AAIOverlordsCameraManager()
{
	CameraLocation = FVector::ZeroVector;
	CameraRotation = FRotator(0.0f, 0.0f, 0.0f);
	CameraFOV = 90.0f;
	ZoomLevel = 1.0f;
	MoveSpeed = 1000.0f;
	RotateSpeed = 2.0f;
	ZoomSpeed = 10.0f;
	MinZoom = 0.5f;
	MaxZoom = 3.0f;
	MinBounds = FVector(-10000.0f, -10000.0f, -1000.0f);
	MaxBounds = FVector(10000.0f, 10000.0f, 1000.0f);
}

void AAIOverlordsCameraManager::BeginPlay()
{
	Super::BeginPlay();
}

void AAIOverlordsCameraManager::UpdateCamera(float DeltaTime)
{
	// Smoothly interpolate camera rotation toward target rotation
	CameraRotation = FMath::RInterpTo(CameraRotation, CameraRotation, DeltaTime, RotateSpeed);
	
	// Clamp zoom level
	ZoomLevel = FMath::Clamp(ZoomLevel, MinZoom, MaxZoom);
	
	// Update FOV based on zoom
	CameraFOV = FMath::Lerp(90.0f, 60.0f, (ZoomLevel - MinZoom) / (MaxZoom - MinZoom));
}

void AAIOverlordsCameraManager::SetPlayerController(AAIOverlordsPlayerController* InPlayerController)
{
	PlayerController = InPlayerController;
}

FVector AAIOverlordsCameraManager::GetCameraLocation() const
{
	return CameraLocation;
}

void AAIOverlordsCameraManager::SetCameraLocation(const FVector& NewLocation)
{
	// Clamp position to bounds
	CameraLocation = FMath::Clamp(NewLocation, MinBounds, MaxBounds);
}

void AAIOverlordsCameraManager::AdjustZoom(float ZoomAmount)
{
	// Adjust zoom level
	ZoomLevel += ZoomAmount * ZoomSpeed * GetWorld()->GetDeltaSeconds();
	ZoomLevel = FMath::Clamp(ZoomLevel, MinZoom, MaxZoom);
}

void AAIOverlordsCameraManager::PanCamera(const FVector2D& PanDirection)
{
	if (!PlayerController) return;
	
	// Calculate movement direction based on camera rotation
	const FRotator CameraRot = PlayerController->GetControlRotation();
	const FVector Forward = FRotationMatrix(CameraRot).GetUnitAxis(EAxis::X);
	const FVector Right = FRotationMatrix(CameraRot).GetUnitAxis(EAxis::Y);
	
	// Calculate movement vector
	FVector MovementVector = Forward * PanDirection.X + Right * PanDirection.Y;
	MovementVector.Z = 0.0f; // Keep movement flat
	MovementVector *= MoveSpeed * GetWorld()->GetDeltaSeconds();
	
	// Apply movement
	CameraLocation += MovementVector;
	
	// Clamp to bounds
	CameraLocation = FMath::Clamp(CameraLocation, MinBounds, MaxBounds);
}

void AAIOverlordsCameraManager::SetCameraRotation(const FRotator& NewRotation)
{
	CameraRotation = NewRotation;
}

FRotator AAIOverlordsCameraManager::GetCameraRotation() const
{
	return CameraRotation;
}

float AAIOverlordsCameraManager::GetCameraFOV() const
{
	return CameraFOV;
}

void AAIOverlordsCameraManager::SetCameraFOV(float FOV)
{
	CameraFOV = FMath::Clamp(FOV, 30.0f, 120.0f);
}

FBoxSphereBounds AAIOverlordsCameraManager::GetCameraBounds() const
{
	return FBoxSphereBounds(FBox(MinBounds, MaxBounds));
}