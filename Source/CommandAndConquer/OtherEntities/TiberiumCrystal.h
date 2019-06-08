// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnumTypes.h"
#include "TiberiumCrystal.generated.h"

UCLASS()
class COMMANDANDCONQUER_API ATiberiumCrystal : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATiberiumCrystal();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Crystal Data")
		int m_CreditWorth = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Crystal Data")
		TiberiumLevels m_TiberiumLevel = TiberiumLevels::VE_LVL1;

	TiberiumWorth m_TiberiumWorth = WORTHLVL1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Crystal Data")
		FTimerHandle m_SpawnCrystalHandle;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Crystal Data")
		FTimerHandle m_GrowCrystalHandle;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Crystal Data")
		float m_SpawnCrystalRadius = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Crystal Data")
		int m_NumberOfSpawningCrystals = 1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Crystal Data")
		class UBoxComponent* m_BoxForFutureCrystal;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Crystal Data")
		float m_MinTimeToSpawn = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Crystal Data")
		float m_MaxTimeToSpawn = 5;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Crystal Data")
		float m_MinTimeToGrow = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Crystal Data")
		float m_MaxTimeToGrow = 5;

	void Grow();
	void SpawnNewCrystal();
	void RefreshModels();
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
		TiberiumLevels GetTiberiumLevel() { return m_TiberiumLevel; }

	UFUNCTION(BlueprintCallable)
		int GetCreditWorth() { return m_CreditWorth; }

	UFUNCTION(BlueprintCallable)
		int CollectTiberiumWorth();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tiberium Models")
		class UStaticMesh* m_SmallCrystal;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tiberium Models")
		class UStaticMesh* m_MediumCrystal;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tiberium Models")
		class UStaticMesh* m_LargeCrystal;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tiberium Models")
		class UStaticMeshComponent* m_ActiveModel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UBoxComponent* m_BoxCollider;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class ATiberiumSpawner* m_OriginSpawner;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool IsBeingCollected = false;

	UFUNCTION(BlueprintCallable)
		int Shrink();
};
