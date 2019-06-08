// Fill out your copyright notice in the Description page of Project Settings.


#include "InGameController.h"
#include "PlayerCharacter.h"
#include "HelperFunctions.h"
#include "SpawningHelpers.h"

#include "Engine/World.h"

#include "Components/AudioComponent.h"
#include "Engine/Classes/Kismet/GameplayStatics.h"

#include "AI/GeneralUnitAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/BoxComponent.h"

#pragma region Buildings
#include "Units/Building.h"
#include "Units/LivingUnit.h"
#include "Units/Unit.h"
#include "Units/Global/ConstructionYard.h"
#include "Units/Global/Powerplant.h"
#include "Units/Buildings/Global/TiberiumRefinery.h"
#include "Units/Buildings/Global/RepairFacility.h"
#include "Units/Buildings/Global/Helipad.h"
#include "Units/Buildings/Global/Comm.h"
#include "Units/Buildings/NOD/Airfield.h"
#include "Units/Buildings/NOD/HandOfNod.h"
#include "Units/Buildings/NOD/Turret.h"
#include "Units/Buildings/NOD/SAM.h"
#pragma endregion Buildings

AInGameController::AInGameController()
{
    m_AudioComponent = CreateDefaultSubobject<UAudioComponent>("Audio Component");
}

void AInGameController::PlayerTick(float DeltaTime)
{
    Super::PlayerTick(DeltaTime);
}

void AInGameController::SetupInputComponent()
{
    Super::SetupInputComponent();

    InputComponent->BindAxis("MoveForward", this, &AInGameController::MoveUp);
    InputComponent->BindAxis("MoveRight", this, &AInGameController::MoveRight);
    InputComponent->BindAxis("ScrollIn", this, &AInGameController::ScrollIn);

    InputComponent->BindAction("Select", IE_Pressed, this, &AInGameController::Select);
    InputComponent->BindAction("Deselect", IE_Released, this, &AInGameController::Deselect);
	InputComponent->BindAction("SelectMultiple", IE_Pressed, this, &AInGameController::SelectMultiple);
}

void AInGameController::MoveRight(float value)
{
    APlayerCharacter* const MyPawn = Cast<APlayerCharacter>(GetPawn());
    if (MyPawn && value != 0.0f) MyPawn->MoveRight(value);
}

void AInGameController::MoveUp(float value)
{
    APlayerCharacter* const MyPawn = Cast<APlayerCharacter>(GetPawn());
    if (MyPawn) MyPawn->MoveUp(value);
}

void AInGameController::ScrollIn(float value)
{
    APlayerCharacter* const MyPawn = Cast<APlayerCharacter>(GetPawn());
    if (MyPawn && value != 0.0f) MyPawn->ScrollIn(value);
}

