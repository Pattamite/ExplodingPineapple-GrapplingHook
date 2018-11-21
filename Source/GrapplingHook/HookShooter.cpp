// Fill out your copyright notice in the Description page of Project Settings.

#include "HookShooter.h"
#include "BasePickUpItem.h"
#include "BasicMapChunk.h"


// Sets default values for this component's properties
UHookShooter::UHookShooter()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

}


// Called when the game starts
void UHookShooter::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UHookShooter::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

bool UHookShooter::IsOnHook()
{
	return onHook;
}

AHook* UHookShooter::GetHook()
{
	return hook;
}

AHook* UHookShooter::ShootHookByDirection_Implementation(FVector direction, float hookLength)
{
	direction.Normalize();
	FVector start = GetOwner()->GetActorLocation();
	FVector end = start + direction * hookLength;

	//UE_LOG(LogTemp, Warning, TEXT("s: %s e: %s"), *start.ToString(), *end.ToString());

	FHitResult HitResult;
	FCollisionQueryParams TraceParameters(FName(TEXT("")), false, GetOwner());
	UWorld* const World = GetWorld();
	if (!World) {
		UE_LOG(LogTemp, Warning, TEXT("world is null"));
		return nullptr;
	}
	bool hit = World->LineTraceSingleByObjectType(
		OUT HitResult,
		start,
		end,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_WorldDynamic),
		TraceParameters
	);
	//ABasePickUpItem* pickUpItem = Cast<ABasePickUpItem>(HitResult.Actor);
	ABasicMapChunk* basicMap = Cast<ABasicMapChunk>(HitResult.Actor);
	if (hit && basicMap->IsValidLowLevel()) {
		UE_LOG(LogTemp, Warning, TEXT("Hit at %s"), *HitResult.Location.ToString());
		return SetHook(HitResult.Location);
	}
	return nullptr;
}

AHook* UHookShooter::SetHook(FVector location)
{
	UWorld* const World = GetWorld();
	if (World) {
		FActorSpawnParameters SpawnParams;
		//SpawnParams.Instigator = this;
		FRotator rotator = FRotator::ZeroRotator;
		AHook* newHook = World->SpawnActor<AHook>(HookBP, location, rotator, SpawnParams);
		if (newHook) {
			UE_LOG(LogTemp, Warning, TEXT("Create Hook at %s"), *location.ToString());
			hook = newHook;
			onHook = true;
            ASoundSystem::PlaySoundEffectAtLocation(ESoundEffectEnum::SFX_Hook, location);
			return hook;
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Can not create hook"));
		}
	}
	return nullptr;
}

void UHookShooter::RemoveHook()
{
	UWorld* const World = GetWorld();
	if (World && hook) {
        ASoundSystem::PlaySoundEffectAtLocation(ESoundEffectEnum::SFX_Unhook, hook->GetActorLocation());
		World->DestroyActor(hook);
		onHook = false;
		hook = nullptr;
	}

}

