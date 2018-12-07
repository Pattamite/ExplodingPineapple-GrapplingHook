// Fill out your copyright notice in the Description page of Project Settings.

#include "GameMusicSystem.h"

AGameMusicSystem* AGameMusicSystem::instance = nullptr;
bool AGameMusicSystem::updateFlag = false;

// Sets default values
AGameMusicSystem::AGameMusicSystem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    instance = this;
}

// Called when the game starts or when spawned
void AGameMusicSystem::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGameMusicSystem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGameMusicSystem::ChangeGameMusicState(EMusicStateEnum state)
{
    if (instance->IsValidLowLevel())
    {
        instance->ChangeGameMusicStateInstance(state);
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("GameMusicSystem : GameMusicSystem instance not found in level."));
    }
}

void AGameMusicSystem::ChangeAmbientSoundState(EAmbientSoundStateEnum state)
{
    if (instance->IsValidLowLevel())
    {
        instance->ChangeAmbientSoundStateInstance(state);
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("GameMusicSystem : GameMusicSystem instance not found in level."));
    }
}

bool AGameMusicSystem::GetMusicUpdateFlag()
{
    return updateFlag;
}

void AGameMusicSystem::SetMusicUpdateFlag(bool value)
{
    updateFlag = value;
}

