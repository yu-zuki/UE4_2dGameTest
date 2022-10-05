// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "RockManGameInstance.generated.h"

UENUM(BlueprintType)
enum class eBossSelect :uint8 {
	CutMan = 0,
	GutsMan,
	IceMan,
	BombMan,
	FireMan,
	ElecMan
};

/**
 * 
 */
UCLASS()
class ROCKMAN_API URockManGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	URockManGameInstance();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player")
	int32 PlayerLife;

	UFUNCTION(BlueprintCallable, Category = "Player")
	int32 getPlayerLife();

	eBossSelect eNowSelectBoss;

	UFUNCTION(BlueprintCallable, Category = "BOSS")
	void NextSelect();

	UFUNCTION(BlueprintCallable, Category = "BOSS")
	void PrevSelect();
};
