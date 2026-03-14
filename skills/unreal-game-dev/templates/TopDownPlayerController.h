// Top Down Player Controller
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TopDownPlayerController.generated.h"

UCLASS()
class AIOVERLORDS_API ATopDownPlayerController : public APlayerController
{
    GENERATED_BODY()

public:	
    // Default constructor
    ATopDownPlayerController();

protected:
    // Called when the game starts
    virtual void BeginPlay() override;

public:	
    // Called every frame
    virtual void Tick(float DeltaTime) override;

    // Input bindings
    UPROPERTY(EditAnywhere)
    FVector2D MovementInput;

    UPROPERTY(EditAnywhere)
    FVector2D LookInput;

    UPROPERTY(EditAnywhere)
    bool bIsLooking;

    // Player unit
    UPROPERTY()
    AActor* PlayerUnit;

    // Methods
    UFUNCTION(BlueprintCallable)
    void SetPlayerUnit(AActor* NewUnit);

    UFUNCTION(BlueprintCallable)
    void HandleMovementInput(float X, float Y);

    UFUNCTION(BlueprintCallable)
    void HandleLookInput(float X, float Y);

    UFUNCTION(BlueprintCallable)
    void StartLooking();

    UFUNCTION(BlueprintCallable)
    void StopLooking();

    UFUNCTION(BlueprintCallable)
    FVector GetWorldClickLocation();

    UFUNCTION(BlueprintCallable)
    FVector2D GetScreenClickLocation();

    // Camera control
    UPROPERTY()
    class ATopDownCamera* FollowCamera;

    UFUNCTION(BlueprintCallable)
    void SetFollowCamera(class ATopDownCamera* Camera);

    // Selection
    UPROPERTY(EditAnywhere)
    float SelectionRadius = 200.0f;

    UFUNCTION(BlueprintCallable)
    TArray<AActor*> GetActorsInSelection(FVector2D StartPoint, FVector2D EndPoint);
};