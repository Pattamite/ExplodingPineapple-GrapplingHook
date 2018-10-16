// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PickUpItemEffect.h"

/**
 * 
 */
class GRAPPLINGHOOK_API PPowerItem : public IPickUpItemEffect
{
public:
	PPowerItem();
	~PPowerItem();
	void effectItem();
};
