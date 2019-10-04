// Fill out your copyright notice in the Description page of Project Settings.


#include "ConstructionYard.h"
#include "Animation/AnimMontage.h"
#include "HelperFunctions.h"

AConstructionYard::AConstructionYard()
{
	m_UnitArmor = UnitArmor::VE_Light;
	m_BuildingID = BuildingID::VE_Yard;
}

void AConstructionYard::BeginPlay()
{
    Super::BeginPlay();


}

void AConstructionYard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	float animTimeRemaining = UHelperFunctions::TimeRemainingInAnimationFromStateMachine(this, "YardStateMachine", "State");

	if (animTimeRemaining != -1 && animTimeRemaining <= 0.5f && m_MakeBuilding == true)
	{
		m_MakeBuilding = false;
	}
}