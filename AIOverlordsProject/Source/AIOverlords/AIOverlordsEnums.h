// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AIOverlordsEnums.generated.h"

/**
 * AI Combat State enum
 */
UENUM(BlueprintType)
enum class EAICombatState : uint8
{
	Idle UMETA(DisplayName = "Idle"),
	Chase UMETA(DisplayName = "Chase"),
	Combat UMETA(DisplayName = "Combat"),
	Investigate UMETA(DisplayName = "Investigate"),
	Patrol UMETA(DisplayName = "Patrol"),
	Retreat UMETA(DisplayName = "Retreat"),
	Dead UMETA(DisplayName = "Dead")
};

/**
 * Team ID enum
 */
UENUM(BlueprintType)
enum class ETeamID : uint8
{
	Team_None UMETA(DisplayName = "None"),
	Team_Player UMETA(DisplayName = "Player"),
	Team_AI UMETA(DisplayName = "AI"),
	Team_Neutral UMETA(DisplayName = "Neutral")
};

/**
 * Weapon Type enum
 */
UENUM(BlueprintType)
enum class EWeaponType : uint8
{
	Weapon_None UMETA(DisplayName = "None"),
	Weapon_Rifle UMETA(DisplayName = "Rifle"),
	Weapon_Shotgun UMETA(DisplayName = "Shotgun"),
	Weapon_Sniper UMETA(DisplayName = "Sniper"),
	Weapon_Pistol UMETA(DisplayName = "Pistol"),
	Weapon_Melee UMETA(DisplayName = "Melee"),
	Weapon_Heavy UMETA(DisplayName = "Heavy"),
	Weapon_Special UMETA(DisplayName = "Special")
};

/**
 * Damage Type enum
 */
UENUM(BlueprintType)
enum class EDamageType : uint8
{
	Damage_Normal UMETA(DisplayName = "Normal"),
	Damage_Explosive UMETA(DisplayName = "Explosive"),
	Damage_Instant UMETA(DisplayName = "Instant"),
	Damage_Fire UMETA(DisplayName = "Fire"),
	Damage_Electric UMETA(DisplayName = "Electric"),
	Damage_Poison UMETA(DisplayName = "Poison"),
	Damage_Cryo UMETA(DisplayName = "Cryo"),
	Damage_Radiation UMETA(DisplayName = "Radiation")
};

/**
 * Projectile Type enum
 */
UENUM(BlueprintType)
enum class EProjectileType : uint8
{
	Projectile_Bullet UMETA(DisplayName = "Bullet"),
	Projectile_Rocket UMETA(DisplayName = "Rocket"),
	Projectile_Grenade UMETA(DisplayName = "Grenade"),
	Projectile_Laser UMETA(DisplayName = "Laser"),
	Projectile_Plasma UMETA(DisplayName = "Plasma"),
	Projectile_Orb UMETA(DisplayName = "Orb")
};

/**
 * Hacking State enum
 */
UENUM(BlueprintType)
enum class EHackingState : uint8
{
	Hack_Idle UMETA(DisplayName = "Idle"),
	Hack_Attempting UMETA(DisplayName = "Attempting"),
	Hack_Success UMETA(DisplayName = "Success"),
	Hack_Failed UMETA(DisplayName = "Failed")
};

/**
 * Mission State enum
 */
UENUM(BlueprintType)
enum class EMissionState : uint8
{
	Mission_None UMETA(DisplayName = "None"),
	Mission_InProgress UMETA(DisplayName = "In Progress"),
	Mission_Paused UMETA(DisplayName = "Paused"),
	Mission_Completed UMETA(DisplayName = "Completed"),
	Mission_Failed UMETA(DisplayName = "Failed")
};

/**
 * Map Region enum
 */
UENUM(BlueprintType)
enum class EMapRegion : uint8
{
	Region_Earth UMETA(DisplayName = "Earth"),
	Region_Mars UMETA(DisplayName = "Mars"),
	Region_Moon UMETA(DisplayName = "Moon"),
	Region_AsteroidBelt UMETA(DisplayName = "Asteroid Belt"),
	Region_GasGiant UMETA(DisplayName = "Gas Giant"),
	Region_DistantStar UMETA(DisplayName = "Distant Star")
};

/**
 * Resource Type enum
 */
UENUM(BlueprintType)
enum class EResourceType : uint8
{
	Resource_None UMETA(DisplayName = "None"),
	Resource_Metal UMETA(DisplayName = "Metal"),
	Resource_Ore UMETA(DisplayName = "Ore"),
	Resource_Gas UMETA(DisplayName = "Gas"),
	Resource_Liquid UMETA(DisplayName = "Liquid"),
	Resource_Data UMETA(DisplayName = "Data"),
	Resource_Crystal UMETA(DisplayName = "Crystal")
};

/**
 * Building Type enum
 */
UENUM(BlueprintType)
enum class EBuildingType : uint8
{
	Building_None UMETA(DisplayName = "None"),
	Building_Barracks UMETA(DisplayName = "Barracks"),
	Building_Factory UMETA(DisplayName = "Factory"),
	Building_Scientific UMETA(DisplayName = "Scientific"),
	Building_Power UMETA(DisplayName = "Power"),
	Building_Defense UMETA(DisplayName = "Defense"),
	Building_Command UMETA(DisplayName = "Command")
};

/**
 * Unit Type enum
 */
UENUM(BlueprintType)
enum class EUnitType : uint8
{
	Unit_None UMETA(DisplayName = "None"),
	Unit_Infantry UMETA(DisplayName = "Infantry"),
	Unit_Tank UMETA(DisplayName = "Tank"),
	Unit_Aircraft UMETA(DisplayName = "Aircraft"),
	Unit_Ship UMETA(DisplayName = "Ship"),
	Unit_Spider UMETA(DisplayName = "Spider"),
	Unit_Walker UMETA(DisplayName = "Walker")
};

/**
 * Tech Level enum
 */
UENUM(BlueprintType)
enum class ETechLevel : uint8
{
	TechLevel_1 UMETA(DisplayName = "Level 1"),
	TechLevel_2 UMETA(DisplayName = "Level 2"),
	TechLevel_3 UMETA(DisplayName = "Level 3"),
	TechLevel_4 UMETA(DisplayName = "Level 4"),
	TechLevel_5 UMETA(DisplayName = "Level 5")
};

/**
 * Difficulty Level enum
 */
UENUM(BlueprintType)
enum class EDifficultyLevel : uint8
{
	Difficulty_Easy UMETA(DisplayName = "Easy"),
	Difficulty_Normal UMETA(DisplayName = "Normal"),
	Difficulty_Hard UMETA(DisplayName = "Hard"),
	Difficulty_Impossible UMETA(DisplayName = "Impossible")
};