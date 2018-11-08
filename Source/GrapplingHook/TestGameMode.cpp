// Fill out your copyright notice in the Description page of Project Settings.

#include "TestGameMode.h"
#include "PlayerCharacter.h"


ATestGameMode::ATestGameMode()
{
	// Set default pawn class to our character
	DefaultPawnClass = APlayerCharacter::StaticClass();
    PrimaryActorTick.bStartWithTickEnabled = true;
    PrimaryActorTick.bCanEverTick = true;
}

void ATestGameMode::BeginPlay()
{
    player = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
    if (player->IsValidLowLevel())
    {
        playerStartPosition = player->GetActorLocation().X;
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("TestGameMode : Cannot get player pawn"));
    }
    SetHighScore();

    Super::BeginPlay();

}

void ATestGameMode::Tick(float DeltaSeconds)
{
    CheckHighScore();
    Super::Tick(DeltaSeconds);
    
}

float ATestGameMode::GetPlayerDistance()
{
    if (player->IsValidLowLevel())
    {
        return player->GetActorLocation().X - playerStartPosition;
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("TestGameMode : Cannot get player pawn"));
        return -99999.0f;
    }
}

float ATestGameMode::GetPlayerScore()
{
    return (GetPlayerDistance() * scorePerDistance) + currentBonusScore;
}

void ATestGameMode::AddPlayerScore(float value)
{
    currentBonusScore += value;
}

void ATestGameMode::SetHighScore()
{
    //TODO Get real high score
    currentHighScore = AHighScoreSystem::LoadHighScore();
    isPassHighScore = false;
    isPassHighScoreFirstTime = false;
}

void ATestGameMode::CheckHighScore()
{
    float currentScore = GetPlayerScore();

    if (!isPassHighScore && currentScore > currentHighScore)
    {
        OnPassHighScore.Broadcast(currentScore);
        isPassHighScore = true;
        if (!isPassHighScoreFirstTime) 
        {
            OnPassHighScoreFirstTime.Broadcast(currentScore);
            isPassHighScoreFirstTime = true;
        }
    }
    else if (isPassHighScore && currentScore <= currentHighScore) {
        isPassHighScore = false;
    }
}

void ATestGameMode::AddCoin(int value)
{
    collectedCoin += value;
}

void ATestGameMode::GameOver(EGameOverEnum condition)
{
    if (!isGameOver)
    {
        isGameOver = true;
        ACurrencySystem::AddCoin(collectedCoin);
        AHighScoreSystem::SaveScore(GetPlayerScore());

        switch (condition)
        {
            case EGameOverEnum::GameOver_Default:
                OnGameOver.Broadcast();
                break;
            case EGameOverEnum::GameOver_Pitfall:
                OnGameOverByPitfall.Broadcast();
                break;
            case EGameOverEnum::GameOver_Chaser:
                OnGameOverByChaser.Broadcast();
                break;
            default:
                OnGameOver.Broadcast();
                break;
        } 
    }
}