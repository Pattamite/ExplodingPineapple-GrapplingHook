// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "Components/ShapeComponent.h"
#include "PickUpItems.generated.h"


UCLASS()
class GRAPPLINGHOOK_API APickUpItems : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APickUpItems();

protected:
	// Called when the game starts or when spawned
	//virtual void BeginPlay() override;

public:	
	// Called every frame
	//virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	USceneComponent *itemsRoot;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent *itemsMesh;

	UPROPERTY(EditAnywhere)
	UShapeComponent *itemsPickUp;

	UFUNCTION()
		void OnOverlapBegin(UPrimitiveComponent *OverlappedComp, AActor *OtherActor, UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult);
	
	
	/*UFUNCTION()
		void PickUp();
		*/

	/*UPROPERTY(EditAnywhere)
	UBoxComponent *BoxCollider;
	*/
	
};
