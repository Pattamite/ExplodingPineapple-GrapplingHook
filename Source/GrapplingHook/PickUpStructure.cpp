// Fill out your copyright notice in the Description page of Project Settings.

#include "PickUpStructure.h"
#include "PlayerCharacter.h"

// Sets default values
APickUpStructure::APickUpStructure()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	itemsRoot = CreateDefaultSubobject<USceneComponent>(TEXT("PowerItemRoot"));
	RootComponent = itemsRoot;
	itemsPickUp = CreateDefaultSubobject<UBoxComponent>(TEXT("PowerItemPickUp"));
	itemsPickUp->bGenerateOverlapEvents = true;
	itemsPickUp->SetWorldScale3D(FVector(1.0f, 1.0f, 1.0f));
	itemsPickUp->OnComponentBeginOverlap.AddDynamic(this, &APickUpStructure::OnOverlapBegin);
	itemsPickUp->AttachToComponent(this->RootComponent, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	
}

void APickUpStructure::OnOverlapBegin(UPrimitiveComponent *OverlappedComp, AActor *OtherActor, UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult)
{
	

	APlayerCharacter* player = Cast<APlayerCharacter>(OtherActor);

	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr) && OtherActor == player) {
		UE_LOG(LogClass, Warning, TEXT("Charactername %s"), *OtherActor->GetName());
		Destroy();
		effectItems();
	}
}
