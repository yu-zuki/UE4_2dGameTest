// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperCharacter.h"
#include "Boss_Cutman.generated.h"

class UBehaviorTree;

/**
 * 
 */
UCLASS()
class ROCKMAN_API ABoss_Cutman : public APaperCharacter
{
	GENERATED_BODY()
private:
	UPROPERTY(EditAnywhere, Category = AI, meta = (AllowPrivateAccess = "true"))
		class UBehaviorTree* BehaviorTree;
public:
	FORCEINLINE UBehaviorTree* GetBehaviorTree()const { return BehaviorTree; }
	
};
