// Fill out your copyright notice in the Description page of Project Settings.


#include "BulletProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/StaticMeshComponent.h"

ABulletProjectile::ABulletProjectile()
{
	m_ProjectileComponent = CreateDefaultSubobject<UProjectileMovementComponent>("Projectile");
	m_ProjectileComponent->SetUpdatedComponent(RootComponent);
	
	GetStaticMeshComponent()->OnComponentHit.AddDynamic(this, &ABulletProjectile::OnHit);
	GetStaticMeshComponent()->SetMobility(EComponentMobility::Movable);
}

void ABulletProjectile::OnHit(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComponent, FVector NormalImpulse, const FHitResult & Hit)
{
}
