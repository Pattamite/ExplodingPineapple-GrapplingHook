// Fill out your copyright notice in the Description page of Project Settings.

#include "PickUpItems.h"


// Sets default values
APickUpItems::APickUpItems()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	itemsRoot = CreateDefaultSubobject<USceneComponent>(TEXT("ItemRoot"));
	RootComponent = itemsRoot;

	itemsPickUp = CreateDefaultSubobject<UBoxComponent>(TEXT("ItemPickUp"));
	itemsPickUp->bGenerateOverlapEvents = true;
	itemsPickUp->SetWorldScale3D(FVector(1.0f, 1.0f, 1.0f));
	itemsPickUp->OnComponentBeginOverlap.AddDynamic(this, &APickUpItems::OnOverlapBegin);
	itemsPickUp->AttachToComponent(this->RootComponent, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	UE_LOG(LogTemp, Warning, TEXT("BoX"));

	speedBox = new PBootBox();
	speedBox->getEffectBox();
	speedBox->displayEffect();

}

void APickUpItems::OnOverlapBegin(UPrimitiveComponent *OverlappedComp, AActor *OtherActor, UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult)
{

	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr)) {
		Destroy();
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("PowerUp!"));
		speedBox->getEffectBox();
		speedBox->displayEffect();
		
	}
	
}

