// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperCharacter.h"
#include "PlayerCharacter.generated.h"

class UTextRenderComponent;

UENUM(BlueprintType)
enum class EPlayerState : uint8
{
	IDLE UMETA(DisplayName = "Idle"),
	RUNNING UMETA(DisplayName = "Running"),
	USEHOOKONAIR UMETA(DisplayName = "UseHookOnAir"),
	NOTUSEHOOKONAIR UMETA(DisplayName = "NotUseHookOnAir")
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
	virtual void Tick(float DeltaSeconds) override;


protected:
	// The animation to play while running around
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
	class UPaperFlipbook* RunningAnimation;

	// The animation to play while idle (standing still)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
	class UPaperFlipbook* IdleAnimation;

	/** Called to choose the correct animation to play based on the character's movement state */
	void UpdateAnimation();

	void UpdateCharacter();

	void UpdatePlayerState();

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

    UFUNCTION(BlueprintCallable, Category = "Action")
        void CallJump();

	FString EnumToString(const TCHAR*, int32) const;
	void CurrentState();

public:
	APlayerCharacter();

	/** Returns SideViewCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetSideViewCameraComponent() const { return SideViewCameraComponent; }
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

	void Running();
	void Jumping();
	void StopRunning();

	EPlayerState playerState;
};
