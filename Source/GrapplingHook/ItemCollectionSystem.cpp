// Fill out your copyright notice in the Description page of Project Settings.

#include "ItemCollectionSystem.h"

const FString AItemCollectionSystem::SaveSlotName = "ItemCollection";
const uint32 AItemCollectionSystem::UserIndex = 0;
int grappleSkip = 0;
int slimeTrail = 0;
int acid = 0;
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
		UE_LOG(LogTemp, Warning, TEXT("Not Found saved"));
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
	SaveItemCollectionSaveGame(SaveGameInstance);
}

void AItemCollectionSystem::AddAcid()
{
	UItemCollectionSaveGame* LoadGameInstance = LoadItemCollectionSaveGame();
	if (LoadGameInstance->IsValidLowLevel()) {
		acid = LoadGameInstance->acid;
		if (LoadGameInstance->acid == 0)
		{
			UE_LOG(LogTemp, Warning, TEXT("Acid Added"));
			acid = 1;
		}	
	}
	SaveAllItemCollection();
}

void AItemCollectionSystem::AddSlimeTrail()
{

	UItemCollectionSaveGame* LoadGameInstance = LoadItemCollectionSaveGame();
	if (LoadGameInstance->IsValidLowLevel()) {
		slimeTrail = LoadGameInstance->slimeTrail;
		if (LoadGameInstance->slimeTrail == 0)
		{
			UE_LOG(LogTemp, Warning, TEXT("slimeTrail Added"));
			slimeTrail = 1;
		}
	}
	SaveAllItemCollection();
}

void AItemCollectionSystem::AddGrappleSkip()
{
	
	UItemCollectionSaveGame* LoadGameInstance = LoadItemCollectionSaveGame();
	if (LoadGameInstance->IsValidLowLevel()) {
		grappleSkip = LoadGameInstance->grappleSkip;
		if (LoadGameInstance->grappleSkip == 0)
		{
			UE_LOG(LogTemp, Warning, TEXT("grappleSkip Added"));
			grappleSkip = 1;
		}
	}
	SaveAllItemCollection();
}

void AItemCollectionSystem::SaveAllItemCollection()
{
	UItemCollectionSaveGame* LoadGameInstance = LoadItemCollectionSaveGame();
	UItemCollectionSaveGame* SaveGameInstance = Cast<UItemCollectionSaveGame>(UGameplayStatics::CreateSaveGameObject(UItemCollectionSaveGame::StaticClass()));
	SaveGameInstance->acid = acid;
	SaveGameInstance->slimeTrail = slimeTrail;
	SaveGameInstance->grappleSkip = grappleSkip;

	UE_LOG(LogTemp, Warning, TEXT("Saved"));
	SaveItemCollectionSaveGame(SaveGameInstance);
}

bool AItemCollectionSystem::AcidIsValid()
{
	UItemCollectionSaveGame* LoadGameInstance = LoadItemCollectionSaveGame();
	if (LoadGameInstance->acid == 1)
		return true;
	else
		return false;
}

bool AItemCollectionSystem::SlimeTrailIsValid()
{
	UItemCollectionSaveGame* LoadGameInstance = LoadItemCollectionSaveGame();
	if (LoadGameInstance->slimeTrail == 1)
		return true;
	else
		return false;
}

bool AItemCollectionSystem::GrappleSkipIsValid()
{
	UItemCollectionSaveGame* LoadGameInstance = LoadItemCollectionSaveGame();
	if (LoadGameInstance->grappleSkip == 1)
		return true;
	else
		return false;
}

void AItemCollectionSystem::ResetItemsInShopStore()
{
	acid = 0;
	slimeTrail = 0;
	grappleSkip = 0;

	SaveAllItemCollection();
}
