// Fill out your copyright notice in the Description page of Project Settings.

#include "HighScoreSystem.h"

const FString AHighScoreSystem::SaveSlotName = "PlayerScore";
const uint32 AHighScoreSystem::UserIndex = 0;
const int AHighScoreSystem::leaderboardSize = 5;

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
    return LoadLeaderboard()[0];
}

TArray<float> AHighScoreSystem::LoadLeaderboard()
{
    TArray<float> leaderboard;
    leaderboard.Init(0, leaderboardSize);

    UMySaveGame* LoadGameInstance = LoadHighScoreSave();

    if (LoadGameInstance->IsValidLowLevel())
    {
        leaderboard = LoadGameInstance->highScore;
    }

    /*for (int i = 0; i < leaderboardSize; i++)
    {
        GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, FString::Printf(TEXT("%d : %f"), i + 1, leaderboard[i]));
    }*/

    return leaderboard;
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

    if (!(SaveGameInstance->IsValidLowLevel()))
    {
        SaveGameInstance = Cast<UMySaveGame>(UGameplayStatics::CreateSaveGameObject(UMySaveGame::StaticClass()));
    }

    AddScoreToLeaderBoard(SaveGameInstance, score);

    UGameplayStatics::SaveGameToSlot(SaveGameInstance, SaveSlotName, UserIndex);
}

UMySaveGame* AHighScoreSystem::LoadHighScoreSave()
{
    if (UGameplayStatics::DoesSaveGameExist(SaveSlotName, UserIndex))
    {
        UMySaveGame* LoadGameInstance = Cast<UMySaveGame>(UGameplayStatics::LoadGameFromSlot(SaveSlotName, UserIndex));
        if (LoadGameInstance->IsValidLowLevel())
        {
            //GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, FString::Printf(TEXT("HighScore Found")));
            return LoadGameInstance;
        }
    }

    //GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, FString::Printf(TEXT("HighScore Not Found")));
    return nullptr;
}

void AHighScoreSystem::ResetHighScore()
{
    if(UGameplayStatics::DoesSaveGameExist(SaveSlotName, UserIndex))
    {
        UGameplayStatics::DeleteGameInSlot(SaveSlotName, UserIndex);
    }
}

void AHighScoreSystem::AddScoreToLeaderBoard(UMySaveGame* SaveGameInstance, float score) {
    SaveGameInstance->lastScore = score;
    SaveGameInstance->highScore.Add(score);
    for(int i = 0 ; i < leaderboardSize ; i++)
    {
        SaveGameInstance->highScore.Add(0.0f);
    }

    SaveGameInstance->highScore.Sort([](const int& A, const int& B) {
        return A > B;
    });

    SaveGameInstance->highScore.SetNum(leaderboardSize);
}

