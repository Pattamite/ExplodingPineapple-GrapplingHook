// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "ItemCollectionSaveGame.generated.h"

/**
 * 
 */
UCLASS()
class GRAPPLINGHOOK_API UItemCollectionSaveGame : public USaveGame
{
	GENERATED_BODY()
	
public:
	UItemCollectionSaveGame();

public:
	UPROPERTY()
		int acid;
	UPROPERTY()
		int slimeTrail;
	UPROPERTY()
		int grappleSkip;

	
	
};
