// AI Overlords, Resistance is Futile
// AIController.h - AI Controller class header template
//
// This is a template for creating AI Controllers.
// The AI Controller manages AI behavior and decision-making.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "AIController.generated.h"

class UAIPerceptionComponent;
class UBlackboardComponent;

UCLASS()
class AIOVERLORDS_API AAIController : public AAIController
{
    GENERATED_BODY()

public:
    // Default constructor
    AAIController();

    // Called when the controller is created
    virtual void BeginPlay() override;

    // Initialize AI behavior and blackboard
    void InitializeAI();

    // Override to handle AI movement
    virtual void MoveToActor(AActor* Goal, float AcceptanceRadius, bool bUseBlocking = false) override;

    // Override to handle AI movement to location
    virtual void MoveToLocation(const FVector& Dest, float AcceptanceRadius, bool bUseBlocking = false) override;

    // Accessors
    UAIPerceptionComponent* GetPerceptionComponent() const { return PerceptionComponent; }
    UBlackboardComponent* GetBlackboardComponent() const { return Blackboard; }

    // Add your public methods and properties here

protected:
    // Add your protected methods and properties here

private:
    // AI Perception Component for sensing the environment
    UAIPerceptionComponent* PerceptionComponent;

    // Blackboard for AI decision-making
    UBlackboardComponent* Blackboard;

    // Add your private methods and properties here
};