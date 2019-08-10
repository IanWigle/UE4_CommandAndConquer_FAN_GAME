// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnumTypes.h"
#include "StructTypes.generated.h"
/**
 * 
 */
USTRUCT(BlueprintType)
struct FLobbyPlayerDetails
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY()
		PlayerTeams m_Team;

	UPROPERTY()
		PlayerFaction m_Faction;

	UPROPERTY()
		FName m_PlayerName;

	UPROPERTY()
		int32 m_StartingLocation;

	FLobbyPlayerDetails()
	{
		m_Team = PlayerTeams::VE_Team0;
		m_Faction = PlayerFaction::VE_NOD;
		m_PlayerName = "";
		m_StartingLocation = 0;
	}
};

