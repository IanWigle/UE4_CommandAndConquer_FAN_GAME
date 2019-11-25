// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Units/Buildings/DefenseBuilding.h"
#include "Obelisk.generated.h"

/**
 * 
 */
UCLASS()
class COMMANDANDCONQUER_API AObelisk : public ADefenseBuilding
{
	GENERATED_BODY()
protected:
	void BeginPlay();

	void ShowLaser();
	void HideLaser();

public:
	AObelisk();
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		class UParticleSystemComponent* m_BeamParticleSystem;


		virtual void OnEnemyEnteredSight(UPrimitiveComponent* OverlappedComponent,
			AActor* OtherActor,
			UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex,
			bool bFromSweep,
			const FHitResult& SweepResult);

		virtual void OnEnemyLeaveSight(UPrimitiveComponent* OverlappedComp,
			AActor* OtherActor,
			UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex);

		UPROPERTY(EditAnywhere, BlueprintReadWrite)
			float m_ChargeUpDelay = 3;

		UPROPERTY(EditAnywhere, BlueprintReadWrite)
			float m_ChargeCooldown= 5;
};
