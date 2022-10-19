// 2022/10/18 22:59		董：射撃挙動を実装した　＋　Jump挙動を最適化しまた

#include "IceMan_Boss.h"
#include "PaperFlipbookComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include <Kismet/GameplayStatics.h>
#include <GameFramework/Actor.h>
#include "RockManBullet.h"
#include <Components/ArrowComponent.h>
#include <Components/SphereComponent.h>
#include <Engine/EngineTypes.h>

AIceMan_Boss::AIceMan_Boss()
{
	GetCharacterMovement()->bOrientRotationToMovement = false;

	// Configure character movement
	GetCharacterMovement()->GravityScale = 1000.0f;
	GetCharacterMovement()->AirControl = 0.80f;
	GetCharacterMovement()->JumpZVelocity = 1000.0f;
	GetCharacterMovement()->GroundFriction = 3.0f;
	GetCharacterMovement()->MaxWalkSpeed = 1200.0f;
	GetCharacterMovement()->MaxFlySpeed = 600.0f;

	// Lock character motion onto the XZ plane, so the character can't move in or out of the screen
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->SetPlaneConstraintNormal(FVector(0.0f, -1.0f, 0.0f));

	// Behave like a traditional 2D platformer character, with a flat bottom instead of a curved capsule bottom
	// Note: This can cause a little floating when going up inclines; you can choose the tradeoff between better
	// behavior on the edge of a ledge versus inclines by setting this to true or false
	GetCharacterMovement()->bUseFlatBaseForFloorChecks = true;

	//弾フラグ用意
	bCanShootBullet.Init(false, 3);

	BulletArrowComponent = CreateDefaultSubobject<UArrowComponent>(TEXT("BulletArrowComp"));
	BulletArrowComponent->SetupAttachment(RootComponent);

	ShotDetectionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("InnerSphereComp"));
	ShotDetectionComponent->SetSphereRadius(10);
	ShotDetectionComponent->SetupAttachment(RootComponent);

	//当たり判定イベントを　追加
	ShotDetectionComponent->OnComponentBeginOverlap.AddDynamic(this, &AIceMan_Boss::OverlapInnerSphere);

	fShootingFlagOffTime = 0.5;
	bIsShooting = false;
}

void AIceMan_Boss::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	UpdateCharacter();
}

void AIceMan_Boss::UpdateAnimation()
{
	const FVector PlayerVelocity = GetVelocity();
	const float PlayerSpeedSqr = PlayerVelocity.SizeSquared();

	UPaperFlipbook* DesiredAnimation = nullptr;

	// Are we moving or standing still?
	DesiredAnimation = (PlayerSpeedSqr > 0.0f) ? RunningAnimation : IdleAnimation;

	// Jump　してますか？
	if (GetCharacterMovement()->IsFalling())
		DesiredAnimation = JumpingAnimation;

	if (bIsShooting)
	{
		//弾を打った？
		DesiredAnimation = ShootAnimation;
	}

	if (false)
	{
		//ダメージを受けてる？
		DesiredAnimation = InjuringAnimation;
	}

	if (GetSprite()->GetFlipbook() != DesiredAnimation)
	{
		GetSprite()->SetFlipbook(DesiredAnimation);
	}
}

void AIceMan_Boss::UpdateCharacter()
{
	UpdateAnimation();

	//ダメージ受けた時の処理
	if (false)
	{
		//プレイヤーの入力を無効化
		auto PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
		DisableInput(PlayerController);

		//座標情報　取得
		FRotator tempRotation = GetActorRotation();
		FVector TempDamgeVector = GetActorLocation();

		if (tempRotation.Yaw <= -179.f && tempRotation.Yaw >= -180.f)
		{
			TempDamgeVector.X += 5.0f;
		}
		else
		{
			TempDamgeVector.X -= 5.0f;
		}
		SetActorLocation(TempDamgeVector);
	}
}



//////////////////////////////////////////////////////////////////////////
// DetectJumpVertices	Jumpの頂点？　True　→　Yes　

bool AIceMan_Boss::DetectJumpVertices()
{

	float tempLocation = NowLocation.Z;
	NowLocation = GetActorLocation();

	if (NowLocation.Z < tempLocation)
	{
		return true;
	}

	return false;
}

void AIceMan_Boss::ReSetNowLocation()
{
	NowLocation = { 0.f,0.f,0.f };
}

//////////////////////////////////////////////////////////////////////////
// Shoot

void AIceMan_Boss::ShootIceBullet()
{
	if (!IceBulletClass)
	{
		return;
	}

	//座標情報　取得
	FTransform tempTransfrom = BulletArrowComponent->GetComponentTransform();
	//弾を作成
	GetWorld()->SpawnActor<ARockManBullet>(IceBulletClass, tempTransfrom);

	//弾のアニメションOn
	bIsShooting = true;
	GetWorldTimerManager().SetTimer(TimerHandle_ShootingFlagOff,this,&AIceMan_Boss::ShootingFlagOff,fShootingFlagOffTime);
}

//////////////////////////////////////////////////////////////////////////
// ShootingAnimationOff
void AIceMan_Boss::ShootingFlagOff()
{
	bIsShooting = false;
}

//////////////////////////////////////////////////////////////////////////
// BulletReLoad

void AIceMan_Boss::ReLoadBullet()
{
	for (bool& ShootBulletFlag : bCanShootBullet)
	{
		ShootBulletFlag = true;		//弾を充填
	}
}

void AIceMan_Boss::OverlapInnerSphere(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//UE_LOG(LogTemp, Warning, TEXT("ShootIceBullet"));

	if (bCanShootBullet[0])	{			//2022/10/18 董：数が多くなると、定義にActorABCをこの書き方で AActor* FlagCheckActor[3] for()
		if (OtherActor == ActorA)		{

			ShootIceBullet();

			bCanShootBullet[0] = false;

			UE_LOG(LogTemp, Warning, TEXT("ShootIceBullet"));
		}
	}

	if (bCanShootBullet[1]) {			
		if (OtherActor == ActorB) {

			ShootIceBullet();

			bCanShootBullet[1] = false;
		}
	}

	if (bCanShootBullet[2]) {			
		if (OtherActor == ActorC) {

			ShootIceBullet();

			bCanShootBullet[2] = false;
		}
	}
	
}

void AIceMan_Boss::SetDetectionActor(AActor* _ActorA, AActor* _ActorB, AActor* _ActorC)
{

	ActorA = _ActorA;
	ActorB = _ActorB;
	ActorC = _ActorC;

	//Actorがセットされてるかをチェック
	int64 NullCheck = (int64)ActorA & (int64)ActorB & (int64)ActorC;
	if (!NullCheck)
	{
		UE_LOG(LogTemp, Warning, TEXT("IceMan DetectionActor Is NULL"));
		return;
	}
}

