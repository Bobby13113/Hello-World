// AI Overlords, Resistance is Futile
// HackingDevice.cpp - Hacking device template
//
// This is a template for creating hacking devices.
// Resistance fighters use these to disrupt AI systems.

#include "HackingDevice.h"
#include "Components/SphereComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"

// Default constructor
AHackingDevice::AHackingDevice()
{
    // Configure collision
    CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionComponent"));
    CollisionComponent->SetSphereRadius(100.0f);
    CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    CollisionComponent->SetCollisionObjectType(ECollisionChannel::ECC_WorldStatic);
    CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
    RootComponent = CollisionComponent;

    // Create hack effect
    HackEffect = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("HackEffect"));
    HackEffect->SetupAttachment(RootComponent);
}

// Start the hacking process
void AHackingDevice::StartHacking(AActor* Target)
{
    if (!Target || bIsHacking)
        return;

    TargetActor = Target;
    bIsHacking = true;
    HackingProgress = 0.0f;

    // Set up hack timer
    GetWorld()->GetTimerManager().SetTimer(HackTimer, this, &AHackingDevice::HackTick, HackTickRate, true);
}

// Stop the hacking process
void AHackingDevice::StopHacking()
{
    bIsHacking = false;
    HackingProgress = 0.0f;
    GetWorld()->GetTimerManager().ClearTimer(HackTimer);

    // Reset hack effect
    if (HackEffect)
    {
        HackEffect->DeactivateSystem();
    }
}

// Handle hacking progress
void AHackingDevice::HackTick()
{
    if (!TargetActor || !bIsHacking)
    {
        StopHacking();
        return;
    }

    // Increase hacking progress
    HackingProgress += HackTickRate * HackProgressRate;

    // Check if hacking is complete
    if (HackingProgress >= 1.0f)
    {
        HackingProgress = 1.0f;
        CompleteHack();
    }
}

// Complete the hack
void AHackingDevice::CompleteHack()
{
    bIsHacking = false;
    GetWorld()->GetTimerManager().ClearTimer(HackTimer);

    if (TargetActor)
    {
        // Apply hack effect to target
        UGameplayStatics::ApplyDamage(
            TargetActor,
            0,  // No damage for hack
            GetInstigatorController(),
            this,
            UDamageType::StaticClass()
        );

        // Execute hack-specific logic
        ExecuteHackEffect(TargetActor);

        // Spawn success effect
        if (HackSuccessEffect)
        {
            UGameplayStatics::SpawnEmitterAtLocation(
                GetWorld(),
                HackSuccessEffect,
                TargetActor->GetActorLocation()
            );
        }
    }

    // Reset device
    HackingProgress = 0.0f;
    TargetActor = nullptr;
}

// Execute hack-specific effect
void AHackingDevice::ExecuteHackEffect(AActor* Target)
{
    // Override in subclasses for specific hack effects
    // Examples: Disable enemy AI, reveal location, etc.
}

// Can the device hack this target?
bool AHackingDevice::CanHack(AActor* Target) const
{
    if (!Target)
        return false;

    float Distance = (Target->GetActorLocation() - GetActorLocation()).Size();
    return Distance <= HackRange;
}