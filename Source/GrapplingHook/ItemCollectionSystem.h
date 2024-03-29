// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include "ItemCollectionSaveGame.h"
#include "Engine/Engine.h"
#include "ItemCollectionSystem.generated.h"

UCLASS()
class GRAPPLINGHOOK_API AItemCollectionSystem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItemCollectionSystem();
	UFUNCTION(BlueprintCallable, Category = "Item Collection")
		static void AddAcid();
	UFUNCTION(BlueprintCallable, Category = "Item Collection")
		static void AddSlimeTrail();
	UFUNCTION(BlueprintCallable, Category = "Item Collection")
		static void AddGrappleSkip();
	UFUNCTION(BlueprintCallable, Category = "Item Collection")
		static void RemoveAcid();
	UFUNCTION(BlueprintCallable, Category = "Item Collection")
		static void RemoveSlimeTrail();
	UFUNCTION(BlueprintCallable, Category = "Item Collection")
		static void RemoveGrappleSkip();
	UFUNCTION(BlueprintCallable, Category = "Item Collection")
		static bool AcidIsValid();
	UFUNCTION(BlueprintCallable, Category = "Item Collection")
		static bool SlimeTrailIsValid();
	UFUNCTION(BlueprintCallable, Category = "Item Collection")
		static bool GrappleSkipIsValid();
	UFUNCTION(BlueprintCallable, Category = "Item Collection")
		static void ResetItemsInShopStore();

	static UItemCollectionSaveGame* LoadItemCollectionSaveGame();
	static void LoadAllItemCollection();
	static void SaveAllItemCollection();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	static const FString SaveSlotName;
	static const uint32 UserIndex;

private:
	static void SaveItemCollectionSaveGame(UItemCollectionSaveGame* SaveGameInstace);
	static void CreateNewItemCollectionSaveGame();
	
};
