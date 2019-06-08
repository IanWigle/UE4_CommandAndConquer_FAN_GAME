// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "Engine/World.h"
#include "MainMenuHUD.generated.h"

/**
 * 
 */
UCLASS()
class COMMANDANDCONQUER_API AMainMenuHUD : public AHUD
{
	GENERATED_BODY()


	UFUNCTION(BlueprintCallable)
	bool IsPlayingInEditor()
	{
		return GetWorld()->IsPlayInEditor();
	}
};
