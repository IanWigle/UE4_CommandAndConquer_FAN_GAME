	// Fill out your copyright notice in the Description page of Project Settings.


#include "TiberiumCrystal.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Engine/Public/TimerManager.h"
#include "TiberiumSpawner.h"

// Sets default values
ATiberiumCrystal::ATiberiumCrystal()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	m_BoxCollider = CreateDefaultSubobject<UBoxComponent>("Box Collider");
	m_BoxCollider->SetBoxExtent(FVector(15.f, 15.f, 30.f));
	m_BoxCollider->SetGenerateOverlapEvents(true);
	RootComponent = m_BoxCollider;

	m_BoxForFutureCrystal = CreateDefaultSubobject<UBoxComponent>("Future Box Collider");
	m_BoxForFutureCrystal->SetBoxExtent(m_BoxCollider->GetUnscaledBoxExtent());
	m_BoxForFutureCrystal->SetWorldLocation(RootComponent->GetComponentLocation());
	m_BoxForFutureCrystal->SetGenerateOverlapEvents(true);

	m_SmallCrystal = CreateDefaultSubobject<UStaticMesh>("Small Crystal");
	m_MediumCrystal = CreateDefaultSubobject<UStaticMesh>("Medium Crystal");
	m_LargeCrystal = CreateDefaultSubobject<UStaticMesh>("Large Crystal");	

	m_ActiveModel = CreateDefaultSubobject<UStaticMeshComponent>("Current Crystal Model");
	m_ActiveModel->SetCollisionProfileName("NoCollision");
	m_ActiveModel->SetupAttachment(RootComponent);


	m_CreditWorth = (int)TiberiumWorth::WORTHLVL1;
	m_ActiveModel->SetStaticMesh(m_SmallCrystal);
}

// Called when the game starts or when spawned
void ATiberiumCrystal::BeginPlay()
{
	Super::BeginPlay();
	m_CreditWorth = (int)TiberiumWorth::WORTHLVL1;
	m_ActiveModel->SetStaticMesh(m_SmallCrystal);
}

// Called every frame
void ATiberiumCrystal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (m_TiberiumLevel == TiberiumLevels::VE_LVL0)
		Destroy();

	RefreshModels();

	FMatrix DebugMatrix;
	DebugMatrix.TransformPosition(GetActorLocation());

	DrawDebugCircle(GetWorld(), DebugMatrix, m_SpawnCrystalRadius, 20, FColor::Green);

	if (m_TiberiumLevel != TiberiumLevels::VE_LVL3 && !GetWorld()->GetTimerManager().IsTimerActive(m_GrowCrystalHandle) && IsBeingCollected == false)
	{
		// run timer
		GetWorld()->GetTimerManager().SetTimer(m_GrowCrystalHandle, this, &ATiberiumCrystal::Grow, FMath::RandRange(m_MinTimeToGrow,m_MaxTimeToGrow));
	}
	else if (m_TiberiumWorth == WORTHLVL3 && !GetWorld()->GetTimerManager().IsTimerActive(m_SpawnCrystalHandle) && m_OriginSpawner->CanCrystalsBeMade())
	{
		// spawn new crystal
		GetWorld()->GetTimerManager().SetTimer(m_SpawnCrystalHandle, this, &ATiberiumCrystal::SpawnNewCrystal, FMath::RandRange(m_MinTimeToSpawn, m_MaxTimeToSpawn));

		
		
	}
}

void ATiberiumCrystal::Grow()
{
	if (IsBeingCollected)
		return;

	switch (m_TiberiumLevel)
	{
	case TiberiumLevels::VE_LVL1:
		m_TiberiumLevel = TiberiumLevels::VE_LVL2;
		m_TiberiumWorth = WORTHLVL2;
		break;
	case TiberiumLevels::VE_LVL2:
		m_TiberiumLevel = TiberiumLevels::VE_LVL3;
		m_TiberiumWorth = WORTHLVL3;
		break;
	}

	m_CreditWorth = (int)m_TiberiumWorth;

	switch (m_TiberiumLevel)
	{
	case TiberiumLevels::VE_LVL0:
		m_ActiveModel->bVisible = false;
		break;
	case TiberiumLevels::VE_LVL1:
		m_ActiveModel->SetStaticMesh(m_SmallCrystal);
		break;
	case TiberiumLevels::VE_LVL2:
		m_ActiveModel->SetStaticMesh(m_MediumCrystal);
		break;
	case TiberiumLevels::VE_LVL3:
		m_ActiveModel->SetStaticMesh(m_LargeCrystal);
		break;
	}
}

