// Fill out your copyright notice in the Description page of Project Settings.


#include "Obelisk.h"

AObelisk::AObelisk()
{
	m_GroundAttackDamage = 200.0f;
	m_AttackCooldown = 90.0f;
	m_AttackRange = 750.0f;
	m_SightRange = 500.0f;

	m_Cost = 1500;
	m_Power = -150;
	m_BuildingID = BuildingID::VE_Obelisk;

	m_UnitType = UnitType::VE_Defense;
	m_UnitArmor = UnitArmor::VE_Light;
	m_UnitName = "Obelisk";
	m_MaxHealth = 200;
	m_Health = m_MaxHealth;

	m_TypesAllowedToAttack.Add(UnitType::VE_Building);
	m_TypesAllowedToAttack.Add(UnitType::VE_Defense);
	m_TypesAllowedToAttack.Add(UnitType::VE_Infantry);
	m_TypesAllowedToAttack.Add(UnitType::VE_NavyUnit);
	m_TypesAllowedToAttack.Add(UnitType::VE_Superweapon);
	m_TypesAllowedToAttack.Add(UnitType::VE_Tank);
}