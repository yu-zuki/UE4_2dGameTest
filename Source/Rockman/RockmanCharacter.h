// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "PaperCharacter.h"
#include "RockManBullet.h"
#include "RockmanCharacter.generated.h"

class UTextRenderComponent;
class ARockManBullet;
class UArrowComponent;

//�ץ�E���`�Υ��˥᥷���״�B
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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
	class UPaperFlipbook* InjuringAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
	class UPaperFlipbook* ShootAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
	class UPaperFlipbook* JumpingShootAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
	class UPaperFlipbook* WalkingShootAnimation;

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

//------------------------------------------�ǉ���������-----------------------------------------------------------


protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameMode")
	int32 iLife;

private:
	//�e�̐�
	int32 iBullets;

protected:
	FTimerHandle TimerHandle_AddBulletsTime;

	//�e��ł���
	bool bIsShooting;

	//�e�̏[�U����
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shoot")
	float fAddBulletTime;

	UFUNCTION(Category = "Shoot")
	void BulletAdd();

	UFUNCTION(Category = "Shoot")
	void BulletSub(int32 _SubNum);

	//�e�̍쐬�ʒu
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shoot")
	UArrowComponent* BulletArrowComponent;

	//Jump���A�e�̍쐬�ʒu
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shoot")
	UArrowComponent* JumpingBulletArrowComponent;

	//�e�̎Q��
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shoot")
	TSubclassOf<ARockManBullet> BulletClass;

						//------------------------damge--------------------------
	//�_���[�W�󂯂�H
	bool bCanInjure;

	//�_���[�W�󂯂���A�A�j���V���������鎞��
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damge")
	float fInjuringAnimationTime;

	FTimerHandle TimerHandle_InjuringAnimationTime;

	//�_���[�W�̏���
	UFUNCTION(BlueprintCallable, Category = "Damge")
	void Damge(int _HpSub);

	UFUNCTION(Category = "Damge")
	bool IsInjuring();

	UFUNCTION(Category = "Damge")
	void SetInjureAnimationON();

	UFUNCTION(Category = "Damge")
	void SetInjureAnimationOFF();



	//Hp���b�N��
	bool bCanHpLock;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerHp")
	int iHP;

	//Hp��񃍃b�N������A�A�����b�N�����鎞�ԁ@�P�ʁFs
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerHp")
	float fUnlockTime;

	FTimerHandle TimerHandle_Unlock;

	//�_���[�W�󂯂����AHp���b�N���� ���G���Ԃ������鏈��
	void SetHpLock();
	void SetHpUnlock();

public:
	UFUNCTION(BlueprintCallable,Category = "PlayerHp")
	int GetPlayerHp() const;

	//HP�̑������炷�@����
	UFUNCTION(BlueprintCallable, Category = "PlayerHp")
	void HPSub(int _subHP);

	UFUNCTION(BlueprintCallable, Category = "PlayerHp")
	void HPAdd(int _addHP);

	//UFUNCTION(BlueprintCallable, Category = "PlayerHp")
	void HPCheck();

protected:
	FTimerHandle TimerHandle_HpLockFlickering;

	//Hp��񃍃b�N������A�A�����b�N�����鎞�ԁ@�P�ʁFs
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerHp")
	float fHpLockFlickeringTime;

	int32 iHpLockFlickerCount;
	void SetHpLockFlickeringTimer();
	void HpLockFlickering_Timer();
						//------------------------damge--------------------------



public:
	//UFUNCTION(BlueprintImplementableEvent, Category = "GameMode")
	//void IsGameOver();

	UFUNCTION(BlueprintImplementableEvent, Category = "GameMode")
	void IsDeath();

	

protected:
	//------------�L�[�{�[�h����-----------------
	void DebugKey();

	void RockmanShoot();
	//------------�L�[�{�[�h����-----------------

protected:

	//ShootAnimation�̏���
	FTimerHandle TimerHandle_ShootingFlagOff;
	bool bIsShootingAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Anime")
		float fShootingFlagOffTime;

	void ShootingFlagOff();

//------------------------------------------�ǉ���������-----------------------------------------------------------
public:
	ARockmanCharacter();

	/** Returns SideViewCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetSideViewCameraComponent() const { return SideViewCameraComponent; }
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }


	UFUNCTION()
	virtual void NotifyActorBeginOverlap(AActor* OtherActor)override;
};
