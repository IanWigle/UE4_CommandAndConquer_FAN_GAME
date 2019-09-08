// Fill out your copyright notice in the Description page of Project Settings.


#include "NODReconBugee.h"

ANODReconBugee::ANODReconBugee()
{
	m_LivingUnitID = LivingUnitID::VE_Buggy;
	m_UnitArmor = UnitArmor::VE_Light;
	m_UnitRange = UnitRange::VE_Short;
	m_PrimaryDamage = 15.0f;
	m_Health = 140;
	m_UnitName = "NODBuggy";
	m_MaxHealth = m_Health;

	m_TypesPossibleToAttack.Add(UnitType::VE_Aircraft);
	m_TypesPossibleToAttack.Add(UnitType::VE_Building);
	m_TypesPossibleToAttack.Add(UnitType::VE_Defense);
	m_TypesPossibleToAttack.Add(UnitType::VE_Infantry);
	m_TypesPossibleToAttack.Add(UnitType::VE_NavyUnit);
	m_TypesPossibleToAttack.Add(UnitType::VE_Superweapon);
	m_TypesPossibleToAttack.Add(UnitType::VE_Tank);
}