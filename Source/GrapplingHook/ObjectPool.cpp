// Fill out your copyright notice in the Description page of Project Settings.

#include "ObjectPool.h"
#include "Engine.h"

// Sets default values for this component's properties
UObjectPool::UObjectPool()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


ACoin * UObjectPool::GetCoin()
{
	for (ACoin* coin : CoinCollection) {
		if (!coin->IsActivation())
			return coin;
	}
	return nullptr;
}

// Called when the game starts
void UObjectPool::BeginPlay()
{
	Super::BeginPlay();
	if (CoinClass != nullptr) {
		UWorld* const World = GetWorld();
		for (int i = 0; i < PoolSize; i++) {
			ACoin* coin = World->SpawnActor<ACoin>(CoinClass, FVector().ZeroVector, FRotator().ZeroRotator);
			coin->SetActive(false);
			CoinCollection.Add(coin);
		}
	}
	// ...
	
}


// Called every frame
void UObjectPool::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

