// Fill out your copyright notice in the Description page of Project Settings.

#include "CoinSpawn.h"

// Sets default values
ACoinSpawn::ACoinSpawn()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ObjectPooler = CreateDefaultSubobject<UObjectPool>(TEXT("ObjectPooler"));
}

// Called when the game starts or when spawned
void ACoinSpawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACoinSpawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	Spawn();
	
	
}

void ACoinSpawn::Spawn()
{
	ACoin* Coin = ObjectPooler->GetCoin();
	if (Coin == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Can't Spawn Coin"));
		return;
	}
	Coin->SetActorLocation(FVector(10,10,10));
	Coin->SetActive(true);
	UE_LOG(LogTemp, Warning, TEXT("Spawn Coin"));
}

