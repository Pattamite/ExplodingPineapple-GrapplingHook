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
#include "BasePickUpItem.h"
#include "BasicMapChunk.h"
#include "TestGameMode.h"

DEFINE_LOG_CATEGORY_STATIC(SideScrollerCharacter, Log, All);

APlayerCharacter::APlayerCharacter()
{
	// Use only Yaw from the controller and ignore the rest of the rotation.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = true;
	bUseControllerRotationRoll = false;

	// Set the size of our collision capsule.
	GetCapsuleComponent()->SetCapsuleHalfHeight(30.0f);
	GetCapsuleComponent()->SetCapsuleRadius(30.0f);

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

	// declare trigger capsule
	TriggerCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Trigger Capsule"));
	TriggerCapsule->InitCapsuleSize(40.f, 40.0f);;
	TriggerCapsule->SetCollisionProfileName(TEXT("Trigger"));
	TriggerCapsule->SetupAttachment(RootComponent);

	// declare overlap events
	TriggerCapsule->OnComponentBeginOverlap.AddDynamic(this, &APlayerCharacter::OnOverlapBegin);
	TriggerCapsule->OnComponentEndOverlap.AddDynamic(this, &APlayerCharacter::OnOverlapEnd);
}

// Called when the game starts
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	myPlayerState = EPlayerState::IDLE;
	useMagnetic = false;
	FindHookShooterComponent();
}

//////////////////////////////////////////////////////////////////////////
// Look for attached component

// Hook Shooter
void APlayerCharacter::FindHookShooterComponent()
{
	hookShooter = FindComponentByClass<UHookShooter>();
	if (hookShooter != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Found hook shooter component"))
	}
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
//void APlayerCharacter::UpdateAnimation()
//{
//	UPaperFlipbook* desiredAnimation = NULL;
//
//	switch (myPlayerState)
//	{
//	case EPlayerState::IDLE:
//		desiredAnimation = RunningAnimation;
//		break;
//	case EPlayerState::RUNNING:
//		desiredAnimation = RunningAnimation;
//		break;
//	case EPlayerState::USEHOOKONAIR:
//		desiredAnimation = ShootRopeAnimation;
//		break;
//	case EPlayerState::NOTUSEHOOKONAIR:
//		desiredAnimation = RunningAnimation;
//		break;
//	case EPlayerState::DIED:
//		// TODO add died animation
//		desiredAnimation = RunningAnimation;
//		break;
//	default:
//		desiredAnimation = RunningAnimation;
//		break;
//	}
//	GetSprite()->SetFlipbook(desiredAnimation);
//	return;
//}

void APlayerCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	UpdateCharacter();
	//UE_LOG(LogTemp, Warning, TEXT("Rotation: %f , %f, %f"), GetActorRotation().Pitch, GetActorRotation().Yaw, GetActorRotation().Roll);
}


//////////////////////////////////////////////////////////////////////////
// Input

void APlayerCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	if (myPlayerState != EPlayerState::DIED)
	{
		// Note: the 'Jump' action is bound to actual keys/buttons/sticks in DefaultInput.ini (editable from Project Settings..Input)
		PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
		PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

		PlayerInputComponent->BindTouch(IE_Pressed, this, &APlayerCharacter::TouchStarted);
		PlayerInputComponent->BindTouch(IE_Released, this, &APlayerCharacter::TouchStopped);
	}
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
	//UpdateAnimation();
	UpdatePlayerState();
	UpdatePlayerRun();
}

void APlayerCharacter::UpdatePlayerState()
{
	isOnGround = GetCharacterMovement()->IsMovingOnGround();
	isOnHook = hookShooter->IsOnHook();

	switch (myPlayerState)
	{
	case EPlayerState::IDLE:
		IdleState();
		break;
	case EPlayerState::RUNNING:
		RunningState();
		break;
	case EPlayerState::USEHOOKONAIR:
		HookOnAirState();
		break;
	case EPlayerState::NOTUSEHOOKONAIR:
		NoHookOnAirState();
		break;
	case EPlayerState::DIED:
		DiedState();
		break;
	case EPlayerState::JUMPING:
		//DiedState();
		Running();
		break;
	case EPlayerState::SHOOTING:
		DiedState();
		break;
	case EPlayerState::LANDING:
		LandingState();
		break;
	default:
		
		break;
	}
}

void APlayerCharacter::UpdatePlayerRun()
{
	const FVector playerVelocity = GetVelocity();
	if (myPlayerState == EPlayerState::RUNNING)
	{
		Running();
	}
	else
	{
		StopRunning();
	}
}

void APlayerCharacter::CallJump()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Jumppppp"));
    if (CanJump())
    {
		pressJump = true;
		SetPlayerState(EPlayerState::JUMPING);
        ASoundSystem::PlaySoundEffectAtLocation(ESoundEffectEnum::SFX_Jump, this->GetActorLocation());
    }
}

//////////////////////////////////////////////////////////////////////////
// Behavior

void APlayerCharacter::Running()
{
	AddMovementInput(FVector(movementSpeed, 0.0f, 0.0f), 1);
	return;
}

void APlayerCharacter::StopRunning()
{
	AddMovementInput(FVector(0.0f, 0.0f, 0.0f), 0);
	return;
}

void APlayerCharacter::Jumping()
{	
	Jump();
	return;
}

void APlayerCharacter::AdjustBouncing()
{
	//BounceByPreviousForce();
	BounceByStaticForce();
}

