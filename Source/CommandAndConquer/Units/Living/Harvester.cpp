// Fill out your copyright notice in the Description page of Project Settings.


#include "Harvester.h"
#include "OtherEntities/TiberiumCrystal.h"
#include "OtherEntities/TiberiumSpawner.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "AI/HarvesterController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Units/Buildings/Global/TiberiumRefinery.h"
#include "PlayerCharacter.h"


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
			lowestDistance = 0;
			lowestDistance = FVector::Distance(GetActorLocation(), closestSpawner->m_Crystals[0]->GetActorLocation());
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

void AHarvester::CollectTiberium(UBlackboardComponent* Blackboard)
{
    bool CargoIsFull = false;
    bool WasCrystalDestroyed = false;

    // If blackboard is invalid exit the function.
    if (Blackboard == nullptr)
        return;

    // Get the target crystal that the harvester is going towards. If the cast is invalid exit the function.
    ATiberiumCrystal* crystal = Cast<ATiberiumCrystal>(Blackboard->GetValueAsObject("TargetCrystal"));
    if (crystal == nullptr)
        return;

    // Mark the crystal to be collected.
    crystal->IsBeingCollected = true;

    // Collect the credits from the crystal
    int credits = crystal->CollectTiberiumWorth();

    // If the cargo would be full or more than the max cargo
    if ((m_Cargo + credits) >= m_MaxCargo)
    {
        // The cargo is full and set the cargo to the max value.
        CargoIsFull = true;
        m_Cargo = m_MaxCargo;
    }
    else
    {
        m_Cargo += credits;
    }

    // If the crystals level is 0
    if (crystal->GetTiberiumLevel() == TiberiumLevels::VE_LVL0)
    {
        // Destroy the crystal.
        crystal->DestroyCrystal();
        WasCrystalDestroyed = true;
    }
        
    if (CargoIsFull)
    {
        Blackboard->SetValueAsEnum("HarvestorMode", 3);
    }
    else if (WasCrystalDestroyed)
    {
        Blackboard->SetValueAsEnum("HarvestorMode", 0);
    }
}

void AHarvester::EmptyHarvester(UBlackboardComponent* Blackboard)
{
    if (Blackboard == nullptr)
        return;

    ATiberiumRefinery* refinery = Cast<ATiberiumRefinery>(Blackboard->GetValueAsObject("OriginalRefinery"));
    if (refinery == nullptr)
        return;

    APlayerCharacter* player = Cast<APlayerCharacter>(refinery->GetOwner());
    if (player == nullptr)
        return;

    if (player->GetUserCredits() < player->GetMaxUserCredits())
    {
        m_Cargo--;
        player->AddCredits(-1);
        if (m_Cargo == 0)        
            Blackboard->SetValueAsEnum("HarvestorMode", 0);        
    }
}