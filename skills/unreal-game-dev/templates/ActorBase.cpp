// AI Overlords, Resistance is Futile
// ActorBase.cpp - Base Actor class template
//
// This is a template for creating custom Actor classes in Unreal Engine.
// Use this as a starting point for all game objects.

#include "ActorBase.h"

// Add custom includes here

// Default constructor
AActorBase::AActorBase()
{
    // Set default properties
    PrimaryActorTick.bCanEverTick = true;
}

// Called when the actor is created
void AActorBase::BeginPlay()
{
    Super::BeginPlay();
    
    // Add initialization code here
}

// Called every frame
void AActorBase::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    
    // Add frame-by-frame logic here
}