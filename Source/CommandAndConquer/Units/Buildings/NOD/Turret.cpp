// Fill out your copyright notice in the Description page of Project Settings.


#include "Turret.h"
#include "HelperFunctions.h"

void ATurret::BeginPlay()
{
	Super::BeginPlay();
	UHelperFunctions::AttachComponentToSkeletalMeshSocket("BarrelShotSocket", m_SpawnArrow, GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale);
}

ATurret::ATurret()
{
	m_GroundAttackDamage = 40.0f;
	m_AttackCooldown = 60.0f;
	m_AttackRange = 500.0f;
	m_SightRange = 600.0f;

	m_Cost = 600;
	m_Power = -20;
	m_BuildingID = BuildingID::VE_Turret;
	
	m_UnitType = UnitType::VE_Defense;
	m_UnitArmor = UnitArmor::VE_Medium;
	m_UnitName = "Turret";
	m_MaxHealth = 200;
	m_Health = m_MaxHealth;

	m_TypesAllowedToAttack.Add(UnitType::VE_Building);
	m_TypesAllowedToAttack.Add(UnitType::VE_Defense);
	m_TypesAllowedToAttack.Add(UnitType::VE_Infantry);
	m_TypesAllowedToAttack.Add(UnitType::VE_NavyUnit);
	m_TypesAllowedToAttack.Add(UnitType::VE_Superweapon);
	m_TypesAllowedToAttack.Add(UnitType::VE_Tank);
}