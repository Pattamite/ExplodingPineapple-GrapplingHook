// Fill out your copyright notice in the Description page of Project Settings.

#include "CoinPool.h"


// Sets default values
ACoinPool::ACoinPool()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("ROOT COMPONENT"));

}


// Called every frame
void ACoinPool::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

ACoin * ACoinPool::GetCoin()
{
	for (ACoin* coin : CoinCollection) {
		if (!coin->IsActivation())
			return coin;
	}
	return SpawnCoin();
}

ACoin * ACoinPool::GetCoinAndActivate(FVector location)
{
	ACoin* Coin = GetCoin();
	Coin->SetActorLocation(location);
	Coin->SetActive(true);
	return Coin;
}

// Called when the game starts
void ACoinPool::BeginPlay()
{
	Super::BeginPlay();
	if (CoinClass != nullptr) {
		for (int i = 0; i < PoolSize; i++) {
			SpawnCoin();
		}
	}
	// ...

}

ACoin * ACoinPool::SpawnCoin()
{
	UWorld* const World = GetWorld();
	ACoin* coin = World->SpawnActor<ACoin>(CoinClass, FVector().ZeroVector, FRotator().ZeroRotator);
	coin->SetActive(false);
	//coin->AttachToActor(this, FAttachmentTransformRules::KeepWorldTransform);
	//coin->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepWorldTransform);
	CoinCollection.Add(coin);
	//coin->AttachRootComponentToActor(this);
	return coin;
}

