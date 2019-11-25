// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/BoxComponent.h"
#include "GameFramework/SpringArmComponent.h"
//#include "MusicPlayer.h"
#include "Components/MusicPlayerComponent.h"
#include "CnCGameInstance.h"

#include "Engine/World.h"
#include "Engine/Public/TimerManager.h"
#include "Helpers/HelperFunctions.h"
#include "Components/SceneCaptureComponent2D.h"
#include "GameModes/CommandAndConquerGameMode.h"
#include "Components/AudioComponent.h"
#include "GameModes/MultiPlayerGameMode.h"
#include "UnrealNetwork.h"
#include "GameFramework/PlayerController.h"

#pragma region Unit Headers
#include "Units/Buildings/ProductionBuilding.h"
#include "Units/Buildings/Building.h"
#include "Units/Buildings/Global/ConstructionYard.h"
#include "Units/Living/NOD/Vehicles/NODBugee.h"
#include "Units/Living/NOD/Vehicles/NODReconBugee.h"
#include "Units/Living/Harvester.h"
#include "Units/Living/NOD/Apache.h"
#pragma endregion Unit Headers

// Sets default values
APlayerCharacter::APlayerCharacter()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	m_Box = CreateDefaultSubobject<UBoxComponent>("Box");
	RootComponent = m_Box;

	m_CameraArm = CreateDefaultSubobject<USpringArmComponent>("Camera Arm");
	m_CameraArm->SetupAttachment(RootComponent);
	m_CameraArm->bAbsoluteRotation = true;
	m_CameraArm->bDoCollisionTest = false;

	m_PlayerCamera = CreateDefaultSubobject<UCameraComponent>("Player Camera");
	m_PlayerCamera->SetupAttachment(m_CameraArm);
	m_PlayerCamera->bUsePawnControlRotation = false;

	m_MusicPlayer = CreateDefaultSubobject<UMusicPlayerComponent>("Music Player");
	m_MusicPlayer->SetRandom(false);
	m_MusicPlayer->SetOnLoop(false);

	m_RadarCameraArm = CreateDefaultSubobject<USpringArmComponent>("Radar Camera Arm");
	m_RadarCameraArm->SetupAttachment(RootComponent);
	m_RadarCameraArm->bAbsoluteRotation = true;
	m_RadarCameraArm->bDoCollisionTest = false;

	RadarCamera = CreateDefaultSubobject<USceneCaptureComponent2D>("Radar Camera");
	RadarCamera->ProjectionType = ECameraProjectionMode::Orthographic;
	RadarCamera->OrthoWidth = 1024.0f;
	RadarCamera->CaptureSource = ESceneCaptureSource::SCS_FinalColorLDR;
	RadarCamera->bCaptureEveryFrame = true;
	RadarCamera->bCaptureOnMovement = true;
	RadarCamera->SetupAttachment(m_RadarCameraArm);

	m_EVAVoiceComponent = CreateDefaultSubobject<UAudioComponent>("EVA VoiceComponent");
	m_EVAVoiceComponent->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	auto instance = Cast<UCnCGameInstance>(GetGameInstance());
	if (instance)
	{
		m_Credits = instance->m_StartingCredits;

		auto spawnPoint = instance->GetSpawnLocationFromLobby(Cast<APlayerController>(GetController())->NetPlayerIndex);
	}		
	else
		m_Credits = 5000;

	FTransform spawnTransform = GetActorTransform();
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	AConstructionYard* yard = GetWorld()->SpawnActor<AConstructionYard>(*m_BuildingArsenal.Find("ConstructionYard"), spawnTransform, SpawnParams);
	if (yard)
	{
		m_PlayerBuildings.Add(yard);
	}
}

void APlayerCharacter::BuildingProductionComplete()
{
	m_BuildingIsReadyToBePlaced = true;
	m_ProducingBuilding = false;
	m_BuildingCredits = 0;

	AConstructionYard* Yard = Cast<AConstructionYard>(UHelperFunctions::GetBuildingFromPlayerArsenal(BuildingID::VE_Yard, m_PlayerBuildings));
}

