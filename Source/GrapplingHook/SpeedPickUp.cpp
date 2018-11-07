// Fill out your copyright notice in the Description page of Project Settings.

#include "SpeedPickUp.h"

ASpeedPickUp::ASpeedPickUp() 
{
	
}

void ASpeedPickUp::effectItems()
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Speed PickUp effect!"));
}

