// Top Down Camera Controller
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TopDownCamera.generated.h"

UCLASS()
class AIOVERLORDS_API ATopDownCamera : public AActor
{
    GENERATED_BODY()

public:	
    // Default constructor
    ATopDownCamera();

protected:
    // Called when the game starts
    virtual void BeginPlay() override;

public:	
    // Called every frame
    virtual void Tick(float DeltaTime) override;

    // Camera settings
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float FollowSpeed = 5.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float ZoomLevel = 1000.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float MinZoom = 500.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float MaxZoom = 2000.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float PanSpeed = 10.0f;

    // Camera component
    UPROPERTY(VisibleAnywhere)
    UCameraComponent* Camera;

    // Target to follow
    UPROPERTY(EditAnywhere)
    AActor* FollowTarget;

    // Mouse input for panning
    UPROPERTY()
    FVector2D MousePosition;

    UPROPERTY()
    FVector2D LastMousePosition;

    // Zoom input
    UPROPERTY()
    float ZoomInput;

    // Methods
    UFUNCTION(BlueprintCallable)
    void SetFollowTarget(AActor* NewTarget);

    UFUNCTION(BlueprintCallable)
    void HandleZoomInput(float AxisValue);

    UFUNCTION(BlueprintCallable)
    void HandlePanInput(float AxisValueX, float AxisValueY);

    UFUNCTION(BlueprintCallable)
    void UpdateCamera(float DeltaTime);

    UFUNCTION(BlueprintCallable)
    void ClampZoom();

    // Get camera bounds
    UFUNCTION(BlueprintCallable)
    FBox GetCurrentViewBounds();
};