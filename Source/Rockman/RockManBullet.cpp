// Fill out your copyright notice in the Description page of Project Settings.


#include "RockManBullet.h"
#include <Components/SphereComponent.h>
#include <PaperFlipbookComponent.h>
#include <GameFramework/ProjectileMovementComponent.h>

// Sets default values
ARockManBullet::ARockManBullet()
	:fDestoryTime(0.05f)
	,fLifeSpan(3.0f)
	,iDamage(10)
	,fBulletSpeed(30)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//球体当たり判定　作成
	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	RootComponent = SphereComponent;

	//当たり判定イベントを　追加
	FScriptDelegate DelegateBegin;
	DelegateBegin.BindUFunction(this, "OnOverlapBegin");
	SphereComponent->OnComponentBeginOverlap.Add(DelegateBegin);

	//アニメション　作成
	FlipbookComponent = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("Sprite"));
	FlipbookComponent->SetupAttachment(RootComponent);

	
	//ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComp"));

	//FPS：30
	//

}

// Called when the game starts or when spawned
void ARockManBullet::BeginPlay()
{
	Super::BeginPlay(); 

	//寿命設定　5秒
	SetLifeSpan(fLifeSpan);
	
}

// Called every frame
void ARockManBullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FRotator Rotator = GetActorRotation();

	if (Rotator.Yaw <= -179.f && Rotator.Yaw >= -180.f)
	{
		FVector Vector = GetActorLocation();
		Vector.X -= fBulletSpeed;
		SetActorLocation(Vector);
	}
	else
	{
		FVector Vector = GetActorLocation();
		Vector.X += fBulletSpeed;
		SetActorLocation(Vector);
	}
	
}

//弾の　当たり判定が　発生した時の　処理
void ARockManBullet::OnOverlapBegin(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//タイマー設定　処理：オブジェクトを消すも
	GetWorldTimerManager().SetTimer(TimerHandle_Destroy, this, &ARockManBullet::TimerDestroy, fDestoryTime);
	StopMovement();

	//ProjectileMovementComponent->StopMovementImmediately();

	SphereComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}


void ARockManBullet::TimerDestroy()
{
	Destroy();
}

void ARockManBullet::StopMovement()
{
	fBulletSpeed = 0;
}

//void ARockManBullet::OnActorOverlapBegin(AActor* OverlappedActor, AActor* OtherActor)
//{
//	//弾を消す
//	Destroy();
//
//	//OtherActorがBOSSの時 ダメージ付き
//	if (false)
//	{
//		//後で書く！
//	}
//	else
//	{
//	}
//}
