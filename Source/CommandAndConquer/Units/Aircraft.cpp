// Fill out your copyright notice in the Description page of Project Settings.


#include "Aircraft.h"
#include "Components/BoxComponent.h"

AAircraft::AAircraft()
{
	m_LivingUnitCollider->SetupAttachment(RootComponent);
}

void AAircraft::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (m_IsFlying)
	{
		if (GetMesh()->GetComponentLocation().Z < m_FlightHeight)
		{
			FVector position = GetMesh()->GetComponentLocation();
			position.Z += (m_HorizontalSpeed * DeltaTime);

			if (position.Z >= m_FlightHeight)
			{
				position.Z = m_FlightHeight;
			}
			//SetActorLocation(position);
			//GetMesh()->SetComponentLocation(position);
			GetMesh()->SetWorldLocation(position);
			
			FVector boundryposition = m_LivingUnitCollider->GetComponentLocation();
			position.Z += (m_HorizontalSpeed * DeltaTime);
			m_LivingUnitCollider->SetWorldLocation(position);
		}
	}
}