void AInGameController::Select()
{
	FHitResult SelectingUnitHit;
	APlayerCharacter* player = Cast<APlayerCharacter>(GetPawn());

#pragma region Selecting and Moving Units  
	// IF the raycast to a unit was successful AND the player is NOT selecting a location for a building.
	if (GetHitResultUnderCursorByChannel(ETraceTypeQuery::TraceTypeQuery1, true, SelectingUnitHit) && !player->IsSelectingLocation())
	{
		// Get the actor selected from the HitResult, then cast it to a livingunit
		auto livingunit = Cast<ALivingUnit>(SelectingUnitHit.GetActor());

		// IF the cast was successful
		if (livingunit)
		{
			// If there are units already selected, deselect them all.
			if (m_SelectedUnits.Num() > 0)
			{
				for (ALivingUnit* obj : m_SelectedUnits)
				{
					obj->SetSelected(false);
				}
				m_SelectedUnits.RemoveAt(0, m_SelectedUnits.Num(), true);
			}

			// Add the unit to the player's selected units.
			m_SelectedUnits.Add(livingunit);
			// Set the unit to be selected.
			livingunit->SetSelected(true);
			// Have the unit say a greeting.
			livingunit->SayGreeting();
			// Make the livingunit's collider visiable.
			livingunit->m_LivingUnitCollider->bHiddenInGame = false;
			// Set the bool that units are selected to true.
			player->SetUnitsSelected(true);
			return;
		}
		// IF there are units selected.
		else if (player->AreUnitsSelected())
		{
			// FOR EACH selected unit
			for (int i = 0; i < m_SelectedUnits.Num(); i++)
			{
				// Get the controller of the selected unit, then cast it to the basic aiunitcontroller
				auto livingunitcontroller = Cast<AGeneralUnitAIController>(m_SelectedUnits[i]->GetController());

				// IF the cast was successful.
				if (livingunitcontroller)
				{
					// Access the backboard of the controller for the behavior tree. Then set the IsMoving bool to TRUE
					// and the TargetEnemyVector to the HitResult impactpoint.
					livingunitcontroller->GetBlackboardComponent()->SetValueAsBool("IsMoving", true);
					livingunitcontroller->GetBlackboardComponent()->SetValueAsVector("TargetEnemyVector", FVector(SelectingUnitHit.ImpactPoint));
				}
			}
			// We don't want every unit saying an achnolegement (that gets loud), only have the first unit say it.
			m_SelectedUnits[0]->SayAcknowledgments();
			return;
		}
		return;
	}
#pragma endregion Selecting and Moving Units

#pragma region Placing Buidlings
    if (player)
    {
        // If Player is selecting place for building
        if (player->IsSelectingLocation())
        {
			// Get the ID of the building being made
            BuildingID ID = player->GetBuildingBeingMadeByID();

			// Reset construction data
            player->ResetBuildingProduction();

			// Is this the only building of this type?
            if (player->DoWeUnlockNewTech(ID))
            {
				// Play "New construction options"
                m_AudioComponent->SetSound(m_NewConstructionOptions);
                m_AudioComponent->Play();
            }

            FHitResult PlaceBuildingHit;

			// Send a raycast from the screen to the ground. If the raycast was successful
            if (GetHitResultUnderCursorByChannel(ETraceTypeQuery::TraceTypeQuery1, true, PlaceBuildingHit))
            {
				// Setup spawn transform and spawn parameters
                FTransform SpawnTransform;
                SpawnTransform.SetLocation(PlaceBuildingHit.ImpactPoint);

                FActorSpawnParameters SpawnParams;
                SpawnParams.Owner = player;
                SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

				// Create the building based on the ID, spawnTransform, and SpawnParams
                auto building = SpawnBuildingFromID(ID, SpawnTransform, SpawnParams);

				// If the spawn was successful, add it to the players building array.
				// Also change the players power based on the made building.
				if (building)
				{
					auto prodbuilding = Cast<AProductionBuilding>(building);
					if (prodbuilding)
					{
						if (player->DoWeUnlockNewTech(ID))
						{
							prodbuilding->SetPrimaryBuilding(true);
						}
					}

					player->m_PlayerBuildings.Add(building);
					player->AddToPlayPower(building->GetPowerValue());					
				}
                
				// Search through the players building array for yards to play 
				// their construction animation.
				for (int i = 0; i < player->m_PlayerBuildings.Num() - 1; i++)
				{
					if (player->m_PlayerBuildings[i]->GetBuildingID() == BuildingID::VE_Yard)
					{
						Cast<AConstructionYard>(player->m_PlayerBuildings[i])->m_MakeBuilding = true;
					}
				}
            }
        }
		return;
    }
#pragma endregion Placing Buildings
}

