// Fill out your copyright notice in the Description page of Project Settings.


#include "Unit.h"
#include "Components/AudioComponent.h"
#include "Components/CapsuleComponent.h"
#include "UnrealNetwork.h"
#include "PlayerCharacter.h"

// Sets default values
AUnit::AUnit()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    m_AudioComponent = CreateDefaultSubobject<UAudioComponent>("Audio Component");    
//	GetCapsuleComponent()->SetCanEverAffectNavigation(true);
	SetReplicates(true);
	SetReplicateMovement(true);
}

// Called when the game starts or when spawned
void AUnit::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AUnit::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (m_InstantlyKill)
	{
		m_InstantlyKill = false;
		Die();
	}
}

// Called to bind functionality to input
void AUnit::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AUnit::SayGreeting(int specificGreeting)
{
    if (m_HasVoiceLines == true)
    {
        if (specificGreeting >= 0 && m_AcknowledgmentsVoices.Num() > 0)
        {
            m_AudioComponent->SetSound(m_GreetingVoices[specificGreeting]);
            m_AudioComponent->Play();
        }
        else
        {
            int32 randomvoice = (int32)FMath::RandRange(0, m_GreetingVoices.Num() - 1);
            m_AudioComponent->SetSound(m_GreetingVoices[randomvoice]);
            m_AudioComponent->Play();
        }
    }
}

void AUnit::SayAcknowledgments(int specificacknowledgment)
{
    if (m_HasVoiceLines == true && m_AcknowledgmentsVoices.Num() > 0)
    {
        if (specificacknowledgment >= 0)
        {
            m_AudioComponent->SetSound(m_AcknowledgmentsVoices[specificacknowledgment]);
            m_AudioComponent->Play();
        }
        else
        {
            int32 randomvoice = (int32)FMath::RandRange(0, m_AcknowledgmentsVoices.Num() - 1);
            m_AudioComponent->SetSound(m_AcknowledgmentsVoices[randomvoice]);
            m_AudioComponent->Play();
        }
    }
}

void AUnit::DealDamage(float damage)
{
	m_Health -= damage;
	if (m_Health < 0)
		m_Health = 0;

	if (m_Health == 0.0f)
	{
		Die();
	}
}

void AUnit::Die()
{
	auto Player = Cast<APlayerCharacter>(GetOwner());

	if (Player)
	{
		Player->m_PlayerBuildings.Remove(this);
		
	}

	this->Destroy();
}

void AUnit::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AUnit, m_UnitType);
	DOREPLIFETIME(AUnit, m_UnitArmor);
	DOREPLIFETIME(AUnit, m_Health);
	DOREPLIFETIME(AUnit, m_Team);
}