// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MusicPlayerComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class COMMANDANDCONQUER_API UMusicPlayerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMusicPlayerComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Track Data")
		int m_CurrentTrack = 0;

	UPROPERTY(EditAnywhere, Category = "Track Data")
		bool m_OnLoop = false;

	UPROPERTY(EditAnywhere, Category = "Track Data")
		bool m_RandomSong = false;

	UPROPERTY(EditAnywhere, Category = "Track Data")
		bool m_ToggleMusic = true;

	void DetermineNewSong();

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        class UAudioComponent* m_AudioComponent;

    UPROPERTY(EditAnywhere, Category = "Music List")
        TArray<class USoundBase*> m_Songs;

    UFUNCTION(BlueprintCallable)
        int GetCurrentTrack() { return m_CurrentTrack; }

    UFUNCTION(BlueprintCallable)
        bool IsOnLoop() { return m_OnLoop; }

    UFUNCTION(BlueprintCallable)
        bool IsRandom() { return m_RandomSong; }

    UFUNCTION(BlueprintCallable, Exec)
        void SetOnLoop(bool state) { m_OnLoop = state; }

    UFUNCTION(BlueprintCallable, Exec)
        void SetRandom(bool state) { m_RandomSong = state; }

    UFUNCTION(BlueprintCallable, Exec)
        void NextSong();

    UFUNCTION(BlueprintCallable, Exec)
        void PreviousSong();

    UFUNCTION(BlueprintCallable)
        class USoundBase* GetCurrentSong() { return m_Songs[m_CurrentTrack]; }

    UFUNCTION(BlueprintCallable, Exec)
        void ToggleMusic(bool state);

    UFUNCTION(BlueprintCallable)
        bool GetToggleMusic() { return m_ToggleMusic; }

	UFUNCTION(BlueprintCallable, Exec)
		void PlayCertainSong(int track);
		
};
