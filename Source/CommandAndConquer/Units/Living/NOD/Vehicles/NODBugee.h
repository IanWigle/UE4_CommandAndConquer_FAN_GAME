// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Units/Vehicle.h"
#include "NODBugee.generated.h"

/**
 * 
 */
UCLASS()
class COMMANDANDCONQUER_API ANODBugee : public AVehicle
{
	GENERATED_BODY()
	
protected:

	void BeginPlay() override;

public:

	ANODBugee();
};
