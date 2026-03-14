// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AIOverlordsCharacterBase.h"
#include "AI/AIController.h"
#include "AIOverlordsAICharacter.generated.h"

/**
 * AI Character class for enemy units in AI Overlords
 * Extends the base character with AI-specific functionality
 */
UCLASS()
class AAIOverlordsAICharacter : public AAIOverlordsCharacterBase
{
	GENERATED_BODY()

public:
	AAIOverlordsAICharacter();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

public:
	/** AI controller reference */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI")
	AAIController* AIController;

	/** AI behavior tree */
	UPROPERTY(EditDefaultsOnly, Category = "AI")
	class UBehaviorTree* BehaviorTree;

	/** AI Blackboard */
	UPROPERTY(EditDefaultsOnly, Category = "AI")
	class UBlackboardData* BlackboardData;

	/** AI vision sphere */
	UPROPERTY(VisibleDefaultsOnly, Category = "AI")
	class USphereComponent* VisionSphere;

	/** AI aggression range */
	UPROPERTY(EditDefaultsOnly, Category = "AI")
	float AggroRange = 1000.0f;

	/** AI sight radius */
	UPROPERTY(EditDefaultsOnly, Category = "AI")
	float SightRadius = 1500.0f;

	/** AI perception config */
	UPROPERTY(EditDefaultsOnly, Category = "AI")
	class UAIPerceptionComponent* AIPerception;

	/** AI move to player */
	UFUNCTION(BlueprintCallable, Category = "AI")
	void MoveToPlayer();

	/** AI return to patrol */
	UFUNCTION(BlueprintCallable, Category = "AI")
	void ReturnToPatrol();

	/** AI detect player */
	UFUNCTION(BlueprintCallable, Category = "AI")
	bool DetectPlayer();

	/** AI check line of sight */
	UFUNCTION(BlueprintCallable, Category = "AI")
	bool HasLineOfSightTo(const FVector& TargetLocation);

	/** AI get patrol point */
	UFUNCTION(BlueprintCallable, Category = "AI")
	FVector GetPatrolPoint();

	/** AI attack player */
	UFUNCTION(BlueprintCallable, Category = "AI")
	void AttackPlayer();

	/** AI set combat state */
	UFUNCTION(BlueprintCallable, Category = "AI")
	void SetCombatState(EAICombatState NewState);

	/** AI get combat state */
	UFUNCTION(BlueprintPure, Category = "AI")
	EAICombatState GetCombatState() const;

protected:
	/** AI state */
	EAICombatState CombatState;

	/** Patrol point index */
	int32 PatrolPointIndex;

	/** Target location for AI movement */
	FVector TargetLocation;

	/** Last seen player location */
	FVector LastSeenPlayerLocation;

	/** AI navigation agent */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI")
	class UAIPerceptionComponent* PerceptionComponent;
};