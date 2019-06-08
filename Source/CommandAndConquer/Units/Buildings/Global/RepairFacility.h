// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Units/Building.h"
#include "RepairFacility.generated.h"

/**
 * 
 */
UCLASS()
class COMMANDANDCONQUER_API ARepairFacility : public ABuilding
{
	GENERATED_BODY()

protected:

	virtual void BeginPlay();

public:

	ARepairFacility();

	UPROPERTY(EditAnywhere, Category = "RepairFacilty")
		UArrowComponent* m_TargetLocation;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "RepairFacilty")
		class USoundBase* m_PrimaryRepairVoice;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "RepairFacility")
		bool m_IsRepairing = false;
};
