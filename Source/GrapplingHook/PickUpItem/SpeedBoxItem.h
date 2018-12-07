// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/ShapeComponent.h"
#include "Components/BoxComponent.h"
#include "PickUpItem/PickUpBox.h"
#include "PickUpItem/PSpeedBox.h"
#include "SpeedBoxItem.generated.h"

UCLASS()
class GRAPPLINGHOOK_API ASpeedBoxItem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpeedBoxItem();

	UPROPERTY(EditAnywhere)
		USceneComponent *itemsRoot;

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent *itemsMesh;

	UPROPERTY(EditAnywhere)
		UShapeComponent *itemsPickUp;

	UFUNCTION()
		void OnOverlapBegin(UPrimitiveComponent *OverlappedComp, AActor *OtherActor, UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult);

	IPickUpBox *speedBox;
	
	
};
