// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/InputComponent.h"
#include "Engine/Engine.h"
#include "GenericPlatform/GenericPlatformMath.h"
#include "Math/UnrealMathUtility.h"
#include "InputTester.generated.h"

UCLASS()
class GRAPPLINGHOOK_API AInputTester : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInputTester();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
    void BindingInputComponent();
    void UpdateInput();
    void UpdateInputValue(float x, float y);
    void CheckInputRealease();

    FVector2D currentInput = FVector2D(0.0f, 0.0f);
    FVector2D previousInput = FVector2D(0.0f, 0.0f);
    FName HookHorizontalAxisName = "HookHorizontal";
    FName HookVerticalAxisName = "HookVertical";
    float inputTreshold = 0.5f;
};
