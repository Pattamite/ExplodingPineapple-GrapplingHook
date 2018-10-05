// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MyHUDSaveScore.generated.h"

/**
 * 
 */
UCLASS()
class GRAPPLINGHOOK_API AMyHUDSaveScore : public AHUD
{
	GENERATED_BODY()
	
public:
	
	AMyHUDSaveScore();

protected:

	virtual void BeginPlay() override;

public:

	TSubclassOf<class USaveScoreWidget> SaveWidgetClass;
	
	class USaveScoreWidget* SaveUI;

	void ActiveWidget();
	
	
	
};
