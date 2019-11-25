// Fill out your copyright notice in the Description page of Project Settings.


#include "Obelisk.h"
#include "Runtime/Engine/Classes/Particles/ParticleSystemComponent.h"
#include "Helpers/HelperFunctions.h"
#include "Components/SphereComponent.h"
#include "Components/ArrowComponent.h"
#include "Controllers/DefenseBuildingController.h"
#include "UnrealNetwork.h"
#include "Classes/BehaviorTree/BlackboardComponent.h"

void AObelisk::BeginPlay()
{
	Super::BeginPlay();

	UHelperFunctions::AttachComponentToSkeletalMeshSocket("CrystalSocket", m_BeamParticleSystem, GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale);

	m_BeamParticleSystem->bHiddenInGame = true;
}

AObelisk::AObelisk()
{
	m_AttackDamage = 200.0f;
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

	m_BeamParticleSystem = CreateDefaultSubobject<UParticleSystemComponent>("Beam Particle");
}

void AObelisk::OnEnemyEnteredSight(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnEnemyEnteredSight(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);

	if (m_Target)
	{
		FTimerHandle ChargeTimer;
		GetWorld()->GetTimerManager().SetTimer(ChargeTimer, this, &AObelisk::ShowLaser, m_ChargeUpDelay, false);
	}	
}

void AObelisk::OnEnemyLeaveSight(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	Super::OnEnemyLeaveSight(OverlappedComp, OtherActor, OtherComp, OtherBodyIndex);

	m_BeamParticleSystem->InstanceParameters[1].Actor = nullptr;

	m_BeamParticleSystem->bHiddenInGame = true;
}

void AObelisk::ShowLaser()
{
	m_BeamParticleSystem->InstanceParameters[0].Actor = this;
	m_BeamParticleSystem->InstanceParameters[1].Actor = m_Target;

	m_BeamParticleSystem->bHiddenInGame = false;

	FTimerHandle CooldownTimer;
	//GetWorld()->GetTimerManager().SetTimer(CooldownTimer, this, &AObelisk::HideLaser, m_ChargeCooldown, false);
}
