// Fill out your copyright notice in the Description page of Project Settings.


#include "NODBugee.h"

ANODBugee::ANODBugee()
{
	m_LivingUnitID = LivingUnitID::VE_Recon;
	m_UnitArmor = UnitArmor::VE_Light;
	m_UnitRange = UnitRange::VE_Medium;
}

void ANODBugee::BeginPlay()
{
	Super::BeginPlay();


}