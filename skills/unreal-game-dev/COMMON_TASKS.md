# Common Tasks in AI Overlords Game Development

## Creating a New Actor

### Using the ActorBase Template

1. Copy `ActorBase.cpp` and `ActorBase.h` to your project
2. Rename files to match your actor class
3. Update class names and functionality

### Example: Creating a New Enemy

```cpp
// MyEnemy.cpp
#include "MyEnemy.h"
#include "Components/SphereComponent.h"

// Default constructor
AMyEnemy::AMyEnemy()
{
    // Configure collision
    CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionComponent"));
    RootComponent = CollisionComponent;
}
```

## Adding a Weapon to Your Character

### Using the Weapon Template

1. Include `Weapon.h` in your character class
2. Create a weapon component in your character's constructor
3. Bind weapon events to character actions

### Example: Adding a Weapon

```cpp
// In your character class header
UPROPERTY(VisibleAnywhere)
AWeapon* CharacterWeapon;

// In your character class constructor
CharacterWeapon = CreateDefaultSubobject<AWeapon>(TEXT("CharacterWeapon"));
```

## Creating a Projectile

### Using the Projectile Template

1. Copy `Projectile.cpp` and `Projectile.h` to your project
2. Customize projectile properties (damage, speed, etc.)
3. Create a Blueprint from the projectile class

### Example: Firing a Projectile

```cpp
// In your weapon class
void AWeapon::Fire()
{
    if (CurrentAmmo > 0 && ProjectileClass)
    {
        FVector SpawnLocation = ProjectileSpawnPoint->GetComponentLocation();
        FRotator SpawnRotation = ProjectileSpawnPoint->GetComponentRotation();

        AActor* Projectile = GetWorld()->SpawnActor<AActor>(
            ProjectileClass,
            SpawnLocation,
            SpawnRotation
        );
    }
}
```

## Implementing AI Controller

### Using the AIController Template

1. Copy `AIController.cpp` and `AIController.h` to your project
2. Customize AI behavior in the `Tick` function
3. Configure AI properties in Unreal Editor

### Example: Patrol Behavior

```cpp
void AAIController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    // Implement patrol logic
    if (CurrentPatrolPoint)
    {
        // Move towards patrol point
        FVector Direction = (CurrentPatrolPoint->GetActorLocation() - GetPawn()->GetActorLocation()).GetSafeNormal();
        GetPawn()->AddMovementInput(Direction);
    }
}
```

## Implementing Hacking Device

### Using the HackingDevice Template

1. Copy `HackingDevice.cpp` and `HackingDevice.h` to your project
2. Add hacking device to your character
3. Implement hacking logic

### Example: Hacking an Enemy

```cpp
// In your character class
void AResistanceUnit::StartHacking(AActor* Target)
{
    if (HackingDevice)
    {
        HackingDevice->StartHacking(Target);
    }
}
```

## Creating a Game Mode

### Using the GameMode Template

1. Copy `GameMode.cpp` and `GameMode.h` to your project
2. Customize game rules in the game mode
3. Set game mode in Unreal Editor

### Example: Setting Game Mode

```cpp
// In your project's DefaultEngine.ini
[/Script/Engine.GameMode]
DefaultGameMode=/Game/YourGameMode.YourGameMode_C
```

## Debugging Tips

### Visual Debugging

```cpp
// Draw debug lines
DrawDebugLine(
    GetWorld(),
    StartLocation,
    EndLocation,
    FColor::Red,
    false,
    -1.f,
    0,
    2.f
);
```

### Log Messages

```cpp
// Log messages
UE_LOG(LogTemp, Warning, TEXT("Debug message: %s"), *YourVariable.ToString());
```

## Performance Optimization

### C++ Best Practices

1. Use components instead of creating actors dynamically
2. Use object pooling for projectiles
3. Minimize blueprint calls from C++
4. Use const references for large objects

### Blueprint Tips

1. Use macro libraries for reusable logic
2. Optimize event graphs with early returns
3. Use timeline nodes for smooth animations
4. Minimize variable usage in event graphs
