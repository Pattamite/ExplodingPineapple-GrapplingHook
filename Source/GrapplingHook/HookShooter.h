// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Hook.h"
#include "Components/ActorComponent.h"
#include "GameFramework/Actor.h"
#include "CollisionQueryParams.h"
#include "Engine/World.h"
#include "Engine/EngineTypes.h"
#include "UObject/ConstructorHelpers.h"

#include "HookShooter.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GRAPPLINGHOOK_API UHookShooter : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHookShooter();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, Category = "AnyString")
	bool IsOnHook();
	UFUNCTION(BlueprintCallable, Category = "AnyString")
	AHook* GetHook();

	UFUNCTION(BlueprintCallable, Category = "AnyString")
	AHook* ShootHookByDirection(FVector direction, float hookLength);
	UFUNCTION(BlueprintCallable, Category = "AnyString")
	AHook* SetHook(FVector location);
	UFUNCTION(BlueprintCallable, Category = "AnyString")
	void OnHook();
	UFUNCTION(BlueprintCallable, Category = "AnyString")
	void RemoveHook();
	
	UPROPERTY(EditAnyWhere)
	TSubclassOf<AHook> HookBP;
		
private:
	bool onHook = false;
	AHook* hook;
};
