// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AIOverlordsWeapon.h"
#include "GameFramework/Character.h"
#include "AIOverlordsCharacterBase.generated.h"

// Forward declarations
class UHealthComponent;
class UAIOverlordsCombatComponent;

/**
 * Base character class for all units in the game
 * Provides common functionality for player and AI characters
 */
UCLASS(Abstract)
class AAIOverlordsCharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	AAIOverlordsCharacterBase();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

public:
	/** Get the character's health component */
	UFUNCTION(BlueprintPure, Category = "Health")
	UHealthComponent* GetHealthComponent() const;

	/** Get the character's combat component */
	UFUNCTION(BlueprintPure, Category = "Combat")
	UAIOverlordsCombatComponent* GetCombatComponent() const;

	/** Get the character's weapon */
	UFUNCTION(BlueprintPure, Category = "Combat")
	AWeapon* GetCurrentWeapon() const;

	/** Set the character's weapon */
	UFUNCTION(BlueprintCallable, Category = "Combat")
	void SetCurrentWeapon(AWeapon* NewWeapon);

	/** Fire the current weapon */
	UFUNCTION(BlueprintCallable, Category = "Combat")
	void FireWeapon();

	/** Reload the current weapon */
	UFUNCTION(BlueprintCallable, Category = "Combat")
	void ReloadWeapon();

	/** Check if character is dead */
	UFUNCTION(BlueprintPure, Category = "Health")
	bool IsDead() const;

	/** Check if character is alive */
	UFUNCTION(BlueprintPure, Category = "Health")
	bool IsAlive() const;

	/** Get character's team ID */
	UFUNCTION(BlueprintPure, Category = "Team")
	int32 GetTeamID() const;

	/** Set character's team ID */
	UFUNCTION(BlueprintCallable, Category = "Team")
	void SetTeamID(int32 NewTeamID);

	/** Take damage */
	UFUNCTION(BlueprintCallable, Category = "Combat")
	void TakeDamage(float DamageAmount, class AController* InstigatedBy, class AActor* DamageCauser);

	/** Kill the character */
	UFUNCTION(BlueprintCallable, Category = "Combat")
	void Kill();

	/**Respawn the character */
	UFUNCTION(BlueprintCallable, Category = "Combat")
	void Respawn();

	/** Character stats */
	UPROPERTY(EditDefaultsOnly, Category = "Stats")
	float MaxHealth = 100.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Stats")
	float MoveSpeed = 600.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Stats")
	float JumpZ = 500.0f;

protected:
	/** Health component */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Health")
	UHealthComponent* HealthComponent;

	/** Combat component */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat")
	UAIOverlordsCombatComponent* CombatComponent;

	/** Current weapon */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat")
	AWeapon* CurrentWeapon;

	/** Team ID */
	int32 TeamID;

	/** Weapon attachment point */
	UPROPERTY(VisibleDefaultsOnly, Category = "Combat")
	TArray<FName> WeaponAttachmentPoints;

	/** Death animation */
	UPROPERTY(EditDefaultsOnly, Category = "Animation")
	class UAnimSequence* DeathAnimation;

	/** Respawn time */
	UPROPERTY(EditDefaultsOnly, Category = "Spawning")
	float RespawnTime = 5.0f;

	/** Respawn timer */
	float RespawnTimer;
};