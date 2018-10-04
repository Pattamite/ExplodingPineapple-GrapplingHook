// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Delegates/Delegate.h"
#include "Components/ActorComponent.h"
#include "GameFramework/Actor.h"
#include "Components/InputComponent.h"
#include "Engine/Engine.h"
#include "GenericPlatform/GenericPlatformMath.h"
#include "Math/UnrealMathUtility.h"
#include "HookInput.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FVectorDelegate, FVector, vector);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FVoidDelegate);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GRAPPLINGHOOK_API UHookInput : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHookInput();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
    UPROPERTY(BlueprintAssignable, Category = "Hook Input")
        FVectorDelegate OnHookCommand;
    UPROPERTY(BlueprintAssignable, Category = "Hook Input")
        FVoidDelegate OnUnHookCommand;
    UPROPERTY(BlueprintAssignable, Category = "Hook Input")
        FVoidDelegate OnJumpCommand;

private:
    void BindingInputComponent();
    void UpdateInput();
    void UpdateInputValue(float x, float y);
    void CheckInputRealease();
    UFUNCTION(BlueprintCallable, Category = "UI Button")
        void ButtonPress();
    UFUNCTION(BlueprintCallable, Category = "UI Button")
        void UnHookButtonPress();
    UFUNCTION(BlueprintCallable, Category = "UI Button")
        void JumpButtonPress();

    AActor* owner;
    FVector2D currentInput = FVector2D(0.0f, 0.0f);
    FVector2D previousInput = FVector2D(0.0f, 0.0f);
    FName HookHorizontalAxisName = "HookHorizontal";
    FName HookVerticalAxisName = "HookVertical";
    FName CutHookActionName = "CutHook";
    UPROPERTY(EditAnywhere)
        float inputTreshold = 0.5f;
    bool lastInputBuffer = false;
    FVector hookAngleVector = FVector(0.0f, 0.0f, 0.0f);
    
	
};