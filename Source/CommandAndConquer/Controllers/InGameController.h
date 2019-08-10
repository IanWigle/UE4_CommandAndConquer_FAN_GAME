// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "EnumTypes.h"
#include "InGameController.generated.h"

/**
 * 
 */
UCLASS()
class COMMANDANDCONQUER_API AInGameController : public APlayerController
{
	GENERATED_BODY()

public:
    AInGameController();

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
    bool m_UnitsAreSelected = false;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
		TArray<class ALivingUnit*> m_SelectedUnits;

    class ABuilding* SpawnBuildingFromID(BuildingID ID, FTransform spawnTransform, FActorSpawnParameters SpawnParams);

    UPROPERTY(EditAnywhere)
        class USoundBase* m_NewConstructionOptions;

    UPROPERTY(EditAnywhere)
        class UAudioComponent* m_AudioComponent;
protected:
    virtual void PlayerTick(float DeltaTime) override;
    virtual void SetupInputComponent() override;
    
    void MoveRight(float value);
    void MoveUp(float value);
    void ScrollIn(float value);
	
    void Select();
    void SelectMultiple();
    void Deselect();
};
