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

void AItemCollectionSystem::LoadAllItemCollection()
{
	UItemCollectionSaveGame* LoadGameInstance = LoadItemCollectionSaveGame();
	if (LoadGameInstance->IsValidLowLevel()) {
		acid = LoadGameInstance->acid;
		slimeTrail = LoadGameInstance->slimeTrail;
		grappleSkip = LoadGameInstance->grappleSkip;
	}
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

	LoadAllItemCollection();
	if (acid == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Acid Added"));
		acid = 1;
	}
	SaveAllItemCollection();
}

void AItemCollectionSystem::AddSlimeTrail()
{

	LoadAllItemCollection();
	if (slimeTrail == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("slimeTrail Added"));
		slimeTrail = 1;
	}
	SaveAllItemCollection();
}

void AItemCollectionSystem::AddGrappleSkip()
{

	LoadAllItemCollection();
	if (grappleSkip == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("grappleSkip Added"));
		grappleSkip = 1;
	}
	SaveAllItemCollection();
}

void AItemCollectionSystem::RemoveAcid()
{
	LoadAllItemCollection();
	acid = 0;
	UE_LOG(LogTemp, Warning, TEXT("acid removed"));
	SaveAllItemCollection();
}

void AItemCollectionSystem::RemoveSlimeTrail()
{
	LoadAllItemCollection();
	slimeTrail = 0;
	UE_LOG(LogTemp, Warning, TEXT("slimeTrail removed"));
	SaveAllItemCollection();
}

void AItemCollectionSystem::RemoveGrappleSkip()
{
	LoadAllItemCollection(); 
	grappleSkip = 0;
	UE_LOG(LogTemp, Warning, TEXT("grappleSkip removed"));
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