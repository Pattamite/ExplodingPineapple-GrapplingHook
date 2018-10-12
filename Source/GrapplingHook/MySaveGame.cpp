// Fill out your copyright notice in the Description page of Project Settings.

#include "MySaveGame.h"
#include "GrapplingHook.h"


UMySaveGame::UMySaveGame()
{
    highScore.Init(0, 1);
    lastScore = 0;
}



