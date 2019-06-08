// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "BulletProjectile.generated.h"

/**
 * 
 */
UCLASS()
class COMMANDANDCONQUER_API ABulletProjectile : public AStaticMeshActor
{
	GENERATED_BODY()

public:
	ABulletProjectile();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UProjectileMovementComponent* m_ProjectileComponent;

	UFUNCTION()
		virtual void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);
};
