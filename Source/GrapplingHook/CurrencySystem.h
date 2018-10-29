// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include "CurrencySaveGame.h"
#include "Engine/Engine.h"
#include "CurrencySystem.generated.h"

UCLASS()
class GRAPPLINGHOOK_API ACurrencySystem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACurrencySystem();
    UFUNCTION(BlueprintCallable, Category = "Currency System")
        static int LoadCoin();
    UFUNCTION(BlueprintCallable, Category = "Currency System")
        static bool AddCoin(int value);
    UFUNCTION(BlueprintCallable, Category = "Currency System")
        static bool UseCoin(int value);
    UFUNCTION(BlueprintCallable, Category = "Currency System")
        static void ResetCoin();
    static UCurrencySaveGame* LoadCurrencySaveGame();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

    static const FString SaveSlotName;
    static const uint32 UserIndex;

private:
    static void EditCoin(int value);
    static void SaveCurrencySaveGame(UCurrencySaveGame* SaveGameInstance);
    static void CreateNewCurrencySaveGame();
	
};
