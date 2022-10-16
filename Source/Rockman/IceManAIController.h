// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "GameFramework/Actor.h"
#include "IceManAIController.generated.h"

class AActor;

/**
 * 
 */
UCLASS()
class ROCKMAN_API AIceManAIController : public AAIController
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MoveActor")
	AActor* ActorA;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MoveActor")
	AActor* ActorB;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MoveActor")
	AActor* ActorC;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MoveActor")
	int32 iLocationSelect;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MoveActor")
	bool bCanRightMove;

	//ŽŸ‚Ì–Ú“I‚ðŽæ“¾
	UFUNCTION(BlueprintCallable, Category = "MoveActor")
	AActor* GetNextMovetoActor();
public:
	AIceManAIController();
};
