// Fill out your copyright notice in the Description page of Project Settings.

#include "SaveScoreWidget.h"
#include "MySaveGame.h"
#include "EngineUtils.h"
#include "GrapplingHook.h"
#include "GrapplingHookCharacter.h"

void USaveScoreWidget::NativeConstruct() {

	Super::NativeConstruct();

	for (TActorIterator<AGrapplingHookCharacter> ActorItr(GetWorld()); ActorItr; ++ActorItr) {

		class AGrapplingHookCharacter* FoundCharacter = *ActorItr;

		if (FoundCharacter != nullptr) {
			if (characterInWorld != FoundCharacter) {
				characterInWorld = FoundCharacter;
			}
		}
	}

	canDisplayScore = false;

}

FText USaveScoreWidget::GetscoreText() const {

	if (characterInWorld == nullptr) {
		return FText::FromString(FString(TEXT("Score: --")));
	}
	else {
		FString scoreWidget = FString(TEXT("Score: "));
		scoreWidget.AppendInt(characterInWorld->characterStats.score);

		return FText::FromString(scoreWidget);
	}
};