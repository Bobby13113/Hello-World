// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "AIOverlordsCameraManager.h"
#include "AIOverlordsPlayerController.generated.h"

/**
 * Player Controller for AI Overlords
 * Handles input for movement, camera control, and actions
 */
UCLASS()
class AAIOverlordsPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AAIOverlordsPlayerController();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

public:
	/** Camera manager class */
	UPROPERTY(EditDefaultsOnly, Category = "Camera")
	TSubclassOf<AAIOverlordsCameraManager> CameraManagerClass;

	/** Current camera manager instance */
	UPROPERTY()
	AAIOverlordsCameraManager* CameraManager;

	/** Get the camera manager */
	UFUNCTION(BlueprintPure, Category = "Camera")
	AAIOverlordsCameraManager* GetCameraManager() const;

	/** Camera movement settings */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	float CameraMoveSpeed = 1000.0f;

	/** Get camera position */
	UFUNCTION(BlueprintPure, Category = "Camera")
	FVector GetCameraPosition() const;

	/** Move camera to position */
	UFUNCTION(BlueprintCallable, Category = "Camera")
	void MoveCameraTo(const FVector& TargetPosition);

	/** Zoom camera */
	UFUNCTION(BlueprintCallable, Category = "Camera")
	void ZoomCamera(float ZoomAmount);

	/** Pan camera */
	UFUNCTION(BlueprintCallable, Category = "Camera")
	void PanCamera(const FVector2D& PanDirection);

	/** Get world position from screen coordinates */
	UFUNCTION(BlueprintCallable, Category = "Camera")
	FVector ScreenToWorld(const FVector2D& ScreenPosition);

	/** Get screen coordinates from world position */
	UFUNCTION(BlueprintCallable, Category = "Camera")
	FVector2D WorldToScreen(const FVector& WorldPosition);

protected:
	/** Camera zoom level */
	float CurrentZoomLevel;

	/** Camera position */
	FVector CameraPosition;

	/** Input handlers */
	UFUNCTION(BlueprintCallable, Category = "Input")
	void OnMoveCamera(const FInputActionValue& InputActionValue);

	UFUNCTION(BlueprintCallable, Category = "Input")
	void OnZoomCamera(const FInputActionValue& InputActionValue);
};