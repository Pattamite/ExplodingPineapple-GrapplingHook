// Fill out your copyright notice in the Description page of Project Settings.

#include "SpeedBoxItem.h"


// Sets default values
ASpeedBoxItem::ASpeedBoxItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	itemsRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SpeedRootItem"));
	RootComponent = itemsRoot;
	itemsPickUp = CreateDefaultSubobject<UBoxComponent>(TEXT("SpeedItemPickUp"));
	itemsPickUp->bGenerateOverlapEvents = true;
	itemsPickUp->SetWorldScale3D(FVector(1.0f, 1.0f, 1.0f));
	itemsPickUp->OnComponentBeginOverlap.AddDynamic(this, &ASpeedBoxItem::OnOverlapBegin);
	//itemsPickUp->AttachToComponent(this->RootComponent, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
    itemsPickUp->SetupAttachment(this->RootComponent);

	speedBox = new PSpeedBox();

}

void ASpeedBoxItem::OnOverlapBegin(UPrimitiveComponent *OverlappedComp, AActor *OtherActor, UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult)
{
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr)) {
		Destroy();
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Speed Up!"));
		speedBox->getEffectBox();
		speedBox->displayEffect();

	}
}

