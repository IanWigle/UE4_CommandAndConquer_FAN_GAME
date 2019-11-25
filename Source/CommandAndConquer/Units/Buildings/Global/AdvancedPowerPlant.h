// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Units/Buildings/Building.h"
#include "AdvancedPowerPlant.generated.h"

/**
 * 
 */
UCLASS()
class COMMANDANDCONQUER_API AAdvancedPowerPlant : public ABuilding
{
	GENERATED_BODY()

public:
	AAdvancedPowerPlant();

	virtual void Die();
	
};
