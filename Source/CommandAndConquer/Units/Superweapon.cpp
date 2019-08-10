// Fill out your copyright notice in the Description page of Project Settings.

#include "Superweapon.h"
#include "HelperFunctions.h"
#include "PlayerCharacter.h"
#include "Engine/World.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/ArrowComponent.h"
#include "Components/AudioComponent.h"

ASuperweapon::ASuperweapon()
{
	m_SuperWeaponAudioComponent = CreateDefaultSubobject<UAudioComponent>("Super Weapon Audio Component");
}

void ASuperweapon::BeginPlay()
{
	Super::BeginPlay();	
	
	auto player = Cast<APlayerCharacter>(GetOwner());

	GetWorld()->GetTimerManager().SetTimer(m_CountdownHandle, this, &ASuperweapon::SuperweaponReady,m_Countdown, false);

	if (player->GetPlayerUsablePower() > 0)
		PauseCountdown();

	if (m_SuperweaonReadyAudio)
		m_SuperWeaponAudioComponent->SetSound(m_SuperweaonReadyAudio);
}

void ASuperweapon::PauseCountdown()
{
	if (GetWorld()->GetTimerManager().IsTimerActive(m_CountdownHandle))
		GetWorld()->GetTimerManager().PauseTimer(m_CountdownHandle);
}

void ASuperweapon::UnPauseCountdown()
{
	if (GetWorld()->GetTimerManager().IsTimerPaused(m_CountdownHandle))
		GetWorld()->GetTimerManager().UnPauseTimer(m_CountdownHandle);
}

void ASuperweapon::SuperweaponReady()
{
	if (m_SuperweaonReadyAudio)
		m_SuperWeaponAudioComponent->Play();
}

void ASuperweapon::Tick(float DeltaTime)
{
	auto player = Cast<APlayerCharacter>(GetOwner());

	if (player->GetPlayerUsablePower() > 0)
		UnPauseCountdown();
	else
		PauseCountdown();
}

float ASuperweapon::CountdownTimeRemaining()
{
	return GetWorld()->GetTimerManager().GetTimerRemaining(m_CountdownHandle);
}
