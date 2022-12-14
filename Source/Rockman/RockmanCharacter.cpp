// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "RockmanCharacter.h"
#include "PaperFlipbookComponent.h"
#include "Components/TextRenderComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "Camera/CameraComponent.h"
#include "RockManBullet.h"
#include <Components/ArrowComponent.h>
#include "Kismet/GameplayStatics.h"
#include "RockManGameInstance.h"

DEFINE_LOG_CATEGORY_STATIC(SideScrollerCharacter, Log, All);

//////////////////////////////////////////////////////////////////////////
// ARockmanCharacter

ARockmanCharacter::ARockmanCharacter()
	 :iBullets(3)
	 ,bIsShooting(false)
	 ,iLife(100)
	 ,fAddBulletTime(1.0f)
	 ,bCanInjure(false)
	 ,bCanHpLock(false)
	 ,fInjuringAnimationTime(1.0f)
	 ,iHP(25)
	 ,fUnlockTime(1.0f)
{
	// Use only Yaw from the controller and ignore the rest of the rotation.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = true;
	bUseControllerRotationRoll = false;

	// Set the size of our collision capsule.
	GetCapsuleComponent()->SetCapsuleHalfHeight(96.0f);
	GetCapsuleComponent()->SetCapsuleRadius(40.0f);

	// Create a camera boom attached to the root (capsule)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 500.0f;
	CameraBoom->SocketOffset = FVector(0.0f, 0.0f, 75.0f);
	CameraBoom->SetUsingAbsoluteRotation(true);
	CameraBoom->bDoCollisionTest = false;
	CameraBoom->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));
	

	// Create an orthographic camera (no perspective) and attach it to the boom
	SideViewCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("SideViewCamera"));
	SideViewCameraComponent->ProjectionMode = ECameraProjectionMode::Orthographic;
	SideViewCameraComponent->OrthoWidth = 2048.0f;
	SideViewCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);

	// Prevent all automatic rotation behavior on the camera, character, and camera component
	CameraBoom->SetUsingAbsoluteRotation(true);
	SideViewCameraComponent->bUsePawnControlRotation = false;
	SideViewCameraComponent->bAutoActivate = true;
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

    // 	TextComponent = CreateDefaultSubobject<UTextRenderComponent>(TEXT("IncarGear"));
    // 	TextComponent->SetRelativeScale3D(FVector(3.0f, 3.0f, 3.0f));
    // 	TextComponent->SetRelativeLocation(FVector(35.0f, 5.0f, 20.0f));
    // 	TextComponent->SetRelativeRotation(FRotator(0.0f, 90.0f, 0.0f));
    // 	TextComponent->SetupAttachment(RootComponent);

	// Enable replication on the Sprite component so animations show up when networked
	GetSprite()->SetIsReplicated(true);
	bReplicates = true;

	//--------------------????????????-----------------------------------

	//?e?????????W?p
	BulletArrowComponent = CreateDefaultSubobject<UArrowComponent>(TEXT("BulletArrowComp"));
	BulletArrowComponent->SetupAttachment(RootComponent);


	JumpingBulletArrowComponent = CreateDefaultSubobject<UArrowComponent>(TEXT("JumpBulletArrowComp"));
	JumpingBulletArrowComponent->SetupAttachment(RootComponent);

	//HpLock
	iHpLockFlickerCount = 0;
	fHpLockFlickeringTime = 0.3f;

	//ShootAnimation???p?????[?^
	fShootingFlagOffTime = 0.5;
	bIsShootingAnimation = false;
	//--------------------????????????-----------------------------------
}

//////////////////////////////////////////////////////////////////////////
// Animation

