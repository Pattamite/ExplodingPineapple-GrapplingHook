// Fill out your copyright notice in the Description page of Project Settings.

#include "BasePickUpItem.h"


// Sets default values
ABasePickUpItem::ABasePickUpItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABasePickUpItem::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABasePickUpItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

UItemEffect * ABasePickUpItem::Collect_Implementation()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Collect item"));
	Destroy();
	return NewObject<UItemEffect>();
}

