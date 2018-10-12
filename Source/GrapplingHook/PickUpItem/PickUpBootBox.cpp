// Fill out your copyright notice in the Description page of Project Settings.

#include "PickUpBootBox.h"


// Sets default values for this component's properties
UPickUpBootBox::UPickUpBootBox()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	pickupBox = new PSpeedItem();
	// ...
}

void UPickUpBootBox::displayEffect()
{
	UE_LOG(LogTemp, Warning, TEXT("Speed Up!"));
}




