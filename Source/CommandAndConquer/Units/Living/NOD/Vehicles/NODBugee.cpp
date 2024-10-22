// Fill out your copyright notice in the Description page of Project Settings.


#include "NODBugee.h"

ANODBugee::ANODBugee()
{
	m_LivingUnitID = LivingUnitID::VE_Recon;
	m_UnitArmor = UnitArmor::VE_Light;
	m_UnitRange = UnitRange::VE_Medium;

	m_TypesPossibleToAttack.Add(UnitType::VE_Building);
	m_TypesPossibleToAttack.Add(UnitType::VE_Defense);
	m_TypesPossibleToAttack.Add(UnitType::VE_Infantry);
	m_TypesPossibleToAttack.Add(UnitType::VE_NavyUnit);
	m_TypesPossibleToAttack.Add(UnitType::VE_Superweapon);
	m_TypesPossibleToAttack.Add(UnitType::VE_Tank);
}