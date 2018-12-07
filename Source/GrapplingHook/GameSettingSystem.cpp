// Fill out your copyright notice in the Description page of Project Settings.

#include "GameSettingSystem.h"

const FString AGameSettingSystem::SaveSlotName = "Setting";
const uint32 AGameSettingSystem::UserIndex = 0;

float AGameSettingSystem::defaultSfxVolume = 1.0f;
float AGameSettingSystem::defaultMusicVolume = 1.0f;
bool AGameSettingSystem::defaultInvertedControl = false;
float AGameSettingSystem::defaultUiVolume = 1.0f;
float AGameSettingSystem::defaultAmbientSoundVolume = 1.0f;
float AGameSettingSystem::currentSfxVolume = defaultSfxVolume;
float AGameSettingSystem::currentMusicVolume = defaultMusicVolume;
bool AGameSettingSystem::currentInvertedControl = defaultInvertedControl;
float AGameSettingSystem::currentUiVolume = defaultUiVolume;
float AGameSettingSystem::currentAmbientSoundVolume = defaultAmbientSoundVolume;

// Sets default values
AGameSettingSystem::AGameSettingSystem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void AGameSettingSystem::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGameSettingSystem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

USettingSaveGame* AGameSettingSystem::LoadSettingSaveGame()
{
    if (!UGameplayStatics::DoesSaveGameExist(SaveSlotName, UserIndex))
    {
        //GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, FString::Printf(TEXT("Setting save Not Found")));
        CreateNewSettingSaveGame();
    }

    USettingSaveGame* LoadGameInstance = Cast<USettingSaveGame>(UGameplayStatics::LoadGameFromSlot(SaveSlotName, UserIndex));
    if (LoadGameInstance->IsValidLowLevel())
    {
        //GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, FString::Printf(TEXT("Setting save Found")));
        return LoadGameInstance;
    }

    return nullptr;
}

void AGameSettingSystem::SaveSettingSaveGame(USettingSaveGame* SaveGameInstance)
{
    if (SaveGameInstance->IsValidLowLevel())
    {
        UGameplayStatics::SaveGameToSlot(SaveGameInstance, SaveSlotName, UserIndex);
    }
}

void AGameSettingSystem::CreateNewSettingSaveGame()
{
    //GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, FString::Printf(TEXT("Create new Setting save")));
    USettingSaveGame* SaveGameInstance = Cast<USettingSaveGame>(UGameplayStatics::CreateSaveGameObject(USettingSaveGame::StaticClass()));
    SaveSettingSaveGame(SaveGameInstance);
}

void AGameSettingSystem::RefreshAllSettingValue()
{
    USettingSaveGame* currentSave = LoadSettingSaveGame();
    if (currentSave->IsValidLowLevel())
    {
        currentSfxVolume = currentSave->sfxVolume;
        currentMusicVolume = currentSave->musicVolume;
        currentInvertedControl = currentSave->isInvertedControl;
        currentUiVolume = currentSave->uiVolume;
        currentAmbientSoundVolume = currentSave->ambientVolume;
    }
    else
    {
        //GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, FString::Printf(TEXT("Can't refresh all setting value")));
    }
}

float AGameSettingSystem::LoadSfxVolume()
{
    return currentSfxVolume;
}

float AGameSettingSystem::LoadMusicVolume()
{
    return currentMusicVolume;
}

bool AGameSettingSystem::LoadInvertrdControl()
{
    return currentInvertedControl;
}

float AGameSettingSystem::LoadUiVolume()
{
    return currentUiVolume;
}

float AGameSettingSystem::LoadAmbientSoundVolume()
{
    return currentAmbientSoundVolume;
}

void AGameSettingSystem::SaveSfxVolume(float value)
{
    value = FMath::Clamp<float>(value, 0.0f, 1.0f);
    USettingSaveGame* currentSave = LoadSettingSaveGame();
    if (currentSave->IsValidLowLevel())
    {
        currentSave->sfxVolume = value;
        SaveSettingSaveGame(currentSave);

        currentSfxVolume = value;
    }
    else
    {
        //GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, FString::Printf(TEXT("Can't Save SFX Volume")));
    }
}

void AGameSettingSystem::SaveMusicVolume(float value)
{
    value = FMath::Clamp<float>(value, 0.0f, 1.0f);
    USettingSaveGame* currentSave = LoadSettingSaveGame();
    if (currentSave->IsValidLowLevel())
    {
        currentSave->musicVolume = value;
        SaveSettingSaveGame(currentSave);
        currentMusicVolume = value;
    }
    else
    {
        //GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, FString::Printf(TEXT("Can't Save Music Volume")));
    }
}

void AGameSettingSystem::SaveInvertrdControl(bool value)
{
    USettingSaveGame* currentSave = LoadSettingSaveGame();
    if (currentSave->IsValidLowLevel())
    {
        currentSave->isInvertedControl = value;
        SaveSettingSaveGame(currentSave);

        currentInvertedControl = value;
    }
    else
    {
        //GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, FString::Printf(TEXT("Can't Save Inverted Control")));
    }
}

void AGameSettingSystem::SaveUiVolume(float value)
{
    value = FMath::Clamp<float>(value, 0.0f, 1.0f);
    USettingSaveGame* currentSave = LoadSettingSaveGame();
    if (currentSave->IsValidLowLevel())
    {
        currentSave->uiVolume = value;
        SaveSettingSaveGame(currentSave);
        currentUiVolume = value;
    }
    else
    {
        //GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, FString::Printf(TEXT("Can't Save Music Volume")));
    }
}

void AGameSettingSystem::SaveAmbientSoundVolume(float value)
{
    value = FMath::Clamp<float>(value, 0.0f, 1.0f);
    USettingSaveGame* currentSave = LoadSettingSaveGame();
    if (currentSave->IsValidLowLevel())
    {
        currentSave->ambientVolume = value;
        SaveSettingSaveGame(currentSave);
        currentAmbientSoundVolume = value;
    }
    else
    {
        //GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, FString::Printf(TEXT("Can't Save Music Volume")));
    }
}

void AGameSettingSystem::ResetAllSetting()
{
    CreateNewSettingSaveGame();
    RefreshAllSettingValue();
}
