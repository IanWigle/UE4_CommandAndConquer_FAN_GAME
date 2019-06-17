#pragma once
#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class UnitType : uint8
{
    VE_NoType       UMETA(DisplayName = "NoType"),
    VE_Infantry     UMETA(DisplayName = "Infantry"),
    VE_Tank         UMETA(DisplayName = "Tank"),
    VE_Aircraft     UMETA(DisplayName = "Aircraft"),
    VE_NavyUnit     UMETA(DisplayName = "NavyUnit"),
    VE_Building     UMETA(DisplayName = "Building"),
    VE_Defense      UMETA(DisplayName = "Defense"),
    VE_Superweapon  UMETA(DisplayName = "Superweapon")
};

UENUM(BlueprintType)
enum class UnitRange : uint8
{
    VE_NA           UMETA(DisplayName = "Not Applicable"),
    VE_Short        UMETA(DisplayName = "Short"),
    VE_Medium       UMETA(DisplayName = "Medium"),
    VE_Long         UMETA(DisplayName = "Long"),
    VE_Extreme      UMETA(DisplayName = "Extreme"),
    VE_Global       UMETA(DisplayName = "Global")
};

UENUM(BlueprintType)
enum class UnitArmor : uint8 
{
    VE_None         UMETA(DisplayName = "None"),
    VE_Light        UMETA(DisplayName = "Light"),
    VE_Medium       UMETA(DisplayName = "Medium"),
    VE_Heavy        UMETA(DisplayName = "Heavy")
};

UENUM(BlueprintType)
enum class BuildingID : uint8
{
    // Global
    VE_NA           UMETA(DisplayName = "Not Applicable"),
    VE_Yard         UMETA(DisplayName = "Construction Yard"),
    VE_Concrete     UMETA(DisplayName = "Concrete Wall"),
    VE_Chain        UMETA(DisplayName = "Chainlink Wall"),
    VE_Sand         UMETA(DisplayName = "Sandbag Wall"),
    VE_Powerplant   UMETA(DisplayName = "Powerplant"),
    VE_AdvPower     UMETA(DisplayName = "Advanced Power"),
    VE_Repair       UMETA(DisplayName = "Repair Facility"),
    VE_Refinery     UMETA(DisplayName = "Tiberium Refinery"),
    VE_Comm         UMETA(DisplayName = "Comm Center"),
    VE_Silo         UMETA(DisplayName = "Silo"),
    VE_Helipad      UMETA(DisplayName = "Helipad"),

    // GDI
    VE_AdvComm      UMETA(DisplayName = "Advanced Comm"),
    VE_AdvGuard     UMETA(DisplayName = "Advanced Guard Tower"),
    VE_Weapon       UMETA(DisplayName = "Weapons Factory"),
    VE_Barracks     UMETA(DisplayName = "Barracks"),
    VE_Guard        UMETA(DisplayName = "Guard Tower"),

    // NOD
    VE_Hand         UMETA(DisplayName = "Hand Of NOD"),
    VE_SAM          UMETA(DisplayName = "SAM"),
    VE_Turret       UMETA(DisplayName = "Turret"),
    VE_Airfield     UMETA(DisplayName = "Airfield"),
    VE_Obelisk      UMETA(DisplayName = "Obelisk"),
    VE_Temple       UMETA(DisplayName = "Temple Of NOD")
};

UENUM(BlueprintType)
enum class LivingUnitID : uint8 
{
	VE_NA			UMETA(DisplayName = "Not Applicable"),

	// Global
	VE_Minigun		UMETA(DisplayName = "Minigun Infantry"),
	VE_Rocket		UMETA(DisplayName = "Rocket Soldier"),
	VE_Engineer		UMETA(DisplayName = "Engineer"),
	VE_Commando		UMETA(DisplayName = "Commando"),
	VE_MCV			UMETA(DisplayName = "MCV"),
	VE_Harvaster	UMETA(DisplayName = "Harvester"),
	VE_Transport	UMETA(DisplayName = "Chinook"),
	VE_MRLS			UMETA(DisplayName = "MRLS"),

	// NOD
	VE_Flamethrower	UMETA(DisplayName = "Flamethrower"),
	VE_ChemWarrior	UMETA(DisplayName = "Chem Warrior"),
	VE_Recon		UMETA(DisplayName = "Recon Bike"),
	VE_Buggy		UMETA(DisplayName = "Buggy"),
	VE_LightTank	UMETA(DisplayName = "Light Tank"),
	VE_Artillery	UMETA(DisplayName = "Mobile Artillery"),
	VE_FlameTank	UMETA(DisplayName = "Flame Tank"),
	VE_Stealth		UMETA(DisplayName = "Stealth Tank"),
	VE_SSM			UMETA(DisplayName = "SSM Missile Launcher"),
	VE_Heli			UMETA(DisplayName = "Apache"),	

	// GDI
	VE_Grenade		UMETA(DisplayName = "Grenaider"),
	VE_HummVee		UMETA(DisplayName = "Humm-Vee"),
	VE_APC			UMETA(DisplayName = "APC"),
	VE_MediumTank	UMETA(DisplayName = "Medium Tank"),
	VE_MammothTank  UMETA(DisplayName = "Mammoth Tank"),
	VE_Orca			UMETA(DisplayName = "Orca")
};

UENUM(BlueprintType)
enum class UnitBehaviors : uint8
{
    VE_Idle                 UMETA(DisplayName = "Idle"),
    VE_Moving               UMETA(DisplayName = "Moving"),
    VE_Attacking            UMETA(DisplayName = "Attacking"),
    VE_MovingAndAttacking   UMETA(DisplayName = "MovingAndAttacking")
};

UENUM(BlueprintType)
enum class TiberiumLevels : uint8
{
	VE_LVL0		UMETA(DisplayName = "Level 0"),
	VE_LVL1		UMETA(DisplayName = "Level 1"),
	VE_LVL2		UMETA(DisplayName = "Level 2"),
	VE_LVL3		UMETA(DisplayName = "Level 3"),
};

enum TiberiumWorth
{
	WORTHLVL0 = 0,
	WORTHLVL1 = 80,
	WORTHLVL2 = 160,
	WORTHLVL3 = 250,
};

UENUM(BlueprintType)
enum class PlayerTeams : uint8 
{
	VE_Team1	UMETA(DisplayName = "Team 1"),
	VE_Team2	UMETA(DisplayName = "Team 2"),
	VE_Team3	UMETA(DisplayName = "Team 3"),
	VE_Team4	UMETA(DisplayName = "Team 4"),
	VE_Team5	UMETA(DisplayName = "Team 5"),
	VE_Team6	UMETA(DisplayName = "Team 6"),
	VE_Team7	UMETA(DisplayName = "Team 7"),
	VE_Team8	UMETA(DisplayName = "Team 8"),
};
