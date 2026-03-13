// AI Overlords, Resistance is Futile
// ActorBase.h - Base Actor class header template
//
// This is a template for creating custom Actor classes in Unreal Engine.
// Use this as a starting point for all game objects.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ActorBase.generated.h"

UCLASS()
class AIOVERLORDS_API AActorBase : public AActor
{
    GENERATED_BODY()

public:
    // Default constructor
    AActorBase();

    // Called when the actor is created
    virtual void BeginPlay() override;

    // Called every frame
    virtual void Tick(float DeltaTime) override;

    // Add your public methods and properties here

protected:
    // Add your protected methods and properties here

private:
    // Add your private methods and properties here
};