// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Units/Building.h"
#include "TiberiumRefinery.generated.h"

/**
 * 
 */
UCLASS()
class COMMANDANDCONQUER_API ATiberiumRefinery : public ABuilding
{
	GENERATED_BODY()

protected:

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Refinery")
		UArrowComponent* m_TargetLocation;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Refinery")
		class USoundBase* m_PrimaryBuildingVoice;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Harvester")
		TSubclassOf<class AHarvester> m_Harvester;

	virtual void BeginPlay() override;

public:

	ATiberiumRefinery();


};
