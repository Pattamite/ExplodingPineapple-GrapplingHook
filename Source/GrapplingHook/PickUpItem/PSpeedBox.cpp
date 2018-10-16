// Fill out your copyright notice in the Description page of Project Settings.

#include "PSpeedBox.h"

PSpeedBox::PSpeedBox()
{
	pickupBox = new PSpeedItem();
}

PSpeedBox::~PSpeedBox()
{
}

void PSpeedBox::displayEffect()
{
	UE_LOG(LogTemp, Warning, TEXT("Display: Speed Up! In PBootBox"));
}