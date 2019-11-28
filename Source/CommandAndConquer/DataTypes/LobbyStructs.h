// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnumTypes.h"
#include "LobbyStructs.generated.h"

USTRUCT(BlueprintType)
struct FLobbyPlayerDetails
{
	GENERATED_USTRUCT_BODY()

		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		PlayerTeams m_Team;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		PlayerFaction m_Faction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString m_Color;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FName m_PlayerName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 m_StartingLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool m_IsComputer;

	UPROPERTY()
		FString m_BotDifficutly;

	FLobbyPlayerDetails()
	{
		m_Team = PlayerTeams::VE_Team0;
		m_Faction = PlayerFaction::VE_NOD;
		m_PlayerName = "";
		m_Color = "Red";
		m_StartingLocation = 0;
	}

	//UFUNCTION(BlueprintCallable)
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