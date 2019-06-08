// Fill out your copyright notice in the Description page of Project Settings.


#include "Vehicle.h"

AVehicle::AVehicle() {}

void AVehicle::BeginPlay()
{
	Super::BeginPlay();

	m_UnitType = UnitType::VE_Tank;
}