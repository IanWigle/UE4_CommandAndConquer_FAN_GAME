// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MenuInterface.generated.h"


/**
 * 
 */
UINTERFACE(MinimalAPI)
class UMenuInterface : public UInterface
{
	GENERATED_BODY()
};

class COMMANDANDCONQUER_API IMenuInterface
{

	GENERATED_BODY()

public:
	virtual void Host(FString ServerName, FString Team) = 0;
	virtual void Join(uint32 Index, FString Team) = 0;
	
	virtual void RefreshServerList() = 0;
};
