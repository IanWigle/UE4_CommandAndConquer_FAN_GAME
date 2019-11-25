// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "DataTypes/EnumTypes.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Units/Buildings/Building.h"
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
    static ABuilding* GetBuildingFromPlayerArsenal(BuildingID ID, TArray<AUnit*> OutActors)
    {
        for (int32 i = 0; i < OutActors.Num(); i++)   
        {
            if (Cast<ABuilding>(OutActors[i])->GetBuildingID() == ID) return Cast<ABuilding>(OutActors[i]);
        }

        return nullptr;
    }

    UFUNCTION(BlueprintCallable, Category = "Building Analytics")
    static bool DoesPlayHaveBuilding(BuildingID ID, TArray<AUnit*> PlayerBuildings)
    {
        for (int i = 0; i < PlayerBuildings.Num(); i++)
        {
            if (Cast<ABuilding>(PlayerBuildings[i])->GetBuildingID() == ID) return true;
        }

        return false;
    }

	UFUNCTION(BlueprintCallable, Category = "Custom Analytics")
	static void QuitGame()
	{
		FGenericPlatformMisc::RequestExit(false);
	}

	static class AActor* GetClosestRefinery(class ACharacter* a_character, class UWorld* world);

	static bool IsInEditor(class UWorld* world);

	static void AttachActorToSkeletalMeshSocket(FName socketName, AActor* attachingActor, USkeletalMeshComponent* mesh, FAttachmentTransformRules attachRule);

	static void AttachActorToStaticMeshSocket(FName socketName, AActor* attachingActor, UStaticMeshComponent* mesh, FAttachmentTransformRules attachRule);
		
	static void AttachComponentToSkeletalMeshSocket(FName socketName, UPrimitiveComponent* attachingComponent, USkeletalMeshComponent* mesh, FAttachmentTransformRules attachRule);

	static void AttachComponentToStaticMeshSocket(FName socketName, UPrimitiveComponent* attachingComponent, UStaticMeshComponent* mesh, FAttachmentTransformRules attachRule);

	//UFUNCTION(BlueprintCallable, Category = "Custom Attachment Functions")
	//	static void AddActorToSkeletalMeshSocket(FName socketName, AActor* attachingActor, USkeletalMeshComponent* mesh) { AttachActorToSkeletalMeshSocket(socketName, attachingActor, mesh, FAttachmentTransformRules::SnapToTargetIncludingScale); }

	//UFUNCTION(BlueprintCallable, Category = "Custom Attachment Functions")
	//	static void AddActorToStaticMeshSocket(FName socketName, AActor* attachingActor, UStaticMeshComponent* mesh) { AttachActorToStaticMeshSocket(socketName, attachingActor, mesh, FAttachmentTransformRules::SnapToTargetIncludingScale); }

	//UFUNCTION(BlueprintCallable, Category = "Custom Attachment Functions")
	//	static void AddComponentToSkeletalMeshSocket(FName socketName, UPrimitiveComponent* attachingComponent, USkeletalMeshComponent* mesh) { AttachComponentToSkeletalMeshSocket(socketName, attachingComponent, mesh, FAttachmentTransformRules::SnapToTargetIncludingScale); }

	//UFUNCTION(BlueprintCallable, Category = "Custom Attachment Functions")
	//	static void AddComponentToStaticMeshSocket(FName socketName, UPrimitiveComponent* attachingComponent, UStaticMeshComponent* mesh) { AttachComponentToStaticMeshSocket(socketName, attachingComponent, mesh, FAttachmentTransformRules::SnapToTargetIncludingScale); }

	
};