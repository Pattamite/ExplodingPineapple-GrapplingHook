// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SoundSystem.generated.h"

UENUM(BlueprintType)
enum class ESoundEffectEnum : uint8
{
    SFX_Hook	UMETA(DisplayName = "Hook"),
    SFX_Unhook 	UMETA(DisplayName = "UnHook"),
    SFX_Jump    UMETA(DisplayName = "Jump")
};

UENUM(BlueprintType)
enum class EUiSoundEnum : uint8
{
    UI_ButtonClicked	UMETA(DisplayName = "ButtonClicked"),
    UI_Select 	        UMETA(DisplayName = "Select"),
    UI_Deselect        UMETA(DisplayName = "Deselect")
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


