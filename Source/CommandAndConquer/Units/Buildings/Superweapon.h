// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Units/Buildings/Building.h"
#include "Superweapon.generated.h"

/**
 * 
 */
UCLASS()
class COMMANDANDCONQUER_API ASuperweapon : public ABuilding
{
	GENERATED_BODY()
public:
	ASuperweapon();
protected:
	void BeginPlay();

	UPROPERTY(VisibleAnywhere, Category = "Superweapon")
		bool m_IsWeaponReady;
public:
	UFUNCTION(BlueprintCallable, Category = "Superweapon")
		virtual void LaunchWeapon();

	UFUNCTION(BlueprintCallable, Category = "Superweapon")
		void PauseCountdown();

	UFUNCTION(BlueprintCallable, Category = "Superweapon")
		void UnPauseCountdown();

	UFUNCTION(BlueprintCallable, Category = "Superweapon")
		virtual void SuperweaponReady();

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Superweapon")
		float CountdownTimeRemaining();

	void Tick(float DeltaTime);

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (ClampMin = "0"), Category = "Superweapon")
		float m_Countdown;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (ClampMin = "0"), Category = "Superweapon")
		float m_OffScreenDelay;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Superweapon")
		FTimerHandle m_CountdownHandle;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Superweapon")
		FTimerHandle m_OffScreenDelayHandle;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Superweapon")
		class USoundBase* m_SuperweaonReadyAudio;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (EditCondition = "m_HasVoiceLines"), Category = Audio)
		class UAudioComponent* m_SuperWeaponAudioComponent;
};
