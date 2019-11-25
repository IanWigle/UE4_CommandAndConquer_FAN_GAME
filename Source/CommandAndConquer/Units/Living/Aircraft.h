// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Units/Living/LivingUnit.h"
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

	FORCEINLINE	void DestroyAircraft() { this->Destroy(); }
public:
	AAircraft();


	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "0"))
		float m_FlightHeight;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "0"))
		float m_HorizontalSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "1"))
		float m_GroundHeight;

	void Tick(float DeltaTime);

	virtual void Die();
};
