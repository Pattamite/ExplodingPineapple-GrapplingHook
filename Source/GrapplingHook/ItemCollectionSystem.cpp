// Fill out your copyright notice in the Description page of Project Settings.

#include "ItemCollectionSystem.h"

const FString AItemCollectionSystem::SaveSlotName = "ItemCollection";
const uint32 AItemCollectionSystem::UserIndex = 0;

// Sets default values
AItemCollectionSystem::AItemCollectionSystem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AItemCollectionSystem::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AItemCollectionSystem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

UItemCollectionSaveGame* AItemCollectionSystem::LoadItemCollectionSaveGame()
{
	if (!UGameplayStatics::DoesSaveGameExist(SaveSlotName, UserIndex))
	{
		CreateNewItemCollectionSaveGame();
	}
	UItemCollectionSaveGame* LoadGameInstace = Cast<UItemCollectionSaveGame>(UGameplayStatics::LoadGameFromSlot(SaveSlotName, UserIndex));
	if (LoadGameInstace->IsValidLowLevel())
	{
		return LoadGameInstace;
	}

	return nullptr;
}

void AItemCollectionSystem::SaveItemCollectionSaveGame(UItemCollectionSaveGame* SaveGameInstance)
{
	if (SaveGameInstance->IsValidLowLevel())
	{
		UGameplayStatics::SaveGameToSlot(SaveGameInstance, SaveSlotName, UserIndex);
	}
}

void AItemCollectionSystem::CreateNewItemCollectionSaveGame()
{
	UItemCollectionSaveGame* SaveGameInstance = Cast<UItemCollectionSaveGame>(UGameplayStatics::CreateSaveGameObject(UItemCollectionSaveGame::StaticClass()));
}
