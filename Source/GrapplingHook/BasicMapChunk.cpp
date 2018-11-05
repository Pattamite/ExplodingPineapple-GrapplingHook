// Fill out your copyright notice in the Description page of Project Settings.

#include "BasicMapChunk.h"


// Sets default values
ABasicMapChunk::ABasicMapChunk()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
    entryPoint = FVector(-1.0f, -1.0f, -1.0f);
    exitPoint = FVector(-1.0f, -1.0f, -1.0f);
}

// Called when the game starts or when spawned
void ABasicMapChunk::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABasicMapChunk::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

const FVector ABasicMapChunk::GetSpawnLocation(FVector lastExitPoint)
{
    return lastExitPoint - entryPoint;
}
