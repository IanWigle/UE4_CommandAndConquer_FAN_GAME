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
#include "Units/Buildings/Global/AdvancedPowerPlant.h"
#include "Units/Buildings/Global/Silo.h"
#include "Units/Buildings/NOD/Airfield.h"
#include "Units/Buildings/NOD/HandOfNod.h"
#include "Units/Buildings/NOD/Turret.h"
#include "Units/Buildings/NOD/SAM.h"
#include "Units/Buildings/NOD/Obelisk.h"
#include "Units/Buildings/NOD/TempleOfNod.h"
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
	InputComponent->BindAxis("MiniMapZoom", this, &AInGameController::MiniMapZoom);
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

void AInGameController::MiniMapZoom(float value)
{
	APlayerCharacter* const MyPawn = Cast<APlayerCharacter>(GetPawn());
	if (MyPawn && value != 0.0f) MyPawn->MiniMapZoom(value);
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
					SpawnBuildingFromID(PlaceBuildingHit.ImpactPoint);

					// Reset construction data
					player->ResetBuildingProduction();
					
				}

				// Search through the players building array for yards to play 
				// their construction animation.
				for (int i = 0; i < player->m_PlayerBuildings.Num() - 1; i++)
				{
					if (Cast<ABuilding>(player->m_PlayerBuildings[i])->GetBuildingID() == BuildingID::VE_Yard)
					{
						Cast<AConstructionYard>(player->m_PlayerBuildings[i])->m_MakeBuilding = true;
					}
				}
			}
		}
	
#pragma endregion Placing Buildings

#pragma region Selecting superweapon target
	if (player->IsSelectingLocationForNuke())
	{
		if (GetHitResultUnderCursorByChannel(ETraceTypeQuery::TraceTypeQuery1, true, SelectingUnitHit) && !player->IsSelectingLocation())
		{
			auto temple = Cast<ASuperweapon>(UHelperFunctions::GetBuildingFromPlayerArsenal(BuildingID::VE_Temple, player->m_PlayerBuildings));
			player->m_TargetLocationForSuperweapon = SelectingUnitHit.ImpactPoint;
			if (temple)
			{
				temple->LaunchWeapon();
				player->SetIsSelectingLocationForNuke(false);
				return;
			}
		}
	}
#pragma endregion
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

void AInGameController::SpawnBuildingFromID(FVector TargetLocation)
{
	

	//*
	APlayerCharacter* player = Cast<APlayerCharacter>(GetPawn());
	BuildingID ID = player->GetBuildingBeingMadeByID();
	FTransform SpawnTransform;
	SpawnTransform.SetLocation(TargetLocation);

	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = player;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	if (player)
	{
		ABuilding* building = nullptr;
		switch (ID)
		{
		case BuildingID::VE_NA:
			break;
		case BuildingID::VE_Yard:
			building = Cast<ABuilding>(GetWorld()->SpawnActor<AConstructionYard>(*player->m_BuildingArsenal.Find("ConstructionYard"), SpawnTransform, SpawnParams));
		case BuildingID::VE_Concrete:
			break;
		case BuildingID::VE_Chain:
			break;
		case BuildingID::VE_Sand:
			break;
		case BuildingID::VE_Powerplant:
			building = Cast<ABuilding>(GetWorld()->SpawnActor<APowerplant>(*player->m_BuildingArsenal.Find("Powerplant"), SpawnTransform, SpawnParams));
			break;
		case BuildingID::VE_AdvPower:
			building = Cast<ABuilding>(GetWorld()->SpawnActor<AAdvancedPowerPlant>(*player->m_BuildingArsenal.Find("AdvancedPowerplant"), SpawnTransform, SpawnParams));
			break;
		case BuildingID::VE_Repair:
			building = Cast<ABuilding>(GetWorld()->SpawnActor<ARepairFacility>(*player->m_BuildingArsenal.Find("RepairFacility"), SpawnTransform, SpawnParams));
			break;
		case BuildingID::VE_Refinery:
			building = Cast<ABuilding>(GetWorld()->SpawnActor<ATiberiumRefinery>(*player->m_BuildingArsenal.Find("TiberiumRefinery"), SpawnTransform, SpawnParams));
			break;
		case BuildingID::VE_Comm:
			building = Cast<ABuilding>(GetWorld()->SpawnActor<AComm>(*player->m_BuildingArsenal.Find("Comm"), SpawnTransform, SpawnParams));
			break;
		case BuildingID::VE_Silo:
			building = Cast<ABuilding>(GetWorld()->SpawnActor<ASilo>(*player->m_BuildingArsenal.Find("Silo"), SpawnTransform, SpawnParams));
			break;
		case BuildingID::VE_Helipad:
			building = Cast<ABuilding>(GetWorld()->SpawnActor<AHelipad>(*player->m_BuildingArsenal.Find("Helipad"), SpawnTransform, SpawnParams));
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
			building = Cast<ABuilding>(GetWorld()->SpawnActor<AHandOfNod>(*player->m_BuildingArsenal.Find("HandOfNod"), SpawnTransform, SpawnParams));
			break;
		case BuildingID::VE_SAM:
			building = Cast<ABuilding>(GetWorld()->SpawnActor<ASAM>(*player->m_BuildingArsenal.Find("SAM"), SpawnTransform, SpawnParams));
			break;
		case BuildingID::VE_Turret:
			building = Cast<ABuilding>(GetWorld()->SpawnActor<ATurret>(*player->m_BuildingArsenal.Find("Turret"), SpawnTransform, SpawnParams));
			break;
		case BuildingID::VE_Airfield:
			building = Cast<ABuilding>(GetWorld()->SpawnActor<AAirfield>(*player->m_BuildingArsenal.Find("Airfield"), SpawnTransform, SpawnParams));
			break;
		case BuildingID::VE_Obelisk:
			building = Cast<ABuilding>(GetWorld()->SpawnActor<AObelisk>(*player->m_BuildingArsenal.Find("Obelisk"), SpawnTransform, SpawnParams));
			break;
		case BuildingID::VE_Temple:
			building = Cast<ABuilding>(GetWorld()->SpawnActor<ATempleOfNod>(*player->m_BuildingArsenal.Find("Temple"), SpawnTransform, SpawnParams));
			break;
		default:
			break;
		}

		player->AddToPlayPower(building->GetPowerValue());


		auto prodbuilding = Cast<AProductionBuilding>(building);
		if (prodbuilding)
		{
			if (player->DoWeUnlockNewTech(ID))
			{
				prodbuilding->SetPrimaryBuilding(true);
			}
		}

		building->m_OwningCharacter = player;
		player->m_PlayerBuildings.Add(building);
	}
	/**/
	//Server_SpawnBuildingFromID(TargetLocation);
}