void APlayerCharacter::BounceByPreviousForce()
{
	const FVector playerVelocity = GetVelocity();
	bounceForce = -(playerVelocity.X * bounceRatio);
	if (FMath::Abs(bounceForce) < minBounceForce)
	{
		bounceForce = bounceForce > 0.0f ? 0.0f : FMath::Clamp(bounceForce, -maxBounceForce, -minBounceForce);
	}
	bounceForce = bounceForce > 0.0f ? minBounceForce : FMath::Clamp(bounceForce, -maxBounceForce, -minBounceForce);
	GetCharacterMovement()->AddImpulse(FVector(bounceForce, 0, 0));
	//UE_LOG(LogTemp, Warning, TEXT("Velocity: %s"), *playerVelocity.ToString());
	//UE_LOG(LogTemp, Warning, TEXT("Bounce force: %f"), bounceForce);
}

void APlayerCharacter::BounceByStaticForce()
{
	const FVector playerVelocity = GetVelocity();
	float prevBounceForceAbs = FMath::Abs(bounceForce);

	bounceForce = playerVelocity.X >= 0.0f ? -prevBounceForceAbs : prevBounceForceAbs;
	GetCharacterMovement()->Velocity = FVector(0.0f, 0.0f, 0.0f);
	GetCharacterMovement()->AddImpulse(FVector(bounceForce, 0, 0));
	//UE_LOG(LogTemp, Warning, TEXT("Velocity: %s"), *playerVelocity.ToString());
	//UE_LOG(LogTemp, Warning, TEXT("Bounce force: %f"), bounceForce);
	bounceForce = bounceForce * reduceBounceForceRatio;
}

void APlayerCharacter::PlayerDied()
{
	myPlayerState = EPlayerState::DIED;
	return;
}

bool APlayerCharacter::IsDead()
{
	if (myPlayerState == EPlayerState::DIED)
	{
		return true;
	}

	return false;
}

void APlayerCharacter::SetPlayerState(EPlayerState state)
{
	myPlayerState = state;
	UpdateAnimation();
}

//////////////////////////////////////////////////////////////////////////
// State transition

void APlayerCharacter::IdleState()
{
	if (isOnGround && !pressJump)
	{
		SetPlayerState(EPlayerState::RUNNING);
	}
	else
	{
		SetPlayerState(EPlayerState::NOTUSEHOOKONAIR);
	}
}

void APlayerCharacter::RunningState()
{
	if (!isOnGround)
	{
		if (!isOnHook)
		{
			SetPlayerState(EPlayerState::NOTUSEHOOKONAIR);
		}
		else
		{
			SetPlayerState(EPlayerState::USEHOOKONAIR);
		}
	}
}

void APlayerCharacter::HookOnAirState()
{
	if (isOnGround)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Hit ground during using hook, CUT!!!"));
		OnRemoveHook(); // Event cut hook

		float walkingSpeed = GetCharacterMovement()->MaxWalkSpeed;
		GetCharacterMovement()->Velocity = FVector(walkingSpeed, 0.0f, 0.0f);
		SetPlayerState(EPlayerState::RUNNING);
	}

	if (!isOnHook)
	{
		SetPlayerState(EPlayerState::NOTUSEHOOKONAIR);
		bounceForce = maxBounceForce;
	}
}

void APlayerCharacter::NoHookOnAirState()
{
	if (GetCharacterMovement()->IsFalling())
	{
		SetPlayerState(EPlayerState::LANDING);
	}
	if (isOnGround)
	{
		SetPlayerState(EPlayerState::RUNNING);
	}
	if (isOnHook)
	{
		SetPlayerState(EPlayerState::USEHOOKONAIR);
	}
}

void APlayerCharacter::LandingState()
{
	const FVector playerVelocity = GetVelocity();

	if (playerVelocity.Z >= 0.0f)
	{
		SetPlayerState(EPlayerState::NOTUSEHOOKONAIR);
	}
	if (isOnGround)
	{
		SetPlayerState(EPlayerState::RUNNING);
	}
	if (isOnHook)
	{
		SetPlayerState(EPlayerState::USEHOOKONAIR);
	}
}

void APlayerCharacter::DiedState()
{
	GetCharacterMovement()->Velocity = FVector(0.0f, 0.0f, 0.0f);
	StopRunning();
	if (isOnHook)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("On hook cut it!"));
		OnRemoveHook();
	}
	else 
	{
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("No hook! Died peacefully"));
	}
}

//////////////////////////////////////////////////////////////////////////
// Getter

UHookShooter *APlayerCharacter::GetHookShooter()
{
	return hookShooter;
}

//////////////////////////////////////////////////////////////////////////
// Check overlap trigger
void APlayerCharacter::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && (OtherActor != this) && OtherComp)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Overlap Begin"));

		ABasicMapChunk* basicMap = Cast<ABasicMapChunk>(OtherActor);
		if (basicMap->IsValidLowLevel() && !OtherComp->ComponentHasTag(FName("Hazard")))
		{
			if (myPlayerState == EPlayerState::USEHOOKONAIR)
			{
				//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Player bounce back"));
				AdjustBouncing();
			}
		}

		if (OtherComp->ComponentHasTag(FName("Hazard")))
		{
			ATestGameMode* testGameMode = Cast<ATestGameMode>(GetWorld()->GetAuthGameMode());
			if (testGameMode->IsValidLowLevel())
			{
				PlayerDied();
				testGameMode->GameOver(EGameOverEnum::GameOver_Pitfall);
			}
		}
	}
}

void APlayerCharacter::OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor && (OtherActor != this) && OtherComp)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Overlap End"));
	}
}