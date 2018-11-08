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
		if (effects[i]->IsValidLowLevel()) 
		{
			UE_LOG(LogTemp, Warning, TEXT("Effect[i] is valid"));
			effects[i]->OnTick(DeltaTime, player);
		}
		else 
		{
			UE_LOG(LogTemp, Error, TEXT("Effect[i] is null"));
		}

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
	UItemEffect *oldEffect = FindEffect(effect->name);
	if (oldEffect != nullptr) {
		oldEffect->OnStart(player);
		return;
	}
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
		if (effect->IsValidLowLevel())
			AddItemEffect(effect);
		else
			UE_LOG(LogTemp, Error, TEXT("Effect is null"));
	}
}

UItemEffect* UItemCollector::FindEffect(FString name)
{
	for (int i = 0; i < effects.Num(); i++) {
		if (effects[i]->name.Compare(name)) {
			return effects[i];
		}
	}
	return nullptr;
}
