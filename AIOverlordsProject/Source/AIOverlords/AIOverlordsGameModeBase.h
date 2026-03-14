// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AIOverlordsCharacterBase.h"
#include "GameFramework/GameModeBase.h"
#include "AIOverlordsGameModeBase.generated.h"

/**
 * Main Game Mode for AI Overlords
 * Manages game rules, player spawning, and game state
 */
UCLASS()
class AIAIOverlordsGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	AIAIOverlordsGameModeBase();

protected:
	virtual void BeginPlay() override;

public:
	/** Spawns a player character at the default spawn point */
	AActor* ChoosePlayerSpawnActor(AController* PlayerController, const TSubclassOf<APawn> PlayerPawnClass, const FString& EntryTag = FString()) override;

	/** Returns the number of players currently in the game */
	int32 GetPlayerCount() const;

	/** Returns the number of AI overlord units */
	int32 GetAIOverlordCount() const;

	/** Returns the number of resistance fighters */
	int32 GetResistanceCount() const;

	/** Game state enum */
	UFUNCTION(BlueprintPure, Category = "Game")
	bool IsGameInProgress() const;

	UFUNCTION(BlueprintPure, Category = "Game")
	bool IsGameOver() const;

	UFUNCTION(BlueprintPure, Category = "Game")
	bool IsPlayerDefeated() const;

protected:
	/** Track game state */
	bool bGameInProgress;
	bool bGameOver;
	bool bPlayerDefeated;

	/** Counters for units */
	int32 PlayerCount;
	int32 AIOverlordCount;
	int32 ResistanceCount;
};