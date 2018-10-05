// Fill out your copyright notice in the Description page of Project Settings.

#include "MyHUDSaveScore.h"
#include "MySaveGame.h"
#include "Runtime/UMG/Public/UMG.h"
#include "Runtime/UMG/Public/UMGStyle.h"
#include "Runtime/UMG/Public/Slate/SObjectWidget.h"
#include "Runtime/UMG/Public/IUMGModule.h"
#include "Runtime/UMG/Public/Blueprint/UserWidget.h"
#include "SaveScoreWidget.h"
#include "UObject/ConstructorHelpers.h"

AMyHUDSaveScore::AMyHUDSaveScore() {

	static ConstructorHelpers::FClassFinder<USaveScoreWidget> WidgetAsset(TEXT("/Game/2DSideScrollerCPP/UI/BP_SaveScore"));
	
	if (WidgetAsset.Succeeded()) {
		SaveWidgetClass = WidgetAsset.Class;
	}

}

void AMyHUDSaveScore::BeginPlay() {
	
	Super::BeginPlay();
	ActiveWidget();
}

void AMyHUDSaveScore::ActiveWidget() {

	class UWorld* const world = GetWorld();

	if(world != nullptr) {
		if (SaveWidgetClass != NULL) {

			SaveUI = CreateWidget<USaveScoreWidget>(world, SaveWidgetClass);
			
			if (SaveUI != NULL) {
				SaveUI->AddToViewport();
			}
		}
	}
}


