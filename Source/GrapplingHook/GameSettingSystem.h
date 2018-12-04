// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include "SettingSaveGame.h"
#include "Engine/Engine.h"
#include "Math/UnrealMathUtility.h"
#include "GameSettingSystem.generated.h"

UCLASS()
class GRAPPLINGHOOK_API AGameSettingSystem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGameSettingSystem();

    UFUNCTION(BlueprintCallable, Category = "Game Setting System")
        static void RefreshAllSettingValue();
    UFUNCTION(BlueprintCallable, Category = "Game Setting System")
        static float LoadSfxVolume();
    UFUNCTION(BlueprintCallable, Category = "Game Setting System")
        static float LoadMusicVolume();
    UFUNCTION(BlueprintCallable, Category = "Game Setting System")
        static bool LoadInvertrdControl();
    UFUNCTION(BlueprintCallable, Category = "Game Setting System")
        static float LoadUiVolume();
    UFUNCTION(BlueprintCallable, Category = "Game Setting System")
        static float LoadAmbientSoundVolume();
    UFUNCTION(BlueprintCallable, Category = "Game Setting System")
        static void SaveSfxVolume(float value);
    UFUNCTION(BlueprintCallable, Category = "Game Setting System")
        static void SaveMusicVolume(float value);
    UFUNCTION(BlueprintCallable, Category = "Game Setting System")
        static void SaveInvertrdControl(bool value);
    UFUNCTION(BlueprintCallable, Category = "Game Setting System")
        static void SaveUiVolume(float value);
    UFUNCTION(BlueprintCallable, Category = "Game Setting System")
        static void SaveAmbientSoundVolume(float value);
    UFUNCTION(BlueprintCallable, Category = "Game Setting System")
        static void ResetAllSetting();
    

    static USettingSaveGame* LoadSettingSaveGame();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

    static const FString SaveSlotName;
    static const uint32 UserIndex;

private:
    static void SaveSettingSaveGame(USettingSaveGame* SaveGameInstance);
    static void CreateNewSettingSaveGame();
    static float currentSfxVolume;
    static float currentMusicVolume;
    static bool currentInvertedControl;
    static float currentUiVolume;
    static float currentAmbientSoundVolume;
    static float defaultSfxVolume;
    static float defaultMusicVolume;
    static bool defaultInvertedControl;
    static float defaultUiVolume;
    static float defaultAmbientSoundVolume;
};
