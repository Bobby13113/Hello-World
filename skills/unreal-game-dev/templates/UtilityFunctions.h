// AI Overlords, Resistance is Futile
// UtilityFunctions.h - Utility functions header template
//
// This is a template for creating utility functions.
// Use this for common operations and AI Overlord-specific logic.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "UtilityFunctions.generated.h"

/**
 * Utility functions for AI Overlords gameplay logic
 */
UCLASS()
class AIOVERLORDS_API UUtilityFunctions : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

public:
    // Get the nearest enemy to a given location
    UFUNCTION(BlueprintCallable, Category = "AI")
    static AActor* GetNearestEnemy(const FVector& Location, float MaxDistance = 1000.0f);

    // Calculate AI decision score for an action
    UFUNCTION(BlueprintCallable, Category = "AI")
    static float CalculateDecisionScore(const FVector& Location, const FString& ActionType);

    // Check if location is visible from another location
    UFUNCTION(BlueprintCallable, Category = "AI")
    static bool IsLocationVisible(const FVector& FromLocation, const FVector& ToLocation);

    // Get random location in a radius around a point
    UFUNCTION(BlueprintCallable, Category = "AI")
    static FVector GetRandomLocationInRadius(const FVector& Center, float Radius);

    // Add your public methods and properties here

protected:
    // Add your protected methods and properties here

private:
    // Add your private methods and properties here
};