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
    UPROPERTY(BlueprintAssignable, Category = "Hook Touch Input")
        FVectorDelegate OnStartHookTouch;
    UPROPERTY(BlueprintAssignable, Category = "Hook Touch Input")
        FVectorDelegate OnRepeatHookTouch;
    UPROPERTY(BlueprintAssignable, Category = "Hook Touch Input")
        FVectorDelegate OnStopHookTouch;

private:
    void BindingInputComponent();
    void TouchStart(ETouchIndex::Type FingerIndex, FVector Location);
    void TouchRepeat(ETouchIndex::Type FingerIndex, FVector Location);
    void TouchStop(ETouchIndex::Type FingerIndex, FVector Location);
    int GetFingerIndexName(ETouchIndex::Type FingerIndex) const;
    UFUNCTION(BlueprintCallable, Category = "UI Button")
        void ButtonPress();
    UFUNCTION(BlueprintCallable, Category = "UI Button")
        void UnHookButtonPress();
    UFUNCTION(BlueprintCallable, Category = "UI Button")
        void JumpButtonPress();

    AActor* owner;

    bool isTouched = false;
    int currentTouchIndex = 0;
    FVector currentInput = FVector(0.0f, 0.0f, 0.0f);
    FVector startInput = FVector(0.0f, 0.0f, 0.0f);
    UPROPERTY(EditAnywhere)
        float inputTreshold = 20.0f;
    FVector hookAngleVector = FVector(0.0f, 0.0f, 0.0f);


    FName CutHookActionName = "CutHook";
    
};