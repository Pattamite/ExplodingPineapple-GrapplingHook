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
    BGM_Stop        UMETA(DisplayName = "Stop"),
    BGM_Menu        UMETA(DisplayName = "Menu"),
    BGM_Intro       UMETA(DisplayName = "Intro"),
    BGM_Loop        UMETA(DisplayName = "Loop")
};

UENUM(BlueprintType)
enum class EAmbientSoundStateEnum : uint8
{
    ABS_Stop	        UMETA(DisplayName = "Stop"),
    ABS_Cave	        UMETA(DisplayName = "Cave"),
    ABS_CristalCave	    UMETA(DisplayName = "Cristal Cave"),
    ABS_Forest	        UMETA(DisplayName = "Forest"),
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

    UFUNCTION(BlueprintCallable, Category = "Music")
        static void ChangeGameMusicState(EMusicStateEnum state);
    UFUNCTION(BlueprintImplementableEvent, Category = "Music")
        void ChangeGameMusicStateInstance(EMusicStateEnum state);
    UFUNCTION(BlueprintCallable, Category = "Ambient Sound")
        static void ChangeAmbientSoundState(EAmbientSoundStateEnum state);
    UFUNCTION(BlueprintImplementableEvent, Category = "Ambient Sound")
        void ChangeAmbientSoundStateInstance(EAmbientSoundStateEnum state);
    UFUNCTION(BlueprintCallable, Category = "Music")
        static bool GetMusicUpdateFlag();
    UFUNCTION(BlueprintCallable, Category = "Music")
        static void SetMusicUpdateFlag(bool value);


protected:
    UPROPERTY(BlueprintReadWrite)
        EMusicStateEnum currentMusicState = EMusicStateEnum::BGM_Normal;
    UPROPERTY(BlueprintReadWrite)
        EAmbientSoundStateEnum currentAmbientSoundStateState = EAmbientSoundStateEnum::ABS_Stop;
    static bool updateFlag;

private:
    static AGameMusicSystem* instance;
    
};
