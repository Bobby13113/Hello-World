// AI Overlords, Resistance is Futile
// HackingDevice.h - Hacking device header template
//
// This is a template for creating hacking devices.
// Resistance fighters use these to disrupt AI systems.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HackingDevice.generated.h"

class USphereComponent;
class UParticleSystemComponent;

/**
 * Base hacking device class
 */
UCLASS()
class AIOVERLORDS_API AHackingDevice : public AActor
{
    GENERATED_BODY()

public:
    // Default constructor
    AHackingDevice();

    // Start the hacking process
    UFUNCTION(BlueprintCallable)
    void StartHacking(AActor* Target);

    // Stop the hacking process
    UFUNCTION(BlueprintCallable)
    void StopHacking();

    // Handle hacking progress
    UFUNCTION(BlueprintCallable)
    void HackTick();

    // Can the device hack this target?
    bool CanHack(AActor* Target) const;

    // Accessors
    UFUNCTION(BlueprintPure)
    float GetHackingProgress() const { return HackingProgress; }

    UFUNCTION(BlueprintPure)
    bool IsHacking() const { return bIsHacking; }

    UFUNCTION(BlueprintCallable)
    void SetHackRange(float NewRange) { HackRange = NewRange; }

    // Add your public methods and properties here

protected:
    // Complete the hack
    virtual void CompleteHack();

    // Execute hack-specific effect
    virtual void ExecuteHackEffect(AActor* Target);

    // Add your protected methods and properties here

private:
    // Hacking properties
    float HackingProgress;
    bool bIsHacking;
    float HackRange = 500.0f;
    float HackTickRate = 0.1f;
    float HackProgressRate = 1.0f;

    // Target actor
    AActor* TargetActor;

    // Hacking components
    USphereComponent* CollisionComponent;
    UParticleSystemComponent* HackEffect;

    // Effects
    UPROPERTY(EditDefaultsOnly, Category = "Effects")
    UParticleSystem* HackSuccessEffect;

    // Timer for hacking
    FTimerHandle HackTimer;

    // Add your private methods and properties here
};