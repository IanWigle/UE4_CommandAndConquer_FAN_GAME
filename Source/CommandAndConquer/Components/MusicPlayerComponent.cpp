// Fill out your copyright notice in the Description page of Project Settings.


#include "MusicPlayerComponent.h"
#include "Components/AudioComponent.h"

// Sets default values for this component's properties
UMusicPlayerComponent::UMusicPlayerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

    m_AudioComponent = CreateDefaultSubobject<UAudioComponent>("Audio Component");
}


// Called when the game starts
void UMusicPlayerComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UMusicPlayerComponent::DetermineNewSong()
{
	if (IsOnLoop())
		m_AudioComponent->Play();
	else
	{
		if (IsRandom())
		{
			m_CurrentTrack = (int)(FMath::RandRange(0, m_Songs.Num()));
			if (!m_Songs.IsValidIndex(m_CurrentTrack))
				m_CurrentTrack = 0;
		}
		else
		{
			m_CurrentTrack++;
			if (m_CurrentTrack >= m_Songs.Num())
				m_CurrentTrack = 0;
		}
	}
}


// Called every frame
void UMusicPlayerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
	if (!m_AudioComponent->IsPlaying() && m_ToggleMusic)
	{
		DetermineNewSong();

		m_AudioComponent->SetSound(m_Songs[m_CurrentTrack]);
		m_AudioComponent->Play();
	}
}

void UMusicPlayerComponent::NextSong()
{
	DetermineNewSong();

	m_AudioComponent->Stop();
	m_AudioComponent->SetSound(m_Songs[m_CurrentTrack]);
	m_AudioComponent->Play();
	
}

void UMusicPlayerComponent::PreviousSong()
{
    m_CurrentTrack--;
    if (m_CurrentTrack < 0)
        m_CurrentTrack = m_Songs.Num() - 1;

    m_AudioComponent->Stop();
    m_AudioComponent->SetSound(m_Songs[m_CurrentTrack]);
    m_AudioComponent->Play();
}

void UMusicPlayerComponent::ToggleMusic(bool state)
{
	m_ToggleMusic = !m_ToggleMusic;

	if (m_ToggleMusic)
		m_AudioComponent->Play();
	else
		m_AudioComponent->Stop();
}

void UMusicPlayerComponent::PlayCertainSong(int track)
{
	if (m_Songs.IsValidIndex(track))
	{
		m_AudioComponent->Stop();
		m_AudioComponent->SetSound(m_Songs[m_CurrentTrack]);
		m_AudioComponent->Play();
	}
}