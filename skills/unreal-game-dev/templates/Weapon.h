// AI Overlords, Resistance is Futile
// Weapon.h - Weapon class header template
//
// This is a template for creating weapons.
// Resistance fighters use scavenged and custom weapons.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Weapon.generated.h"

class UStaticMeshComponent;
class UParticleSystemComponent;
class USceneComponent;

/**
 * Base weapon class for all resistance weapons
 */
UCLASS()
class AIOVERLORDS_API AWeapon : public AActor
{
    GENERATED_BODY()

public:
    // Default constructor
    AWeapon();

    // Fire the weapon
    UFUNCTION(BlueprintCallable)
    void Fire();

    // Reload the weapon
    UFUNCTION(BlueprintCallable)
    void Reload();

    // Can the weapon fire?
    bool CanFire() const;

    // Accessors
    UFUNCTION(BlueprintPure)
    float GetDamage() const { return Damage; }

    UFUNCTION(BlueprintPure)
    float GetFireRate() const { return FireRate; }

    UFUNCTION(BlueprintPure)
    int GetAmmo() const { return CurrentAmmo; }

    UFUNCTION(BlueprintPure)
    int GetMaxAmmo() const { return MaxAmmo; }

    UFUNCTION(BlueprintPure)
    float GetRange() const { return Range; }

    UFUNCTION(BlueprintCallable)
    void SetProjectileClass(TSubclassOf<AActor> NewClass) { ProjectileClass = NewClass; }

    // Add your public methods and properties here

protected:
    // Spawn a projectile
    virtual void SpawnProjectile();

    // Apply damage to targets in range
    virtual void ApplyWeaponDamage();

    // Event when weapon fires
    UFUNCTION(BlueprintImplementableEvent)
    void OnFire();

    // Event when weapon is reloaded
    UFUNCTION(BlueprintImplementableEvent)
    void OnReloaded();

    // Event when projectile is spawned
    UFUNCTION(BlueprintImplementableEvent)
    void OnProjectileSpawned(AActor* Projectile);

    // Add your protected methods and properties here

private:
    // Weapon properties
    float Damage;
    float FireRate;
    int MaxAmmo;
    int CurrentAmmo;
    float Range;

    // Weapon components
    UStaticMeshComponent* WeaponMesh;
    UParticleSystemComponent* MuzzleFlash;
    USceneComponent* ProjectileSpawnPoint;

    // Projectile class to spawn
    TSubclassOf<AActor> ProjectileClass;

    // Timer for firing
    FTimerHandle FireTimer;

    // Add your private methods and properties here
};