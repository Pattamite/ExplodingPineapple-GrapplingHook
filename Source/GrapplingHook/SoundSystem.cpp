// Fill out your copyright notice in the Description page of Project Settings.

#include "SoundSystem.h"


ASoundSystem* ASoundSystem::instance = nullptr;

// Sets default values
ASoundSystem::ASoundSystem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    instance = this;
}

// Called when the game starts or when spawned
void ASoundSystem::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASoundSystem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASoundSystem::PlaySoundEffectAtLocation(ESoundEffectEnum sound, FVector location)
{
    if (instance->IsValidLowLevel())
    {
        instance->PlaySoundEffectAtLocationInstance(sound, location);
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("SoundSystem : SoundSystem instance not found in level."));
    }
}

void ASoundSystem::PlayUiSound(EUiSoundEnum sound)
{
    if (instance->IsValidLowLevel())
    {
        instance->PlayUiSoundInstance(sound);
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("SoundSystem : SoundSystem instance not found in level."));
    }
}

