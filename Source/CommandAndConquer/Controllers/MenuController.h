// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MenuController.generated.h"

/**
 * 
 */
UCLASS()
class COMMANDANDCONQUER_API AMenuController : public APlayerController
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay();

	class UMainMenu* UserInterface;
	
};
