// AI Overlords, Resistance is Futile
// GameMode.cpp - Game Mode class template
//
// This is a template for creating custom Game Mode classes.
// The GameMode controls the core game rules.

#include "GameMode.h"
#include "Player/PlayerStart.h"
#include "GameFramework/PlayerController.h"

// Default constructor
AGameMode::AGameMode()
{
    // Set default pawn class to our base character class
    DefaultPawnClass = nullptr;
    PlayerControllerClass = APlayerController::StaticClass();
    GameStateClass = AGameStateBase::StaticClass();
}

// Called when the game starts
void AGameMode::BeginPlay()
{
    Super::BeginPlay();
    
    // Initialize game rules
    InitializeGameRules();
}

// Called when a player joins the game
void AGameMode::OnPlayerJoined(APlayerController* NewPlayer)
{
    // Spawn player at a valid spawn point
    SpawnPlayerAtStart(NewPlayer);
}

// Initialize game rules and state
void AGameMode::InitializeGameRules()
{
    // Set up game-specific rules
    // This is where you'd configure AI Overlords vs Resistance rules
}

// Spawn player at a valid spawn point
void AGameMode::SpawnPlayerAtStart(APlayerController* Player)
{
    // Find first available player start
    for (TActorIterator<APlayerStart> It(GetWorld()); It; ++It)
    {
        if (It->IsPendingKill())
            continue;
            
        Player->StartSpot = *It;
        break;
    }
}