// AI Overlords, Resistance is Futile
// Projectile.h - Projectile class header template
//
// This is a template for creating projectiles.
// Used for bullets, missiles, and other thrown objects.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

class USphereComponent;
class UProjectileMovementComponent;
class UParticleSystemComponent;

// Collision channels
#define COLLISION_PROJECTILE ECC_GameTraceChannel1
#define COLLISION_WORLD ECC_WorldStatic
#define COLLISION_PLAYER ECC_GameTraceChannel2
#define COLLISION_ENEMY ECC_GameTraceChannel3

/**
 * Base projectile class for all in-game projectiles
 */
UCLASS()
class AIOVERLORDS_API AProjectile : public AActor
{
    GENERATED_BODY()

public:
    // Default constructor
    AProjectile();

    // Called when the game starts
    virtual void BeginPlay() override;

    // Set projectile velocity
    void SetVelocity(const FVector& NewVelocity);

    // Get projectile velocity
    FVector GetVelocity() const;

    // Add your public methods and properties here

protected:
    // Handle component hit
    virtual void OnComponentHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

    // Auto-destruct the projectile
    virtual void AutoDestruct();

    // Add your protected methods and properties here

private:
    // Projectile properties
    float Damage = 25.0f;
    float AutoDestructTime = 5.0f;

    // Projectile components
    USphereComponent* CollisionComponent;
    UProjectileMovementComponent* MovementComponent;
    UParticleSystemComponent* TrailEffect;

    // Impact and explosion effects
    UPROPERTY(EditDefaultsOnly, Category = "Effects")
    UParticleSystem* ImpactEffect;

    UPROPERTY(EditDefaultsOnly, Category = "Effects")
    UParticleSystem* ExplosionEffect;

    // Timer for auto-destruct
    FTimerHandle AutoDestructTimer;

    // Add your private methods and properties here
};