void AInGameController::SelectMultiple()
{
	FHitResult SelectingUnitHit;
	APlayerCharacter* player = Cast<APlayerCharacter>(GetPawn());

	if (GetHitResultUnderCursorByChannel(ETraceTypeQuery::TraceTypeQuery1, true, SelectingUnitHit) && !player->IsSelectingLocation())
	{
		auto livingunit = Cast<ALivingUnit>(SelectingUnitHit.GetActor());

		if (livingunit)
		{
			m_SelectedUnits.Add(livingunit);
			livingunit->SetSelected(true);
			livingunit->SayGreeting();
			livingunit->m_LivingUnitCollider->bHiddenInGame = false;
			player->SetUnitsSelected(true);
		}
		return;
	}
	return;
}

void AInGameController::Deselect()
{
    for (ALivingUnit* obj : m_SelectedUnits)
    {
        obj->SetSelected(false);
		obj->m_LivingUnitCollider->bHiddenInGame = true;
    }

    m_SelectedUnits.RemoveAt(0, m_SelectedUnits.Num(), true);
	APlayerCharacter* player = Cast<APlayerCharacter>(GetPawn());
	if (player)
		player->SetUnitsSelected(false);
}

ABuilding* AInGameController::SpawnBuildingFromID(BuildingID ID, FTransform spawnTransform, FActorSpawnParameters SpawnParams)
{
    APlayerCharacter* player = Cast<APlayerCharacter>(GetPawn());

    if (player)
    {
        switch (ID)
        {
        case BuildingID::VE_NA:
            break;
        case BuildingID::VE_Yard:
            return Cast<ABuilding>(GetWorld()->SpawnActor<AConstructionYard>(*player->m_BuildingArsenal.Find("ConstructionYard"),spawnTransform,SpawnParams));
        case BuildingID::VE_Concrete:
            break;
        case BuildingID::VE_Chain:
            break;
        case BuildingID::VE_Sand:
            break;
        case BuildingID::VE_Powerplant:
            return Cast<ABuilding>(GetWorld()->SpawnActor<APowerplant>(*player->m_BuildingArsenal.Find("Powerplant"), spawnTransform, SpawnParams));
        case BuildingID::VE_AdvPower:
            break;
        case BuildingID::VE_Repair:
			return Cast<ABuilding>(GetWorld()->SpawnActor<ARepairFacility>(*player->m_BuildingArsenal.Find("RepairFacility"), spawnTransform, SpawnParams));
        case BuildingID::VE_Refinery:
			return Cast<ABuilding>(GetWorld()->SpawnActor<ATiberiumRefinery>(*player->m_BuildingArsenal.Find("TiberiumRefinery"), spawnTransform, SpawnParams));
        case BuildingID::VE_Comm:
			return Cast<ABuilding>(GetWorld()->SpawnActor<AComm>(*player->m_BuildingArsenal.Find("Comm"), spawnTransform, SpawnParams));
        case BuildingID::VE_Silo:
            break;
        case BuildingID::VE_Helipad:
			return Cast<ABuilding>(GetWorld()->SpawnActor<AHelipad>(*player->m_BuildingArsenal.Find("Helipad"), spawnTransform, SpawnParams));
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
			return Cast<ABuilding>(GetWorld()->SpawnActor<AHandOfNod>(*player->m_BuildingArsenal.Find("HandOfNod"), spawnTransform, SpawnParams));
        case BuildingID::VE_SAM:
			return Cast<ABuilding>(GetWorld()->SpawnActor<ASAM>(*player->m_BuildingArsenal.Find("SAM"), spawnTransform, SpawnParams));
        case BuildingID::VE_Turret:
			return Cast<ABuilding>(GetWorld()->SpawnActor<ATurret>(*player->m_BuildingArsenal.Find("Turret"), spawnTransform, SpawnParams));
        case BuildingID::VE_Airfield:
			return Cast<ABuilding>(GetWorld()->SpawnActor<AAirfield>(*player->m_BuildingArsenal.Find("Airfield"), spawnTransform, SpawnParams));
        case BuildingID::VE_Obelisk:
            break;
        case BuildingID::VE_Temple:
            break;
        default:
            break;
        }
    }
    return nullptr;

}