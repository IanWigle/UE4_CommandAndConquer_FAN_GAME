// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "DataTypes/EnumTypes.h"
#include "GameModes/MultiPlayerGameMode.h"
#include "PlayerCharacter.generated.h"

UCLASS()
class COMMANDANDCONQUER_API APlayerCharacter : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APlayerCharacter();

private:
	friend class AMultiPlayerGameMode;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

    void BuildingProductionComplete();
    void UnitProductionComplete();

    FTimerHandle UnitProductionHandle;
    FTimerHandle BuildingProductionHandle;

    UPROPERTY(VisibleAnywhere, Category = "Building Logic")
        bool m_ProducingBuilding = false;
    UPROPERTY(VisibleAnywhere, Category = "Building Logic")
        bool m_BuildingIsReadyToBePlaced = false;
    UPROPERTY(VisibleAnywhere, Category = "Building Logic")
        bool m_SelectingLocation = false;
    UPROPERTY(VisibleAnywhere, Category = "Building Logic")
        bool m_IsBuildingMakingPaused = false;
	UPROPERTY(VisibleAnywhere, Category = "Superweapons")
		bool m_IsSelectingNukeTarget = false;

	UPROPERTY(VisibleAnywhere, Category = "UI Buttons")
		bool m_IsSelling = false;
	UPROPERTY(VisibleAnywhere, Category = "UI Buttons")
		bool m_IsRepairing = false;
	UPROPERTY(VisibleAnywhere, Category = "UI Buttons")
		bool m_TogglePower = false;

	UPROPERTY(VisibleAnywhere, Category = "Unit Logic")
		bool m_ProducingUnit = false;
	UPROPERTY(VisibleAnywhere, Category = "Unit Logic")
		bool m_IsUnitMakingPaused = false;

    bool m_RadarEnabled = false;

	UPROPERTY(Replicated)
		BuildingID m_BuildingThatIsBeingMade = BuildingID::VE_NA;
	UPROPERTY(Replicated)
		LivingUnitID m_UnitThatIsBeingMade = LivingUnitID::VE_NA;
	UPROPERTY(Replicated)
		UnitType m_UnitTypeThatIsBeingMade = UnitType::VE_NoType;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Credit Data")
        int m_Credits;
    UPROPERTY(VisibleAnywhere, AdvancedDisplay, Category = "Credit Data")
        int m_ConsumedBuildingCredits = 0;
    UPROPERTY(VisibleAnywhere, AdvancedDisplay, Category = "Credit Data")
        int m_BuildingCredits = 0;
	UPROPERTY(VisibleAnywhere, AdvancedDisplay, Category = "Credit Data")
		int m_ConsumedUnitCredits = 0;
	UPROPERTY(VisibleAnywhere, AdvancedDisplay, Category = "Credit Data")
		int m_UnitCredits = 0;
	UPROPERTY(VisibleAnywhere, Category = "Credit Data")
		int m_MaxCredits;

	UPROPERTY(VisibleAnywhere, Category = "Power")
		int m_PlayerPowerGenerated = 0;
	UPROPERTY(VisibleAnywhere, Category = "Power")
		int m_PowerConsumed = 0;
	UPROPERTY(VisibleAnywhere, Category = "Power")
		int m_UsablePower = 0;

    UPROPERTY(VisibleAnywhere, AdvancedDisplay, BlueprintReadWrite, Category = "YardPlayAnimation")
        bool m_YardIsMakingBuilding = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Replicated)
		PlayerFaction m_PlayerFaction;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

#pragma region Buildings

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Buildings | Player Arsenal")
        TArray<class AUnit*> m_PlayerBuildings;

#pragma region Building Templates
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Buildings | Player Arsenal")
        TMap<FString, TSubclassOf<class ABuilding>> m_BuildingArsenal;
#pragma endregion Building Templates    

