// Fill out your copyright notice in the Description page of Project Settings.


#include "LivingUnit.h"
#include "Components/BoxComponent.h"

ALivingUnit::ALivingUnit() 
{
	m_LivingUnitCollider = CreateDefaultSubobject<UBoxComponent>("Living Unit Collider");
	m_LivingUnitCollider->SetCollisionObjectType(ECC_Visibility);
	m_LivingUnitCollider->SetCollisionProfileName("BlockAllDynamic");
	m_LivingUnitCollider->SetupAttachment(RootComponent);
	m_LivingUnitCollider->SetCanEverAffectNavigation(false);
}

void ALivingUnit::BeginPlay()
{
	Super::BeginPlay();
}