// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RockManBullet.generated.h"

class USphereComponent;
class UPaperFlipbook;
class UPaperFlipbookComponent;
class UProjectileMovementComponent;

UCLASS()
class ROCKMAN_API ARockManBullet : public AActor
{
	GENERATED_BODY()
protected:
	//�^�C�}�[�ݒ� �I�u�W�F�N�g����������
	FTimerHandle TimerHandle_Destroy;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bullet")
	float fDestoryTime;

	//�e�@�A�j���V����
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bullet")
	UPaperFlipbook* FlipbookBullet;	
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bullet")
	UPaperFlipbookComponent* FlipbookComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bullet")
	int32 iDamage;

	//�e�@�����蔻��
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bullet")
	USphereComponent* SphereComponent;

	//�e�@�X�s�[�h
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bullet")
	float fBulletSpeed;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bullet")
	//UProjectileMovementComponent* ProjectileMovementComponent;

	//Actor �����蔻�蔭����
	UFUNCTION()
	void OnOverlapBegin(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	void TimerDestroy();
	void StopMovement();

public:	
	// Sets default values for this actor's properties
	ARockManBullet();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