void APlayerCharacter::UnitProductionComplete()
{
	SpawnUnitFromID(m_UnitThatIsBeingMade);
	ResetUnitProduction();
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (m_ProducingBuilding == true && m_IsBuildingMakingPaused == false)
	{
		if (m_Credits > 0)
			m_Credits--;

		if (m_Credits <= 0.0f) m_Credits = 0.0f;
		else
		{
			m_ConsumedBuildingCredits++;

			if (m_ConsumedBuildingCredits == m_BuildingCredits) BuildingProductionComplete();
		}
	}

	if (m_ProducingUnit == true && m_IsUnitMakingPaused == false)
	{
		m_Credits--;
		if (m_Credits <= 0.0f) m_Credits = 0.0f;
		else
		{
			m_ConsumedUnitCredits++;
			if (m_ConsumedUnitCredits == m_UnitCredits) UnitProductionComplete();
		}
	}

	int tempMaxCredits = 0;
	for (int i = 0; i < m_PlayerBuildings.Num(); i++)
	{
		if (Cast<ABuilding>(m_PlayerBuildings[i])->GetBuildingID() == BuildingID::VE_Yard)
			tempMaxCredits += 1000;
		else if (Cast<ABuilding>(m_PlayerBuildings[i])->GetBuildingID() == BuildingID::VE_Refinery)
			tempMaxCredits += 1000;
		else if (Cast<ABuilding>(m_PlayerBuildings[i])->GetBuildingID() == BuildingID::VE_Silo)
			tempMaxCredits += 1500;
	}
	m_MaxCredits = tempMaxCredits;
}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void APlayerCharacter::BeginBuildingProduction(BuildingID ID, int TotalCost, float TimeToBuild)
{
	m_ProducingBuilding = true;

	BuildingProductionHandle;

	m_BuildingCredits = TotalCost;

	m_BuildingThatIsBeingMade = ID;
}

void APlayerCharacter::CancelBuildingProduction()
{
	m_ProducingBuilding = false;
	m_BuildingCredits = 0;
	m_BuildingThatIsBeingMade = BuildingID::VE_NA;
	m_Credits += m_ConsumedBuildingCredits;
	m_ConsumedBuildingCredits = 0;
	m_BuildingIsReadyToBePlaced = false;
	m_IsBuildingMakingPaused = false;
}

void APlayerCharacter::BeginUnitProduction(LivingUnitID ID, UnitType type, int TotalCost, float TimeToBuild)
{
	m_ProducingUnit = true;
	m_UnitCredits = TotalCost;
	m_UnitThatIsBeingMade = ID;
	m_UnitTypeThatIsBeingMade = type;
}

void APlayerCharacter::CancelUnitProduction()
{
	m_ProducingUnit = false;
	m_UnitCredits = 0;
	m_UnitThatIsBeingMade = LivingUnitID::VE_NA;
	m_UnitTypeThatIsBeingMade = UnitType::VE_NoType;
	m_Credits += m_ConsumedUnitCredits;
	m_ConsumedUnitCredits = 0;
	m_IsUnitMakingPaused = false;
}

void APlayerCharacter::ResetUnitProduction()
{
	m_ProducingUnit = false;
	m_UnitCredits = 0;
	m_UnitThatIsBeingMade = LivingUnitID::VE_NA;
	m_UnitTypeThatIsBeingMade = UnitType::VE_NoType;
	m_ConsumedUnitCredits = 0;
	m_IsUnitMakingPaused = false;
}

