// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine.h"
#include "PaperCharacter.h"
#include "HookShooter.h"
#include "SoundSystem.h"
#include "PlayerCharacter.generated.h"

class UTextRenderComponent;

UENUM(BlueprintType)
enum class EPlayerState : uint8
{
	IDLE UMETA(DisplayName = "Idle"),
	RUNNING UMETA(DisplayName = "Running"),
	JUMPING UMETA(DisplayName = "Jumping"),
	SHOOTING UMETA(DisplayName = "Shooting"),
	USEHOOKONAIR UMETA(DisplayName = "UseHookOnAir"),
	NOTUSEHOOKONAIR UMETA(DisplayName = "NotUseHookOnAir"),
	DIED UMETA(DisplayName = "Died"),
	LANDING UMETA(DisplayName = "Landing"),
};

/**
 * 
 */
UCLASS(config=Game)
class GRAPPLINGHOOK_API APlayerCharacter : public APaperCharacter
{
	GENERATED_BODY()

	// TODO create enum class for player state

	/** Side view camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* SideViewCameraComponent;

	/** Camera boom positioning the camera beside the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	

	UTextRenderComponent* TextComponent;

	// Called when the game starts
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;


protected:
	// The animation to play while running around
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
	class UPaperFlipbook* RunningAnimation;

	// The animation to play while shooting rope
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
	class UPaperFlipbook* ShootRopeAnimation;

	// The animation to play while jumping
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
	class UPaperFlipbook* JumpingAnimation;

	// The animation to play while landing
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
	class UPaperFlipbook* LandingAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Attribute)
	bool pressJump = false;

	/** Update animation event in blueprint */
	UFUNCTION(BlueprintImplementableEvent, Category = Animations)
	void UpdateAnimation();

	void UpdateCharacter();

	void UpdatePlayerState();

	void UpdatePlayerRun();

	/** State behavior */
	void IdleState();
	void RunningState();
	void HookOnAirState();
	void NoHookOnAirState();
	void DiedState();
	void LandingState();
	void ShootingState();

	/** Handle touch inputs. */
	void TouchStarted(const ETouchIndex::Type FingerIndex, const FVector Location);

	/** Handle touch stop event. */
	void TouchStopped(const ETouchIndex::Type FingerIndex, const FVector Location);

	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;
	// End of APawn interface

private:
	UPROPERTY(EditAnywhere, Category = Attribute)
	float movementSpeed = 1.0f;

	/// Bounce from static value force and reduce over the time
	UPROPERTY(EditAnywhere, Category = Attribute)
	float staticBounceForce = 75000.0f;

	UPROPERTY(EditAnywhere, Category = Attribute)
	float reduceBounceForceRatio = 0.8f;

	/// Bounce calculate by using force from player swing 
	UPROPERTY(EditAnywhere, Category = Attribute)
	float bounceRatio = 150.0f;
	
	UPROPERTY(EditAnywhere, Category = Attribute)
	float minBounceForce = 50000.0f;

	UPROPERTY(EditAnywhere, Category = Attribute)
	float maxBounceForce = 75000.0f;

	UPROPERTY(VisibleAnywhere, Category = Attribute)
	float bounceForce = staticBounceForce;

	UPROPERTY(VisibleAnywhere, Category = Attribute)
	bool isOnGround = false;

	UPROPERTY(VisibleAnywhere, Category = Attribute)
	bool isOnHook = false;

    UFUNCTION(BlueprintCallable, Category = "Action")
    void CallJump();

	FString EnumToString(const TCHAR*, int32) const;
	UHookShooter* hookShooter = nullptr;

	void FindHookShooterComponent();
	void CurrentState();
	void AdjustBouncing();
	void BounceByPreviousForce();
	void BounceByStaticForce();

public:
	APlayerCharacter();

	/** Returns SideViewCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetSideViewCameraComponent() const { return SideViewCameraComponent; }
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

	/** Create trigger capsule */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Trigger Capsule")
	class UCapsuleComponent* TriggerCapsule;
	/**/

	/** Create player state variable */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Enum)
	EPlayerState myPlayerState;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player")
	bool useMagnetic = false;

	UFUNCTION(BlueprintCallable, Category = "Player")
	UHookShooter* GetHookShooter();

	UFUNCTION(BlueprintCallable, Category = "Player")
	void PlayerDied();

	UFUNCTION(BlueprintCallable, Category = "Player")
	bool IsDead();

	UFUNCTION(BlueprintCallable, Category = "Player")
	void SetPlayerState(EPlayerState state);

	UFUNCTION(BlueprintImplementableEvent, Category = "Player")
	void OnPlayerJump();

	UFUNCTION(BlueprintImplementableEvent, Category = "AnyString")
	void OnRemoveHook();
	
	// declare overlap begin function
	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	// declare overlap end function
	UFUNCTION()
	void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	void Running();
	void Jumping();
	void StopRunning();
};
