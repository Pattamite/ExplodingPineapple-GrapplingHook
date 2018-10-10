// Fill out your copyright notice in the Description page of Project Settings.

#include "MySaveGame.h"
#include "GrapplingHook.h"


UMySaveGame::UMySaveGame()
{
	Score = 0;
	SaveSlotName = FString(TEXT("PlayerSaveSlot"));
	UserIndex = 0;

}



