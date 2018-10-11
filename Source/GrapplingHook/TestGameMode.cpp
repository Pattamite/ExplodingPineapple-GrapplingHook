// Fill out your copyright notice in the Description page of Project Settings.

#include "TestGameMode.h"
#include "PlayerCharacter.h"


ATestGameMode::ATestGameMode()
{
	// Set default pawn class to our character
	DefaultPawnClass = APlayerCharacter::StaticClass();
}

void ATestGameMode::BeginPlay()
{
    player = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
    if (player->IsValidLowLevel())
    {
        playerStartPosition = player->GetActorLocation().X;
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("TestGameMode : Cannot get player pawn"));
    }

    Super::BeginPlay();

}

void ATestGameMode::Tick(float DeltaSeconds)
{

    Super::Tick(DeltaSeconds);
}

float ATestGameMode::GetPlayerDistance()
{
    if (player->IsValidLowLevel())
    {
        return player->GetActorLocation().X - playerStartPosition;
    }
    else
    {
        return -99999.0f;
    }
}

