// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Units/Buildings/Building.h"
#include "ConstructionYard.generated.h"

/**
 * 
 */
UCLASS()
class COMMANDANDCONQUER_API AConstructionYard : public ABuilding
{
	GENERATED_BODY()

public:

    AConstructionYard();

protected:

    virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

    UPROPERTY(BlueprintReadWrite ,EditAnywhere)
        bool m_MakeBuilding = false;	
};
