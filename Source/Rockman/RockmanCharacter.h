// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "PaperCharacter.h"
#include "RockManBullet.h"
#include "RockmanCharacter.generated.h"

class UTextRenderComponent;
class ARockManBullet;
class UArrowComponent;

//₯Χ₯E€₯δ©`€Ξ₯’₯Λ₯α₯·₯η₯σΧ΄B
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

//------------------------------------------ΗΑ΅½ΰΜ-----------------------------------------------------------


protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameMode")
	int32 iLife;

private:
	//eΜ
	int32 iBullets;

protected:
	FTimerHandle TimerHandle_AddBulletsTime;

	//eπΕΑ½
	bool bIsShooting;

	//eΜ[UΤ
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shoot")
	float fAddBulletTime;

	UFUNCTION(Category = "Shoot")
	void BulletAdd();

	UFUNCTION(Category = "Shoot")
	void BulletSub(int32 _SubNum);

	//eΜμ¬Κu
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shoot")
	UArrowComponent* BulletArrowComponent;

	//eΜQΖ
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shoot")
	TSubclassOf<ARockManBullet> BulletClass;

						//------------------------damge--------------------------
	//_[Wσ―ιH
	bool bCanInjure;

	//_[Wσ―½ηAAjV³ΉιΤ
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damge")
	float fInjuringAnimationTime;

	FTimerHandle TimerHandle_InjuringAnimationTime;

	//_[WΜ
	UFUNCTION(BlueprintCallable, Category = "Damge")
	void Damge(int _HpSub);

	UFUNCTION(Category = "Damge")
	bool IsInjuring();

	UFUNCTION(Category = "Damge")
	void SetInjureAnimationON();

	UFUNCTION(Category = "Damge")
	void SetInjureAnimationOFF();



	//HpbN
	bool bCanHpLock;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerHp")
	int iHP;

	//HpκρbN΅½ηAAbN©©ιΤ@PΚFs
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerHp")
	float fUnlockTime;

	FTimerHandle TimerHandle_Unlock;

	//_[Wσ―½AHpbN΅Δ ³GΤπ³Ήι
	void SetHpLock();
	void SetHpUnlock();

public:
	UFUNCTION(BlueprintCallable,Category = "PlayerHp")
	int GetPlayerHp() const;

	//HPΜΑΈη·@
	UFUNCTION(BlueprintCallable, Category = "PlayerHp")
	void HPSub(int _subHP);

	UFUNCTION(BlueprintCallable, Category = "PlayerHp")
	void HPAdd(int _addHP);

	//UFUNCTION(BlueprintCallable, Category = "PlayerHp")
	void HPCheck();
						//------------------------damge--------------------------



public:
	UFUNCTION(BlueprintImplementableEvent, Category = "GameMode")
	void IsGameOver();

	UFUNCTION(BlueprintImplementableEvent, Category = "GameMode")
	void IsDeath();

	

protected:
	//------------L[{[hόΝ-----------------
	void DebugKey();

	void RockmanShoot();
	//------------L[{[hόΝ-----------------

//------------------------------------------ΗΑ΅½ΰΜ-----------------------------------------------------------
public:
	ARockmanCharacter();

	/** Returns SideViewCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetSideViewCameraComponent() const { return SideViewCameraComponent; }
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }


	UFUNCTION()
	virtual void NotifyActorBeginOverlap(AActor* OtherActor)override;
};