void ARockmanCharacter::UpdateAnimation()
{
	const FVector PlayerVelocity = GetVelocity();
	const float PlayerSpeedSqr = PlayerVelocity.SizeSquared();

	UPaperFlipbook* DesiredAnimation = nullptr;

	// Are we moving or standing still?
	DesiredAnimation = (PlayerSpeedSqr > 0.0f) ? RunningAnimation : IdleAnimation;

	// Jump?
	if (GetCharacterMovement()->IsFalling())
		DesiredAnimation = JumpingAnimation;

	// Shoot?
	if (bIsShootingAnimation)
	{
		
		DesiredAnimation = ShootAnimation;
	}

	// Walk & Shoot?
	if (PlayerSpeedSqr > 0.0f && bIsShootingAnimation)
	{
		DesiredAnimation = WalkingShootAnimation;
	}

	// Jump & Shoot?
	if (bIsShootingAnimation && GetCharacterMovement()->IsFalling())
	{
		DesiredAnimation = JumpingShootAnimation;
	}


	// Injure?
	if (bCanInjure)
	{
		//?_???[?W???????????H
		DesiredAnimation = InjuringAnimation;
	}
	
	// Set Animation
	if (GetSprite()->GetFlipbook() != DesiredAnimation)
	{
		GetSprite()->SetFlipbook(DesiredAnimation);
	}

}

void ARockmanCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	
	UpdateCharacter();	

	HPCheck();
}


//////////////////////////////////////////////////////////////////////////
// Input

void ARockmanCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Note: the 'Jump' action and the 'MoveRight' axis are bound to actual keys/buttons/sticks in DefaultInput.ini (editable from Project Settings..Input)
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
	PlayerInputComponent->BindAxis("MoveRight", this, &ARockmanCharacter::MoveRight);
	PlayerInputComponent->BindAction("Debug", IE_Pressed, this, &ARockmanCharacter::DebugKey);
	PlayerInputComponent->BindAction("Shoot", IE_Pressed, this, &ARockmanCharacter::RockmanShoot);

	PlayerInputComponent->BindTouch(IE_Pressed, this, &ARockmanCharacter::TouchStarted);
	PlayerInputComponent->BindTouch(IE_Released, this, &ARockmanCharacter::TouchStopped);
}

void ARockmanCharacter::BulletAdd()
{
	iBullets = 3;
}

void ARockmanCharacter::BulletSub(int32 _SubNum)
{
	iBullets -= _SubNum;

	if (iBullets < 0)
	{
		iBullets = 0;
	}
}
//////////////////////////////////////////////////////////////////////////
// Damge

void ARockmanCharacter::Damge(int _HpSub = 0)
{
	if (bCanHpLock)
	{
		return;
	}
	else
	{
		HPSub(_HpSub);

		SetInjureAnimationON();

		SetHpLock();
		
		SetHpLockFlickeringTimer();

		PlayerPlaySound();
	}
}

//////////////////////////////////////////////////////////////////////////
// InjureAnim

bool ARockmanCharacter::IsInjuring()
{
	return bCanInjure;
}

void ARockmanCharacter::SetInjureAnimationON()
{
	bCanInjure = true;

	GetWorldTimerManager().SetTimer(TimerHandle_InjuringAnimationTime, this, &ARockmanCharacter::SetInjureAnimationOFF, fInjuringAnimationTime);
}

void ARockmanCharacter::SetInjureAnimationOFF()
{
	bCanInjure = false;

	//?v???C???[?????????L????
	auto PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	EnableInput(PlayerController);
}

//////////////////////////////////////////////////////////////////////////
// HP

void ARockmanCharacter::HPSub(int _subHP = 0)
{
	iHP -= _subHP;
	if (iHP < 0)
	{
		iHP = 0;
	}
}

void ARockmanCharacter::HPAdd(int  _addHP = 0)
{
	iHP += _addHP;
	if (iHP > 25)
	{
		iHP = 25;
	}
}


void ARockmanCharacter::HPCheck()
{
	//UGameInstance* TempGameInstance = GetGameInstance();
	//URockManGameInstance* TempRockManGameInstance = Cast<URockManGameInstance>(GetGameInstance());
	//if (TempRockManGameInstance)
	//{
	//	//Life 0 is GameOver
	//	if (TempRockManGameInstance->getPlayerLife() <= 0)
	//	{
	//		IsGameOver();
	//	}
	//}

	//?v???C???[??HP??0?????@????
	if (iHP <= 0)
	{
		IsDeath();
	}
}

//////////////////////////////////////////////////////////////////////////
// PlayerFlickering

void ARockmanCharacter::SetHpLockFlickeringTimer()
{
	UWorld* world = this->GetWorld();
	if (world)
	{
		iHpLockFlickerCount = 0;
		world->GetTimerManager().SetTimer(TimerHandle_HpLockFlickering,this,&ARockmanCharacter::HpLockFlickering_Timer,fHpLockFlickeringTime,true);
	}
}

