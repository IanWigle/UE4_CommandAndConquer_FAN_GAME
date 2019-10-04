// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Units/Building.h"
#include "Powerplant.generated.h"

/**
 * 
 */
UCLASS()
class COMMANDANDCONQUER_API APowerplant : public ABuilding
{
	GENERATED_BODY()

public:
    // Sets default values for this character's properties
    APowerplant();

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;

	virtual void Die();
	
};
