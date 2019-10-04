// Fill out your copyright notice in the Description page of Project Settings.


#include "LivingUnit.h"
#include "UnrealNetwork.h"
#include "Components/BoxComponent.h"
#include "Components/SphereComponent.h"
#include "Runtime/Engine/Classes/GameFramework/Controller.h"

bool ALivingUnit::IsUnitAlreadyListed(AUnit* unit)
{
	return m_Targets.Contains(unit);
}

bool ALivingUnit::CanUnitAttackTarget(UnitType othertype)
{
	for (UnitType type : m_TypesPossibleToAttack)
	{
		if (type == othertype)
			return true;
	}

	return false;
}

AUnit* ALivingUnit::GetClosestEnemyInSight()
{
	if (m_Targets.Num() > 2)
	{
		float lowestdistance = 0.0f;
		int closesttargetindex = 0;
		lowestdistance = FVector::Dist(GetActorLocation(), m_Targets[0]->GetActorLocation());
		for (int i = 0; i < m_Targets.Num(); i++)
		{
			float distance = FVector::Dist(GetActorLocation(), m_Targets[i]->GetActorLocation());
			if (distance < lowestdistance)
			{
				lowestdistance = distance;
				closesttargetindex = i;
			}
		}
		return m_Targets[closesttargetindex];
	}
	else if (m_Targets.Num() == 1)
	{
		return m_Targets[0];
	}
	else
	{
		return nullptr;
	}

	return nullptr;
}

ALivingUnit::ALivingUnit()
{
	m_LivingUnitCollider = CreateDefaultSubobject<UBoxComponent>("Living Unit Collider");
	m_LivingUnitCollider->SetCollisionObjectType(ECC_Visibility);
	m_LivingUnitCollider->SetCollisionProfileName("BlockAllDynamic");
	m_LivingUnitCollider->SetupAttachment(RootComponent);
	//m_LivingUnitCollider->SetCanEverAffectNavigation(true);

	m_SightRadiusComponent = CreateDefaultSubobject<USphereComponent>("Sight Radius");
	m_SightRadiusComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	m_SightRadiusComponent->SetGenerateOverlapEvents(true);
	m_SightRadiusComponent->SetupAttachment(RootComponent);
	m_SightRadiusComponent->SetSphereRadius(m_SightRange);
	m_SightRadiusComponent->OnComponentBeginOverlap.AddDynamic(this, &ALivingUnit::OnEnemyEnteredSight);
	m_SightRadiusComponent->OnComponentEndOverlap.AddDynamic(this, &ALivingUnit::OnEnemyLeaveSight);
}

void ALivingUnit::OnEnemyEnteredSight(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AUnit* OtherUnit = Cast<AUnit>(OtherActor);

	if (OtherUnit)
	{
		if (OtherUnit->m_Team != m_Team && CanUnitAttackTarget(OtherUnit->GetUnitType()) && !IsUnitAlreadyListed(OtherUnit))
		{
			m_Targets.Add(OtherUnit);
			if (m_Targets.Num() >= 2)
			{
				m_MainTarget = GetClosestEnemyInSight();
				return;
			}
			else
			{
				m_MainTarget = OtherUnit;
				return;
			}
		}
	}
}

void ALivingUnit::OnEnemyLeaveSight(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	AUnit* OtherUnit = Cast<AUnit>(OtherActor);

	if (OtherUnit)
	{
		if (m_Targets.Contains(OtherUnit) && m_MainTarget != OtherUnit)
			m_Targets.Remove(OtherUnit);
		else if (m_Targets.Contains(OtherUnit) && m_MainTarget == OtherUnit)
		{
			m_Targets.Remove(OtherUnit);

			if (m_Targets.Num() == 0)
			{
				m_MainTarget = nullptr;
			}
			else
			{
				m_MainTarget = GetClosestEnemyInSight();
			}
		}
	}
}

void ALivingUnit::BeginPlay()
{
	Super::BeginPlay();

	
}

void ALivingUnit::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ALivingUnit, m_LivingUnitCollider);
	DOREPLIFETIME(ALivingUnit, m_MainTarget);
}