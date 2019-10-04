// Fill out your copyright notice in the Description page of Project Settings.


#include "Powerplant.h"
#include "PlayerCharacter.h"

APowerplant::APowerplant()
{
	m_Cost = 300;
	m_Power = 100;
	m_UnitArmor = UnitArmor::VE_Light;
	m_UnitName = "Powerplant";
	m_BuildingID = BuildingID::VE_Powerplant;
}

void APowerplant::BeginPlay()
{
    Super::BeginPlay();


}

void APowerplant::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void APowerplant::Die()
{
	Cast<APlayerCharacter>(GetOwner())->RemoveFromPlayerPower(m_Power);

	Super::Die();
}
