// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "PaperCharacter.h"
#include "RockmanCharacter.generated.h"

class UTextRenderComponent;

//�ץ쥤��`�Υ��˥᥷���״�B
UENUM(BlueprintType)
enum class ePlayerStatus : uint8
{
	Idle = 0x0,
	Walk,
	Jump

};

/**
 * This class is the default character for Rockman, and it is responsible for all
 * physical interaction between the player and the world.
 *
 * The capsule component (inherited from ACharacter) handles collision with the world
 * The CharacterMovementComponent (inherited from ACharacter) handles movement of the collision capsule
 * The Sprite component (inherited from APaperCharacter) handles the visuals
 */
UCLASS(config=Game)
class ARockmanCharacter : public APaperCharacter
{
	GENERATED_BODY()

	/** Side view camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera, meta=(AllowPrivateAccess="true"))
	class UCameraComponent* SideViewCameraComponent;

	/** Camera boom positioning the camera beside the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	UTextRenderComponent* TextComponent;
	virtual void Tick(float DeltaSeconds) override;
protected:
	// The animation to play while running around
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Animations)
	class UPaperFlipbook* RunningAnimation;

	// The animation to play while idle (standing still)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
	class UPaperFlipbook* IdleAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
	class UPaperFlipbook* JumpingAnimation;

	/** Called to choose the correct animation to play based on the character's movement state */
	void UpdateAnimation();

	/** Called for side to side input */
	void MoveRight(float Value);

	void UpdateCharacter();

	/** Handle touch inputs. */
	void TouchStarted(const ETouchIndex::Type FingerIndex, const FVector Location);

	/** Handle touch stop event. */
	void TouchStopped(const ETouchIndex::Type FingerIndex, const FVector Location);

	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;
	// End of APawn interface

//------------------------------------------׷�Ӥ������-----------------------------------------------------------
	float fHP;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameMode")
	int32 iLife;

	//��������������
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Jump")
	float fGravityScale;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Jump")
	float fJumpZVelocity;

	void DebugKey();
public:
	UFUNCTION(BlueprintImplementableEvent, Category = "GameMode")
	void IsGameOver();

	UFUNCTION(BlueprintImplementableEvent, Category = "GameMode")
	void IsDeath();
//------------------------------------------׷�Ӥ������-----------------------------------------------------------
public:
	ARockmanCharacter();

	/** Returns SideViewCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetSideViewCameraComponent() const { return SideViewCameraComponent; }
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
};