#pragma region Building Functions
    UFUNCTION(BlueprintCallable, Category = "Buildings | Building Production")
        void BeginBuildingProduction(BuildingID ID, int TotalCost, float TimeToBuild);
    UFUNCTION(BlueprintCallable, Category = "Buildings | Building Production")
        void CancelBuildingProduction();
    UFUNCTION(BlueprintCallable, Category = "Buildings | Building Production")
        bool IsMakingBuilding() { return m_ProducingBuilding; };
    UFUNCTION(BlueprintCallable, Category = "Buildings | Building Production")
        bool IsBuildingReady() { return m_BuildingIsReadyToBePlaced; }
    UFUNCTION(BlueprintCallable, Category = "Buildings | Building Production")
        void SetBuildingReady(bool state) { m_BuildingIsReadyToBePlaced = state; }
    UFUNCTION(BlueprintCallable, Category = "Buildings | Building Production")
        BuildingID GetBuildingBeingMadeByID() { return m_BuildingThatIsBeingMade; }
    UFUNCTION(BlueprintCallable)
        void SetSelectingLocation(bool state) { m_SelectingLocation = state; }
    UFUNCTION(BlueprintCallable, Category = "Buildings | Building Production")
        bool IsBuildingProductionPaused() { return m_IsBuildingMakingPaused; }
    UFUNCTION(BlueprintCallable, Category = "Buildings | Building Production")
        void SetBuildingPause(bool state) { m_IsBuildingMakingPaused = state; }
    UFUNCTION(BlueprintCallable, Category = "Buildings | Building Production")
        void SetSettingBuildingLocation(bool state) { m_SelectingLocation = state; }
    UFUNCTION(BlueprintCallable, Category = "Buildings | Building Production")
        void ChooseBuildingLocation(FVector requestedPosition);
    UFUNCTION(BlueprintCallable)
        bool IsSelectingLocation() { return m_SelectingLocation; }
    /** Same as the CancelBuildingProduction but used for when a build was successfully
    made, therefore credits spent are not reset.*/
    UFUNCTION(BlueprintCallable, Category = "Buildings | Building Production")
        void ResetBuildingProduction();
#pragma endregion Building Functions

#pragma endregion Buildings

#pragma region Camera and Radar
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera | Components")
        class UCameraComponent* m_PlayerCamera;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera | Components")
        class USpringArmComponent* m_CameraArm;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Radar | Components")
        class USpringArmComponent* m_RadarCameraArm;
    UPROPERTY(EditAnywhere, Category = "Radar | Components")
        class USceneCaptureComponent2D* RadarCamera;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera | Camera Speeds")
        float m_CameraMovementSpeed;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera | Camera Speeds")
        float m_CameraZoomSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Radar | Misc")
		float m_RadarZoomSpeed;
    UFUNCTION(BlueprintCallable, Category = "Radar")
        void ToggleRadar(bool state) { m_RadarEnabled = state; }
    UFUNCTION(BlueprintCallable, Category = "Radar")
        bool IsRadarAvailable() { return m_RadarEnabled; }

    void MoveRight(float value);
    void MoveUp(float value);
    void ScrollIn(float value);
	void MiniMapZoom(float value);
#pragma endregion Camera and Radar

#pragma region Debug
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Debug")
        class UBoxComponent* m_Box;
#pragma endregion Debug

#pragma region Local Player Settings
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")
        class UMusicPlayerComponent* m_MusicPlayer;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Properties")
        bool m_IsFullScreen = false;
#pragma endregion Local Player Settings

#pragma region Player Power
    UFUNCTION(BlueprintCallable)
        int GetPlayerConsumedPower() { return m_PowerConsumed; }
	UFUNCTION(BlueprintCallable)
		int GetPlayerGeneratedPower() { return m_PlayerPowerGenerated; }
	UFUNCTION(BlueprintCallable)
		int GetPlayerUsablePower() { return m_UsablePower; }
	UFUNCTION(BlueprintCallable, Exec)
		void AddToPlayPower(int power);
	UFUNCTION(BlueprintCallable, Exec)
		void RemoveFromPlayerPower(int power);
#pragma endregion Player Power
   
#pragma region Tech Tree
    UFUNCTION(BlueprintCallable)
        bool DoWeUnlockNewTech(BuildingID ID);
#pragma endregion Tech Tree

#pragma region Units
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Army")
        TArray<class AUnit*> m_PlayerArmy;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Army")
		TMap<FString, TSubclassOf<ALivingUnit>> m_UnitArsenal;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Army")
		bool m_UnitsAreSelected = false;
