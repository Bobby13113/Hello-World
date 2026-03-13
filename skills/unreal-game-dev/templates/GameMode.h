// AI Overlords, Resistance is Futile
// GameMode.h - Game Mode class header template
//
// This is a template for creating custom Game Mode classes.
// The GameMode controls the core game rules.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GameMode.generated.h"

class APlayerController;

UCLASS()
class AIOVERLORDS_API AGameMode : public AGameModeBase
{
    GENERATED_BODY()

public:
    // Default constructor
    AGameMode();

    // Called when the game starts
    virtual void BeginPlay() override;

    // Called when a player joins the game
    virtual void OnPlayerJoined(APlayerController* NewPlayer);

    // Initialize game rules and state
    void InitializeGameRules();

    // Spawn player at a valid spawn point
    void SpawnPlayerAtStart(APlayerController* Player);

    // Add your public methods and properties here

protected:
    // Add your protected methods and properties here

private:
    // Add your private methods and properties here
};