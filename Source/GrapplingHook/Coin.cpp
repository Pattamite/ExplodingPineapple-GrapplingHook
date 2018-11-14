// Fill out your copyright notice in the Description page of Project Settings.

#include "Coin.h"


// Sets default values
ACoin::ACoin()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	coinTimer = 5;
}

void ACoin::SetActive(bool isActive)
{
	Active = isActive;
	SetActorHiddenInGame(!isActive);
}

bool ACoin::IsActivation()
{
	return Active;
}

// Called when the game starts or when spawned
void ACoin::BeginPlay()
{
	Super::BeginPlay();
	GetWorldTimerManager().SetTimer(CountdownTimerHandle, this, &ACoin::DisableCoin, 1.0f, true);

}

void ACoin::DisableCoin()
{
	--coinTimer;
	if (coinTimer <= 0)
	{
		GetWorldTimerManager().ClearTimer(CountdownTimerHandle);
		if (!IsActivation()) {
			Deactive();
		}
		
	}
}

void ACoin::Deactive()
{
	SetActive(false);
}

// Called every frame
void ACoin::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

