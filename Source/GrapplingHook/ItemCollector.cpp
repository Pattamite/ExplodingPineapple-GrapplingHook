// Fill out your copyright notice in the Description page of Project Settings.

#include "ItemCollector.h"


// Sets default values for this component's properties
UItemCollector::UItemCollector()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UItemCollector::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UItemCollector::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	TArray<UItemEffect*> removeEffects;

	for (int i = 0; i < effects.Num(); i++) {
		effects[i]->OnTick(DeltaTime, player);
		if (effects[i]->DecreaseTime(DeltaTime)) {
			effects[i]->OnEnd(player);
			removeEffects.Add(effects[i]);
		}
	}
	for (int i = 0; i < removeEffects.Num(); i++) {
		effects.Remove(removeEffects[i]);
	}
}


void UItemCollector::AddItemEffect(UItemEffect *effect) {
	effect->OnStart(player);
	if (effect->lifeTime > 0) {
		effects.Add(effect);
	}
	else {
		effect->OnEnd(player);
	}
}

APlayerCharacter * UItemCollector::GetPlayer()
{
	return player;
}
void UItemCollector::SetPlayer(APlayerCharacter *newPlayer) {
	player = newPlayer;
}

void UItemCollector::SetupColider(UPrimitiveComponent* component) {
	component->OnComponentBeginOverlap.AddDynamic(this, &UItemCollector::OnOverlapBegin);

}

void UItemCollector::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ABasePickUpItem* item = Cast<ABasePickUpItem>(OtherActor);
	if (item != nullptr) {
		UItemEffect *effect = item->Collect();
		AddItemEffect(effect);
	}
}