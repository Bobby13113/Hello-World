// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AIOverlordsCharacterBase.h"
#include "AIOverlordsCharacter.generated.h"

/**
 * Player character class for AI Overlords
 * Extends the base character with player-specific functionality
 */
UCLASS()
class AAIOverlordsCharacter : public AAIOverlordsCharacterBase
{
	GENERATED_BODY()

public:
	AAIOverlordsCharacter();

protected:
	virtual void BeginPlay() override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	/** Move input handler */
	UFUNCTION(BlueprintCallable, Category = "Input")
	void MoveForward(float Value);

	UFUNCTION(BlueprintCallable, Category = "Input")
	void MoveRight(float Value);

	UFUNCTION(BlueprintCallable, Category = "Input")
	void LookUp(float Value);

	UFUNCTION(BlueprintCallable, Category = "Input")
	void LookRight(float Value);

	/** Jump input handler */
	UFUNCTION(BlueprintCallable, Category = "Input")
	void JumpInput(bool bPressed);

	/** Fire input handler */
	UFUNCTION(BlueprintCallable, Category = "Input")
	void FireInput(bool bPressed);

	/** Reload input handler */
	UFUNCTION(BlueprintCallable, Category = "Input")
	void ReloadInput(bool bPressed);

protected:
	/** Input binding */
	UPROPERTY(VisibleAnywhere, Category = "Input")
	UInputComponent* InputComponent;

	/** Mouse sensitivity */
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	float MouseSensitivity = 1.0f;

	/** Camera boom */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	class UCameraComponent* FollowCamera;

	/** Character mesh */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Mesh")
	class USkeletalMeshComponent* CharacterMesh;
};