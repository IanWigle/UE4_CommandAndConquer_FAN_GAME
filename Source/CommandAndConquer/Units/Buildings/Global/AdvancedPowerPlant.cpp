// Fill out your copyright notice in the Description page of Project Settings.


#include "AdvancedPowerPlant.h"

AAdvancedPowerPlant::AAdvancedPowerPlant()
{
	m_Cost = 700;
	m_Power = 200;
	m_UnitArmor = UnitArmor::VE_Light;
	m_UnitName = "Advanced Powerplant";
	m_BuildingID = BuildingID::VE_AdvPower;
}