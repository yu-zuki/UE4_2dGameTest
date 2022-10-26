// 2022/10/18 22:59		���F�ˌ����������������@�{�@Jump�������œK�����܂�

#pragma once

#include "CoreMinimal.h"
#include "PaperCharacter.h"
#include "IceMan_Boss.generated.h"

class ARockManBullet;
class UArrowComponent;
class USphereComponent;

UENUM(BlueprintType)
enum class EEnemyName : uint8
{
	CutMan = 0x0,
	FireMan,
	IceMan
};

/**
 * 
 */
UCLASS()
class ROCKMAN_API AIceMan_Boss : public APaperCharacter
{
	GENERATED_BODY()
	
	virtual void Tick(float DeltaSeconds) override;

	EEnemyName EnemyName;

public:
	UFUNCTION(BlueprintImplementableEvent, Category = "GameClear")
	void IsDeath();

protected:
	UFUNCTION(BlueprintCallable, Category = "EnemyName")
	EEnemyName GetEnemyName() const;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
		class UPaperFlipbook* StartAnimation;

	// The animation to play while running around
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
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

	void UpdateCharacter();

				//------------------------Move--------------------------
	FVector NowLocation;
public:
	AIceMan_Boss();

	UFUNCTION(BlueprintCallable, Category = "MoveActor")
	bool DetectJumpVertices();

	UFUNCTION(BlueprintCallable, Category = "MoveActor")
	void ReSetNowLocation();
				//------------------------Move--------------------------


				//------------------------Shoot--------------------------
protected:
	//�e�̍쐬�ʒu
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shoot")
	UArrowComponent* BulletArrowComponent;

	//IceMan�̒e
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shoot")
	TSubclassOf<ARockManBullet> IceBulletClass;

	UPROPERTY(VisibleAnywhere, Category = "Shoot")
	USphereComponent* ShotDetectionComponent;

	//�e�̏[�UFalg
	TArray<bool> bCanShootBullet;

	UFUNCTION(BlueprintCallable, Category = "Shoot")
	void ShootIceBullet();

	UFUNCTION(BlueprintCallable, Category = "Shoot")
	void ReLoadBullet();

	UFUNCTION()
	void OverlapInnerSphere(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shoot")
		AActor* ActorA;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shoot")
		AActor* ActorB;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shoot")
		AActor* ActorC;

	UFUNCTION(BlueprintCallable, Category = "Shoot")
	void SetDetectionActor(AActor* _ActorA, AActor* _ActorB, AActor* _ActorC);
	/*UFUNCTION(BlueprintCallable, Category = "Shoot")
	void ShotDetectionComponent();*/

	//ShootAnimation�̏���
	FTimerHandle TimerHandle_ShootingFlagOff;
	bool bIsShooting;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shoot")
	float fShootingFlagOffTime;

	void ShootingFlagOff();
				//------------------------Shoot--------------------------


				//------------------------damge--------------------------
	//�_���[�W�󂯂�H
	bool bCanInjure;

	//�_���[�W�󂯂���A�A�j���V���������鎞��
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damge")
		float fInjuringAnimationTime;

	FTimerHandle TimerHandle_InjuringAnimationTime;

	//�_���[�W�̏���
	UFUNCTION(BlueprintCallable, Category = "Damge")
	virtual void Damge(int _HpSub);

	UFUNCTION(Category = "Damge")
		bool IsInjuring();

	UFUNCTION(Category = "Damge")
		void SetInjureAnimationON();

	UFUNCTION(Category = "Damge")
		void SetInjureAnimationOFF();

	UFUNCTION(BlueprintImplementableEvent, Category = "Sound")
	void EnemyPlaySound();

	//Hp���b�N��
	bool bCanHpLock;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EnemyHp")
		int iHP;

	//Hp��񃍃b�N������A�A�����b�N�����鎞�ԁ@�P�ʁFs
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EnemyHp")
		float fUnlockTime;

	FTimerHandle TimerHandle_Unlock;

	//�_���[�W�󂯂����AHp���b�N���� ���G���Ԃ������鏈��
	void SetHpLock();
	void SetHpUnlock();

public:
	UFUNCTION(BlueprintCallable, Category = "EnemyHp")
		int GetEnemyHp() const;

	//HP�̑������炷�@����
	UFUNCTION(BlueprintCallable, Category = "EnemyHp")
		void HPSub(int _subHP);

	UFUNCTION(BlueprintCallable, Category = "EnemyHp")
		void HPAdd(int _addHP);

	//UFUNCTION(BlueprintCallable, Category = "EnemyHp")
	void HPCheck();

protected:
	FTimerHandle TimerHandle_HpLockFlickering;

	//Hp��񃍃b�N������A�A�����b�N�����鎞�ԁ@�P�ʁFs
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EnemyHp")
		float fHpLockFlickeringTime;

	int32 iHpLockFlickerCount;
	void SetHpLockFlickeringTimer();
	void HpLockFlickering_Timer();
				//------------------------damge--------------------------
};
