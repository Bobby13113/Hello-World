// AI Overlords, Resistance is Futile
// Projectile.cpp - Projectile class template
//
// This is a template for creating projectiles.
// Used for bullets, missiles, and other thrown objects.

#include "Projectile.h"
#include "Components/SphereComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"

// Default constructor
AProjectile::AProjectile()
{
    // Configure collision
    CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionComponent"));
    CollisionComponent->SetSphereRadius(20.0f);
    CollisionComponent->BodyInstance.SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
    CollisionComponent->BodyInstance.SetCollisionObjectType(COLLISION_PROJECTILE);
    CollisionComponent->BodyInstance.SetCollisionResponsesToAllChannels(ECollisionResponse::ECR_Ignore);
    CollisionComponent->BodyInstance.SetCollisionResponseToChannel(COLLISION_WORLD, ECollisionResponse::ECR_Block);
    CollisionComponent->BodyInstance.SetCollisionResponseToChannel(COLLISION_PLAYER, ECollisionResponse::ECR_Overlap);
    CollisionComponent->BodyInstance.SetCollisionResponseToChannel(COLLISION_ENEMY, ECollisionResponse::ECR_Overlap);
    RootComponent = CollisionComponent;

    // Configure movement
    MovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("MovementComponent"));
    MovementComponent->InitialSpeed = 2000.0f;
    MovementComponent->MaxSpeed = 2000.0f;
    MovementComponent->Velocity = FVector(1.0f, 0.0f, 0.0f);
    MovementComponent->bRotationFollowsVelocity = true;

    // Create trail effect
    TrailEffect = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("TrailEffect"));
    TrailEffect->SetupAttachment(RootComponent);
}

// Called when the game starts
void AProjectile::BeginPlay()
{
    Super::BeginPlay();
    
    // Set initial velocity
    FVector LaunchDirection = GetActorRotation().Vector();
    MovementComponent->Velocity = LaunchDirection * MovementComponent->InitialSpeed;
    
    // Set projectile owner
    FActorSpawnParameters SpawnParams;
    SpawnParams.Owner = this;
    SpawnParams.Instigator = Instigator;

    // Start auto-destruct timer
    GetWorld()->GetTimerManager().SetTimer(AutoDestructTimer, this, &AProjectile::AutoDestruct, AutoDestructTime, false);
}

// Handle collision
void AProjectile::OnComponentHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
    if (OtherActor && OtherActor != this)
    {
        // Apply damage to hit actor
        if (OtherActor->IsA<ACharacter>() || OtherActor->IsA<AActor>())
        {
            UGameplayStatics::ApplyDamage(
                OtherActor,
                Damage,
                GetInstigatorController(),
                this,
                UDamageType::StaticClass()
            );
        }

        // Spawn impact effect
        if (ImpactEffect)
        {
            UGameplayStatics::SpawnEmitterAtLocation(
                GetWorld(),
                ImpactEffect,
                Hit.Location,
                Hit.Normal.Rotation()
            );
        }

        // Destroy projectile
        Destroy();
    }
}

// Auto-destruct the projectile
void AProjectile::AutoDestruct()
{
    if (ExplosionEffect)
    {
        UGameplayStatics::SpawnEmitterAtLocation(
            GetWorld(),
            ExplosionEffect,
            GetActorLocation()
        );
    }

    Destroy();
}

// Set projectile velocity
void AProjectile::SetVelocity(const FVector& NewVelocity)
{
    MovementComponent->Velocity = NewVelocity;
}

// Get projectile velocity
FVector AProjectile::GetVelocity() const
{
    return MovementComponent->Velocity;
}