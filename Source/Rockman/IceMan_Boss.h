// 2022/10/18 22:59		ìüÅFéÀåÇãììÆÇé¿ëïÇµÇΩÅ@Å{Å@JumpãììÆÇç≈ìKâªÇµÇ‹ÇΩ

#pragma once

#include "CoreMinimal.h"
#include "PaperCharacter.h"
#include "IceMan_Boss.generated.h"

class ARockManBullet;
class UArrowComponent;
class USphereComponent;

/**
 * 
 */
UCLASS()
class ROCKMAN_API AIceMan_Boss : public APaperCharacter
{
	GENERATED_BODY()
	
	virtual void Tick(float DeltaSeconds) override;

protected:
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

	//ëOÇÃç¿ïW
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Jump")
	FVector NowLocation;
public:
	AIceMan_Boss();

	UFUNCTION(BlueprintCallable, Category = "MoveActor")
	bool DetectJumpVertices();

	UFUNCTION(BlueprintCallable, Category = "MoveActor")
	void ReSetNowLocation();

protected:
	//íeÇÃçÏê¨à íu
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shoot")
	UArrowComponent* BulletArrowComponent;

	//IceManÇÃíe
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shoot")
	TSubclassOf<ARockManBullet> IceBulletClass;

	UPROPERTY(VisibleAnywhere, Category = "Shoot")
	USphereComponent* ShotDetectionComponent;

	//íeÇÃè[ìUFalg
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

	FTimerHandle TimerHandle_ShootingFlagOff;
	bool bIsShooting;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shoot")
	float fShootingFlagOffTime;

	void ShootingFlagOff();
};
