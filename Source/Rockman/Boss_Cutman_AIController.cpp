// Fill out your copyright notice in the Description page of Project Settings.


#include "Boss_Cutman_AIController.h"
#include "Boss_Cutman.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

//コンストラクタ
ABoss_Cutman_AIController::ABoss_Cutman_AIController()
{
	BlackboardComponent = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComponent"));
	check(BlackboardComponent);

	BehaviorTreeComponent = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorTreeComponent"));
	check(BehaviorTreeComponent);
}

void ABoss_Cutman_AIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (InPawn == nullptr) return;
	ABoss_Cutman* Enemy = Cast<ABoss_Cutman>(InPawn);
	if (Enemy)
	{
		if (Enemy->GetBehaviorTree())
		{
			BlackboardComponent->InitializeBlackboard(*(Enemy->GetBehaviorTree()->BlackboardAsset));
		}
	}
}