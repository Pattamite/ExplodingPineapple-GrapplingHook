// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "PickUpItemEffect.h"
#include "PickUpBox.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UPickUpBox : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class GRAPPLINGHOOK_API IPickUpBox
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	IPickUpItemEffect* getEffectBox();
	void activateEffectBox();
	void setEffectBox(IPickUpItemEffect *pickupBox);
	virtual void displayEffect() = 0;

private:
	IPickUpItemEffect* pickupBox;

};
