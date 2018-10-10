// Fill out your copyright notice in the Description page of Project Settings.

#include "TestGameMode.h"
#include "PlayerCharacter.h"


ATestGameMode::ATestGameMode()
{
	// Set default pawn class to our character
	DefaultPawnClass = APlayerCharacter::StaticClass();
}

