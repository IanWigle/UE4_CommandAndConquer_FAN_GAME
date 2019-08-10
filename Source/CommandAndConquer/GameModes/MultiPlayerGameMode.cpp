// Fill out your copyright notice in the Description page of Project Settings.


#include "MultiPlayerGameMode.h"
#include "PlayerCharacter.h"

AMultiPlayerGameMode::AMultiPlayerGameMode() {}

void AMultiPlayerGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	auto player = Cast<APlayerCharacter>(NewPlayer->GetPawn());

	if (player)
	{
		player->m_Credits = m_StartingCredits;
	}
}