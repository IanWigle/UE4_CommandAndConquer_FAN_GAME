// Fill out your copyright notice in the Description page of Project Settings.


#include "NukeclearMissile.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/AudioComponent.h"
#include "Units/Buildings/Superweapon.h"
#include "Engine/World.h"
#include "PlayerCharacter.h"
#include "Units/Living/Unit.h"

void ANukeclearMissile::Explode()
{
	m_DetonationSound->Play();
	APlayerCharacter* player = Cast<APlayerCharacter>(GetOwner()->GetOwner());
	if (player)
	{
		player->m_TargetLocationForSuperweapon = FVector(0.0f);
	}
	m_Direction = NukeMissileDirection::VE_NA;

	TArray<AActor*> ActorsInNuke;
	GetOverlappingActors(ActorsInNuke);

	for (AActor* actor : ActorsInNuke)
	{
		auto Unit = Cast<AUnit>(actor);
		if (Unit)
		{
			Unit->DealDamage(Unit->GetMaxHealth());
		}
	}

	this->Destroy();
}

ANukeclearMissile::ANukeclearMissile()
{
	m_ExplosionRadiusSphere = CreateDefaultSubobject<USphereComponent>("ExplosionRadius");
	m_ExplosionRadiusSphere->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	m_ExplosionRadiusSphere->SetGenerateOverlapEvents(false);
	m_ExplosionRadiusSphere->SetupAttachment(RootComponent);
	m_ExplosionRadiusSphere->SetSphereRadius(m_ExplosionRadius);
	m_ExplosionRadiusSphere->OnComponentBeginOverlap.AddDynamic(this, &ANukeclearMissile::OnComponentHit);
	
	//GetStaticMeshComponent()->OnComponentHit.AddDynamic(this, &ANukeclearMissile::OnComponentHit)

	m_DetonationSound = CreateDefaultSubobject<UAudioComponent>("Audio Component");
	GetStaticMeshComponent()->SetMobility(EComponentMobility::Movable);

	PrimaryActorTick.bCanEverTick = true;
}

void ANukeclearMissile::Tick(float DeltaSeconds)
{
	switch (m_Direction)
	{
	case NukeMissileDirection::VE_UP:
	{
		FVector origin = GetActorLocation();
		origin.Z = origin.Z + (m_MissileSpeedUpwards * DeltaSeconds);
		SetActorLocation(origin);
		if (GetActorLocation().Z >= m_MaxHeight)
		{
			auto temple = Cast<ASuperweapon>(GetOwner());
			if (temple)
			{
				//GetStaticMeshComponent()->bHiddenInGame = true;
				GetWorld()->GetTimerManager().SetTimer(temple->m_OffScreenDelayHandle, this, &ANukeclearMissile::ComeDown,
					temple->m_OffScreenDelay, false);
				m_Direction = NukeMissileDirection::VE_NA;
			}
			
		}
		break;
	}
	case NukeMissileDirection::VE_DOWN:
	{
		FVector origin = GetActorLocation();
		origin.Z = origin.Z - (m_MissileSpeedDownwards * DeltaSeconds);
		SetActorLocation(origin);

		if (GetActorLocation().Z <= 0.0f)
		{
			Explode();
		}
	}
	}
}

void ANukeclearMissile::OnComponentHit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult)
{
	
	

	//this->Destroy();
}

void ANukeclearMissile::ComeDown()
{
	m_Direction = NukeMissileDirection::VE_DOWN;
	FVector origin = GetActorLocation();
	
	// Getting the nukes owner which is the temple. Then getting the temples owner which is the player.
	APlayerCharacter* player = Cast<APlayerCharacter>(GetOwner()->GetOwner());
	if (player)
	{
		origin.X = player->m_TargetLocationForSuperweapon.X;
		origin.Y = player->m_TargetLocationForSuperweapon.Y;

		SetActorLocation(origin);
		
		FRotator originRot = GetActorRotation();
		originRot.Pitch = -180;
		SetActorRotation(originRot);

		m_Direction = NukeMissileDirection::VE_DOWN;
		m_ExplosionRadiusSphere->SetGenerateOverlapEvents(true);
		m_ExplosionRadiusSphere->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	}
}
