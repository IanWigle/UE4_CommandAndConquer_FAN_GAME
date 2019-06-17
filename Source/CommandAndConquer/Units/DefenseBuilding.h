// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Units/Building.h"
#include "EnumTypes.h"
#include "DefenseBuilding.generated.h"

/**
 * 
 */
UCLASS()
class COMMANDANDCONQUER_API ADefenseBuilding : public ABuilding
{
	GENERATED_BODY()
	
protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float m_GroundAttackDamage;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		float m_AttackCooldown;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		float m_AttackRange;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		float m_SightRange;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		FRotator m_LookAtDirection = FRotator(0.0f);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		class AUnit* m_Target = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		TArray<class AUnit*> m_UnitsInSightRange;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		TArray<UnitType> m_TypesAllowedToAttack;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class USphereComponent* m_SightRadiusComponent;	

	bool CanDefenseAttack(UnitType othertype);
	bool IsUnitAlreadyListed(AUnit* unit);

public:
	ADefenseBuilding();

	/**Update the LookAtDirection */
	UFUNCTION(BlueprintCallable)
		void UpdateLookAtDirection();

	UFUNCTION(BlueprintCallable)
		FRotator GetLookAtDirection() { return m_LookAtDirection; };

	/**If the defense has a target	*/
	UFUNCTION(BlueprintCallable)
		bool HasTarget();

	/** Get the closest unit that is in the Defense's sight.*/
	UFUNCTION(BlueprintCallable)
		class AUnit* GetClosestEnemyInSight();

	UFUNCTION(BlueprintCallable)
		void ResetTargetPointer() { m_Target = nullptr; }

	/** Check to see if the target is still in range.*/
	UFUNCTION(BlueprintCallable)
		bool IsTargetUnitInAttackRange();

	UFUNCTION(BlueprintCallable)
		void UpdateToCheckIfTargetIsInRange();

	UFUNCTION()
		virtual void OnEnemyEnteredSight(UPrimitiveComponent* OverlappedComponent,
			AActor* OtherActor,
			UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex,
			bool bFromSweep,
			const FHitResult &SweepResult);

	UFUNCTION()
		virtual void OnEnemyLeaveSight(UPrimitiveComponent* OverlappedComp, 
			AActor* OtherActor, 
			UPrimitiveComponent* OtherComp, 
			int32 OtherBodyIndex);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UArrowComponent* m_SpawnArrow;
};
