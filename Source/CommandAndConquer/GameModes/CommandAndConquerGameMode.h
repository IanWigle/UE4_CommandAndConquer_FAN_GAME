// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "CommandAndConquerGameMode.generated.h"

UCLASS(minimalapi)
class ACommandAndConquerGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ACommandAndConquerGameMode();

	UPROPERTY(EditAnywhere,Category = "Credits", meta = (ClampMin = "5000"))
		int m_StartingCredits;
};



