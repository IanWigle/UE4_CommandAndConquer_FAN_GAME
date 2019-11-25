// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawningHelpers.h"
#include "Units/Buildings/Building.h"
#include "PlayerCharacter.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"

#include "Units/Buildings/Global/ConstructionYard.h"
#include "Units/Buildings/Global/Powerplant.h"

TSubclassOf<class ABuilding> USpawningHelpers::DetermineWhichBuildingToMake(BuildingID ID, APlayerController* playerController)
{
    if (playerController)
    {
        APlayerCharacter* player = Cast<APlayerCharacter>(playerController->GetPawn());

        if (player)
        {
            switch (ID)
            {
            case BuildingID::VE_NA:
                return nullptr;
                break;
            case BuildingID::VE_Yard:
                return *player->m_BuildingArsenal.Find("ConstructionYard");
                break;
            case BuildingID::VE_Concrete:
                break;
            case BuildingID::VE_Chain:
                break;
            case BuildingID::VE_Sand:
                break;
            case BuildingID::VE_Powerplant:
                return *player->m_BuildingArsenal.Find("Powerplant");
                break;
            case BuildingID::VE_AdvPower:
                break;
            case BuildingID::VE_Repair:
                break;
            case BuildingID::VE_Refinery:
                break;
            case BuildingID::VE_Comm:
                break;
            case BuildingID::VE_Silo:
                break;
            case BuildingID::VE_Helipad:
                break;
            case BuildingID::VE_AdvComm:
                break;
            case BuildingID::VE_AdvGuard:
                break;
            case BuildingID::VE_Weapon:
                break;
            case BuildingID::VE_Barracks:
                break;
            case BuildingID::VE_Guard:
                break;
            case BuildingID::VE_Hand:
                break;
            case BuildingID::VE_SAM:
                break;
            case BuildingID::VE_Turret:
                break;
            case BuildingID::VE_Airfield:
                break;
            case BuildingID::VE_Obelisk:
                break;
            case BuildingID::VE_Temple:
                break;
            default:
                return nullptr;
                break;
            }            
        }
        return nullptr;
    }
    return nullptr;
}


