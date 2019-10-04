// Fill out your copyright notice in the Description page of Project Settings.


#include "Building.h"
#include "Components/BoxComponent.h"
#include "UnrealNetwork.h"
#include "Components/StaticMeshComponent.h"
#include "PlayerCharacter.h"
#include "DestructibleComponent.h"

ABuilding::ABuilding()
{
    m_BuildingCollider = CreateDefaultSubobject<UBoxComponent>("Building Collider");
    m_BuildingCollider->SetCollisionObjectType(ECC_Visibility);
    m_BuildingCollider->SetCollisionProfileName("OverlapAllDynamic");
	m_BuildingCollider->SetupAttachment(RootComponent);
	m_BuildingCollider->bDynamicObstacle = true;
	m_BuildingCollider->SetCanEverAffectNavigation(true);
    //RootComponent = m_BuildingCollider;

	m_DestructibleMesh = CreateDefaultSubobject<UDestructibleComponent>("Destructable Mesh");
	m_DestructibleMesh->SetCollisionObjectType(ECC_Visibility);
	m_DestructibleMesh->SetCollisionProfileName("OverlapAllDynamic");
	m_DestructibleMesh->SetupAttachment(RootComponent);
	m_DestructibleMesh->SetCanEverAffectNavigation(true);

	

    m_StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("Building Mesh");
    m_StaticMesh->SetCollisionObjectType(ECC_Visibility);
	m_StaticMesh->SetupAttachment(RootComponent);
}

void ABuilding::BeginPlay()
{
    Super::BeginPlay();

    m_UnitType = UnitType::VE_Building;
}

void ABuilding::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

	if (m_IsBeingRepaired)
	{
		APlayerCharacter* player = Cast<APlayerCharacter>(GetOwner());

		if (m_Health == m_MaxHealth)
			m_IsBeingRepaired = false;

		if (player && m_IsBeingRepaired == true)
		{
			if (player->GetUserCredits() > 0)
			{
				player->AddCredits(-5);

				if (player->GetUserCredits() < 0)
					player->AddCredits(-player->GetUserCredits());

				m_Health += 10;

				if (m_Health >= m_MaxHealth)
				{
					m_Health = m_MaxHealth;
					m_IsBeingRepaired = false;
				}
			}
		}
	}
}

void ABuilding::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ABuilding, m_BuildingCollider);
	DOREPLIFETIME(ABuilding, m_StaticMesh);
}
