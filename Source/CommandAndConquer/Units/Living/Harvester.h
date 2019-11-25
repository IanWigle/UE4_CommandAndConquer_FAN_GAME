// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Units/Living/Vehicle.h"
#include "Units/Buildings/Global/TiberiumRefinery.h"
#include "DataTypes/EnumTypes.h"
#include "Harvester.generated.h"

/**
 * 
 */
UCLASS()
class COMMANDANDCONQUER_API AHarvester : public AVehicle
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

	bool m_IsCollectorFindingCrystal = false;

	class ATiberiumCrystal* m_TargetCrystal;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<class ATiberiumSpawner> m_SpawnerTemplate;

	

#pragma region AI Behavior
    UFUNCTION(BlueprintCallable, Category = "Havester | AI")
        void FindClosestCrystal();
    UFUNCTION(BlueprintCallable, Category = "Havester | AI")
        void CollectTiberium(UBlackboardComponent* Blackboard); 
    UFUNCTION(BlueprintCallable, Category = "Havester | AI")
        void EmptyHarvester(UBlackboardComponent* Blackboard);
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
        HarvesterBehavior m_HarvesterCurrentBehavior;
#pragma endregion

public:
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cargo")
		bool m_ChangeCargoMaxinum = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cargo", meta = (EditCondition = "m_ChangeCargoMaxinum"))
		int m_MaxCargo = 1500;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cargo")
		int m_Cargo = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Refinery")
		ATiberiumRefinery* m_OwningRefinery;

	UFUNCTION()
		virtual void OnComponentBeginOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
