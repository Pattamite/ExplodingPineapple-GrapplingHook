// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Coin.h"
#include "GameFramework/Actor.h"
#include "CoinPool.generated.h"

UCLASS()
class GRAPPLINGHOOK_API ACoinPool : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACoinPool();

	UFUNCTION(BlueprintCallable, Category = "Coin")
	ACoin* GetCoin();

	UFUNCTION(BlueprintCallable, Category = "Coin")
		ACoin* GetCoinAndActivate(FVector location);

	UPROPERTY(EditAnywhere, Category = "Object Pool")
		TSubclassOf<class ACoin> CoinClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Object Pool")
		int PoolSize = 50;

	TArray<ACoin*> CoinCollection;

	//USceneComponent* RootComponent;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	ACoin* SpawnCoin();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	
};
