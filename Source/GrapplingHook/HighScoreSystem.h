// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MySaveGame.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/Engine.h"
#include "HighScoreSystem.generated.h"

UCLASS()
class GRAPPLINGHOOK_API AHighScoreSystem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHighScoreSystem();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
    UFUNCTION(BlueprintCallable, Category = "Highscore System")
        static float LoadLastScore();
    UFUNCTION(BlueprintCallable, Category = "Highscore System")
        static float LoadHighScore();
    UFUNCTION(BlueprintCallable, Category = "Highscore System")
        static void SaveScore(float score);
    UFUNCTION(BlueprintCallable, Category = "Highscore System")
        static void ResetHighScore();
    static UMySaveGame* LoadHighScoreSave();

private:
    static const FString SaveSlotName;
    static const uint32 UserIndex;

};
