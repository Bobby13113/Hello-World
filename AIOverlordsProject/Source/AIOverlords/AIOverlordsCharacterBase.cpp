// Copyright Epic Games, Inc. All Rights Reserved.

#include "AIOverlordsCharacterBase.h"
#include "AIOverlordsWeapon.h"
#include "HealthComponent.h"
#include "AIOverlordsCombatComponent.h"
#include "Engine/World.h"

AAIOverlordsCharacterBase::AAIOverlordsCharacterBase()
{
	// Set default values
	TeamID = 0;
	RespawnTimer = 0.0f;
	MaxHealth = 100.0f;
	MoveSpeed = 600.0f;
	JumpZ = 500.0f;

	// Create health component
	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));
	
	// Create combat component
	CombatComponent = CreateDefaultSubobject<UAIOverlordsCombatComponent>(TEXT("CombatComponent"));
	
	// Set character movement
	if (GetCharacterMovement())
	{
		GetCharacterMovement()->MaxWalkSpeed = MoveSpeed;
		GetCharacterMovement()->JumpZVelocity = JumpZ;
		GetCharacterMovement()->AirControl = 0.35f;
	}

	// Setup weapon attachment
	WeaponAttachmentPoints.Add(FName("WeaponSocket"));
	
	// Set default respawn time
	RespawnTime = 5.0f;
}

void AAIOverlordsCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
	// Initialize health
	if (HealthComponent)
	{
		HealthComponent->SetMaxHealth(MaxHealth);
		HealthComponent->SetHealth(MaxHealth);
	}
}

void AAIOverlordsCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Handle respawn logic
	if (IsDead() && RespawnTimer > 0.0f)
	{
		RespawnTimer -= DeltaTime;
		if (RespawnTimer <= 0.0f)
		{
			Respawn();
		}
	}
}

UHealthComponent* AAIOverlordsCharacterBase::GetHealthComponent() const
{
	return HealthComponent;
}

UAIOverlordsCombatComponent* AAIOverlordsCharacterBase::GetCombatComponent() const
{
	return CombatComponent;
}

AWeapon* AAIOverlordsCharacterBase::GetCurrentWeapon() const
{
	return CurrentWeapon;
}

void AAIOverlordsCharacterBase::SetCurrentWeapon(AWeapon* NewWeapon)
{
	CurrentWeapon = NewWeapon;
	
	if (CurrentWeapon)
	{
		CurrentWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, FName("WeaponSocket"));
	}
}

void AAIOverlordsCharacterBase::FireWeapon()
{
	if (CurrentWeapon && IsAlive())
	{
		CurrentWeapon->Fire();
	}
}

void AAIOverlordsCharacterBase::ReloadWeapon()
{
	if (CurrentWeapon)
	{
		CurrentWeapon->Reload();
	}
}

bool AAIOverlordsCharacterBase::IsDead() const
{
	return HealthComponent && HealthComponent->GetHealth() <= 0.0f;
}

bool AAIOverlordsCharacterBase::IsAlive() const
{
	return HealthComponent && HealthComponent->GetHealth() > 0.0f;
}

int32 AAIOverlordsCharacterBase::GetTeamID() const
{
	return TeamID;
}

void AAIOverlordsCharacterBase::SetTeamID(int32 NewTeamID)
{
	TeamID = NewTeamID;
}

void AAIOverlordsCharacterBase::TakeDamage(float DamageAmount, class AController* InstigatedBy, class AActor* DamageCauser)
{
	if (!IsAlive()) return;
	
	if (HealthComponent)
	{
		HealthComponent->TakeDamage(DamageAmount, InstigatedBy, DamageCauser);
		
		if (IsDead())
		{
			Kill();
		}
	}
}

void AAIOverlordsCharacterBase::Kill()
{
	if (!IsAlive()) return;
	
	// Set respawn timer
	RespawnTimer = RespawnTime;
	
	// Hide character
	GetMesh()->SetVisibility(false);
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	
	// Detach from controller
	DetachFromControllerPendingDestroy();
	
	// Set collision to no collision
	SetActorEnableCollision(false);
	
	// Play death animation if available
	if (DeathAnimation && GetMesh())
	{
		// Play animation (simplified - would need proper animation montage in real implementation)
		GetMesh()->PlayAnimation(DeathAnimation, false);
	}
}

void AAIOverlordsCharacterBase::Respawn()
{
	// Get world spawn point
	AActor* SpawnActor = nullptr;
	for (TActorIterator<AActor> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		if (ActorItr->HasActorTag("PlayerSpawn"))
		{
			SpawnActor = *ActorItr;
			break;
		}
	}
	
	if (!SpawnActor)
	{
		SpawnActor = GetWorld()->GetFirstPlayerController()->GetPawn();
	}
	
	// Reset health
	if (HealthComponent)
	{
		HealthComponent->SetHealth(MaxHealth);
	}
	
	// Reset team ID
	TeamID = 0;
	
	// Show character
	GetMesh()->SetVisibility(true);
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	
	// Set collision to query and physics
	SetActorEnableCollision(true);
	
	// Move to spawn point
	if (SpawnActor)
	{
		SetActorLocation(SpawnActor->GetActorLocation());
		SetActorRotation(SpawnActor->GetActorRotation());
	}
	
	// Reactivate controller
	if (GetController())
	{
		GetController()->SetPawn(this);
	}
	
	RespawnTimer = 0.0f;
}