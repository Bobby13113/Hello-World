// AI Overlords, Resistance is Futile
// ResistanceUnit.h - Player resistance fighter header template
//
// This is a template for creating resistance fighter characters.
// Players use unconventional warfare against AI Overlords.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ResistanceUnit.generated.h"

class USpringArmComponent;
class UCameraComponent;

UCLASS()
class AIOVERLORDS_API AResistanceUnit : public ACharacter
{
    GENERATED_BODY()

public:
    // Default constructor
    AResistanceUnit();

    // Called when the controller is changed
    virtual void PossessedBy(AController* NewController) override;

    // Called when the game starts
    virtual void BeginPlay() override;

    // Setup player input
    virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

    // Movement functions
    UFUNCTION(BlueprintCallable)
    void MoveForward(float Value);

    UFUNCTION(BlueprintCallable)
    void MoveRight(float Value);

    // Action functions
    UFUNCTION(BlueprintCallable)
    void Attack();

    UFUNCTION(BlueprintCallable)
    void UseItem();

    // Initialize resistance-specific abilities
    void InitializeResistanceAbilities();

    // Add your public methods and properties here

protected:
    // Add your protected methods and properties here

private:
    // Camera setup
    USpringArmComponent* CameraBoom;
    UCameraComponent* FollowCamera;

    // Add your private methods and properties here
};