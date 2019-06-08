// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Units/DefenseBuilding.h"
#include "Turret.generated.h"

/**
 * 
 */
UCLASS()
class COMMANDANDCONQUER_API ATurret : public ADefenseBuilding
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;

public:
	ATurret();
};
