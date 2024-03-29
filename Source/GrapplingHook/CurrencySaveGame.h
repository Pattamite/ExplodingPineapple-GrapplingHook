// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "CurrencySaveGame.generated.h"

/**
 * 
 */
UCLASS()
class GRAPPLINGHOOK_API UCurrencySaveGame : public USaveGame
{
	GENERATED_BODY()

public:
    UCurrencySaveGame();
	
public:
    UPROPERTY()
        int coin;
    UPROPERTY()
        int mana;
    UPROPERTY()
        int premium;
};
