// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "PlayerCharacter.h"
#include "ItemEffect.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class GRAPPLINGHOOK_API UItemEffect : public UObject
{
	GENERATED_BODY()
	
public:

	UFUNCTION(BlueprintCallable, Category = "Item")
	virtual void OnStart(APlayerCharacter *player);

	UFUNCTION(BlueprintNativeEvent, Category = "Item")
	void OnStart_BP(APlayerCharacter *player);

	UFUNCTION(BlueprintCallable, Category = "Item")
	virtual void OnTick(float DeltaTime, APlayerCharacter *player);

	UFUNCTION(BlueprintNativeEvent, Category = "Item")
	void OnTick_BP(float DeltaTime, APlayerCharacter *player);

	UFUNCTION(BlueprintCallable, Category = "Item")
	virtual void OnEnd(APlayerCharacter *player);

	UFUNCTION(BlueprintNativeEvent, Category = "Item")
	void OnEnd_BP(APlayerCharacter *player);

	bool DecreaseTime(float time);

	UPROPERTY(SimpleDisplay, EditAnywhere, BlueprintReadWrite, Category = "Item")
	float lifeTime = 0;

private:
	float remainingTime = 0;
};