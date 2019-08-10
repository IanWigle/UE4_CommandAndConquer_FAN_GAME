// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameModes/SinglePlayerGameMode.h"
#include "MultiPlayerGameMode.generated.h"

/**
 * 
 */
class APlayerCharacter;

UCLASS()
class COMMANDANDCONQUER_API AMultiPlayerGameMode : public ASinglePlayerGameMode
{
	GENERATED_BODY()

public:

	AMultiPlayerGameMode();

	virtual void PostLogin(APlayerController* NewPlayer) override;
private:
	
};
