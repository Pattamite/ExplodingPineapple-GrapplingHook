// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemEffect.h"
#include "BasePickUpItem.h"
#include "PlayerCharacter.h"
#include "Components/ActorComponent.h"
#include "Components/PrimitiveComponent.h"
#include "ItemCollector.generated.h"


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class GRAPPLINGHOOK_API UItemCollector : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UItemCollector();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void AddItemEffect(UItemEffect *effect);

	UFUNCTION(BlueprintCallable, Category = "Item")
	APlayerCharacter* GetPlayer();
	UFUNCTION(BlueprintCallable, Category = "Item")
	void SetPlayer(APlayerCharacter *newPlayer);
	UFUNCTION(BlueprintCallable, Category = "Item")
	void SetupColider(UPrimitiveComponent* component);
	UFUNCTION(BlueprintCallable, Category = "Item")
	UItemEffect* FindEffect(FString name);

	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

private:
	TArray<UItemEffect*> effects;
	APlayerCharacter *player;
};