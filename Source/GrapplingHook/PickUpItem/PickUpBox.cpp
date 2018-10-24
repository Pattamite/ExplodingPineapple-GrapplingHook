// Fill out your copyright notice in the Description page of Project Settings.

#include "PickUpBox.h"


// Add default functionality here for any IPickUpBox functions that are not pure virtual.

IPickUpItemEffect* IPickUpBox::getEffectBox()
{
	return pickupBox;
}

void IPickUpBox::activateEffectBox()
{
	pickupBox->effectItem();
}

void IPickUpBox::setEffectBox(IPickUpItemEffect *newpickupBox)
{
	pickupBox = newpickupBox;
}

