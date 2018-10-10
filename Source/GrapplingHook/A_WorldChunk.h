// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "A_WorldChunk.generated.h"

UCLASS()
class GRAPPLINGHOOK_API AA_WorldChunk : public AActor
{
  GENERATED_BODY()

public:
  UPROPERTY(EditAnywhere, Category="Chunk Data")
  FString TargetChunk = TEXT("NULL");
  // Sets default values for this actor's properties
  AA_WorldChunk();

protected:
  // Called when the game starts or when spawned
  virtual void BeginPlay() override;

public:
  // Called every frame
  virtual void Tick(float DeltaTime) override;

};
