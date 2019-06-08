// Fill out your copyright notice in the Description page of Project Settings.


#include "DefenseBuilding.h"
#include "Components/SphereComponent.h"
#include "Components/ArrowComponent.h"
#include "HelperFunctions.h"
#include "Controllers/DefenseBuildingController.h"

ADefenseBuilding::ADefenseBuilding()
{
	m_SightRadiusComponent = CreateDefaultSubobject<USphereComponent>("Sight Radius");
	m_SightRadiusComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	m_SightRadiusComponent->SetGenerateOverlapEvents(true);
	m_SightRadiusComponent->SetupAttachment(RootComponent);
	m_SightRadiusComponent->SetSphereRadius(m_SightRange);
	m_SightRadiusComponent->OnComponentBeginOverlap.AddDynamic(this, &ADefenseBuilding::OnEnemyEnteredSight);

	m_SpawnArrow = CreateDefaultSubobject<UArrowComponent>("Projectile Spawn Arrow");
	m_SpawnArrow->bHiddenInGame = false;
}

void ADefenseBuilding::UpdateLookAtDirection()
{
	if (m_Target)
	{
		FVector Position1 = GetActorLocation();
		FVector Position2 = m_Target->GetActorLocation();

		FVector PlaneOrigin = GetActorLocation();
		FVector PlaneNormal = FVector(0.0f, 0.0f, 1.0f);

		FVector LookLocation = FMath::LinePlaneIntersection(Position1, Position2, PlaneOrigin, PlaneNormal);
		LookLocation = (LookLocation - GetActorLocation());
		LookLocation.Normalize();

		m_LookAtDirection = LookLocation.Rotation();
	}
	else
	{
		m_LookAtDirection = FRotator(0.0f);
	}
}

bool ADefenseBuilding::HasTarget()
{
	return (m_Target != nullptr) ? true : false;
}

AUnit * ADefenseBuilding::GetClosestEnemyInSight()
{
	if (m_UnitsInSightRange.Num() > 2)
	{
		float lowestdistance = 0.0f;
		int closesttargetindex = 0;
		lowestdistance = FVector::Dist(GetActorLocation(), m_UnitsInSightRange[0]->GetActorLocation());
		for (int i = 0; i < m_UnitsInSightRange.Num();i++)
		{
			float distance = FVector::Dist(GetActorLocation(), m_UnitsInSightRange[i]->GetActorLocation());
			if (distance < lowestdistance)
			{
				lowestdistance = distance;
				closesttargetindex = i;
			}
		}
		return m_UnitsInSightRange[closesttargetindex];
	}
	else if (m_UnitsInSightRange.Num() == 1)
	{
		return m_UnitsInSightRange[0];
	}
	else
	{
		return nullptr;
	}
	return nullptr;
}

bool ADefenseBuilding::IsTargetUnitInAttackRange()
{
	if (m_Target)
	{
		bool result = ((FVector::Dist(GetActorLocation(), m_Target->GetTargetLocation())) <= m_AttackRange);
		return result;
	}

	return false;
}

void ADefenseBuilding::UpdateToCheckIfTargetIsInRange()
{
	if (m_Target)
	{
		if (FVector::Dist(GetActorLocation(), m_Target->GetTargetLocation()) <= m_SightRange)
		{
			m_UnitsInSightRange.Remove(m_Target);
			m_Target = nullptr;
		}
	}
}

void ADefenseBuilding::OnEnemyEnteredSight(UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult &SweepResult)
{
	if (OtherActor->GetOwner() != GetOwner())
	{
		auto castedActor = Cast<AUnit>(OtherActor);
		if (castedActor)
		{
			for (UnitType type : m_TypesAllowedToAttack)
			{
				if (type == castedActor->GetUnitType())
					return;
			}

			m_UnitsInSightRange.Add(castedActor);
			if (m_UnitsInSightRange.Num() >= 2)
			{
				m_Target = GetClosestEnemyInSight();
				Cast<ADefenseBuildingController>(GetController())->GetBlackboardComponent()->SetValueAsBool("HasTarget", true);
			}
			else
			{
				m_Target = castedActor;
				Cast<ADefenseBuildingController>(GetController())->GetBlackboardComponent()->SetValueAsBool("HasTarget", true);
			}
		}			
	}
}

