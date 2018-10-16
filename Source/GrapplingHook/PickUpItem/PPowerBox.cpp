// Fill out your copyright notice in the Description page of Project Settings.

#include "PPowerBox.h"

PPowerBox::PPowerBox()
{
	pickupBox = new PPowerItem();
}

PPowerBox::~PPowerBox()
{
}

void PPowerBox::displayEffect()
{
	UE_LOG(LogTemp, Warning, TEXT("Display: Power UP! In PBootBox"));
}