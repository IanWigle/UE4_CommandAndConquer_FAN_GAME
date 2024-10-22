// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Units/Buildings/Superweapon.h"
#include "TempleOfNod.generated.h"

/**
 * 
 */
UCLASS()
class COMMANDANDCONQUER_API ATempleOfNod : public ASuperweapon
{
	GENERATED_BODY()
protected:
	void BeginPlay();
public:
	ATempleOfNod();

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Superweapon")
		class UArrowComponent* m_MissileSpawnArrow;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Superweapon")
		class USkeletalMeshComponent* m_Missile;

	//UFUNCTION(BlueprintCallable, Category = "Superweapon")
		virtual void SuperweaponReady() override;

		UPROPERTY(EditAnywhere, BlueprintReadWrite)
			TSubclassOf<class ANukeclearMissile> m_MissileObject;

		virtual void LaunchWeapon() override;

		UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
			ANukeclearMissile* m_SpawnedMissile;
	
};
