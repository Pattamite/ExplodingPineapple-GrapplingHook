// Fill out your copyright notice in the Description page of Project Settings.

#include "HighScoreSystem.h"


// Sets default values
AHighScoreSystem::AHighScoreSystem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void AHighScoreSystem::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AHighScoreSystem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

float AHighScoreSystem::LoadHighScore()
{
    float highScore = 0;
    UMySaveGame* LoadGameInstance = LoadHighScoreSave();

    if (LoadGameInstance->IsValidLowLevel())
    {
        highScore = LoadGameInstance->highScore;
    }
    return highScore;
}

float AHighScoreSystem::LoadLastScore()
{
    float lastScore = 0;
    UMySaveGame* LoadGameInstance = LoadHighScoreSave();

    if (LoadGameInstance->IsValidLowLevel())
    {
        lastScore = LoadGameInstance->lastScore;
    }
    return lastScore;
}

void AHighScoreSystem::SaveScore(float score)
{
    UMySaveGame* SaveGameInstance = LoadHighScoreSave();

    if (SaveGameInstance->IsValidLowLevel())
    {
        SaveGameInstance->lastScore = score;
        if (score > SaveGameInstance->highScore)
        {
            //GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, FString::Printf(TEXT("New High Score")));
            SaveGameInstance->highScore = score;
        }
        
    }
    else {
        SaveGameInstance = Cast<UMySaveGame>(UGameplayStatics::CreateSaveGameObject(UMySaveGame::StaticClass()));
        SaveGameInstance->lastScore = score;
        SaveGameInstance->highScore = score;
    }

    UGameplayStatics::SaveGameToSlot(SaveGameInstance, SaveGameInstance->SaveSlotName, SaveGameInstance->UserIndex);
}

UMySaveGame* AHighScoreSystem::LoadHighScoreSave()
{
    UMySaveGame* LoadGameInstance = Cast<UMySaveGame>(UGameplayStatics::CreateSaveGameObject(UMySaveGame::StaticClass()));

    if (LoadGameInstance->IsValidLowLevel() &&
        UGameplayStatics::DoesSaveGameExist(LoadGameInstance->SaveSlotName, LoadGameInstance->UserIndex))
    {
        LoadGameInstance = Cast<UMySaveGame>(UGameplayStatics::LoadGameFromSlot(LoadGameInstance->SaveSlotName, LoadGameInstance->UserIndex));
        if (LoadGameInstance->IsValidLowLevel())
        {
            GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, FString::Printf(TEXT("HighScore Found")));
            return LoadGameInstance;
        }
    }

    GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, FString::Printf(TEXT("HighScore Not Found")));
    return nullptr;
}

