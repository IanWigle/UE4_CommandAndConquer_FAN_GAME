// Fill out your copyright notice in the Description page of Project Settings.


#include "Comm.h"

AComm::AComm()
{
	m_Cost = 1000;
	m_Power = -40;
	m_BuildingID = BuildingID::VE_Comm;

	m_UnitArmor = UnitArmor::VE_Medium;
	m_UnitType = UnitType::VE_Building;
	m_UnitName = "Comm";
	m_MaxHealth = 500;
	m_Health = m_MaxHealth;
}