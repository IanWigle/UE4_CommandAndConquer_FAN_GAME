	// Fill out your copyright notice in the Description page of Project Settings.


#include "TiberiumSpawner.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "TiberiumCrystal.h"
#include "Engine/World.h"
#include "Engine/Public/TimerManager.h"

// Sets default values
ATiberiumSpawner::ATiberiumSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	m_StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("Static Mesh");
	SetRootComponent(m_StaticMesh);

	m_BoxForFutureCrystal = CreateDefaultSubobject<UBoxComponent>("Future Box Collider");
	m_BoxForFutureCrystal->SetBoxExtent(FVector(15.f, 15.f, 30.f));
	m_BoxForFutureCrystal->SetWorldLocation(RootComponent->GetComponentLocation());
	m_BoxForFutureCrystal->SetGenerateOverlapEvents(true);
}

// Called when the game starts or when spawned
void ATiberiumSpawner::BeginPlay()
{
	Super::BeginPlay();
	SpawnNewCrystal();
}

void ATiberiumSpawner::SpawnNewCrystal()
{
	if (CanCrystalsBeMade())
	{
		for (int i = 0; i < m_NumberOfSpawningCrystals; i++)
		{

			FVector2D randomPoint = FMath::RandPointInCircle(m_SpawnCrystalRadius);
			m_BoxForFutureCrystal->SetWorldLocation(GetActorLocation() + FVector(randomPoint, 0.0f));
			TArray<AActor*> FoundCrystals;
			TSubclassOf<ATiberiumCrystal> crystalTemplate;

			m_BoxForFutureCrystal->GetOverlappingActors(FoundCrystals, crystalTemplate);

			if (FoundCrystals.Num() == 0)
			{
				FActorSpawnParameters SpawnParams;
				FTransform SpawnTransform;
				SpawnTransform.SetLocation(m_BoxForFutureCrystal->GetComponentLocation());
				auto newCrystal = GetWorld()->SpawnActor<ATiberiumCrystal>(m_Crystal, SpawnTransform, SpawnParams);
				if (newCrystal)
				{
					newCrystal->m_OriginSpawner = this;
					AddToCrystalPool();
					m_Crystals.Add(newCrystal);
				}
			}

		}
	}	
}

// Called every frame
void ATiberiumSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (m_NumberOfActiveCrystals < (m_MaxinumCrystalsForPool / 2) && !GetWorld()->GetTimerManager().IsTimerActive(m_SpawnCrystalHandle))
	{
		GetWorld()->GetTimerManager().SetTimer(m_SpawnCrystalHandle, this, &ATiberiumSpawner::SpawnNewCrystal, FMath::RandRange(m_MinTimeToSpawn,m_MaxTimeToSpawn));
	}
}

bool ATiberiumSpawner::CanCrystalsBeMade()
{
	if (m_NumberOfActiveCrystals < m_MaxinumCrystalsForPool)
		return true;
	else
		return false;
}


