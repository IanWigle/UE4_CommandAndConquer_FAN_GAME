// Fill out your copyright notice in the Description page of Project Settings.


#include "TiberiumRefinery.h"
#include "Components/ArrowComponent.h"
#include "Units/Living/Harvester.h"
#include "PlayerCharacter.h"
#include "Engine/World.h"

ATiberiumRefinery::ATiberiumRefinery()
{
	m_BuildingID = BuildingID::VE_Refinery;
	m_Power = -40;
	m_Cost = 2000;
	m_Health = 450;

	m_TargetLocation = CreateDefaultSubobject<UArrowComponent>("Unit Spawn Location");
	m_TargetLocation->SetupAttachment(RootComponent);
}

void ATiberiumRefinery::BeginPlay()
{
	Super::BeginPlay();

	FTransform SpawnTransform = m_TargetLocation->GetComponentTransform();

	FActorSpawnParameters Spawnparams;
	Spawnparams.Owner = this;
	Spawnparams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	auto harvester = GetWorld()->SpawnActor<AHarvester>(*m_Harvester, SpawnTransform, Spawnparams);
	if (harvester)
	{
		Cast<APlayerCharacter>(GetOwner())->m_PlayerArmy.Add(harvester);
		harvester->m_OwningRefinery = this;
	}
		
}