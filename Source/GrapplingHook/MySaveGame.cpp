// Fill out your copyright notice in the Description page of Project Settings.

#include "MySaveGame.h"
#include "GrapplingHook.h"


UMySaveGame::UMySaveGame()
{
	
	SaveSlotName = FString(TEXT("PlayerScore"));
	UserIndex = 0;
	score = 0;
	savedScore = 0;

}



