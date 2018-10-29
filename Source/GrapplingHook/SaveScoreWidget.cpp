// Fill out your copyright notice in the Description page of Project Settings.

#include "SaveScoreWidget.h"
#include "MySaveGame.h"
#include "EngineUtils.h"
#include "GrapplingHook.h"
#include "GrapplingHookCharacter.h"

void USaveScoreWidget::NativeConstruct() {

	Super::NativeConstruct();

	LoadSaveGame();

}

void USaveScoreWidget::LoadSaveGame()
{
	if (this->IsValidLowLevel()) {
        lastScore = AHighScoreSystem::LoadLastScore();
        highScore = AHighScoreSystem::LoadHighScore();
        coin = ACurrencySystem::LoadCoin();
	}

}
