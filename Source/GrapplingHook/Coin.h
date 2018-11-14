// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BasePickUpItem.h"
#include "Coin.generated.h"

UCLASS()
class GRAPPLINGHOOK_API ACoin : public ABasePickUpItem
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACoin();

	UFUNCTION(BlueprintCallable, Category = "Coin")
	void SetActive(bool isActive);

	UFUNCTION(BlueprintCallable, Category = "Coin")
	bool IsActivation();

	void DisableCoin();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	bool Active;
	void Deactive();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Coin")
	int coinTimer;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	FTimerHandle CountdownTimerHandle;


	
	
};
