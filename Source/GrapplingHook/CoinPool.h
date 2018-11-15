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

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "--- Balancing Editables ---")
        int PoolSize = 50;

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

public: 
    // Called every frame
    virtual void Tick(float DeltaTime) override;

    
    
};
