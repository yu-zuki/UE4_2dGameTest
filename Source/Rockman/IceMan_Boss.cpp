// Fill out your copyright notice in the Description page of Project Settings.


#include "IceMan_Boss.h"
#include "PaperFlipbookComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include <Kismet/GameplayStatics.h>
#include <GameFramework/Actor.h>

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
}


void AIceMan_Boss::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
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

	if (false)
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

	// Now setup the rotation of the controller based on the direction we are travelling
	const FVector PlayerVelocity = GetVelocity();
	float TravelDirection = PlayerVelocity.X;
	// Set the rotation so that the character faces his direction of travel.
	if (Controller != nullptr)
	{
		if (TravelDirection < 0.0f)
		{
			Controller->SetControlRotation(FRotator(0.0, 180.0f, 0.0f));
		}
		else if (TravelDirection > 0.0f)
		{
			Controller->SetControlRotation(FRotator(0.0f, 0.0f, 0.0f));
		}
	}

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

