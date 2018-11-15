// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Delegates/Delegate.h"
#include "GameFramework/Actor.h"
#include "GameFramework/GameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "PlayerCharacter.h"
#include "Engine/Engine.h"
#include "HighScoreSystem.h"
#include "CurrencySystem.h"
#include "TestGameMode.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FFloatGameModeDelegate, float, value);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FVoidGameModeDelegate);

UENUM(BlueprintType)
enum class EGameOverEnum : uint8
{
    GameOver_Default    UMETA(DisplayName = "Default"),
    GameOver_Pitfall	UMETA(DisplayName = "Pitfall"),
    GameOver_Chaser 	UMETA(DisplayName = "Chaser"),
    GameOver_Water      UMETA(DisplayName = "Water")
};

UCLASS()
class GRAPPLINGHOOK_API ATestGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	ATestGameMode();
    virtual void Tick(float DeltaSeconds) override;
    virtual void BeginPlay() override;
    UFUNCTION(BlueprintCallable, Category = "Score")
        float GetPlayerDistance();
    UFUNCTION(BlueprintCallable, Category = "Score")
        float GetPlayerScore();
    UFUNCTION(BlueprintCallable, Category = "Score")
        void AddPlayerScore(float value);

    UFUNCTION(BlueprintCallable, Category = "Currency")
        void AddCoin(int value);
    UFUNCTION(BlueprintCallable, Category = "Currency")
        int GetCoin();

    UFUNCTION(BlueprintCallable, Category = "Game State")
        bool IsGamePause();
    UFUNCTION(BlueprintCallable, Category = "Game State")
        void SetGamePause(bool isPause);

    UFUNCTION(BlueprintCallable, Category = "Debug")
        void GameOver(EGameOverEnum condition);


    UPROPERTY(BlueprintAssignable, Category = "Score Event")
        FFloatGameModeDelegate OnPassHighScore;
    UPROPERTY(BlueprintAssignable, Category = "Score Event")
        FFloatGameModeDelegate OnPassHighScoreFirstTime;

    UPROPERTY(BlueprintAssignable, Category = "Game Event")
        FVoidGameModeDelegate OnGameOver;
    UPROPERTY(BlueprintAssignable, Category = "Game Event")
        FVoidGameModeDelegate OnGameOverByPitfall;
    UPROPERTY(BlueprintAssignable, Category = "Game Event")
        FVoidGameModeDelegate OnGameOverByChaser;
    UPROPERTY(BlueprintAssignable, Category = "Game Event")
        FVoidGameModeDelegate OnGameOverByWater;

protected:
    UPROPERTY(BlueprintReadOnly)
        float playerStartPosition = 0.0f;
    UPROPERTY(BlueprintReadWrite)
        float scorePerDistance = 0.1f;

private:
    void SetHighScore();
    void CheckHighScore();
    
    APawn* player = nullptr;
    
    float currentBonusScore = 0.0f;

    float currentHighScore = 0.0f;
    bool isPassHighScore = false;
    bool isPassHighScoreFirstTime = false;
    bool isGameOver = false;
    int collectedCoin = 0;
    bool isPause = false;
};
