// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperCharacter.h"
#include "IceMan_Boss.generated.h"

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
};
