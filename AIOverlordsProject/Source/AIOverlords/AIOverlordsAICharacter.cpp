// Copyright Epic Games, Inc. All Rights Reserved.

#include "AIOverlordsAICharacter.h"
#include "AIOverlordsCharacter.h"
#include "AI/AIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "Perception/AIPerceptionComponent.h"
#include "Navigation/PathFollowingComponent.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"

AAIOverlordsAICharacter::AAIOverlordsAICharacter()
{
	// Set default values
	AggroRange = 1000.0f;
	SightRadius = 1500.0f;
	PatrolPointIndex = 0;

	// Create vision sphere
	VisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("VisionSphere"));
	VisionSphere->SetupAttachment(GetRootComponent());
	VisionSphere->SetSphereRadius(AggroRange);
	VisionSphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	VisionSphere->SetCollisionResponseToAllChannels(ECR_Ignore);
	VisionSphere->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

	// Create AI perception component
	AIPerception = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerception"));

	// Set up perception config
	TArray<TSubclassOf<UAISense>> Senses;
	Senses.Add(UAISense_Sight::StaticClass());
	Senses.Add(UAISense_Damage::StaticClass());
	Senses.Add(UAISense_Audio::StaticClass());

	AIPerception->SetDominantSense(Senses[0]);
	AIPerception->ConfigureSense(*Senses[0], SightRadius, 0.0f, true, true);
	AIPerception->SetPerceptionRadius(SightRadius);
	AIPerception->SetUpdatingMode(EAIPerceptionUpdateMode::Dynamic);

	// Set combat state to idle
	CombatState = EAICombatState::Idle;
}

void AAIOverlordsAICharacter::BeginPlay()
{
	Super::BeginPlay();

	// Get AI controller
	AIController = Cast<AAIController>(GetController());

	if (AIController && BehaviorTree)
	{
		// Run behavior tree
		AIController->RunBehaviorTree(BehaviorTree);
	}

	// Set up perception listener
	if (AIPerception)
	{
		AIPerception->OnPerceptionUpdated.AddDynamic(this, &AAIOverlordsAICharacter::OnPerceptionUpdated);
	}
}

void AAIOverlordsAICharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Handle AI logic based on state
	switch (CombatState)
	{
	case EAICombatState::Idle:
	{
		// Check for player detection
		if (DetectPlayer())
	{
			SetCombatState(EAICombatState::Chase);
		}
		break;
	}
	case EAICombatState::Chase:
	{
		// Move to player
		MoveToPlayer();

		// Check if player is in range to attack
		if (HasLineOfSightTo(GetActorLocation() + (GetControlRotation().Vector() * 500.0f)))
		{
			SetCombatState(EAICombatState::Combat);
		}

		// If player lost sight, return to last seen location
		if (!DetectPlayer())
		{
			SetCombatState(EAICombatState::Investigate);
		}
		break;
	}
	case EAICombatState::Combat:
	{
		// Attack player
		AttackPlayer();

		// If player escaped, return to chase
		if (!HasLineOfSightTo(GetActorLocation() + (GetControlRotation().Vector() * 500.0f)))
		{
			SetCombatState(EAICombatState::Chase);
		}
		break;
	}
	case EAICombatState::Investigate:
	{
		// Move to last seen location
		if (LastSeenPlayerLocation != FVector::ZeroVector)
		{
			if (AIController)
			{
				AIController->MoveToLocation(LastSeenPlayerLocation, 50.0f);
			}

			// If reached last seen location, return to patrol
			if (GetDistanceTo(LastSeenPlayerLocation) < 100.0f)
			{
				SetCombatState(EAICombatState::Patrol);
			}
		}
		else
		{
			SetCombatState(EAICombatState::Patrol);
		}
		break;
	}
	case EAICombatState::Patrol:
	{
		// Move to patrol point
		FVector PatrolPoint = GetPatrolPoint();
		if (AIController)
		{
			AIController->MoveToLocation(PatrolPoint, 50.0f);
		}

		// If reached patrol point, check for player
		if (GetDistanceTo(PatrolPoint) < 100.0f)
		{
			if (DetectPlayer())
			{
				SetCombatState(EAICombatState::Chase);
			}
		}
		break;
	}
	}
}

void AAIOverlordsAICharacter::OnPerceptionUpdated(TArray<AActor*> UpdatedActors)
{
	for (AActor* Actor : UpdatedActors)
	{
		if (Actor && Actor->ActorHasTag("Player"))
		{
			// Player detected
			LastSeenPlayerLocation = Actor->GetActorLocation();
		}
	}
}

void AAIOverlordsAICharacter::MoveToPlayer()
{
	if (AAIOverlordsCharacter* Player = UGameplayStatics::GetPlayerPawn(GetWorld(), 0))
	{
		if (AIController)
		{
			AIController->MoveToActor(Player, AggroRange * 0.5f);
		}
	}
}

void AAIOverlordsAICharacter::ReturnToPatrol()
{
	SetCombatState(EAICombatState::Patrol);
}

bool AAIOverlordsAICharacter::DetectPlayer()
{
	if (AAIOverlordsCharacter* Player = UGameplayStatics::GetPlayerPawn(GetWorld(), 0))
	{
		// Check distance
		if (GetDistanceTo(Player) <= AggroRange)
		{
			// Check line of sight
			if (HasLineOfSightTo(Player->GetActorLocation()))
			{
				return true;
			}
		}
	}
	return false;
}

bool AAIOverlordsAICharacter::HasLineOfSightTo(const FVector& TargetLocation)
{
	// Perform line trace
	FVector StartLocation = GetActorLocation();
	FVector EndLocation = TargetLocation;
	FHitResult HitResult;

	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(this);
	CollisionParams.bTraceComplex = false;
	CollisionParams.bReturnPhysicalMaterial = false;

	return GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECC_Visibility, CollisionParams) == false;
}

FVector AAIOverlordsAICharacter::GetPatrolPoint()
{
	// Get patrol points from world
	TArray<AActor*> PatrolPoints;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AActor::StaticClass(), PatrolPoints);

	// Filter for patrol points (tagged with "PatrolPoint")
	TArray<AActor*> FilteredPatrolPoints;
	for (AActor* Point : PatrolPoints)
	{
		if (Point && Point->ActorHasTag("PatrolPoint"))
		{
			FilteredPatrolPoints.Add(Point);
		}
	}

	if (FilteredPatrolPoints.Num() > 0)
	{
		// Get next patrol point
		AActor* PatrolPoint = FilteredPatrolPoints[PatrolPointIndex % FilteredPatrolPoints.Num()];
		if (PatrolPoint)
		{
			PatrolPointIndex++;
			return PatrolPoint->GetActorLocation();
		}
	}

	// Return default location if no patrol points found
	return GetActorLocation();
}

void AAIOverlordsAICharacter::AttackPlayer()
{
	if (AAIOverlordsCharacter* Player = UGameplayStatics::GetPlayerPawn(GetWorld(), 0))
	{
		// Fire weapon if in range
		if (GetDistanceTo(Player) <= AggroRange * 0.5f)
		{
			FireWeapon();
		}
	}
}

void AAIOverlordsAICharacter::SetCombatState(EAICombatState NewState)
{
	CombatState = NewState;
}

EAICombatState AAIOverlordsAICharacter::GetCombatState() const
{
	return CombatState;
}