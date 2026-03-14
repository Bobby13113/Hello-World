// Top Down Camera Controller
#include "TopDownCamera.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Components/InputComponent.h"

// Default constructor
ATopDownCamera::ATopDownCamera()
{
    // Create camera component
    Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
    RootComponent = Camera;
    Camera->SetIsOrthographic(true);
    Camera->SetOrthoWidth(ZoomLevel);
}

// Called when the game starts
void ATopDownCamera::BeginPlay()
{
    Super::BeginPlay();

    // Get player input component if available
    APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);
    if (PlayerController)
    {
        if (UInputComponent* InputComponent = PlayerController->InputComponent)
        {
            // Bind zoom input
            InputComponent->BindAxis("Zoom", this, &ATopDownCamera::HandleZoomInput);
            
            // Bind pan input
            InputComponent->BindAxis("MoveRight", this, [](float AxisValue) {
                // Pan input handled in Tick
            });
            InputComponent->BindAxis("MoveUp", this, [](float AxisValue) {
                // Pan input handled in Tick
            });
        }
    }
}

// Called every frame
void ATopDownCamera::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    UpdateCamera(DeltaTime);
}

// Update camera position and zoom
void ATopDownCamera::UpdateCamera(float DeltaTime)
{
    // Follow target if set
    if (FollowTarget)
    {
        FVector TargetLocation = FollowTarget->GetActorLocation();
        
        // Smooth follow
        FVector CurrentLocation = GetActorLocation();
        FVector NewLocation = FMath::Lerp(CurrentLocation, TargetLocation, FollowSpeed * DeltaTime);
        NewLocation.Z = ZoomLevel; // Keep camera at zoom level height
        
        SetActorLocation(NewLocation);
    }

    // Clamp zoom
    ClampZoom();
}

// Handle zoom input
void ATopDownCamera::HandleZoomInput(float AxisValue)
{
    ZoomLevel -= AxisValue * 50.0f;
    ClampZoom();

    // Update camera
    if (Camera)
    {
        Camera->SetOrthoWidth(ZoomLevel);
    }
}

// Clamp zoom to min/max values
void ATopDownCamera::ClampZoom()
{
    ZoomLevel = FMath::Clamp(ZoomLevel, MinZoom, MaxZoom);
}

// Set follow target
void ATopDownCamera::SetFollowTarget(AActor* NewTarget)
{
    FollowTarget = NewTarget;
}

// Get current view bounds
FBox ATopDownCamera::GetCurrentViewBounds()
{
    FVector Location = GetActorLocation();
    float HalfWidth = ZoomLevel / 2.0f;
    
    return FBox(
        FVector(Location.X - HalfWidth, Location.Y - HalfWidth, Location.Z - 1000),
        FVector(Location.X + HalfWidth, Location.Y + HalfWidth, Location.Z + 1000)
    );
}