// Fill out your copyright notice in the Description page of Project Settings.


#include "MusicPlayer.h"
#include "Components/AudioComponent.h"

// Sets default values
AMusicPlayer::AMusicPlayer()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    m_AudioComponent = CreateDefaultSubobject<UAudioComponent>("Audio Component");    
}

// Called when the game starts or when spawned
void AMusicPlayer::BeginPlay()
{
	Super::BeginPlay();
	
    m_AudioComponent->SetSound(m_Songs[m_CurrentTrack]);
    m_AudioComponent->Play();
}

// Called every frame
void AMusicPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    if (m_Songs.IsValidIndex(m_CurrentTrack))
    {
        if (!m_AudioComponent->IsPlaying())
        {
            if (m_OnLoop)
            {
                m_AudioComponent->Play();
                return;
            }
            else
            {
                if (m_RandomSong)
                    m_CurrentTrack = (int)FMath::RandRange(0, m_Songs.Num() - 1);
                else
                {
                    m_CurrentTrack++;
                    if (m_CurrentTrack >= m_Songs.Num())
                        m_CurrentTrack = 0;

                    m_AudioComponent->SetSound(m_Songs[m_CurrentTrack]);
                    m_AudioComponent->Play();
                    return;
                }
            }
        }        
    }
    else
        m_CurrentTrack = 0;
}

void AMusicPlayer::NextSong()
{
    m_CurrentTrack++;
    if (m_CurrentTrack >= m_Songs.Num())
        m_CurrentTrack = 0;

    m_AudioComponent->Stop();
    m_AudioComponent->SetSound(m_Songs[m_CurrentTrack]);
    m_AudioComponent->Play();
}

void AMusicPlayer::PreviousSong()
{
    m_CurrentTrack--;
    if (m_CurrentTrack < 0)
        m_CurrentTrack = m_Songs.Num() - 1;

    m_AudioComponent->Stop();
    m_AudioComponent->SetSound(m_Songs[m_CurrentTrack]);
    m_AudioComponent->Play();
}