ALivingUnit* APlayerCharacter::SpawnUnitFromID(LivingUnitID ID)
{
	FActorSpawnParameters Spawnparams;
	Spawnparams.Owner = this;
	Spawnparams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	FTransform SpawnTransform;

	for (int i = 0; i < m_PlayerBuildings.Num(); i++)
	{
		if (m_UnitTypeThatIsBeingMade == UnitType::VE_Infantry)
		{
			if (Cast<ABuilding>(m_PlayerBuildings[i])->GetBuildingID() == BuildingID::VE_Barracks || Cast<ABuilding>(m_PlayerBuildings[i])->GetBuildingID() == BuildingID::VE_Hand)
			{
				auto prodbuilding = Cast<AProductionBuilding>(m_PlayerBuildings[i]);

				if (prodbuilding)
				{
					if (prodbuilding->IsPrimaryBuilding())
					{
						SpawnTransform.SetLocation(prodbuilding->GetSpawnLocation());

						ALivingUnit* livingunit = nullptr;
						{
							switch (ID)
							{
							case LivingUnitID::VE_NA:
								break;
							case LivingUnitID::VE_Minigun:
								break;
							case LivingUnitID::VE_Rocket:
								break;
							case LivingUnitID::VE_Engineer:
								break;
							case LivingUnitID::VE_Commando:
								break;
							case LivingUnitID::VE_Flamethrower:
								break;
							case LivingUnitID::VE_ChemWarrior:
								break;
							case LivingUnitID::VE_Grenade:
								break;
							};
						}
						if (livingunit)
						{
							m_PlayerArmy.Add(livingunit);
							m_EVAVoiceComponent->SetSound(*m_EVASoundsMap.Find("UnitReady"));
							m_EVAVoiceComponent->Play();
							livingunit->m_OwningCharacter = this;
						}

						return livingunit;
					}
				}
			}
		}
		else if (m_UnitTypeThatIsBeingMade == UnitType::VE_Tank)
		{
			if (Cast<ABuilding>(m_PlayerBuildings[i])->GetBuildingID() == BuildingID::VE_Airfield || Cast<ABuilding>(m_PlayerBuildings[i])->GetBuildingID() == BuildingID::VE_Weapon)
			{
				auto prodbuilding = Cast<AProductionBuilding>(m_PlayerBuildings[i]);

				if (prodbuilding)
				{
					if (prodbuilding->IsPrimaryBuilding())
					{
						SpawnTransform.SetLocation(prodbuilding->GetSpawnLocation());

						ALivingUnit* livingunit = nullptr;

						switch (ID)
						{
						case LivingUnitID::VE_MCV:
							break;
						case LivingUnitID::VE_Harvaster:
							livingunit = Cast<ALivingUnit>(GetWorld()->SpawnActor<AHarvester>(*m_UnitArsenal.Find("Harvester"), SpawnTransform, Spawnparams));
							Cast<AHarvester>(livingunit)->m_OwningRefinery = Cast<ATiberiumRefinery>(UHelperFunctions::GetClosestRefinery(livingunit, GetWorld()));
							break;
						case LivingUnitID::VE_Transport:
							break;
						case LivingUnitID::VE_MRLS:
							break;
						case LivingUnitID::VE_Recon:
							livingunit = Cast<ALivingUnit>(GetWorld()->SpawnActor<ANODBugee>(*m_UnitArsenal.Find("NODRecon"), SpawnTransform, Spawnparams));
							break;
						case LivingUnitID::VE_Buggy:
							livingunit = Cast<ALivingUnit>(GetWorld()->SpawnActor<ANODReconBugee>(*m_UnitArsenal.Find("NODBuggy"), SpawnTransform, Spawnparams));
							break;
						case LivingUnitID::VE_LightTank:
							break;
						case LivingUnitID::VE_Artillery:
							break;
						case LivingUnitID::VE_FlameTank:
							break;
						case LivingUnitID::VE_Stealth:
							break;
						case LivingUnitID::VE_SSM:
							break;
						case LivingUnitID::VE_Heli:
							break;
						case LivingUnitID::VE_HummVee:
							break;
						case LivingUnitID::VE_APC:
							break;
						case LivingUnitID::VE_MediumTank:
							break;
						case LivingUnitID::VE_MammothTank:
							break;
						}

						if (livingunit)
						{
							m_PlayerArmy.Add(livingunit);
							m_EVAVoiceComponent->SetSound(*m_EVASoundsMap.Find("UnitReady"));
							m_EVAVoiceComponent->Play();
						}
						return livingunit;
					}
				}
			}
		}
		else if (m_UnitTypeThatIsBeingMade == UnitType::VE_Aircraft)
		{
			if (Cast<ABuilding>(m_PlayerBuildings[i])->GetBuildingID() == BuildingID::VE_Helipad)
			{
				auto prodbuilding = Cast<AProductionBuilding>(m_PlayerBuildings[i]);

				if (prodbuilding)
				{
					if (prodbuilding->IsPrimaryBuilding())
					{
						SpawnTransform.SetLocation(prodbuilding->GetSpawnLocation());

						ALivingUnit* livingunit = nullptr;

						switch (ID)
						{
						case LivingUnitID::VE_Heli:
							livingunit = Cast<ALivingUnit>(GetWorld()->SpawnActor<AApache>(*m_UnitArsenal.Find("Apache"), SpawnTransform, Spawnparams));
							break;
						}
					}
				}
			}
		}
	}
	return nullptr;
}

