// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "MySaveGame.generated.h"

/**
 * 
 */
UCLASS()
class GRAPPLINGHOOK_API UMySaveGame : public USaveGame
{
	GENERATED_BODY()
	
public:
	UMySaveGame();

public:

	UPROPERTY()
		FString SaveSlotName;

	UPROPERTY()
		uint32 UserIndex;

	UPROPERTY()
		float highScore;

    UPROPERTY()
        float lastScore;
		
};
