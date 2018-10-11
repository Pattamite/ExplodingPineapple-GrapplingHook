// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/GameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "PlayerCharacter.h"
#include "Engine/Engine.h"
#include "TestGameMode.generated.h"

/**
 * 
 */
UCLASS()
class GRAPPLINGHOOK_API ATestGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	ATestGameMode();
    virtual void Tick(float DeltaSeconds) override;
    virtual void BeginPlay() override;

    UFUNCTION(BlueprintCallable, Category = "Score")
        float GetPlayerDistance();

private:
    APawn* player = nullptr;
    float playerStartPosition = 0.0f;

};
