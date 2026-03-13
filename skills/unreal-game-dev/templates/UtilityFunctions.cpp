// AI Overlords, Resistance is Futile
// UtilityFunctions.cpp - Utility functions template
//
// This is a template for creating utility functions.
// Use this for common operations and AI Overlord-specific logic.

#include "UtilityFunctions.h"

// Get the nearest enemy to a given location
AActor* UUtilityFunctions::GetNearestEnemy(const FVector& Location, float MaxDistance)
{
    AActor* NearestEnemy = nullptr;
    float MinDistance = MaxDistance;

    // Iterate through all actors to find nearest enemy
    for (TActorIterator<AActor> It(GetWorld()); It; ++It)
    {
        AActor* Actor = *It;
        if (!Actor || Actor == GetOwner())
            continue;

        float Distance = (Actor->GetActorLocation() - Location).Size();
        if (Distance < MinDistance)
        {
            MinDistance = Distance;
            NearestEnemy = Actor;
        }
    }

    return NearestEnemy;
}

// Calculate AI decision score for an action
float UUtilityFunctions::CalculateDecisionScore(const FVector& Location, const FString& ActionType)
{
    float Score = 0.0f;

    // Add action-specific scoring logic
    if (ActionType == "Attack")
    {
        // Score based on enemy proximity, line of sight, etc.
    }
    else if (ActionType == "Defend")
    {
        // Score based on strategic position, cover availability, etc.
    }
    else if (ActionType == "Patrol")
    {
        // Score based on coverage, previous patrol patterns, etc.
    }

    return Score;
}

// Check if location is visible from another location
bool UUtilityFunctions::IsLocationVisible(const FVector& FromLocation, const FVector& ToLocation)
{
    FHitResult HitResult;
    FCollisionQueryParams QueryParams;
    QueryParams.bTraceComplex = false;
    QueryParams.bReturnPhysicalMaterial = false;

    // Trace from FromLocation to ToLocation
    bool bHit = GetWorld()->LineTraceSingleByChannel(
        HitResult,
        FromLocation,
        ToLocation,
        ECC_Visibility,
        QueryParams
    );

    return !bHit || HitResult.GetActor() == nullptr;
}

// Get random location in a radius around a point
FVector UUtilityFunctions::GetRandomLocationInRadius(const FVector& Center, float Radius)
{
    float Angle = FMath::FRand() * 360.0f;
    float Distance = FMath::FRand() * Radius;

    FVector Offset = FVector(
        FMath::Cos(FMath::DegreesToRadians(Angle)) * Distance,
        FMath::Sin(FMath::DegreesToRadians(Angle)) * Distance,
        0.0f
    );

    return Center + Offset;
}