void ARockmanCharacter::HpLockFlickering_Timer()
{
	UE_LOG(LogTemp, Warning, TEXT("FlickeringAnimation_Timer exec Succeed!"));

	//Player??Flickering??????
	bool bNewVisible = GetSprite()->GetVisibleFlag();
	GetSprite()->SetVisibility(!bNewVisible);

	
	//----------------------------HPLock?????????????????ATimerClear-----------------------------
	
	//----------------------------?^?C?}?[??50?????s??????Clear----------------------------------
	
	iHpLockFlickerCount++;
	
	if (iHpLockFlickerCount > 5000 || bCanHpLock != true)
	{
		//Actor NoHidden
		GetSprite()->SetVisibility(true);

		//GetSprite()->
		//TimerClear
		UWorld* world = this->GetWorld();
		if (world)
		{
			world->GetTimerManager().ClearTimer(TimerHandle_HpLockFlickering);
			UE_LOG(LogTemp, Warning, TEXT("FlickeringAnimation_Timer clear Succeed!"));
		}
	}

	//----------------------------?^?C?}?[??50?????s??????Clear--------------------------------

	//----------------------------HPLock?????????????????ATimerClear-----------------------------
}

//////////////////////////////////////////////////////////////////////////
// HpLock

void ARockmanCharacter::SetHpLock()
{
	bCanHpLock = true;
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldDynamic, ECollisionResponse::ECR_Ignore);

	GetWorldTimerManager().SetTimer(TimerHandle_Unlock, this, &ARockmanCharacter::SetHpUnlock, fUnlockTime);
}

void ARockmanCharacter::SetHpUnlock()
{
	bCanHpLock = false;
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldDynamic, ECollisionResponse::ECR_Block);
}

int ARockmanCharacter::GetPlayerHp() const
{
	return iHP;
}

void ARockmanCharacter::DebugKey()
{
	//????????????
	iHP = 0;
}


//////////////////////////////////////////////////////////////////////////
// Overlap
void ARockmanCharacter::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	
}



//////////////////////////////////////////////////////////////////////////
// Shoot

void ARockmanCharacter::RockmanShoot()
{
	//
	if (BulletClass)
	{
		if (iBullets > 0)
		{
			//1?b???A?e???[?U
			GetWorldTimerManager().SetTimer(TimerHandle_AddBulletsTime, this, &ARockmanCharacter::BulletAdd, fAddBulletTime);

			//Bullte???@- 1
			BulletSub(1);

			//?e???A?j???V????On
			bIsShootingAnimation = true;
			GetWorldTimerManager().SetTimer(TimerHandle_ShootingFlagOff, this, &ARockmanCharacter::ShootingFlagOff, fShootingFlagOffTime);


			if (GetCharacterMovement()->IsFalling())
			{
				FTransform tempTransfrom = JumpingBulletArrowComponent->GetComponentTransform();
				//?e??????
				GetWorld()->SpawnActor<ARockManBullet>(BulletClass, tempTransfrom);
			}
			else
			{

				//???W?????@????
				FTransform tempTransfrom = BulletArrowComponent->GetComponentTransform();
				//?e??????
				GetWorld()->SpawnActor<ARockManBullet>(BulletClass, tempTransfrom);

			}

					}
	}
}

void ARockmanCharacter::ShootingFlagOff()
{
	bIsShootingAnimation = false;
}

//////////////////////////////////////////////////////////////////////////
// Move

void ARockmanCharacter::MoveRight(float Value)
{
	/*UpdateChar();*/

	// Apply the input to the character motion
	AddMovementInput(FVector(1.0f, 0.0f, 0.0f), Value);
}

void ARockmanCharacter::TouchStarted(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	// Jump on any touch
	Jump();
}

void ARockmanCharacter::TouchStopped(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	// Cease jumping once touch stopped
	StopJumping();
}

//////////////////////////////////////////////////////////////////////////
// UpdateCharacter

void ARockmanCharacter::UpdateCharacter()
{
	// Update animation to match the motion
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

	//?_???[?W??????????????
	if (bCanInjure)
	{
		//?v???C???[??????????????
		auto PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
		DisableInput(PlayerController);

		//???W?????@????
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
