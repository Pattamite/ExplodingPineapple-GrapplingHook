// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "GrapplingHookCharacter.h"
#include "PaperFlipbookComponent.h"
#include "Components/TextRenderComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "Camera/CameraComponent.h"
#include "MySaveGame.h"
#include "GrapplingHook.h"
#include "EngineUtils.h"


//DEFINE_LOG_CATEGORY_STATIC(SideScrollerCharacter, Log, All);

int scorePlayer = 1;

//////////////////////////////////////////////////////////////////////////
// AGrapplingHookCharacter

AGrapplingHookCharacter::AGrapplingHookCharacter()
{
    // Use only Yaw from the controller and ignore the rest of the rotation.
    bUseControllerRotationPitch = false;
    bUseControllerRotationYaw = true;
    bUseControllerRotationRoll = false;

    // Set the size of our collision capsule.
    GetCapsuleComponent()->SetCapsuleHalfHeight(96.0f);
    GetCapsuleComponent()->SetCapsuleRadius(40.0f);

    // Create a camera boom attached to the root (capsule)
    CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
    CameraBoom->SetupAttachment(RootComponent);
    CameraBoom->TargetArmLength = 500.0f;
    CameraBoom->SocketOffset = FVector(0.0f, 0.0f, 75.0f);
    CameraBoom->bAbsoluteRotation = true;
    CameraBoom->bDoCollisionTest = false;
    CameraBoom->RelativeRotation = FRotator(0.0f, -90.0f, 0.0f);
    

    // Create an orthographic camera (no perspective) and attach it to the boom
    SideViewCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("SideViewCamera"));
    SideViewCameraComponent->ProjectionMode = ECameraProjectionMode::Orthographic;
    SideViewCameraComponent->OrthoWidth = 2048.0f;
    SideViewCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);

    // Prevent all automatic rotation behavior on the camera, character, and camera component
    CameraBoom->bAbsoluteRotation = true;
    SideViewCameraComponent->bUsePawnControlRotation = false;
    SideViewCameraComponent->bAutoActivate = true;
    GetCharacterMovement()->bOrientRotationToMovement = false;

    // Configure character movement
    GetCharacterMovement()->GravityScale = 2.0f;
    GetCharacterMovement()->AirControl = 0.80f;
    GetCharacterMovement()->JumpZVelocity = 1000.f;
    GetCharacterMovement()->GroundFriction = 3.0f;
    GetCharacterMovement()->MaxWalkSpeed = 600.0f;
    GetCharacterMovement()->MaxFlySpeed = 600.0f;

    // Lock character motion onto the XZ plane, so the character can't move in or out of the screen
    GetCharacterMovement()->bConstrainToPlane = true;
    GetCharacterMovement()->SetPlaneConstraintNormal(FVector(0.0f, -1.0f, 0.0f));

    // Behave like a traditional 2D platformer character, with a flat bottom instead of a curved capsule bottom
    // Note: This can cause a little floating when going up inclines; you can choose the tradeoff between better
    // behavior on the edge of a ledge versus inclines by setting this to true or false
    GetCharacterMovement()->bUseFlatBaseForFloorChecks = true;

    // 	TextComponent = CreateDefaultSubobject<UTextRenderComponent>(TEXT("IncarGear"));
    // 	TextComponent->SetRelativeScale3D(FVector(3.0f, 3.0f, 3.0f));
    // 	TextComponent->SetRelativeLocation(FVector(35.0f, 5.0f, 20.0f));
    // 	TextComponent->SetRelativeRotation(FRotator(0.0f, 90.0f, 0.0f));
    // 	TextComponent->SetupAttachment(RootComponent);

    // Enable replication on the Sprite component so animations show up when networked
    GetSprite()->SetIsReplicated(true);
    bReplicates = true;

	//Default Value
	//characterStats.score = 1;
	gameStart = false;

}

//////////////////////////////////////////////////////////////////////////
// Animation

void AGrapplingHookCharacter::UpdateAnimation()
{
    const FVector PlayerVelocity = GetVelocity();
    const float PlayerSpeedSqr = PlayerVelocity.SizeSquared();

    // Are we moving or standing still?
    UPaperFlipbook* DesiredAnimation = (PlayerSpeedSqr > 0.0f) ? RunningAnimation : IdleAnimation;
    if( GetSprite()->GetFlipbook() != DesiredAnimation 	)
    {
        GetSprite()->SetFlipbook(DesiredAnimation);
    }
}

void AGrapplingHookCharacter::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
    
    UpdateCharacter();	
	
	/*if (!isLoaded) {
		//LoadGame();
		scorePlayer = 0;
		isLoaded = true;
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Orange, FString::Printf(TEXT("Score: %d"), scorePlayer));
	}
	// GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("Score: %d"), scorePlayer));

	 scorePlayer++;
	 //SaveGame();
	 if (scorePlayer == 50) {
		 SaveGame();
	 }
	 if (scorePlayer >= 300) {
		 LoadGame();
	 }
	 
	 if (scorePlayer > characterStats.score) {
		 SaveGame();
	 }*/

	 //UE_LOG(LogClass, Warning, TEXT("%d"), characterStats.score);
}


