// Fill out your copyright notice in the Description page of Project Settings.


#include "ProductionBuilding.h"
#include "UnrealNetwork.h"
#include "Components/AudioComponent.h"


AProductionBuilding::AProductionBuilding()
{
	m_SpawnLocation = CreateDefaultSubobject<UArrowComponent>("Unit Spawn Location");
	m_SpawnLocation->SetupAttachment(RootComponent);
}

void AProductionBuilding::SetPrimaryBuilding(bool state)
{
	m_IsPrimaryBuilding = state;

	if (m_IsPrimaryBuilding)
	{
		m_AudioComponent->SetSound(m_PrimaryBuildingVoice);
		m_AudioComponent->Play();
	}
}

void AProductionBuilding::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AProductionBuilding, m_SpawnLocation);
}