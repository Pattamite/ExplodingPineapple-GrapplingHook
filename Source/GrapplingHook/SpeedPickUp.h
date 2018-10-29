// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PickUpStructure.h"
#include "Components/ShapeComponent.h"
#include "Components/BoxComponent.h"
#include "SpeedPickUp.generated.h"

/**
 * 
 */
UCLASS()
class GRAPPLINGHOOK_API ASpeedPickUp : public APickUpStructure
{
	GENERATED_BODY()
	
public:
	ASpeedPickUp();
	
	void effectItems();
	
	
};
