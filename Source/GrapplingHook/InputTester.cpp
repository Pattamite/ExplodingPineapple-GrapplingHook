// Fill out your copyright notice in the Description page of Project Settings.

#include "InputTester.h"


// Sets default values
AInputTester::AInputTester()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AInputTester::BeginPlay()
{
	Super::BeginPlay();
    BindingInputComponent();
}

// Called every frame
void AInputTester::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
    UpdateInput();
}

void AInputTester::BindingInputComponent()
{
    InputComponent->BindAxis(HookHorizontalAxisName);
    InputComponent->BindAxis(HookVerticalAxisName);
}

void AInputTester::UpdateInput()
{
    float xInput = InputComponent->GetAxisValue(HookHorizontalAxisName);
    float yInput = InputComponent->GetAxisValue(HookVerticalAxisName);
    UpdateInputValue(xInput, yInput);
    CheckInputRealease();
}

void AInputTester::UpdateInputValue(float x, float y)
{
    previousInput = currentInput;
    currentInput.Set(x, y);

    /*GEngine->AddOnScreenDebugMessage(
        -1,
        0.0f,
        FColor::Red,
        FString::Printf(TEXT("Current Input: x: %f, y: %f"), currentInput.X, currentInput.Y)
    );*/
}

void AInputTester::CheckInputRealease()
{
    if (currentInput.IsZero() && previousInput.Size() >= inputTreshold)
    {
        float angle = FMath::RadiansToDegrees(FGenericPlatformMath::Atan2(previousInput.Y, previousInput.X));
        GEngine->AddOnScreenDebugMessage(
            -1,
            1.0f,
            FColor::Yellow,
            FString::Printf(TEXT("Hook at: %f degree"), angle)
        );
    }
}

