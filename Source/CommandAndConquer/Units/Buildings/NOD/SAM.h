// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Units/DefenseBuilding.h"
#include "SAM.generated.h"

/**
 * 
 */
UCLASS()
class COMMANDANDCONQUER_API ASAM : public ADefenseBuilding
{
	GENERATED_BODY()

protected:

	virtual void BeginPlay() override;

public:

	ASAM();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		bool m_IsSomethingNearby = false;
};
