// Fill out your copyright notice in the Description page of Project Settings.


#include "RepairFacility.h"
#include "Components/ArrowComponent.h"

ARepairFacility::ARepairFacility()
{
	m_UnitArmor = UnitArmor::VE_Light;
	m_BuildingID = BuildingID::VE_Repair;
	m_Health = 400;
	m_Cost = 1200;
	m_Power = -30;

	m_TargetLocation = CreateDefaultSubobject<UArrowComponent>("Unit Spawn Location");
	m_TargetLocation->SetupAttachment(RootComponent);
}

void ARepairFacility::BeginPlay()
{
	Super::BeginPlay();
}