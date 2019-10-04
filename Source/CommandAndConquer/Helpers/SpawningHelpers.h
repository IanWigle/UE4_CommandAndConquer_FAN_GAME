// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "EnumTypes.h"
#include "SpawningHelpers.generated.h"

/**
 *
 */
UCLASS()
class COMMANDANDCONQUER_API USpawningHelpers : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()
public:
    UFUNCTION(BlueprintCallable, Category = "Spawning Helpers")
        static TSubclassOf<class ABuilding> DetermineWhichBuildingToMake(BuildingID ID, APlayerController* playerController);



};
