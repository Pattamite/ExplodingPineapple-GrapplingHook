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
}

void UHookInput::ButtonPress() {
    GEngine->AddOnScreenDebugMessage(
        -1,
        1.0f,
        FColor::Yellow,
        FString::Printf(TEXT("Button Press"))
    );
}

bool UHookInput::IsTouched()
{
	return isTouched;
}

void UHookInput::BindingInputComponent()
{
    owner->InputComponent->BindTouch(IE_Pressed, this, &UHookInput::TouchStart);
    owner->InputComponent->BindTouch(IE_Repeat, this, &UHookInput::TouchRepeat);
    owner->InputComponent->BindTouch(IE_Released, this, &UHookInput::TouchStop);
}

void UHookInput::UnHookButtonPress()
{
    OnUnHookCommand.Broadcast();
}

void UHookInput::JumpButtonPress()
{
    OnJumpCommand.Broadcast();
}

void UHookInput::TouchStart(ETouchIndex::Type FingerIndex, FVector Location)
{
    if (!isTouched)
    {
        startInput = Location;
        currentTouchIndex = GetFingerIndexName(FingerIndex);
        isTouched = true;
        OnStartHookTouch.Broadcast(Location);
    }
}

void UHookInput::TouchRepeat(ETouchIndex::Type FingerIndex, FVector Location)
{
    if (GetFingerIndexName(FingerIndex) == currentTouchIndex)
    {
        currentInput = Location;
        OnRepeatHookTouch.Broadcast(Location);
    }
}

void UHookInput::TouchStop(ETouchIndex::Type FingerIndex, FVector Location)
{
    if (GetFingerIndexName(FingerIndex) == currentTouchIndex)
    {
        currentInput = Location;

        FVector DragDistance = currentInput - startInput;
        DragDistance.Set(DragDistance.X, DragDistance.Y * -1.0f, 0.0f);

        if (DragDistance.Size() > inputTreshold)
        {
            OnHookCommand.Broadcast(FVector(DragDistance.X * -1.0f, 0.0f, DragDistance.Y * -1.0f));
        }
        else
        {
            OnUnHookCommand.Broadcast();
        }

        isTouched = false;

        OnStopHookTouch.Broadcast(Location);
    }
}

int UHookInput::GetFingerIndexName(ETouchIndex::Type FingerIndex) const
{
    switch (FingerIndex)
    {
        case ETouchIndex::Touch1:
            return 1;
        case ETouchIndex::Touch2:
            return 2;
        case ETouchIndex::Touch3:
            return 3;
        case ETouchIndex::Touch4:
            return 4;
        case ETouchIndex::Touch5:
            return 5;
        case ETouchIndex::Touch6:
            return 6;
        case ETouchIndex::Touch7:
            return 7;
        case ETouchIndex::Touch8:
            return 8;
        case ETouchIndex::Touch9:
            return 9;
        case ETouchIndex::Touch10:
            return 10;
        default:
            return -1;
    }
}

