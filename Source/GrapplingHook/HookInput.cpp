// Fill out your copyright notice in the Description page of Project Settings.

#include "HookInput.h"


// Sets default values for this component's properties
UHookInput::UHookInput()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UHookInput::BeginPlay()
{
	Super::BeginPlay();
    
    owner = GetOwner();
    BindingInputComponent();
	
}


// Called every frame
void UHookInput::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    UpdateInput();
}

void UHookInput::ButtonPress() {
    GEngine->AddOnScreenDebugMessage(
        -1,
        1.0f,
        FColor::Yellow,
        FString::Printf(TEXT("Button Press"))
    );
}

void UHookInput::BindingInputComponent()
{
    owner->InputComponent->BindAxis(HookHorizontalAxisName);
    owner->InputComponent->BindAxis(HookVerticalAxisName);
}

void UHookInput::UpdateInput()
{
    float xInput = owner->InputComponent->GetAxisValue(HookHorizontalAxisName);
    float yInput = owner->InputComponent->GetAxisValue(HookVerticalAxisName);
    UpdateInputValue(xInput, yInput);
    CheckInputRealease();
}

void UHookInput::UpdateInputValue(float x, float y)
{
    previousInput = currentInput;
    currentInput.Set(x, y);

    /*GEngine->AddOnScreenDebugMessage(
        -1,
        0.2f,
        FColor::Red,
        FString::Printf(TEXT("Current Input: x: %f, y: %f"), currentInput.X, currentInput.Y)
    );*/
}

void UHookInput::CheckInputRealease()
{
    if (currentInput.IsZero() && previousInput.Size() >= inputTreshold && !lastInputBuffer)
    {
        lastInputBuffer = true;
        hookAngleVector.Set(previousInput.X * -1.0f , 0.0f, previousInput.Y * -1.0f);
    }
    else if (lastInputBuffer)
    {
        if (currentInput.IsZero()) {
            //Fire Hook
            /*GEngine->AddOnScreenDebugMessage(
                -1,
                1.0f,
                FColor::Yellow,
                FString::Printf(TEXT("Hook at: %s degree"), *(hookAngleVector.ToString()))
            );*/
            OnHookCommand.Broadcast(hookAngleVector);
        }

        lastInputBuffer = false;
    }
}

void UHookInput::UnHookButtonPress()
{
    OnUnHookCommand.Broadcast();
}

void UHookInput::JumpButtonPress()
{
    OnJumpCommand.Broadcast();
}

