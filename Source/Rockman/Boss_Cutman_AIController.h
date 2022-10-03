// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Boss_Cutman_AIController.generated.h"

//ëOï˚êÈåæ
class UBlackboardComponent;
class UBehaviorTreeComponent;

/**
 * 
 */
UCLASS()
class ROCKMAN_API ABoss_Cutman_AIController : public AAIController
{
	GENERATED_BODY()
public:
	ABoss_Cutman_AIController();
	virtual void OnPossess(APawn* InPawn) override;
private:
	UPROPERTY(BlueprintReadWrite, Category = AI, meta = (AllowPrivateAccess = "true"))
		class UBlackboardComponent* BlackboardComponent;

	UPROPERTY(BlueprintReadWrite, Category = AI, meta = (AllowPrivateAccess = "true"))
		class UBehaviorTreeComponent* BehaviorTreeComponent;

public:
	FORCEINLINE UBlackboardComponent* GetBlackboardComponent() const { return BlackboardComponent; }
};
