// 2022/10/18 22:59		FË®ðÀµ½@{@Jump®ðÅK»µÜ½

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
	//eÌì¬Êu
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shoot")
	UArrowComponent* BulletArrowComponent;

	//IceManÌe
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shoot")
	TSubclassOf<ARockManBullet> IceBulletClass;

	UPROPERTY(VisibleAnywhere, Category = "Shoot")
	USphereComponent* ShotDetectionComponent;

	//eÌ[UFalg
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

	//ShootAnimationÌ
	FTimerHandle TimerHandle_ShootingFlagOff;
	bool bIsShooting;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shoot")
	float fShootingFlagOffTime;

	void ShootingFlagOff();
				//------------------------Shoot--------------------------


				//------------------------damge--------------------------
	//_[Wó¯éH
	bool bCanInjure;

	//_[Wó¯½çAAjV³¹éÔ
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damge")
		float fInjuringAnimationTime;

	FTimerHandle TimerHandle_InjuringAnimationTime;

	//_[WÌ
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

	//HpbN
	bool bCanHpLock;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EnemyHp")
		int iHP;

	//HpêñbNµ½çAAbN©©éÔ@PÊFs
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EnemyHp")
		float fUnlockTime;

	FTimerHandle TimerHandle_Unlock;

	//_[Wó¯½AHpbNµÄ ³GÔð³¹é
	void SetHpLock();
	void SetHpUnlock();

public:
	UFUNCTION(BlueprintCallable, Category = "EnemyHp")
		int GetEnemyHp() const;

	//HPÌÁ¸ç·@
	UFUNCTION(BlueprintCallable, Category = "EnemyHp")
		void HPSub(int _subHP);

	UFUNCTION(BlueprintCallable, Category = "EnemyHp")
		void HPAdd(int _addHP);

	//UFUNCTION(BlueprintCallable, Category = "EnemyHp")
	void HPCheck();

protected:
	FTimerHandle TimerHandle_HpLockFlickering;

	//HpêñbNµ½çAAbN©©éÔ@PÊFs
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EnemyHp")
		float fHpLockFlickeringTime;

	int32 iHpLockFlickerCount;
	void SetHpLockFlickeringTimer();
	void HpLockFlickering_Timer();
				//------------------------damge--------------------------
};
