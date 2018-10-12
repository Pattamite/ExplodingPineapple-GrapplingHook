// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PickUpItem/PickUpBox.h"
#include "PickUpItem/PPowerItem.h"

/**
 * 
 */
class GRAPPLINGHOOK_API PPowerBox : public IPickUpBox
{
public:
	PPowerBox();
	~PPowerBox();
	void displayEffect();
};
