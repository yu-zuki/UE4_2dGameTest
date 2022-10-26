// 2022/10/18 22:59		董：射撃挙動を実装した　＋　Jump挙動を最適化しまた

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
	//弾の作成位置
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shoot")
	UArrowComponent* BulletArrowComponent;

	//IceManの弾
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shoot")
	TSubclassOf<ARockManBullet> IceBulletClass;

	UPROPERTY(VisibleAnywhere, Category = "Shoot")
	USphereComponent* ShotDetectionComponent;

	//弾の充填Falg
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

	//ShootAnimationの処理
	FTimerHandle TimerHandle_ShootingFlagOff;
	bool bIsShooting;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shoot")
	float fShootingFlagOffTime;

	void ShootingFlagOff();
				//------------------------Shoot--------------------------


				//------------------------damge--------------------------
	//ダメージ受ける？
	bool bCanInjure;

	//ダメージ受けたら、アニメションさせる時間
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damge")
		float fInjuringAnimationTime;

	FTimerHandle TimerHandle_InjuringAnimationTime;

	//ダメージの処理
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

	//Hpロック中
	bool bCanHpLock;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EnemyHp")
		int iHP;

	//Hp一回ロックしたら、アンロックかかる時間　単位：s
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EnemyHp")
		float fUnlockTime;

	FTimerHandle TimerHandle_Unlock;

	//ダメージ受けた時、Hpロックして 無敵時間をさせる処理
	void SetHpLock();
	void SetHpUnlock();

public:
	UFUNCTION(BlueprintCallable, Category = "EnemyHp")
		int GetEnemyHp() const;

	//HPの増加減らす　処理
	UFUNCTION(BlueprintCallable, Category = "EnemyHp")
		void HPSub(int _subHP);

	UFUNCTION(BlueprintCallable, Category = "EnemyHp")
		void HPAdd(int _addHP);

	//UFUNCTION(BlueprintCallable, Category = "EnemyHp")
	void HPCheck();

protected:
	FTimerHandle TimerHandle_HpLockFlickering;

	//Hp一回ロックしたら、アンロックかかる時間　単位：s
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EnemyHp")
		float fHpLockFlickeringTime;

	int32 iHpLockFlickerCount;
	void SetHpLockFlickeringTimer();
	void HpLockFlickering_Timer();
				//------------------------damge--------------------------
};
