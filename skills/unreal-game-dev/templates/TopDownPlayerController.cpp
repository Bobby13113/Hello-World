// Top Down Player Controller
#include "TopDownPlayerController.h"
#include "TopDownCamera.h"
#include "Kismet/GameplayStatics.h"
#include "Components/InputComponent.h"

// Default constructor
ATopDownPlayerController::ATopDownPlayerController()
{
    bShowMouseCursor = true;
    bEnableClickEvents = true;
    bEnableMouseOverEvents = true;
}

// Called when the game starts
void ATopDownPlayerController::BeginPlay()
{
    Super::BeginPlay();

    // Get player input component if available
    if (UInputComponent* InputComponent = InputComponent)
    {
        // Bind movement input
        InputComponent->BindAxis("MoveRight", this, &ATopDownPlayerController::HandleMovementInput);
        InputComponent->BindAxis("MoveUp", this, &ATopDownPlayerController::HandleMovementInput);
        
        // Bind look input
        InputComponent->BindAxis("LookRight", this, &ATopDownPlayerController::HandleLookInput);
        InputComponent->BindAxis("LookUp", this, &ATopDownPlayerController::HandleLookInput);
        
        // Bind mouse events
        InputComponent->BindAction("SelectStart", IE_Pressed, this, &ATopDownPlayerController::StartLooking);
        InputComponent->BindAction("SelectStart", IE_Released, this, &ATopDownPlayerController::StopLooking);
    }
}

// Called every frame
void ATopDownPlayerController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    // Move player unit if has input
    if (PlayerUnit && (MovementInput.X != 0.0f || MovementInput.Y != 0.0f))
    {
        FVector MovementVector = FVector(MovementInput.X, MovementInput.Y, 0.0f);
        PlayerUnit->AddMovementInput(MovementVector, 1.0f);
    }
}

// Handle movement input
void ATopDownPlayerController::HandleMovementInput(float X, float Y)
{
    MovementInput = FVector2D(X, Y);
}

// Handle look input
void ATopDownPlayerController::HandleLookInput(float X, float Y)
{
    LookInput = FVector2D(X, Y);
}

// Start looking (selection mode)
void ATopDownPlayerController::StartLooking()
{
    bIsLooking = true;
    LastMousePosition = GetMousePosition();
}

// Stop looking (selection complete)
void ATopDownPlayerController::StopLooking()
{
    bIsLooking = false;
}

// Get world click location
FVector ATopDownPlayerController::GetWorldClickLocation()
{
    FVector2D MousePosition = GetMousePosition();
    FVector WorldLocation;
    FVector WorldDirection;
    
    DeprojectScreenPositionToWorld(MousePosition.X, MousePosition.Y, WorldLocation, WorldDirection);
    
    return WorldLocation;
}

// Get screen click location
FVector2D ATopDownPlayerController::GetScreenClickLocation()
{
    return GetMousePosition();
}

// Set follow camera
void ATopDownPlayerController::SetFollowCamera(ATopDownCamera* Camera)
{
    FollowCamera = Camera;
}

// Set player unit
void ATopDownPlayerController::SetPlayerUnit(AActor* NewUnit)
{
    PlayerUnit = NewUnit;
    
    // Set follow camera target
    if (FollowCamera)
    {
        FollowCamera->SetFollowTarget(PlayerUnit);
    }
}

// Get actors in selection area
TArray<AActor*> ATopDownPlayerController::GetActorsInSelection(FVector2D StartPoint, FVector2D EndPoint)
{
    TArray<AActor*> SelectedActors;
    
    // Calculate selection box bounds
    FVector2D MinPoint = FVector2D(FMath::Min(StartPoint.X, EndPoint.X), FMath::Min(StartPoint.Y, EndPoint.Y));
    FVector2D MaxPoint = FVector2D(FMath::Max(StartPoint.X, EndPoint.X), FMath::Max(StartPoint.Y, EndPoint.Y));
    
    // Find actors in selection area
    FBox2D SelectionBox(MinPoint, MaxPoint);
    
    // This would be implemented with your specific actor types
    // For now, returns empty array
    return SelectedActors;
}