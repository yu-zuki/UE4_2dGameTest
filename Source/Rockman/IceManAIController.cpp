// Fill out your copyright notice in the Description page of Project Settings.


#include "IceManAIController.h"
#include <GameFramework/Actor.h>

AIceManAIController::AIceManAIController()
{
	bCanRightMove = true;
	iLocationSelect = 0;
}

//////////////////////////////////////////////////////////////////////////
// NextMove

AActor* AIceManAIController::GetNextMovetoActor()
{
	if (bCanRightMove)
	{
		iLocationSelect += 1;
		if (iLocationSelect >= 3) {
			bCanRightMove = false;
		}
	}
	else
	{
		iLocationSelect -= 1;
		if (iLocationSelect <= 1) {
			bCanRightMove = true;
		}
	}

	//Actorがセットされてるかをチェック
	int64 NullCheck = (int64)ActorA & (int64)ActorB & (int64)ActorC;
	if (!NullCheck)
	{
		UE_LOG(LogTemp, Warning, TEXT("IceManController_NextMoveToActor Is NULL"));
		return nullptr;
	}

	if (iLocationSelect == 1)
	{
		return ActorA;
	}
	else if (iLocationSelect == 2)
	{
		return ActorB;
	}
	else if (iLocationSelect == 3)
	{
		return ActorC;
	}
	else 
	{
		return nullptr;
	}

	
}

void AIceManAIController::SetNavActor(AActor* _ActorA, AActor* _ActorB, AActor* _ActorC)
{
	ActorA = _ActorA;
	ActorB = _ActorB;
	ActorC = _ActorC;

	//Actorがセットされてるかをチェック
	int64 NullCheck = (int64)ActorA & (int64)ActorB & (int64)ActorC;
	if (!NullCheck)
	{
		UE_LOG(LogTemp, Warning, TEXT("IceManController_NextMoveToActor Is NULL"));
		return;
	}
}
