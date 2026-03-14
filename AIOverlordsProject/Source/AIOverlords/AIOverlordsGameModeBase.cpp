// Copyright Epic Games, Inc. All Rights Reserved.

#include "AIOverlordsGameModeBase.h"
#include "AIOverlordsPlayerController.h"
#include "AIOverlordsCharacter.h"

AIAIOverlordsGameModeBase::AIAIOverlordsGameModeBase()
{
	// Set default player controller class
	DefaultPlayerControllerClass = AAIOverlordsPlayerController::StaticClass();
	
	// Game state defaults
	bGameInProgress = false;
	bGameOver = false;
	bPlayerDefeated = false;
	PlayerCount = 0;
	AIOverlordCount = 0;
	ResistanceCount = 0;
}

void AIAIOverlordsGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	bGameInProgress = true;
}

AActor* AIAIOverlordsGameModeBase::ChoosePlayerSpawnActor(AController* PlayerController, const TSubclassOf<APawn> PlayerPawnClass, const FString& EntryTag)
{
	// Find the first player start and return it
	for (TActorIterator<AActor> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		if (ActorItr->HasActorTag("PlayerSpawn"))
		{
			return *ActorItr;
		}
	}
	
	// Fallback to default player start if none found
	return Super::ChoosePlayerSpawnActor(PlayerController, PlayerPawnClass, EntryTag);
}

int32 AIAIOverlordsGameModeBase::GetPlayerCount() const
{
	return PlayerCount;
}

int32 AIAIOverlordsGameModeBase::GetAIOverlordCount() const
{
	return AIOverlordCount;
}

int32 AIAIOverlordsGameModeBase::GetResistanceCount() const
{
	return ResistanceCount;
}

bool AIAIOverlordsGameModeBase::IsGameInProgress() const
{
	return bGameInProgress && !bGameOver;
}

bool AIAIOverlordsGameModeBase::IsGameOver() const
{
	return bGameOver;
}

bool AIAIOverlordsGameModeBase::IsPlayerDefeated() const
{
	return bPlayerDefeated;
}