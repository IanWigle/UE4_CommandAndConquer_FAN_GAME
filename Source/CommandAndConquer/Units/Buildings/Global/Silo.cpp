// Fill out your copyright notice in the Description page of Project Settings.


#include "Silo.h"

ASilo::ASilo()
{
	m_Cost = 150;
	m_Power = -10;
	m_UnitArmor = UnitArmor::VE_Light;
	m_UnitName = "Silo";
	m_BuildingID = BuildingID::VE_Silo;
}