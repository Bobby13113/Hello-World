// Earth Map Generator - Top Down Scroller
#include "EarthMapGenerator.h"
#include "Components/InstancedStaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"

// Default constructor
AEarthMapGenerator::AEarthMapGenerator()
{
    // Set this actor to call Tick() every frame
    PrimaryActorTick.bCanEverTick = true;

    // Create components
    TerrainMesh = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("TerrainMesh"));
    RootComponent = TerrainMesh;

    CityMesh = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("CityMesh"));
    CityMesh->SetupAttachment(RootComponent);

    TerrainFeatureMesh = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("TerrainFeatureMesh"));
    TerrainFeatureMesh->SetupAttachment(RootComponent);
}

// Called when the game starts
void AEarthMapGenerator::BeginPlay()
{
    Super::BeginPlay();
    GenerateEarthMap();
}

// Called every frame
void AEarthMapGenerator::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    // Camera scrolling logic
    if (GetWorld())
    {
        FVector CameraLocation = UGameplayStatics::GetPlayerCameraLocation(this, 0);
        
        // Keep camera within bounds
        if (CameraLocation.X < Bounds.Min.X) CameraLocation.X = Bounds.Min.X;
        if (CameraLocation.X > Bounds.Max.X) CameraLocation.X = Bounds.Max.X;
        if (CameraLocation.Y < Bounds.Min.Y) CameraLocation.Y = Bounds.Min.Y;
        if (CameraLocation.Y > Bounds.Max.Y) CameraLocation.Y = Bounds.Max.Y;
    }
}

// Generate the Earth map
void AEarthMapGenerator::GenerateEarthMap()
{
    // Calculate bounds
    Bounds.Min = FVector(-MapWidth / 2, -MapHeight / 2, 0);
    Bounds.Max = FVector(MapWidth / 2, MapHeight / 2, 0);

    // Generate terrain (simplified grid)
    for (float X = Bounds.Min.X; X < Bounds.Max.X; X += GridSize)
    {
        for (float Y = Bounds.Min.Y; Y < Bounds.Max.Y; Y += GridSize)
        {
            SpawnTerrain(X, Y);
        }
    }

    // Spawn cities at key locations
    SpawnCity(0, 0, "New York");
    SpawnCity(1000, 500, "Los Angeles");
    SpawnCity(-800, 1200, "London");
    SpawnCity(1500, -500, "Tokyo");
    SpawnCity(-1200, -800, "Sydney");
}

// Spawn terrain tile
void AEarthMapGenerator::SpawnTerrain(float X, float Y)
{
    if (TerrainType)
    {
        FTransform Transform(FVector(X, Y, 0));
        TerrainMesh->AddInstanceWorld(Transform);
    }
}

// Spawn city
void AEarthMapGenerator::SpawnCity(float X, float Y, const FString& CityName)
{
    if (CityType)
    {
        FTransform Transform(FVector(X, Y, 100));
        CityMesh->AddInstanceWorld(Transform);

        // Add city label for debugging
        UE_LOG(LogTemp, Log, TEXT("Spawned city: %s at (%.2f, %.2f)"), *CityName, X, Y);
    }
}

// Spawn terrain feature
void AEarthMapGenerator::SpawnTerrainFeature(float X, float Y, const FString& FeatureName)
{
    if (TerrainFeatureType)
    {
        FTransform Transform(FVector(X, Y, 50));
        TerrainFeatureMesh->AddInstanceWorld(Transform);
    }
}

// Convert lat/lon to map coordinates
FVector AEarthMapGenerator::LatLonToMapCoordinates(float Latitude, float Longitude)
{
    // Convert lat/lon to world coordinates
    float X = (Longitude + 180.0f) / 360.0f * MapWidth - MapWidth / 2.0f;
    float Y = (90.0f - Latitude) / 180.0f * MapHeight - MapHeight / 2.0f;
    
    return FVector(X, Y, 0);
}

// Convert map coordinates to lat/lon
void AEarthMapGenerator::MapCoordinatesToLatLon(FVector Coordinates, float& Latitude, float& Longitude)
{
    Longitude = (Coordinates.X + MapWidth / 2.0f) / MapWidth * 360.0f - 180.0f;
    Latitude = 90.0f - (Coordinates.Y + MapHeight / 2.0f) / MapHeight * 180.0f;
}