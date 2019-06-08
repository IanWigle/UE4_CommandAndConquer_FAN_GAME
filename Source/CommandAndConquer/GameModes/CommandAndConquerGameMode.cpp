// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "CommandAndConquerGameMode.h"
#include "CommandAndConquerPlayerController.h"
#include "CommandAndConquerCharacter.h"
#include "UObject/ConstructorHelpers.h"

ACommandAndConquerGameMode::ACommandAndConquerGameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = ACommandAndConquerPlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDownCPP/Blueprints/TopDownCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}