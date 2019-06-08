// Fill out your copyright notice in the Description page of Project Settings.


#include "Helipad.h"

AHelipad::AHelipad()
{
	m_Cost = 1500;
	m_Power = -10;
	m_BuildingID = BuildingID::VE_Helipad;

	m_UnitArmor = UnitArmor::VE_Light;
	m_UnitType = UnitType::VE_Building;
	m_UnitName = "Helipad";
	m_MaxHealth = 400;
	m_Health = m_MaxHealth;
}