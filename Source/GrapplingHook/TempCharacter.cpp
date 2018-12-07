// Fill out your copyright notice in the Description page of Project Settings.

#include "TempCharacter.h"


// Sets default values
ATempCharacter::ATempCharacter()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATempCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	UE_LOG(LogTemp, Warning, TEXT("Hello from %s"), *GetName());
}

// Called every frame
void ATempCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ATempCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ATempCharacter::Jump);
}

void ATempCharacter::ShootHook() {
	UE_LOG(LogTemp, Warning, TEXT("testing"));
	float Reach = 100.f;
	FVector start = GetActorLocation();
	FVector end = start + GetActorForwardVector() * Reach;

	FHitResult HitResult;
	FCollisionQueryParams TraceParameters(FName(TEXT("")), false, this);
	bool hit = GetWorld()->LineTraceSingleByObjectType(
		OUT HitResult,
		start,
		end,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParameters
	);

}

void ATempCharacter::Jump() {
	UStaticMeshComponent* sm = Cast<UStaticMeshComponent>(this);
	

	if (sm) {
		FVector force = FVector(0, 0, 10.f);
		sm->AddForce(force * sm->GetMass());
	}
	else {
		GLog->Log("this is not a static mesh");
	}
}