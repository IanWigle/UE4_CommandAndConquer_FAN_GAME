// Fill out your copyright notice in the Description page of Project Settings.


#include "SAM.h"
#include "HelperFunctions.h"
#include "Components/ArrowComponent.h"
#include "Components/SkeletalMeshComponent.h"

void ASAM::BeginPlay()
{
	Super::BeginPlay();
	UHelperFunctions::AttachComponentToSkeletalMeshSocket("SAMMissileSocket", m_SpawnArrow, GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale);
}

ASAM::ASAM()
{
	m_AttackDamage = 50.0f;
	m_AttackCooldown = 50.0f;
	m_AttackRange = 300.0f;
	m_SightRange = 400.0f;

	m_Cost = 750;
	m_Power = -20;
	m_BuildingID = BuildingID::VE_SAM;

	m_UnitType = UnitType::VE_Defense;
	m_UnitArmor = UnitArmor::VE_Light;
	m_UnitName = "SAM";
	m_MaxHealth = 200;
	m_Health = m_MaxHealth;

	m_TypesAllowedToAttack.Add(UnitType::VE_Aircraft);
}