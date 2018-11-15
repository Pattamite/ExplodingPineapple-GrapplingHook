// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ObjectPool.h"
#include "GameFramework/Actor.h"
#include "CoinSpawn.generated.h"

UCLASS()
class GRAPPLINGHOOK_API ACoinSpawn : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACoinSpawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category = "Spawner")
		UObjectPool* ObjectPooler;

	void Spawn();
	
};
