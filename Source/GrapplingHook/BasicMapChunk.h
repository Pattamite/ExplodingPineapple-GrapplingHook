// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Runtime/Engine/Classes/Engine/TargetPoint.h"
#include "BasicMapChunk.generated.h"

UCLASS()
class GRAPPLINGHOOK_API ABasicMapChunk : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABasicMapChunk();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
    UFUNCTION(BlueprintCallable, Category = "Map Chunk Position")
        const FVector GetSpawnLocation(FVector lastExitPoint);
    UFUNCTION(BlueprintCallable, Category = "Map Chunk Position")
        const FVector GetWorldExitLocation();

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
        FVector entryPoint;
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
        FVector exitPoint;

    

};
