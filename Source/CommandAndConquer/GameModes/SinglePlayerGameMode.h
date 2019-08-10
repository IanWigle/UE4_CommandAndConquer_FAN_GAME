// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "SinglePlayerGameMode.generated.h"

/**
 * 
 */
UCLASS()
class COMMANDANDCONQUER_API ASinglePlayerGameMode : public AGameMode
{
	GENERATED_BODY()

public:
	ASinglePlayerGameMode();

	UPROPERTY(EditAnywhere, Category = "Credits", meta = (ClampMin = "5000"))
		int m_StartingCredits;
	
};
