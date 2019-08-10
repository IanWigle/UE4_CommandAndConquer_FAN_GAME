// Fill out your copyright notice in the Description page of Project Settings.


#include "LivingUnit.h"
#include "UnrealNetwork.h"
#include "Components/BoxComponent.h"

ALivingUnit::ALivingUnit() 
{
	m_LivingUnitCollider = CreateDefaultSubobject<UBoxComponent>("Living Unit Collider");
	m_LivingUnitCollider->SetCollisionObjectType(ECC_Visibility);
	m_LivingUnitCollider->SetCollisionProfileName("BlockAllDynamic");
	m_LivingUnitCollider->SetupAttachment(RootComponent);
	m_LivingUnitCollider->SetCanEverAffectNavigation(true);
}

void ALivingUnit::BeginPlay()
{
	Super::BeginPlay();
}

void ALivingUnit::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ALivingUnit, m_LivingUnitCollider);
}