void APlayerCharacter::ChooseBuildingLocation(FVector requestedPosition) {}

void APlayerCharacter::ResetBuildingProduction()
{
	m_ProducingBuilding = false;
	m_BuildingCredits = 0;
	m_ConsumedBuildingCredits = 0;
	m_BuildingThatIsBeingMade = BuildingID::VE_NA;
	m_BuildingIsReadyToBePlaced = false;
	m_IsBuildingMakingPaused = false;
	m_SelectingLocation = false;
}

void APlayerCharacter::AddToPlayPower(int power)
{
	if (power < 0)
		m_PowerConsumed += power;
	else if (power > 0)
		m_PlayerPowerGenerated += power;

	m_UsablePower = m_PlayerPowerGenerated + m_PowerConsumed;

	if (m_UsablePower <= 0)
	{
		m_EVAVoiceComponent->SetSound(*m_EVASoundsMap.Find("LowPower"));
		m_EVAVoiceComponent->Play();
	}
}

void APlayerCharacter::RemoveFromPlayerPower(int power)
{
	if (power < 0)
		m_PowerConsumed -= power;
	else if (power > 0)
		m_PlayerPowerGenerated -= power;

	m_UsablePower = m_PlayerPowerGenerated + m_PowerConsumed;

	if (m_UsablePower <= 0)
	{
		m_EVAVoiceComponent->SetSound(*m_EVASoundsMap.Find("LowPower"));
		m_EVAVoiceComponent->Play();
	}
}

void APlayerCharacter::RefreshPlayerPower()
{
	for (auto unit : m_PlayerBuildings)
	{
		ABuilding* building = Cast<ABuilding>(unit);
		if (building)
		{
			if (building->GetPowerValue() < 0 && building->m_HasPower == true)
				m_PowerConsumed -= building->GetPowerValue();
			else if (building->GetPowerValue() > 0 && building->m_HasPower == true)
				m_PlayerPowerGenerated -= building->GetPowerValue();
		}
	}

	m_UsablePower = m_PlayerPowerGenerated + m_PowerConsumed;
}

bool APlayerCharacter::DoWeUnlockNewTech(BuildingID ID)
{
	for (int i = 0; i < m_PlayerBuildings.Num(); i++)
	{
		if (Cast<ABuilding>(m_PlayerBuildings[i])->GetBuildingID() == ID)
		{
			return false;
		}
	}

	return true;
}

void APlayerCharacter::MoveRight(float value)
{
	FVector pos = GetActorLocation();
	pos.Y += value * m_CameraMovementSpeed;
	SetActorLocation(pos);
}

void APlayerCharacter::MoveUp(float value)
{
	FVector pos = GetActorLocation();
	pos.X += value * m_CameraMovementSpeed;
	SetActorLocation(pos);
}

void APlayerCharacter::ScrollIn(float value)
{
	if (m_CameraArm)
	{
		m_CameraArm->TargetArmLength += value * m_CameraZoomSpeed;
	}
}

void APlayerCharacter::MiniMapZoom(float value)
{
	//m_RadarCameraArm->TargetArmLength += value;
	FVector origin = RadarCamera->GetComponentLocation();
	origin.Z += value * m_RadarZoomSpeed;
	RadarCamera->SetWorldLocation(origin);
}

bool APlayerCharacter::AreThereAnyRadarPowered()
{
	for (auto unit : m_PlayerBuildings)
	{
		ABuilding* building = Cast<ABuilding>(unit);
		if (building)
		{
			if ((building->GetBuildingID() == BuildingID::VE_AdvComm || building->GetBuildingID() == BuildingID::VE_Comm) &&
				building->m_HasPower == true) return true;
		}
	}

	return false;
}

void APlayerCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(APlayerCharacter, m_BuildingThatIsBeingMade);
	DOREPLIFETIME(APlayerCharacter, m_UnitTypeThatIsBeingMade);
	DOREPLIFETIME(APlayerCharacter, m_UnitThatIsBeingMade);
}