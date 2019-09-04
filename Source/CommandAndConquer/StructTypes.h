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
		FString m_Color;

	UPROPERTY()
		FName m_PlayerName;

	UPROPERTY()
		int32 m_StartingLocation;

	FLobbyPlayerDetails()
	{
		m_Team = PlayerTeams::VE_Team0;
		m_Faction = PlayerFaction::VE_NOD;
		m_PlayerName = "";
		m_Color = "Red";
		m_StartingLocation = 0;
	}

	
		void ChangeTeam(PlayerTeams team) { m_Team = team; }
	
		void ChangeFaction(PlayerFaction faction) { m_Faction = faction; }
	
		void ChangeColor(FString color) { m_Color = color; }
	
		void ChangeName(FName name) { m_PlayerName = name; }
	
		void ChangeStartingLocation(int32 loc) { m_StartingLocation = loc; }

	
		PlayerTeams GetTeam() { return m_Team; }
	
		PlayerFaction GetFaction() { return m_Faction; }
	
		FString GetColor() { return m_Color; }
	
		FName GetPlayerName() { return m_PlayerName; }
	
		int32 GetStartingLocation() { return m_StartingLocation; }
};

