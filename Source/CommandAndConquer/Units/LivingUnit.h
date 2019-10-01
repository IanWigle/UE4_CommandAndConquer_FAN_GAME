// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Units/Unit.h"
#include "LivingUnit.generated.h"

/**
 * 
 */
UCLASS()
class COMMANDANDCONQUER_API ALivingUnit : public AUnit
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay();

	UnitRange m_UnitRange = UnitRange::VE_NA;
	LivingUnitID m_LivingUnitID = LivingUnitID::VE_NA;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UnitAttackBehavior m_UnitAttackBehavior;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float m_AttackCooldown;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float m_AttackRange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "0"))
		float m_SightRange;

	/*UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<class AController> m_AIController;*/

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated)
		AActor* m_MainTarget;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		TArray<class AUnit*> m_Targets;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<UnitType> m_TypesPossibleToAttack;

	bool IsUnitAlreadyListed(AUnit* unit);
	bool CanUnitAttackTarget(UnitType othertype);

	AUnit* GetClosestEnemyInSight();

public:

	ALivingUnit();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "0"))
		float m_PrimaryDamage = 0;

	UFUNCTION(BlueprintCallable)
		UnitRange GetUnitRange() { return m_UnitRange; }

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Replicated)
		class UBoxComponent* m_LivingUnitCollider;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class USphereComponent* m_SightRadiusComponent;

	UFUNCTION()
		virtual void OnEnemyEnteredSight(UPrimitiveComponent* OverlappedComponent,
			AActor* OtherActor,
			UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex,
			bool bFromSweep,
			const FHitResult& SweepResult);

	UFUNCTION()
		virtual void OnEnemyLeaveSight(UPrimitiveComponent* OverlappedComp,
			AActor* OtherActor,
			UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex);
};
