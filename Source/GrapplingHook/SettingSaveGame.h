// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "SettingSaveGame.generated.h"

/**
 * 
 */
UCLASS()
class GRAPPLINGHOOK_API USettingSaveGame : public USaveGame
{
	GENERATED_BODY()
	
public:
    USettingSaveGame();

public:
    UPROPERTY()
        float sfxVolume;
    UPROPERTY()
        float musicVolume;
    UPROPERTY()
        bool isInvertedControl;
    UPROPERTY()
        float uiVolume;
    UPROPERTY()
        float ambientVolume;
};
