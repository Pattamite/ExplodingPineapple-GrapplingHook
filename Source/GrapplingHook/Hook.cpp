// Fill out your copyright notice in the Description page of Project Settings.

#include "Hook.h"


// Sets default values
AHook::AHook()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void AHook::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AHook::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AHook::Setup(UStaticMeshComponent* RootSM, UStaticMeshComponent* TargetSM)
{
	FConstraintInstance ConstraintInstance;
	UPhysicsConstraintComponent* ConstraintComp = NewObject<UPhysicsConstraintComponent>(RootSM);
	if (!ConstraintComp)
	{
		//UE_LOG constraint UObject could not be created!
		return;
	}

	ConstraintComp->SetWorldLocation(GetActorLocation());
	ConstraintComp->AttachTo(GetRootComponent(), NAME_None, EAttachLocation::KeepWorldPosition);
	ConstraintComp->SetConstrainedComponents(RootSM, NAME_None, TargetSM, NAME_None);
}

