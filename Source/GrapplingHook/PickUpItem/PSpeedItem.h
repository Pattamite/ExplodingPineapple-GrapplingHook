// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PickUpItemEffect.h"

/**
 * 
 */
class GRAPPLINGHOOK_API PSpeedItem : public IPickUpItemEffect
{
public:
	PSpeedItem();
	~PSpeedItem();
	void effectItem();
};
