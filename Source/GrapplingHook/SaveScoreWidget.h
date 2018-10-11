// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WidgetTree.h"
#include "TextWidgetTypes.h"
#include "TextBlock.h"
#include "SaveScoreWidget.generated.h"

/**
 * 
 */

USTRUCT(BlueprintType)
struct FData {
	GENERATED_USTRUCT_BODY()

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Score")
		int scorePlayer;
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Scored")
		int savedScorePlayer;
		
};

UCLASS(BlueprintType, Blueprintable)
class GRAPPLINGHOOK_API USaveScoreWidget : public UUserWidget
{
	GENERATED_BODY()
	
private:
	bool canDisplayScore;

public:
	virtual void NativeConstruct() override;

public:
	
	UFUNCTION(BlueprintPure, Category = "Text")
	FText GetscoreText() const;
	
	UPROPERTY()
	class AGrapplingHookCharacter* characterInWorld;

	void LoadSaveGame();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stats")
	FData dataStats;

};
