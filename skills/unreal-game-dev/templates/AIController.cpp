// AI Overlords, Resistance is Futile
// AIController.cpp - AI Controller class template
//
// This is a template for creating AI Controllers.
// The AI Controller manages AI behavior and decision-making.

#include "AIController.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

// Default constructor
AAIController::AAIController()
{
    // Configure perception system
    PerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerception"));
    
    // Configure sight sense
    FAISenseConfig_Sight SightConfig;
    SightConfig.SightRadius = 1000.0f;
    SightConfig.LossRadius = 1200.0f;
    SightConfig.PeripheralVisionAngle = 45.0f;
    SightConfig.SetMaxAge(5.0f);
    SightConfig.AutoRegister = true;
    SightConfig.RegisterWithPerceptionSystem(*PerceptionComponent);
}

// Called when the controller is created
void AAIController::BeginPlay()
{
    Super::BeginPlay();
    
    // Initialize AI behavior
    InitializeAI();
}

// Initialize AI behavior and blackboard
void AAIController::InitializeAI()
{
    // Set up blackboard for AI decision-making
    Blackboard = GetBlackboardComponent();
    
    // Add AI-specific initialization
    // Example: Set starting state, target priorities, etc.
}

// Override to handle AI movement
void AAIController::MoveToActor(AActor* Goal, float AcceptanceRadius, bool bUseBlocking)
{
    Super::MoveToActor(Goal, AcceptanceRadius, bUseBlocking);
    
    // Add AI Overlord-specific movement logic
    // Example: Patrol patterns, aggressive chasing, etc.
}

// Override to handle AI movement to location
void AAIController::MoveToLocation(const FVector& Dest, float AcceptanceRadius, bool bUseBlocking)
{
    Super::MoveToLocation(Dest, AcceptanceRadius, bUseBlocking);
    
    // Add AI Overlord-specific movement logic
}