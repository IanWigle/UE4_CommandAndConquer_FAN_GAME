// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EnumTypes.h"
#include "Unit.generated.h"


UCLASS()
class COMMANDANDCONQUER_API AUnit : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AUnit();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unit Data", Replicated)
	    UnitType m_UnitType = UnitType::VE_NoType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unit Data", Replicated)
		UnitArmor m_UnitArmor = UnitArmor::VE_None;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unit Data")
		FName m_UnitName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Unit Data")
		float m_MaxHealth = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unit Data", Replicated)
		float m_Health = 0;

    bool m_IsSelected = false;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")
        bool m_HasVoiceLines = false;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (EditCondition = "m_HasVoiceLines"), Category = Audio)
        TArray<class USoundBase*> m_GreetingVoices;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (EditCondition = "m_HasVoiceLines"), Category = Audio)
        TArray<class USoundBase*> m_AcknowledgmentsVoices;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (EditCondition = "m_HasVoiceLines"), Category = Audio)
        class UAudioComponent* m_AudioComponent;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		class APlayerCharacter* m_OwningCharacter;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Replicated)
		PlayerTeams m_Team;

    UFUNCTION(BlueprintCallable, BlueprintPure)
        UnitType GetUnitType() { return m_UnitType; }

    UFUNCTION(BlueprintCallable, BlueprintPure)
        UnitArmor GetUnitArmor() { return m_UnitArmor; }

    UFUNCTION(BlueprintCallable, BlueprintPure)
        FName GetUnitName() { return m_UnitName; }

    UFUNCTION(BlueprintCallable, BlueprintPure)
        bool IsSelected() { return m_IsSelected; }

    UFUNCTION(BlueprintCallable) 
        void SetSelected(bool state) { m_IsSelected = true; }

    /** If the specificGreeting value more than -1 than it will try and 
        use the value as an index for the array of greetings.*/
    UFUNCTION(BlueprintCallable, Category = "Unit Audio")
        void SayGreeting(int specificGreeting = -1);

    /** If the specificAch value more than -1 than it will try and
        use the value as an index for the array of acknowledgments.*/
    UFUNCTION(BlueprintCallable, Category = "Unit Audio")
        void SayAcknowledgments(int specificacknowledgment = -1);
};
