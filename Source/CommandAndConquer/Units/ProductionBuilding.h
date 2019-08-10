// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Units/Building.h"
#include "Components/ArrowComponent.h"
#include "ProductionBuilding.generated.h"

/**
 * 
 */
UCLASS()
class COMMANDANDCONQUER_API AProductionBuilding : public ABuilding
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditAnywhere, Category = "Production Building", Replicated)
		UArrowComponent* m_SpawnLocation;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Production Building")
		bool m_IsPrimaryBuilding;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Production Building")
		class USoundBase* m_PrimaryBuildingVoice;

public:

	AProductionBuilding();

	void SetPrimaryBuilding(bool state);
	bool IsPrimaryBuilding() { return m_IsPrimaryBuilding; }
	FVector GetSpawnLocation() { return m_SpawnLocation->GetComponentLocation(); }
};
