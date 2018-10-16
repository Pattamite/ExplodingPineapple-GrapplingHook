// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Delegates/Delegate.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include "PlayerCharacter.h"
#include "Engine/Engine.h"
#include "HighScoreSystem.h"
#include "GrapplingHookGameMode.generated.h"

/**
 * The GameMode defines the game being played. It governs the game rules, scoring, what actors
 * are allowed to exist in this game type, and who may enter the game.
 *
 * This game mode just sets the default pawn to be the MyCharacter asset, which is a subclass of GrapplingHookCharacter
 */
UCLASS(minimalapi)
class AGrapplingHookGameMode : public AGameModeBase
{
    GENERATED_BODY()
public:
    AGrapplingHookGameMode();
};
