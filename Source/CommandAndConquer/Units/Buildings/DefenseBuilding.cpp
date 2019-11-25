// Fill out your copyright notice in the Description page of Project Settings.


#include "DefenseBuilding.h"
#include "Components/SphereComponent.h"
#include "Components/ArrowComponent.h"
#include "Helpers/HelperFunctions.h"
#include "Controllers/DefenseBuildingController.h"
#include "UnrealNetwork.h"
#include "Classes/BehaviorTree/BlackboardComponent.h"

bool ADefenseBuilding::CanDefenseAttack(UnitType othertype)
{
	for (UnitType type : m_TypesAllowedToAttack)
	{	
		if (type == othertype)
			return true;
	}

	return false;
}

bool ADefenseBuilding::IsUnitAlreadyListed(AUnit * unit)
{
	if (m_UnitsInSightRange.Contains(unit))
		return true;
	else
		return false;
}

ADefenseBuilding::ADefenseBuilding()
{
	m_SightRadiusComponent = CreateDefaultSubobject<USphereComponent>("Sight Radius");
	m_SightRadiusComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	m_SightRadiusComponent->SetGenerateOverlapEvents(true);
	m_SightRadiusComponent->SetupAttachment(RootComponent);
	m_SightRadiusComponent->SetSphereRadius(m_SightRange);
	m_SightRadiusComponent->OnComponentBeginOverlap.AddDynamic(this, &ADefenseBuilding::OnEnemyEnteredSight);
	m_SightRadiusComponent->OnComponentEndOverlap.AddDynamic(this, &ADefenseBuilding::OnEnemyLeaveSight);

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
	auto OtherUnit = Cast<AUnit>(OtherActor);

	// IF cast successful
	if (OtherUnit)
	{
		// IF the unit is from an opposing team AND is the defense able to attack it AND is the unit NOT on the list of nearby targets
		if (OtherUnit->m_Team != m_Team && CanDefenseAttack(OtherUnit->GetUnitType()) && !IsUnitAlreadyListed(OtherUnit))
		{
			m_UnitsInSightRange.Add(OtherUnit);
			// IF UnitsInSightRange is 2 OR MORE
			if (m_UnitsInSightRange.Num() >= 2)
			{
				m_Target = GetClosestEnemyInSight();
				Cast<ADefenseBuildingController>(GetController())->GetBlackboardComponent()->SetValueAsBool("HasTarget", true);
				return;
			}
			// END IF
			// ELSE
			else
			{
				m_Target = OtherUnit;
				Cast<ADefenseBuildingController>(GetController())->GetBlackboardComponent()->SetValueAsBool("HasTarget", true);
				return;
			}
			// END ELSE
		}		
		// END IF
	}
	// END IF
}

void ADefenseBuilding::OnEnemyLeaveSight(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	auto OtherUnit = Cast<AUnit>(OtherActor);

	if (OtherUnit)
	{
		if (m_UnitsInSightRange.Contains(OtherUnit) && m_Target != OtherUnit)
		{
			m_UnitsInSightRange.Remove(OtherUnit);
		}
		else if (m_UnitsInSightRange.Contains(OtherUnit) && m_Target == OtherUnit)
		{
			m_UnitsInSightRange.Remove(OtherUnit);

			if (m_UnitsInSightRange.Num() == 0)
			{
				m_Target = nullptr;
				Cast<ADefenseBuildingController>(GetController())->GetBlackboardComponent()->SetValueAsBool("HasTarget", false);
				m_LookAtDirection = FRotator(0.0f, 0.0f, 0.0f);
			}
			else
			{
				m_Target = GetClosestEnemyInSight();
			}			
		}
	}
}

void ADefenseBuilding::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ADefenseBuilding, m_Target);
	//DOREPLIFETIME(ADefenseBuilding, m_SpawnArrow);
}

