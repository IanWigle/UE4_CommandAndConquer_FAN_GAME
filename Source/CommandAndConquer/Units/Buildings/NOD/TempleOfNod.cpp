// Fill out your copyright notice in the Description page of Project Settings.


#include "TempleOfNod.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/ArrowComponent.h"
#include "HelperFunctions.h"

ATempleOfNod::ATempleOfNod()
{
	m_Missile = CreateDefaultSubobject<USkeletalMeshComponent>("Missile");
	m_MissileSpawnArrow = CreateDefaultSubobject<UArrowComponent>("MissileSpawn");
	m_Missile->bHiddenInGame = true;
	FVector origin = m_MissileSpawnArrow->GetComponentLocation();
	m_Missile->SetWorldLocation(origin);
}

void ATempleOfNod::BeginPlay()
{
	Super::BeginPlay();

	UHelperFunctions::AttachComponentToSkeletalMeshSocket("MissileSpawn", 
		Cast<UPrimitiveComponent>(m_MissileSpawnArrow), GetMesh(), 
		FAttachmentTransformRules::SnapToTargetNotIncludingScale);

	

	m_Health = 1000;
	m_BuildingID = BuildingID::VE_Temple;
	m_Cost = 3000;
	m_Power = -150;
	m_UnitType = UnitType::VE_Superweapon;
	m_UnitArmor = UnitArmor::VE_Heavy;
	m_UnitName = "Temple Of Nod";
	m_MaxHealth = m_Health;
}

void ATempleOfNod::SuperweaponReady()
{
	Super::SuperweaponReady();

	m_Missile->bHiddenInGame = false;
}