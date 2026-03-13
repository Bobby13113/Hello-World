// AI Overlords, Resistance is Futile
// Weapon.cpp - Weapon class template
//
// This is a template for creating weapons.
// Resistance fighters use scavenged and custom weapons.

#include "Weapon.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"

// Default constructor
AWeapon::AWeapon()
{
    // Configure weapon properties
    Damage = 25.0f;
    FireRate = 0.1f;
    MaxAmmo = 30;
    CurrentAmmo = MaxAmmo;
    Range = 1000.0f;

    // Create weapon mesh
    WeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WeaponMesh"));
    RootComponent = WeaponMesh;

    // Create muzzle flash particle system
    MuzzleFlash = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("MuzzleFlash"));
    MuzzleFlash->SetupAttachment(WeaponMesh);

    // Create projectile spawn point
    ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("ProjectileSpawnPoint"));
    ProjectileSpawnPoint->SetupAttachment(WeaponMesh);
}

// Fire the weapon
void AWeapon::Fire()
{
    if (CurrentAmmo <= 0)
        return;

    CurrentAmmo--;
    OnFire();

    // Spawn projectile or apply damage
    if (ProjectileClass)
    {
        SpawnProjectile();
    }
    else
    {
        ApplyWeaponDamage();
    }

    // Reset fire timer
    GetWorld()->GetTimerManager().SetTimer(FireTimer, this, &AWeapon::CanFire, FireRate, false);
}

// Spawn a projectile
void AWeapon::SpawnProjectile()
{
    FVector SpawnLocation = ProjectileSpawnPoint->GetComponentLocation();
    FRotator SpawnRotation = ProjectileSpawnPoint->GetComponentRotation();

    FActorSpawnParameters SpawnParams;
    SpawnParams.Owner = this;
    SpawnParams.Instigator = GetInstigator();

    AActor* Projectile = GetWorld()->SpawnActor<AActor>(ProjectileClass, SpawnLocation, SpawnRotation, SpawnParams);
    
    if (Projectile)
    {
        OnProjectileSpawned(Projectile);
    }
}

// Apply damage to targets in range
void AWeapon::ApplyWeaponDamage()
{
    FVector ShootDirection = ProjectileSpawnPoint->GetForwardVector();
    FVector StartTrace = ProjectileSpawnPoint->GetComponentLocation();
    FVector EndTrace = StartTrace + (ShootDirection * Range);

    FHitResult HitResult;
    FCollisionQueryParams QueryParams;
    QueryParams.bTraceComplex = false;
    QueryParams.AddIgnoredActor(this);
    QueryParams.AddIgnoredActor(GetInstigator());

    if (GetWorld()->LineTraceSingleByChannel(HitResult, StartTrace, EndTrace, ECC_Visibility, QueryParams))
    {
        AActor* HitActor = HitResult.GetActor();
        if (HitActor)
        {
            // Apply damage to hit actor
            UGameplayStatics::ApplyDamage(
                HitActor,
                Damage,
                GetInstigatorController(),
                this,
                UDamageType::StaticClass()
            );
        }
    }
}

// Reload the weapon
void AWeapon::Reload()
{
    CurrentAmmo = MaxAmmo;
    OnReloaded();
}

// Can the weapon fire?
bool AWeapon::CanFire() const
{
    return CurrentAmmo > 0;
}