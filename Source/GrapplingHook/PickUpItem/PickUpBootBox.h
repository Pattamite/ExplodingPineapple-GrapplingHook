// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PickUpItem/PickUpBox.h"
#include "PickUpItem/PSpeedItem.h"
#include "PickUpBootBox.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GRAPPLINGHOOK_API UPickUpBootBox : public UActorComponent, public IPickUpBox
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPickUpBootBox();

/*protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	*/
public:	
	// Called every frame
	//virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void displayEffect();
		
	
};
