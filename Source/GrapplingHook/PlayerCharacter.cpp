// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerCharacter.h"
#include "PaperFlipbookComponent.h"
#include "Components/TextRenderComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "Camera/CameraComponent.h"

DEFINE_LOG_CATEGORY_STATIC(SideScrollerCharacter, Log, All);

APlayerCharacter::APlayerCharacter()
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

	// Enable replication on the Sprite component so animations show up when networked
	GetSprite()->SetIsReplicated(true);
	bReplicates = true;

	// Initialize state
	myPlayerState = EPlayerState::IDLE;
	CurrentState();

	//hookShooter = Cast<UHookShooter>(GetComponentByClass(UHookShooter::StaticClass()));
	/*if (hookShooter != nullptr) 
	{
		UE_LOG(LogTemp, Warning, TEXT("Hook name: %s"), *hookShooter->GetName());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Not found hook shooter"));
	}	*/
}

// Called when the game starts
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("Start game"));
	FindHookShooterComponent();
}

//////////////////////////////////////////////////////////////////////////
// Debug

// Get state from enum
FString APlayerCharacter::EnumToString(const TCHAR *Enum, int32 EnumValue) const
{
	const UEnum* EnumPtr = FindObject<UEnum>(ANY_PACKAGE, Enum, true);
	if (!EnumPtr)
		return NSLOCTEXT("Invalid", "Invalid", "Invalid").ToString();

#if WITH_EDITOR
	return EnumPtr->GetDisplayNameText(EnumValue).ToString();
#else
	return EnumPtr->GetEnumName(EnumValue);
#endif
}

// Print current state
void APlayerCharacter::CurrentState()
{
	FString msg = TEXT("Init Player state: ") + EnumToString(TEXT("EPlayerState"), static_cast<uint8>(myPlayerState));
	UE_LOG(LogTemp, Warning, TEXT("%s"), *msg);
	return;
}

//////////////////////////////////////////////////////////////////////////
// Animation

// Update animation from state 
void APlayerCharacter::UpdateAnimation()
{
	UPaperFlipbook* desiredAnimation = NULL;

	switch (myPlayerState)
	{
	case EPlayerState::IDLE:
		desiredAnimation = IdleAnimation;
		break;
	case EPlayerState::RUNNING:
		desiredAnimation = RunningAnimation;
		break;
	case EPlayerState::USEHOOKONAIR:
		desiredAnimation = IdleAnimation;
		break;
	case EPlayerState::NOTUSEHOOKONAIR:
		desiredAnimation = IdleAnimation;
		break;
	default:
		desiredAnimation = IdleAnimation;
		break;
	}
	GetSprite()->SetFlipbook(desiredAnimation);
	return;
}

void APlayerCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	UpdateCharacter();
}


//////////////////////////////////////////////////////////////////////////
// Input

void APlayerCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Note: the 'Jump' action is bound to actual keys/buttons/sticks in DefaultInput.ini (editable from Project Settings..Input)
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindTouch(IE_Pressed, this, &APlayerCharacter::TouchStarted);
	PlayerInputComponent->BindTouch(IE_Released, this, &APlayerCharacter::TouchStopped);
}

void APlayerCharacter::TouchStarted(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	// Jump on any touch
	// Jump();
}

void APlayerCharacter::TouchStopped(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	// Cease jumping once touch stopped
	// StopJumping();
}

void APlayerCharacter::UpdateCharacter()
{
	// Update animation to match the motion
	UpdateAnimation();

	// Update player current state
	UpdatePlayerState();

	const FVector playerVelocity = GetVelocity();
	UE_LOG(LogTemp, Warning, TEXT("Velocity: %s"), *playerVelocity.ToString());
	// Move right endless
	if (myPlayerState == EPlayerState::RUNNING)
	{ 
		Running();
	}
	else 
	{
		StopRunning();
	}
}

void APlayerCharacter::UpdatePlayerState()
{
	if (GetCharacterMovement()->IsMovingOnGround())
	{
		myPlayerState = EPlayerState::RUNNING;
	}
	else
	{
		if (hookShooter->IsOnHook())
		{
			myPlayerState = EPlayerState::USEHOOKONAIR;
		}
		else
		{
			myPlayerState = EPlayerState::NOTUSEHOOKONAIR;
		}
	}
	CurrentState();
}

void APlayerCharacter::CallJump()
{
    Jump();
}

// Look for attached Hook Shooter
void APlayerCharacter::FindHookShooterComponent()
{
	hookShooter = FindComponentByClass<UHookShooter>();
	if (hookShooter != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Found hook shooter component"))
	}
}

//////////////////////////////////////////////////////////////////////////
// TODO behavior walk, jump, shoot

void APlayerCharacter::Running()
{
	AddMovementInput(FVector(movementSpeed, 0.0f, 0.0f), 1);
	return;
}

void APlayerCharacter::StopRunning()
{
	AddMovementInput(FVector(movementSpeed, 0.0f, 0.0f), 0);
	return;
}

void APlayerCharacter::Jumping()
{
	Jump();
	return;
}

