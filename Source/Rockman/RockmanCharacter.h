// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "PaperCharacter.h"
#include "RockManBullet.h"
#include "RockmanCharacter.generated.h"

class UTextRenderComponent;
class ARockManBullet;
class UArrowComponent;

//･ﾗ･・､･茫`､ﾎ･｢･ﾋ･皈ｷ･逾ｴ腺
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

//------------------------------------------追加したもの-----------------------------------------------------------


protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameMode")
	int32 iLife;

private:
	//弾の数
	int32 iBullets;

protected:
	FTimerHandle TimerHandle_AddBulletsTime;

	//弾を打った
	bool bIsShooting;

	//弾の充填時間
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shoot")
	float fAddBulletTime;

	UFUNCTION(Category = "Shoot")
	void BulletAdd();

	UFUNCTION(Category = "Shoot")
	void BulletSub(int32 _SubNum);

	//弾の作成位置
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shoot")
	UArrowComponent* BulletArrowComponent;

	//Jump中、弾の作成位置
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shoot")
	UArrowComponent* JumpingBulletArrowComponent;

	//弾の参照
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shoot")
	TSubclassOf<ARockManBullet> BulletClass;

						//------------------------damge--------------------------
	//ダメージ受ける？
	bool bCanInjure;

	//ダメージ受けたら、アニメションさせる時間
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damge")
	float fInjuringAnimationTime;

	FTimerHandle TimerHandle_InjuringAnimationTime;

	//ダメージの処理
	UFUNCTION(BlueprintCallable, Category = "Damge")
	void Damge(int _HpSub);

	UFUNCTION(Category = "Damge")
	bool IsInjuring();

	UFUNCTION(Category = "Damge")
	void SetInjureAnimationON();

	UFUNCTION(Category = "Damge")
	void SetInjureAnimationOFF();



	//Hpロック中
	bool bCanHpLock;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerHp")
	int iHP;

	//Hp一回ロックしたら、アンロックかかる時間　単位：s
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerHp")
	float fUnlockTime;

	FTimerHandle TimerHandle_Unlock;

	//ダメージ受けた時、Hpロックして 無敵時間をさせる処理
	void SetHpLock();
	void SetHpUnlock();

public:
	UFUNCTION(BlueprintCallable,Category = "PlayerHp")
	int GetPlayerHp() const;

	//HPの増加減らす　処理
	UFUNCTION(BlueprintCallable, Category = "PlayerHp")
	void HPSub(int _subHP);

	UFUNCTION(BlueprintCallable, Category = "PlayerHp")
	void HPAdd(int _addHP);

	//UFUNCTION(BlueprintCallable, Category = "PlayerHp")
	void HPCheck();

protected:
	FTimerHandle TimerHandle_HpLockFlickering;

	//Hp一回ロックしたら、アンロックかかる時間　単位：s
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
	//------------キーボード入力-----------------
	void DebugKey();

	void RockmanShoot();
	//------------キーボード入力-----------------

protected:

	//ShootAnimationの処理
	FTimerHandle TimerHandle_ShootingFlagOff;
	bool bIsShootingAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Anime")
		float fShootingFlagOffTime;

	void ShootingFlagOff();

//------------------------------------------追加したもの-----------------------------------------------------------
public:
	ARockmanCharacter();

	/** Returns SideViewCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetSideViewCameraComponent() const { return SideViewCameraComponent; }
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }


	UFUNCTION()
	virtual void NotifyActorBeginOverlap(AActor* OtherActor)override;
};