//////////////////////////////////////////////////////////////////////////
// Input

void AGrapplingHookCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
    // Note: the 'Jump' action and the 'MoveRight' axis are bound to actual keys/buttons/sticks in DefaultInput.ini (editable from Project Settings..Input)
    PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
    PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
    PlayerInputComponent->BindAxis("MoveRight", this, &AGrapplingHookCharacter::MoveRight);

    PlayerInputComponent->BindTouch(IE_Pressed, this, &AGrapplingHookCharacter::TouchStarted);
    PlayerInputComponent->BindTouch(IE_Released, this, &AGrapplingHookCharacter::TouchStopped);
}

void AGrapplingHookCharacter::MoveRight(float Value)
{
    /*UpdateChar();*/

    // Apply the input to the character motion
    AddMovementInput(FVector(1.0f, 0.0f, 0.0f), Value);
}

void AGrapplingHookCharacter::TouchStarted(const ETouchIndex::Type FingerIndex, const FVector Location)
{
    // Jump on any touch
    Jump();
}

void AGrapplingHookCharacter::TouchStopped(const ETouchIndex::Type FingerIndex, const FVector Location)
{
    // Cease jumping once touch stopped
    StopJumping();
}

void AGrapplingHookCharacter::UpdateCharacter()
{
    // Update animation to match the motion
    UpdateAnimation();

    // Now setup the rotation of the controller based on the direction we are travelling
    const FVector PlayerVelocity = GetVelocity();	
    float TravelDirection = PlayerVelocity.X;
    // Set the rotation so that the character faces his direction of travel.
    if (Controller != nullptr)
    {
        if (TravelDirection < 0.0f)
        {
            Controller->SetControlRotation(FRotator(0.0, 180.0f, 0.0f));
        }
        else if (TravelDirection > 0.0f)
        {
            Controller->SetControlRotation(FRotator(0.0f, 0.0f, 0.0f));
        }
    }
}

/*void AGrapplingHookCharacter::SaveGame() 
{
	class UMySaveGame* SaveGameInstance = Cast<UMySaveGame>(UGameplayStatics::CreateSaveGameObject(UMySaveGame::StaticClass()));
	SaveGameInstance = Cast<UMySaveGame>(UGameplayStatics::LoadGameFromSlot(SaveGameInstance->SaveSlotName, SaveGameInstance->UserIndex));

	if (SaveGameInstance->IsValidLowLevel()) {
		SaveGameInstance->score = scorePlayer;
		UGameplayStatics::SaveGameToSlot(SaveGameInstance, SaveGameInstance->SaveSlotName, SaveGameInstance->UserIndex);
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, FString::Printf(TEXT("SAVED")));
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, FString::Printf(TEXT("Score: %d"), SaveGameInstance->Score));
	else {
		UMySaveGame* SaveGameInstance_2 = Cast<UMySaveGame>(UGameplayStatics::CreateSaveGameObject(UMySaveGame::StaticClass()));

		if (!SaveGameInstance_2)
			return;
		else {
			SaveGameInstance->score = scorePlayer;
			UGameplayStatics::SaveGameToSlot(SaveGameInstance, SaveGameInstance->SaveSlotName, SaveGameInstance->UserIndex);
			//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, FString::Printf(TEXT("save2")));
			//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, FString::Printf(TEXT("score2: %d"), SaveGameInstance->Score));
		}
	}
	
}

void AGrapplingHookCharacter::LoadGame()
{

	if (this->IsValidLowLevel()) {
		
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, FString::Printf(TEXT("LOADsave")));
		const FString SaveSlotName = FString(TEXT("PlayerSaveSlot"));
		if (UGameplayStatics::DoesSaveGameExist(SaveSlotName, 0)) {
			UMySaveGame* LoadGameInstance = Cast<UMySaveGame>(UGameplayStatics::CreateSaveGameObject(UMySaveGame::StaticClass()));
			if (LoadGameInstance->IsValidLowLevel()) {
				LoadGameInstance = Cast<UMySaveGame>(UGameplayStatics::LoadGameFromSlot(LoadGameInstance->SaveSlotName, LoadGameInstance->UserIndex));
				characterStats.score = LoadGameInstance->Score;
				//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, FString::Printf(TEXT("LOADsave")));
			}
			else {
				
				class UMySaveGame* LoadGameInstance_2 = Cast<UMySaveGame>(UGameplayStatics::CreateSaveGameObject(UMySaveGame::StaticClass()));

				if (!LoadGameInstance_2)
					return;
				else {
					LoadGameInstance = Cast<UMySaveGame>(UGameplayStatics::LoadGameFromSlot(LoadGameInstance->SaveSlotName, LoadGameInstance->UserIndex));
					characterStats.score = LoadGameInstance->Score;
					//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, FString::Printf(TEXT("LOADsave")));

				}

			}
		}
		else {
			//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, FString::Printf(TEXT("No save game found")));
		}
	}
}*/
