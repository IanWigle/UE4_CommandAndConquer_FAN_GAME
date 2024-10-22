// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Units/Living/Unit.h"
#include "Building.generated.h"



/**
 * 
 */
UCLASS()
class COMMANDANDCONQUER_API ABuilding : public AUnit
{
	GENERATED_BODY()
	
public:
    // Sets default values for this character's properties
    ABuilding();

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

    /** The cost to produce the required building*/
    int m_Cost = 0;
    
    /** If the value is a negative it costs that amount of power, if 
    positive it generates that amount of power*/
    int m_Power = 0;

	UPROPERTY(VisibleAnywhere)
		BuildingID m_BuildingID = BuildingID::VE_NA;

public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Replicated)
        class UBoxComponent* m_BuildingCollider;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Replicated)
        class UStaticMeshComponent* m_StaticMesh;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Replicated)
		class UDestructibleComponent* m_DestructibleMesh;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Replicated)
		bool m_UsesDestructableMesh = false;

    UFUNCTION(BlueprintCallable, BlueprintPure)
        BuildingID GetBuildingID() { return m_BuildingID; }

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		bool m_HasPower = true;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		bool m_IsBeingRepaired = false;

    UFUNCTION(BlueprintCallable, BlueprintPure)
        int GetPowerValue() { return m_Power; }

    UFUNCTION(BlueprintCallable, BlueprintPure)
        int GetBuildingCost() { return m_Cost; }
};
