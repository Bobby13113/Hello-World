// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CameraManager.h"
#include "AIOverlordsCameraManager.generated.h"

/**
 * Camera Manager for AI Overlords
 * Handles camera movement, zoom, and view logic
 */
UCLASS()
class AAIOverlordsCameraManager : public ACameraManager
{
	GENERATED_BODY()

public:
	AAIOverlordsCameraManager();

protected:
	virtual void BeginPlay() override;

public:
	/** Update camera each frame */
	UFUNCTION(BlueprintCallable, Category = "Camera")
	void UpdateCamera(float DeltaTime);

	/** Set player controller reference */
	UFUNCTION(BlueprintCallable, Category = "Camera")
	void SetPlayerController(class AAIOverlordsPlayerController* PlayerController);

	/** Get camera location */
	UFUNCTION(BlueprintPure, Category = "Camera")
	FVector GetCameraLocation() const;

	/** Set camera location */
	UFUNCTION(BlueprintCallable, Category = "Camera")
	void SetCameraLocation(const FVector& NewLocation);

	/** Adjust camera zoom */
	UFUNCTION(BlueprintCallable, Category = "Camera")
	void AdjustZoom(float ZoomAmount);

	/** Pan camera */
	UFUNCTION(BlueprintCallable, Category = "Camera")
	void PanCamera(const FVector2D& PanDirection);

	/** Set camera rotation */
	UFUNCTION(BlueprintCallable, Category = "Camera")
	void SetCameraRotation(const FRotator& NewRotation);

	/** Get camera rotation */
	UFUNCTION(BlueprintPure, Category = "Camera")
	FRotator GetCameraRotation() const;

	/** Get camera FOV */
	UFUNCTION(BlueprintPure, Category = "Camera")
	float GetCameraFOV() const;

	/** Set camera FOV */
	UFUNCTION(BlueprintCallable, Category = "Camera")
	void SetCameraFOV(float FOV);

	/** Get camera bounds */
	UFUNCTION(BlueprintPure, Category = "Camera")
	FBoxSphereBounds GetCameraBounds() const;

protected:
	/** Player controller reference */
	AAIOverlordsPlayerController* PlayerController;

	/** Camera position */
	FVector CameraLocation;

	/** Camera rotation */
	FRotator CameraRotation;

	/** Camera FOV */
	float CameraFOV;

	/** Zoom level (1.0 = normal, < 1 = zoomed in, > 1 = zoomed out) */
	float ZoomLevel;

	/** Camera movement speed */
	float MoveSpeed;

	/** Camera rotation speed */
	float RotateSpeed;

	/** Camera zoom speed */
	float ZoomSpeed;

	/** Minimum zoom level */
	float MinZoom;

	/** Maximum zoom level */
	float MaxZoom;

	/** Camera movement bounds */
	FVector MinBounds;
	FVector MaxBounds;
};