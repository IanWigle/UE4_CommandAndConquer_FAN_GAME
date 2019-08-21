// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "EnumTypes.h"
#include "NukeclearMissile.generated.h"

/**
 * 
 */


UCLASS()
class COMMANDANDCONQUER_API ANukeclearMissile : public AStaticMeshActor
{
	GENERATED_BODY()
protected:
	UPROPERTY(VisibleAnywhere)
		NukeMissileDirection m_Direction;

	void Explode();
	
public:
	ANukeclearMissile();

	void Tick(float DeltaSeconds) override;

	UPROPERTY(EditAnywhere)
		class UAudioComponent* m_DetonationSound;

	UPROPERTY(EditAnywhere, Category = "Nuke Data")
		float m_ExplosionRadius;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class USphereComponent* m_ExplosionRadiusSphere;

	UFUNCTION()
		virtual void OnComponentHit(UPrimitiveComponent* OverlappedComponent,
			AActor* OtherActor,
			UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex,
			bool bFromSweep,
			const FHitResult &SweepResult);

	void ComeDown();
	void ShootMissile() { m_Direction = NukeMissileDirection::VE_UP; }

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Nuke Data")
		float m_MissileSpeedUpwards;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Nuke Data")
		float m_MissileSpeedDownwards;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Nuke Data")
		float m_MaxHeight = 1500.0f;
};
