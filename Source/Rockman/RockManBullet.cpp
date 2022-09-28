// Fill out your copyright notice in the Description page of Project Settings.


#include "RockManBullet.h"
#include <Components/SphereComponent.h>
#include <PaperFlipbookComponent.h>
#include <GameFramework/ProjectileMovementComponent.h>

// Sets default values
ARockManBullet::ARockManBullet()
	:fDestoryTime(0.05f)
	,iDamage(10)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//���̓����蔻��@�쐬
	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	RootComponent = SphereComponent;

	FScriptDelegate DelegateBegin;
	DelegateBegin.BindUFunction(this, "OnOverlapBegin");
	SphereComponent->OnComponentBeginOverlap.Add(DelegateBegin);

	//�A�j���V�����@�쐬
	FlipbookComponent = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("Sprite"));
	FlipbookComponent->SetupAttachment(RootComponent);

	
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComp"));

}

// Called when the game starts or when spawned
void ARockManBullet::BeginPlay()
{
	Super::BeginPlay(); 

	//�����ݒ�@5�b
	SetLifeSpan(5);
	
}

// Called every frame
void ARockManBullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

//�e�́@�����蔻�肪�@�����������́@����
void ARockManBullet::OnOverlapBegin(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//�^�C�}�[�ݒ�@�����F�I�u�W�F�N�g��������
	GetWorldTimerManager().SetTimer(TimerHandle_Destroy, this, &ARockManBullet::TimerDestroy, fDestoryTime);
	ProjectileMovementComponent->StopMovementImmediately();

	SphereComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}


void ARockManBullet::TimerDestroy()
{
	Destroy();
}

//void ARockManBullet::OnActorOverlapBegin(AActor* OverlappedActor, AActor* OtherActor)
//{
//	//�e������
//	Destroy();
//
//	//OtherActor��BOSS�̎� �_���[�W�t��
//	if (false)
//	{
//		//��ŏ����I
//	}
//	else
//	{
//	}
//}
