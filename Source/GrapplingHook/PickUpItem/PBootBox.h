// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PickUpItem/PickUpBox.h"
#include "PickUpItem/PSpeedItem.h"

/**
 * 
 */
class GRAPPLINGHOOK_API PBootBox : public IPickUpBox
{
public:
	PBootBox();
	~PBootBox();
	void displayEffect();
};
