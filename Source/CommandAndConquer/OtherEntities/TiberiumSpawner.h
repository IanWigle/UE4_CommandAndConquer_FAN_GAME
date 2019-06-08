// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TiberiumSpawner.generated.h"

UCLASS()
class COMMANDANDCONQUER_API ATiberiumSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATiberiumSpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Crystal Data")
		TSubclassOf<class ATiberiumCrystal> m_Crystal;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Crystal Data")
		int m_MaxinumCrystalsForPool = 40;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Crystal Data")
		int m_NumberOfActiveCrystals = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Crystal Data")
		float m_SpawnCrystalRadius = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Crystal Data")
		int m_NumberOfSpawningCrystals = 1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Crystal Data")
		class UBoxComponent* m_BoxForFutureCrystal;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Crystal Data")
		FTimerHandle m_SpawnCrystalHandle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Crystal Data")
		float m_MinTimeToSpawn = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Crystal Data")
		float m_MaxTimeToSpawn = 5;

	

	void SpawnNewCrystal();
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "Crystal Data")
		bool CanCrystalsBeMade();

	UFUNCTION(BlueprintCallable, Category = "Crystal Data")
		void AddToCrystalPool() { m_NumberOfActiveCrystals++; };

	UFUNCTION(BlueprintCallable, Category = "Crystal Data")
		void RemoveFromCrystalPool() { m_NumberOfActiveCrystals--; }

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Crystal Data")
		TArray<ATiberiumCrystal*> m_Crystals;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UStaticMeshComponent* m_StaticMesh;
};