void AInGameController::Server_SpawnBuildingFromID_Implementation(FVector TargetLocation)
{
	APlayerCharacter* player = Cast<APlayerCharacter>(GetPawn());
	BuildingID ID = player->GetBuildingBeingMadeByID();
	FTransform SpawnTransform;
	SpawnTransform.SetLocation(TargetLocation);

	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = player;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	if (player)
	{
		ABuilding* building = nullptr;
		switch (ID)
		{
		case BuildingID::VE_NA:
			break;
		case BuildingID::VE_Yard:
			player->m_PlayerBuildings.Add(Cast<ABuilding>(GetWorld()->SpawnActor<AConstructionYard>(*player->m_BuildingArsenal.Find("ConstructionYard"), SpawnTransform, SpawnParams)));
		case BuildingID::VE_Concrete:
			break;
		case BuildingID::VE_Chain:
			break;
		case BuildingID::VE_Sand:
			break;
		case BuildingID::VE_Powerplant:
			building = Cast<ABuilding>(GetWorld()->SpawnActor<APowerplant>(*player->m_BuildingArsenal.Find("Powerplant"), SpawnTransform, SpawnParams));
			break;
		case BuildingID::VE_AdvPower:
			break;
		case BuildingID::VE_Repair:
			player->m_PlayerBuildings.Add(Cast<ABuilding>(GetWorld()->SpawnActor<ARepairFacility>(*player->m_BuildingArsenal.Find("RepairFacility"), SpawnTransform, SpawnParams)));
			break;
		case BuildingID::VE_Refinery:
			player->m_PlayerBuildings.Add(Cast<ABuilding>(GetWorld()->SpawnActor<ATiberiumRefinery>(*player->m_BuildingArsenal.Find("TiberiumRefinery"), SpawnTransform, SpawnParams)));
			break;
		case BuildingID::VE_Comm:
			player->m_PlayerBuildings.Add(Cast<ABuilding>(GetWorld()->SpawnActor<AComm>(*player->m_BuildingArsenal.Find("Comm"), SpawnTransform, SpawnParams)));
			break;
		case BuildingID::VE_Silo:
			break;
		case BuildingID::VE_Helipad:
			player->m_PlayerBuildings.Add(Cast<ABuilding>(GetWorld()->SpawnActor<AHelipad>(*player->m_BuildingArsenal.Find("Helipad"), SpawnTransform, SpawnParams)));
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
			player->m_PlayerBuildings.Add(Cast<ABuilding>(GetWorld()->SpawnActor<AHandOfNod>(*player->m_BuildingArsenal.Find("HandOfNod"), SpawnTransform, SpawnParams)));
			break;
		case BuildingID::VE_SAM:
			player->m_PlayerBuildings.Add(Cast<ABuilding>(GetWorld()->SpawnActor<ASAM>(*player->m_BuildingArsenal.Find("SAM"), SpawnTransform, SpawnParams)));
			break;
		case BuildingID::VE_Turret:
			player->m_PlayerBuildings.Add(Cast<ABuilding>(GetWorld()->SpawnActor<ATurret>(*player->m_BuildingArsenal.Find("Turret"), SpawnTransform, SpawnParams)));
			break;
		case BuildingID::VE_Airfield:
			player->m_PlayerBuildings.Add(Cast<ABuilding>(GetWorld()->SpawnActor<AAirfield>(*player->m_BuildingArsenal.Find("Airfield"), SpawnTransform, SpawnParams)));
			break;
		case BuildingID::VE_Obelisk:
			player->m_PlayerBuildings.Add(Cast<ABuilding>(GetWorld()->SpawnActor<AObelisk>(*player->m_BuildingArsenal.Find("Obelisk"), SpawnTransform, SpawnParams)));
			break;
		case BuildingID::VE_Temple:
			player->m_PlayerBuildings.Add(Cast<ABuilding>(GetWorld()->SpawnActor<ATempleOfNod>(*player->m_BuildingArsenal.Find("Temple"), SpawnTransform, SpawnParams)));
			break;
		default:
			break;
		}

		player->AddToPlayPower(building->GetPowerValue());


		auto prodbuilding = Cast<AProductionBuilding>(building);
		if (prodbuilding)
		{
			if (player->DoWeUnlockNewTech(ID))
			{
				prodbuilding->SetPrimaryBuilding(true);
			}
		}

		building->m_OwningCharacter = player;
		player->m_PlayerBuildings.Add(building);
	}
}
