// Fill out your copyright notice in the Description page of Project Settings.

#include "CurrencySystem.h"

const FString ACurrencySystem::SaveSlotName = "Currency";
const uint32 ACurrencySystem::UserIndex = 0;

// Sets default values
ACurrencySystem::ACurrencySystem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void ACurrencySystem::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACurrencySystem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

UCurrencySaveGame* ACurrencySystem::LoadCurrencySaveGame()
{
    if (!UGameplayStatics::DoesSaveGameExist(SaveSlotName, UserIndex))
    {
        //GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, FString::Printf(TEXT("Currency save Not Found")));
        CreateNewCurrencySaveGame();
    }

    UCurrencySaveGame* LoadGameInstance = Cast<UCurrencySaveGame>(UGameplayStatics::LoadGameFromSlot(SaveSlotName, UserIndex));
    if (LoadGameInstance->IsValidLowLevel())
    {
        //GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, FString::Printf(TEXT("Currency save Found")));
        return LoadGameInstance;    
    }

    return nullptr;
}

void ACurrencySystem::SaveCurrencySaveGame(UCurrencySaveGame* SaveGameInstance)
{
    if (SaveGameInstance->IsValidLowLevel())
    {
        UGameplayStatics::SaveGameToSlot(SaveGameInstance, SaveSlotName, UserIndex);
    }
}

void ACurrencySystem::CreateNewCurrencySaveGame()
{
    //GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, FString::Printf(TEXT("Create new Currency save")));
    UCurrencySaveGame* SaveGameInstance = Cast<UCurrencySaveGame>(UGameplayStatics::CreateSaveGameObject(UCurrencySaveGame::StaticClass()));
    SaveCurrencySaveGame(SaveGameInstance);
}

void ACurrencySystem::EditCoin(int value)
{
    UCurrencySaveGame* SaveGameInstance = LoadCurrencySaveGame();

    if (SaveGameInstance->IsValidLowLevel())
    {
        SaveGameInstance->coin += value;
        SaveCurrencySaveGame(SaveGameInstance);
    }
}

int ACurrencySystem::LoadCoin()
{
    int coin = 0;
    UCurrencySaveGame* LoadGameInstance = LoadCurrencySaveGame();
    if (LoadGameInstance->IsValidLowLevel())
    {
        coin = LoadGameInstance->coin;
    }

    return coin;
}

bool ACurrencySystem::AddCoin(int value)
{
    if (value >= 0)
    {
        EditCoin(value);
        return true;
    }
    else
    {
        return false;
    }
}

bool ACurrencySystem::UseCoin(int value)
{
    if (LoadCoin() >= value && value >= 0)
    {
        EditCoin(-value);
        return true;
    }
    else
    {
        return false;
    }
}

void ACurrencySystem::ResetCoin()
{
    CreateNewCurrencySaveGame();
}




