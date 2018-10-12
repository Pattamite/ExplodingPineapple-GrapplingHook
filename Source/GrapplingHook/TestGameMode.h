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
#include "TestGameMode.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FFloatGameModeDelegate, float, value);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FVoidGameModeDelegate);

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

    UPROPERTY(BlueprintAssignable, Category = "Score Event")
        FFloatGameModeDelegate OnPassHighScore;
    UPROPERTY(BlueprintAssignable, Category = "Score Event")
        FFloatGameModeDelegate OnPassHighScoreFirstTime;

    UPROPERTY(BlueprintAssignable, Category = "Game Event")
        FVoidGameModeDelegate OnGameOver;

private:
    void SetHighScore();
    void CheckHighScore();
    UFUNCTION(BlueprintCallable, Category = "Debug")
        void GameOver();
    

    APawn* player = nullptr;
    float playerStartPosition = 0.0f;
    UPROPERTY(EditAnywhere)
        float scorePerDistance = 0.1f;
    float currentBonusScore = 0.0f;

    float currentHighScore = 0.0f;
    bool isPassHighScore = false;
    bool isPassHighScoreFirstTime = false;
};
