// Fill out your copyright notice in the Description page of Project Settings.

#include "ItemEffect.h"

void UItemEffect::OnStart(APlayerCharacter * player)
{
	remainingTime = lifeTime;
	OnStart_BP(player);
}

void UItemEffect::OnTick(float deltaTime, APlayerCharacter *player)
{
	OnTick_BP(deltaTime, player);
}


void UItemEffect::OnEnd(APlayerCharacter * player)
{
	OnEnd_BP(player);
}

bool UItemEffect::DecreaseTime(float time)
{
	remainingTime -= time;
	return remainingTime <= 0;
}



void UItemEffect::OnStart_BP_Implementation(APlayerCharacter * player)
{
}

void UItemEffect::OnTick_BP_Implementation(float DeltaTime, APlayerCharacter * player)
{
}

void UItemEffect::OnEnd_BP_Implementation(APlayerCharacter * player)
{
}
