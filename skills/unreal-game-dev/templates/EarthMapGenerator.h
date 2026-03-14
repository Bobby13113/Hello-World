// Earth Map Generator - Top Down Scroller
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EarthMapGenerator.generated.h"

UCLASS()
class AIOVERLORDS_API AEarthMapGenerator : public AActor
{
    GENERATED_BODY()

public:	
    // Default constructor
    AEarthMapGenerator();

protected:
    // Called when the game starts
    virtual void BeginPlay() override;

public:	
    // Called every frame
    virtual void Tick(float DeltaTime) override;

    // Earth map settings
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float MapWidth = 20000.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float MapHeight = 10000.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float GridSize = 100.0f;

    // Map features
    UPROPERTY(EditAnywhere)
    TSubclassOf<AActor> TerrainType;

    UPROPERTY(EditAnywhere)
    TSubclassOf<AActor> CityType;

    UPROPERTY(EditAnywhere)
    TSubclassOf<AActor> TerrainFeatureType;

    // Generated map components
    UPROPERTY()
    UInstancedStaticMeshComponent* TerrainMesh;

    UPROPERTY()
    UInstancedStaticMeshComponent* CityMesh;

    UPROPERTY()
    UInstancedStaticMeshComponent* TerrainFeatureMesh;

    // Methods
    UFUNCTION(BlueprintCallable)
    void GenerateEarthMap();

    UFUNCTION(BlueprintCallable)
    void SpawnTerrain(float X, float Y);

    UFUNCTION(BlueprintCallable)
    void SpawnCity(float X, float Y, const FString& CityName);

    UFUNCTION(BlueprintCallable)
    void SpawnTerrainFeature(float X, float Y, const FString& FeatureName);

    // Coordinate conversion
    UFUNCTION(BlueprintCallable)
    FVector LatLonToMapCoordinates(float Latitude, float Longitude);

    UFUNCTION(BlueprintCallable)
    void MapCoordinatesToLatLon(FVector Coordinates, float& Latitude, float& Longitude);

    // Camera bounds
    UPROPERTY(VisibleAnywhere)
    FBox Bounds;
};