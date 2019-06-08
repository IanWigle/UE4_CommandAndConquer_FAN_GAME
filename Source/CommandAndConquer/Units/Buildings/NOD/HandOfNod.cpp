// Fill out your copyright notice in the Description page of Project Settings.


#include "HandOfNod.h"

AHandOfNod::AHandOfNod()
{
	m_UnitArmor = UnitArmor::VE_Heavy;
	m_Power = -20;
	m_BuildingID = BuildingID::VE_Hand;
	m_MaxHealth = 400;
	m_Health = m_MaxHealth;
}