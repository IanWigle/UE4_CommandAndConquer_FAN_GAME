// Fill out your copyright notice in the Description page of Project Settings.


#include "Harvester.h"
#include "OtherEntities/TiberiumCrystal.h"
#include "OtherEntities/TiberiumSpawner.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "AI/HarvesterController.h"


void AHarvester::BeginPlay()
{
	Super::BeginPlay();

	m_MaxHealth = 600;
	m_Health = m_MaxHealth;
}

void AHarvester::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//if (!m_IsCollectorFindingCrystal)
		//FindClosestCrystal();
}

void AHarvester::OnComponentBeginOverlap(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	auto crystal = Cast<ATiberiumCrystal>(OtherActor);
	if (crystal)
	{
		//Cast<AHarvesterController>(GetController())->GetBlackboardComponent()->SetValueAsBool("AreThereCrystalsInSight", true);
	}
}

void AHarvester::FindClosestCrystal()
{
	TSubclassOf<ATiberiumSpawner> spawnerTemplate;
	TArray<AActor*> FoundSpawners;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), m_SpawnerTemplate, FoundSpawners);

	ATiberiumSpawner* closestSpawner = nullptr;
	if (FoundSpawners.Num() > 0)
	{
		float lowestDistance = 0.0f;
		lowestDistance = FVector::Distance(GetActorLocation(), FoundSpawners[0]->GetActorLocation());
		int closestSpawnerIndex = 0;
		for (int i = 1; i < FoundSpawners.Num(); i++)
		{
			float distance = FVector::Distance(GetActorLocation(), FoundSpawners[i]->GetActorLocation());
			if (distance < lowestDistance)
			{
				lowestDistance = distance;
				closestSpawnerIndex = i;
			}
		}

		closestSpawner = Cast<ATiberiumSpawner>(FoundSpawners[closestSpawnerIndex]);

		if (closestSpawner)
		{
			float lowestDistance = FVector::Distance(GetActorLocation(), closestSpawner->m_Crystals[0]->GetActorLocation());
			int closestCrystalIndex = 0;
			for (int i = 1; i < closestSpawner->m_Crystals.Num(); i++)
			{
				float distance = FVector::Distance(GetActorLocation(), closestSpawner->m_Crystals[i]->GetActorLocation());
				if (distance < lowestDistance)
				{
					lowestDistance = distance;
					closestCrystalIndex = i;
				}
			}
			m_TargetCrystal = closestSpawner->m_Crystals[closestCrystalIndex];
			m_IsCollectorFindingCrystal = true;
			UAIBlueprintHelperLibrary::SimpleMoveToLocation(GetController(), m_TargetCrystal->GetActorLocation());			
		}
	}
}