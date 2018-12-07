// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SoundSystem.generated.h"

UENUM(BlueprintType)
enum class ESoundEffectEnum : uint8
{
    SFX_Hook	UMETA(DisplayName = "Hook"),
    SFX_Hook2   UMETA(DisplayName = "Hook2"),
    SFX_Unhook 	UMETA(DisplayName = "UnHook"),
    SFX_Jump    UMETA(DisplayName = "Jump"),
    SFX_Landing UMETA(DisplayName = "Landing"),
    SFX_Pickup  UMETA(DisplayName = "Pickup"),
    SFX_Swing   UMETA(DisplayName = "Swing"),
    SFX_Swing2  UMETA(DisplayName = "Swing2"),
    SFX_Coin    UMETA(DisplayName = "Coin"),
    SFX_Chaser_Hit      UMETA(DisplayName = "Chaser Hit"),
    SFX_Chaser_Hit2     UMETA(DisplayName = "Chaser Hit2"),
    SFX_Chaser_Jump     UMETA(DisplayName = "Chaser Jump"),
    SFX_Chaser_Jump2    UMETA(DisplayName = "Chaser Jump2"),
    SFX_Chaser_Landing  UMETA(DisplayName = "Chaser Landing"),
    SFX_Chaser_Landing2 UMETA(DisplayName = "Chaser Landing2"),
    SFX_Chaser_Swing    UMETA(DisplayName = "Chaser Swing"),
    SFX_Chaser_Swing2   UMETA(DisplayName = "Chaser Swing2")
};

UENUM(BlueprintType)
enum class EUiSoundEnum : uint8
{
    UI_ButtonClicked	UMETA(DisplayName = "ButtonClicked"),
    UI_Select 	        UMETA(DisplayName = "Select"),
    UI_Deselect         UMETA(DisplayName = "Deselect"),
    UI_Purchased        UMETA(DisplayName = "Purchased"),
};

UCLASS()
class GRAPPLINGHOOK_API ASoundSystem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASoundSystem();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
    UFUNCTION(BlueprintCallable, Category = "Sound")
        static void PlaySoundEffectAtLocation(ESoundEffectEnum sound, FVector location);
    UFUNCTION(BlueprintImplementableEvent, Category = "Sound")
        void PlaySoundEffectAtLocationInstance(ESoundEffectEnum sound, FVector location);
    UFUNCTION(BlueprintCallable, Category = "Sound")
        static void PlayUiSound(EUiSoundEnum sound);
    UFUNCTION(BlueprintImplementableEvent, Category = "Sound")
        void PlayUiSoundInstance(EUiSoundEnum sound);

private:
    static ASoundSystem* instance;
    
	
};


