// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MusicPlayer.generated.h"

UCLASS()
class COMMANDANDCONQUER_API AMusicPlayer : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMusicPlayer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

    UPROPERTY(EditAnywhere, Category = "Music List")
        TArray<class USoundBase*> m_Songs;

    UPROPERTY(VisibleAnywhere, Category = "Track Data")
        int m_CurrentTrack = 0;

    UPROPERTY(VisibleAnywhere, Category = "Track Data")
        bool m_OnLoop = false;

    UPROPERTY(VisibleAnywhere, Category = "Track Data")
        bool m_RandomSong = false;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

    UPROPERTY(EditAnywhere)
        class UAudioComponent* m_AudioComponent;

    UFUNCTION(BlueprintCallable)
        int GetCurrentTrack() { return m_CurrentTrack; }

    UFUNCTION(BlueprintCallable)
        bool IsOnLoop() { return m_OnLoop; }

    UFUNCTION(BlueprintCallable)
        bool IsRandom() { return m_RandomSong; }

    UFUNCTION(BlueprintCallable)
        void SetOnLoop(bool state) { m_OnLoop = state; }

    UFUNCTION(BlueprintCallable)
        void SetRandom(bool state) { m_RandomSong = state; }

    UFUNCTION(BlueprintCallable)
        void NextSong();

    UFUNCTION(BlueprintCallable)
        void PreviousSong();
};
