// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Units/LivingUnit.h"
#include "Aircraft.generated.h"

/**
 * 
 */
UCLASS()
class COMMANDANDCONQUER_API AAircraft : public ALivingUnit
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool m_IsFlying = true;
public:
	AAircraft();


	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "0"))
		float m_FlightHeight;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "0"))
		float m_HorizontalSpeed;

	void Tick(float DeltaTime);
};
