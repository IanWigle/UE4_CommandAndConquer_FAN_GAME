// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Units/LivingUnit.h"
#include "Vehicle.generated.h"

/**
 * 
 */
UCLASS()
class COMMANDANDCONQUER_API AVehicle : public ALivingUnit
{
	GENERATED_BODY()

protected:

	void BeginPlay() override;

public:

	AVehicle();
	
	UPROPERTY(EditAnywhere)
		float HeadXAxis;

	UPROPERTY(EditAnywhere)
		float HeadYAxis;

	UPROPERTY(EditAnywhere)
		float HeadZAxis;


};
