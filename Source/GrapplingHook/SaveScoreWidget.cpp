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

FText USaveScoreWidget::GetscoreText() const {

	/*if (characterInWorld == nullptr) {
		return FText::FromString(FString(TEXT("Score: --")));
	}
	else {
		FString scoreWidget = FString(TEXT("Score: "));
		//scoreWidget.AppendInt(characterInWorld->characterStats.score);

		return FText::FromString(scoreWidget);
	}*/
	
	FString scoreSave = FString(TEXT("Score: "));
	scoreSave.AppendInt(dataStats.scorePlayer);
	return FText::FromString(scoreSave);


};

void USaveScoreWidget::LoadSaveGame()
{
	if (this->IsValidLowLevel()) {
        float highScore = AHighScoreSystem::LoadHighScore();
        dataStats.scorePlayer = highScore;
        dataStats.savedScorePlayer = highScore;
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, FString::Printf(TEXT("LOADsave")));
		/*const FString SaveSlotName = FString(TEXT("PlayerScore"));
		if (UGameplayStatics::DoesSaveGameExist(SaveSlotName, 0)) {
			UMySaveGame* LoadGameInstance = Cast<UMySaveGame>(UGameplayStatics::CreateSaveGameObject(UMySaveGame::StaticClass()));
			

			if (LoadGameInstance->IsValidLowLevel()) {
				LoadGameInstance = Cast<UMySaveGame>(UGameplayStatics::LoadGameFromSlot(LoadGameInstance->SaveSlotName, LoadGameInstance->UserIndex));
				
				if (LoadGameInstance->score > LoadGameInstance->savedScore) 
				{
					dataStats.scorePlayer = LoadGameInstance->score;
					LoadGameInstance->savedScore = LoadGameInstance->score;
					UGameplayStatics::SaveGameToSlot(LoadGameInstance, LoadGameInstance->SaveSlotName, LoadGameInstance->UserIndex);
				}
				else {
					dataStats.scorePlayer = LoadGameInstance->savedScore;
				}

				GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, FString::Printf(TEXT("LOADsave")));
			}
			else {

				class UMySaveGame* LoadGameInstance_2 = Cast<UMySaveGame>(UGameplayStatics::CreateSaveGameObject(UMySaveGame::StaticClass()));

				if (!LoadGameInstance_2)
					return;
				else {
					LoadGameInstance = Cast<UMySaveGame>(UGameplayStatics::LoadGameFromSlot(LoadGameInstance->SaveSlotName, LoadGameInstance->UserIndex));

					dataStats.scorePlayer = LoadGameInstance->score;
					if (dataStats.scorePlayer > dataStats.savedScorePlayer) {
						dataStats.savedScorePlayer = dataStats.scorePlayer;
						LoadGameInstance->savedScore = dataStats.savedScorePlayer;
						UGameplayStatics::SaveGameToSlot(LoadGameInstance, LoadGameInstance->SaveSlotName, LoadGameInstance->UserIndex);
					}
					dataStats.savedScorePlayer = LoadGameInstance->savedScore;
					
					GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, FString::Printf(TEXT("LOADsave2")));

				}

			}
		}
		else {
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, FString::Printf(TEXT("No save game found")));
		}*/

	}

}
