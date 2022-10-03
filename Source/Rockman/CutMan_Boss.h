// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CutMan_Boss.generated.h"

class UBehaviorTree;

UCLASS()
class ROCKMAN_API ACutMan_Boss : public ACharacter
{
	GENERATED_BODY()
private:
	UPROPERTY(EditAnywhere, Category = AI, meta = (AllowPrivateAccess = "true"))
		class UBehaviorTree* BehaviorTree;

public:
	// Sets default values for this character's properties
	ACutMan_Boss();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	//RCEINLINE UBehaviorTree* GetBehaviorTree()const { return BehaviorTree; }

};