void ATiberiumCrystal::SpawnNewCrystal()
{
	if (m_OriginSpawner->CanCrystalsBeMade())
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
				//GetWorld()->SpawnActor<ATiberiumCrystal>(FVector(randomPoint, 0.0f), FRotator::ZeroRotator, SpawnParams);
				auto newCrystal = GetWorld()->SpawnActor<ATiberiumCrystal>(this->StaticClass(), SpawnTransform, SpawnParams);
				if (newCrystal)
				{
					newCrystal->m_SmallCrystal = m_SmallCrystal;
					newCrystal->m_MediumCrystal = m_MediumCrystal;
					newCrystal->m_LargeCrystal = m_LargeCrystal;
					newCrystal->m_OriginSpawner = m_OriginSpawner;
					m_OriginSpawner->AddToCrystalPool();
					m_OriginSpawner->m_Crystals.Add(newCrystal);
				}
			}

		}
	}
	
}

void ATiberiumCrystal::RefreshModels()
{
	switch (m_TiberiumLevel)
	{
	case TiberiumLevels::VE_LVL0:
		m_ActiveModel->bVisible = false;
		break;
	case TiberiumLevels::VE_LVL1:
		m_ActiveModel->SetStaticMesh(m_SmallCrystal);
		break;
	case TiberiumLevels::VE_LVL2:
		m_ActiveModel->SetStaticMesh(m_MediumCrystal);
		break;
	case TiberiumLevels::VE_LVL3:
		m_ActiveModel->SetStaticMesh(m_LargeCrystal);
		break;
	}
}

int ATiberiumCrystal::Shrink()
{
	switch (m_TiberiumLevel)
	{
	case TiberiumLevels::VE_LVL0:
		return 0;
	case TiberiumLevels::VE_LVL1:
		m_TiberiumLevel = TiberiumLevels::VE_LVL0;
		m_TiberiumWorth = WORTHLVL0;
		m_CreditWorth = (int)m_TiberiumWorth;
		RefreshModels();
		return m_CreditWorth;
	case TiberiumLevels::VE_LVL2:
		m_TiberiumLevel = TiberiumLevels::VE_LVL1;
		m_TiberiumWorth = WORTHLVL1;
		m_CreditWorth = (int)m_TiberiumWorth;
		RefreshModels();
		return m_CreditWorth;
	case TiberiumLevels::VE_LVL3:
		m_TiberiumLevel = TiberiumLevels::VE_LVL2;
		m_TiberiumWorth = WORTHLVL2;
		m_CreditWorth = (int)m_TiberiumWorth;
		RefreshModels();
		return m_CreditWorth;
	}

	RefreshModels();

	return 0;
}

int ATiberiumCrystal::CollectTiberiumWorth()
{
	int credits = 0;
	switch (m_TiberiumLevel)
	{
	case TiberiumLevels::VE_LVL3:
		credits = (int)m_TiberiumWorth - (int)TiberiumWorth::WORTHLVL2;
		m_TiberiumLevel = TiberiumLevels::VE_LVL2;
		m_TiberiumWorth = WORTHLVL2;
		return credits;
	case TiberiumLevels::VE_LVL2:
		credits = (int)m_TiberiumWorth - (int)TiberiumWorth::WORTHLVL1;
		m_TiberiumLevel = TiberiumLevels::VE_LVL1;
		m_TiberiumWorth = WORTHLVL1;
		return credits;
	case TiberiumLevels::VE_LVL1:
		credits = (int)m_TiberiumWorth;
		m_TiberiumLevel = TiberiumLevels::VE_LVL0;
		m_TiberiumWorth = WORTHLVL0;
		return credits;
	}

	return credits;
}