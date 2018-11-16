// Fill out your copyright notice in the Description page of Project Settings.

#include "CoinPool.h"


// Sets default values
ACoinPool::ACoinPool()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;
}


// Called every frame
void ACoinPool::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

// Called when the game starts
void ACoinPool::BeginPlay()
{
}

