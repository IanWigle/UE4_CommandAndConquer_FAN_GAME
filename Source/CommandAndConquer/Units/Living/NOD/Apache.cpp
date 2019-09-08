// Fill out your copyright notice in the Description page of Project Settings.


#include "Apache.h"

AApache::AApache()
{
	m_LivingUnitID = LivingUnitID::VE_Heli;
	m_UnitArmor = UnitArmor::VE_Heavy;
	m_UnitRange = UnitRange::VE_Medium;

	m_TypesPossibleToAttack.Add(UnitType::VE_Building);
	m_TypesPossibleToAttack.Add(UnitType::VE_Defense);
	m_TypesPossibleToAttack.Add(UnitType::VE_Infantry);
	m_TypesPossibleToAttack.Add(UnitType::VE_NavyUnit);
	m_TypesPossibleToAttack.Add(UnitType::VE_Superweapon);
	m_TypesPossibleToAttack.Add(UnitType::VE_Tank);
}