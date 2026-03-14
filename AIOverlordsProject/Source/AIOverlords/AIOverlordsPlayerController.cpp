// Copyright Epic Games, Inc. All Rights Reserved.

#include "AIOverlordsPlayerController.h"
#include "AIOverlordsCameraManager.h"
#include "Engine/World.h"

AAIOverlordsPlayerController::AAIOverlordsPlayerController()
{
	CameraManagerClass = AAIOverlordsCameraManager::StaticClass();
	CameraManager = nullptr;
	CurrentZoomLevel = 1.0f;
	CameraPosition = FVector::ZeroVector;
}

void AAIOverlordsPlayerController::BeginPlay()
{
	Super::BeginPlay();
	
	// Create camera manager
	if (CameraManagerClass)
	{
		CameraManager = GetWorld()->SpawnActor<AAIOverlordsCameraManager>(CameraManagerClass);
		CameraManager->SetPlayerController(this);
	}
}

void AAIOverlordsPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	// Update camera if we have a camera manager
	if (CameraManager)
	{
		CameraManager->UpdateCamera(DeltaTime);
	}
}

AAIOverlordsCameraManager* AAIOverlordsPlayerController::GetCameraManager() const
{
	return CameraManager;
}

FVector AAIOverlordsPlayerController::GetCameraPosition() const
{
	if (CameraManager)
	{
		return CameraManager->GetCameraLocation();
	}
	return FVector::ZeroVector;
}

void AAIOverlordsPlayerController::MoveCameraTo(const FVector& TargetPosition)
{
	if (CameraManager)
	{
		CameraManager->SetCameraLocation(TargetPosition);
	}
}

void AAIOverlordsPlayerController::ZoomCamera(float ZoomAmount)
{
	if (CameraManager)
	{
		CameraManager->AdjustZoom(ZoomAmount);
	}
}

void AAIOverlordsPlayerController::PanCamera(const FVector2D& PanDirection)
{
	if (CameraManager)
	{
		CameraManager->PanCamera(PanDirection);
	}
}

FVector AAIOverlordsPlayerController::ScreenToWorld(const FVector2D& ScreenPosition)
{
	FVector WorldDirection;
	FVector WorldPosition;
	
	if (DeprojectScreenPositionToWorld(ScreenPosition.X, ScreenPosition.Y, WorldPosition, WorldDirection))
	{
		return WorldPosition;
	}
	
	return FVector::ZeroVector;
}

FVector2D AAIOverlordsPlayerController::WorldToScreen(const FVector& WorldPosition)
{
	FVector2D ScreenPosition;
	
	if (ProjectWorldToScreen(WorldPosition, ScreenPosition))
	{
		return ScreenPosition;
	}
	
	return FVector2D::ZeroVector;
}

void AAIOverlordsPlayerController::OnMoveCamera(const FInputActionValue& InputActionValue)
{
	if (CameraManager)
	{
		const FVector2D MovementVector = InputActionValue.Get<FVector2D>();
		CameraManager->PanCamera(MovementVector * CameraMoveSpeed * GetWorld()->GetDeltaSeconds());
	}
}

void AAIOverlordsPlayerController::OnZoomCamera(const FInputActionValue& InputActionValue)
{
	if (CameraManager)
	{
		const float ZoomValue = InputActionValue.Get<float>();
		CameraManager->AdjustZoom(ZoomValue);
	}
}