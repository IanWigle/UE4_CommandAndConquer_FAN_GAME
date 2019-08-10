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

public:

	ALivingUnit();

	UPROPERTY(EditAnywhere, meta = (ClampMin = "0"))
		float m_PrimaryDamage = 0;

	UFUNCTION(BlueprintCallable)
		UnitRange GetUnitRange() { return m_UnitRange; }

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Replicated)
		class UBoxComponent* m_LivingUnitCollider;
};
