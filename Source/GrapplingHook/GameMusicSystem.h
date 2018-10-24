// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Sound/AmbientSound.h"
#include "GameMusicSystem.generated.h"

UENUM(BlueprintType)
enum class EMusicStateEnum : uint8
{
    BGM_Normal	    UMETA(DisplayName = "Normal"),
    BGM_Rush 	    UMETA(DisplayName = "Rush"),
    BGM_Changing    UMETA(DisplayName = "Changing"),
    BGM_Stop        UMETA(DisplayName = "Stop")
};

UCLASS()
class GRAPPLINGHOOK_API AGameMusicSystem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGameMusicSystem();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

    UFUNCTION(BlueprintCallable, Category = "Sound")
        static void ChangeGameMusicState(EMusicStateEnum state);
    UFUNCTION(BlueprintImplementableEvent, Category = "Sound")
        void ChangeGameMusicStateInstance(EMusicStateEnum state);

protected:
    UPROPERTY(BlueprintReadWrite)
        EMusicStateEnum currentMusicState = EMusicStateEnum::BGM_Normal;

private:
    static AGameMusicSystem* instance;
    
};
