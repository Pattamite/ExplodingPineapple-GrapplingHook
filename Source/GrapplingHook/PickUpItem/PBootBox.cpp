// Fill out your copyright notice in the Description page of Project Settings.

#include "PBootBox.h"

PBootBox::PBootBox()
{
	pickupBox = new PSpeedItem();
}

PBootBox::~PBootBox()
{
}

void PBootBox::displayEffect()
{
	UE_LOG(LogTemp, Warning, TEXT("Display: Speed Up! In PBootBox"));
}