#pragma region Unit Functions
    UFUNCTION(BlueprintCallable, Category = "Unit Production")
        void BeginUnitProduction(LivingUnitID ID, UnitType type, int TotalCost, float TimeToBuild);
	UFUNCTION(BlueprintCallable, Category = "Unit Production")
		void SetPauseUnitProduction(bool state) { m_IsUnitMakingPaused = state; };
	UFUNCTION(BlueprintCallable, Category = "Unit Production")
		void CancelUnitProduction();
    UFUNCTION(BlueprintCallable, Category = "Unit Production")
        bool IsMakingUnit() { return m_ProducingUnit; }
	UFUNCTION(BlueprintCallable, Category = "Unit Production")
		bool IsMakingUnitPaused() { return m_IsUnitMakingPaused; }
	UFUNCTION(BlueprintCallable, Category = "Unit Production")
		LivingUnitID GetUnitBeingMadeByID() { return m_UnitThatIsBeingMade; }
	/** Same as the CancelUnitProduction but used for when a build was successfully
		made, therefore credits spent are not reset.*/
	UFUNCTION(BlueprintCallable, Category = "Unit Production")
		void ResetUnitProduction();
	UFUNCTION(BlueprintCallable, Category = "Unit Production")
		class ALivingUnit* SpawnUnitFromID(LivingUnitID ID);
	UFUNCTION(BlueprintCallable, Category = "Unit Production")
		UnitType GetUnitBeingMadeByUnitType() { return m_UnitTypeThatIsBeingMade; }
	UFUNCTION(BlueprintCallable, Category = "Player Army")
		void SetUnitsSelected(bool toggle) { m_UnitsAreSelected = toggle; }
	UFUNCTION(BlueprintCallable, Category = "Player Army")
		bool AreUnitsSelected() { return m_UnitsAreSelected; }
#pragma endregion Unit Functions

#pragma endregion Units

#pragma region Misc
    UFUNCTION(BlueprintCallable)
        int GetUserCredits() { return m_Credits; }
	UFUNCTION(BlueprintCallable, Exec)
		bool IsPlayingInEditor()
	{
		return GetWorld()->IsPlayInEditor();
	}
	UFUNCTION(BlueprintCallable)
		int GetMaxUserCredits() { return m_MaxCredits; }
#pragma endregion Misc

#pragma region Audio

#pragma region EVA Voices
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "EVA Voices")
		TMap<FString, class USoundWave*> m_EVASoundsMap;
#pragma endregion EVA Voices

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UAudioComponent* m_EVAVoiceComponent;

#pragma endregion Audio

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		PlayerTeams m_PlayerTeam;
	UFUNCTION(Exec, meta = (DevelopmentOnly))
		void AddCredits(int credits) { m_Credits += credits; }
	UFUNCTION(BlueprintPure, BlueprintCallable)
		PlayerFaction GetPlayerFaction() { return m_PlayerFaction; }
	UFUNCTION(BlueprintPure, BlueprintCallable)
		bool IsSelectingLocationForNuke() { return m_IsSelectingNukeTarget; }
	UFUNCTION(BlueprintCallable)
		void SetIsSelectingLocationForNuke(bool state) { m_IsSelectingNukeTarget = state; }
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		FVector m_TargetLocationForSuperweapon;
	UFUNCTION(BlueprintCallable, BlueprintPure)
		bool IsRepairing() { return m_IsRepairing; }
	UFUNCTION(BlueprintCallable, BlueprintPure)
		bool IsSelling() { return m_IsSelling; }
	UFUNCTION(BlueprintCallable, BlueprintPure)
		bool IsTogglingPower() { return m_TogglePower; }
	UFUNCTION(BlueprintCallable)
		void SetRepairing(bool state) { m_IsRepairing = state; }
	UFUNCTION(BlueprintCallable)
		void SetSelling(bool state) { m_IsSelling = state; }
	UFUNCTION(BlueprintCallable)
		void SetTogglePower(bool state) { m_TogglePower = state; }
	UFUNCTION(BlueprintCallable, Exec)
		void RefreshPlayerPower();
	UFUNCTION(BlueprintCallable)
		bool AreThereAnyRadarPowered();
};