// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "EnumTypes.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Units/Building.h"
#include "Engine/World.h"
#include "Engine/EngineTypes.h"
#include "GenericPlatform/GenericPlatformMisc.h"
#include "HelperFunctions.generated.h"


/**
 * 
 */
UCLASS()
class COMMANDANDCONQUER_API UHelperFunctions : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

    /** If you see this in editor it means you can see the UHelperFunctionLibrary*/
    UFUNCTION(BlueprintCallable)
        float GetTestValue() { return 0.0f; }

    UFUNCTION(BlueprintCallable, Category = "Custom Analytics")
        static float TimeRemainingInAnimationFromStateMachine(class ACharacter* a_character, FName a_StateMachineName, FName a_StateName);

    template<typename TEnum>
    FORCEINLINE FString GetEnumValueAsString(const FString& Name, TEnum value)
    {
        const UEnum* enumPtr = FindObject(ANY_PACKAGE, *Name, true);
        if (!enumPtr)
        {
            return FString("Invalid enum name");
        }
        return enumPtr->GetNameByValue((int64)value).ToString();
    }

    UFUNCTION(BlueprintCallable, Category = "Custom Analytics")
    static ABuilding* GetBuildingFromPlayerArsenal(BuildingID ID, TArray<ABuilding*> OutActors)
    {
        for (int32 i = 0; i < OutActors.Num(); i++)   
        {
            if (OutActors[i]->GetBuildingID() == ID) return OutActors[i];
        }

        return nullptr;
    }

    UFUNCTION(BlueprintCallable, Category = "Building Analytics")
    static bool DoesPlayHaveBuilding(BuildingID ID, TArray<ABuilding*> PlayerBuildings)
    {
        for (int i = 0; i < PlayerBuildings.Num(); i++)
        {
            if (PlayerBuildings[i]->GetBuildingID() == ID) return true;
        }

        return false;
    }

	UFUNCTION(BlueprintCallable, Category = "Custom Analytics")
	static void QuitGame()
	{
		FGenericPlatformMisc::RequestExit(false);
	}

	static class AActor* GetClosestRefinery(class ACharacter* a_character, class UWorld* world);

	UFUNCTION(BlueprintCallable, Category = "Custom Analytics")
		static bool IsInEditor(class UWorld* world);

	
	static void AttachActorToSkeletalMeshSocket(FName socketName, AActor* attachingActor, USkeletalMeshComponent* mesh, FAttachmentTransformRules attachRule);

	
	static void AttachComponentToSkeletalMeshSocket(FName socketName, UPrimitiveComponent* attachingComponent, USkeletalMeshComponent* mesh, FAttachmentTransformRules attachRule);
};