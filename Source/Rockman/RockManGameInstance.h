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
	//GameOver�̏���
	UFUNCTION(BlueprintImplementableEvent, Category = "GameMode")
	void IsGameOver();

	//�v���C���[Life
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player")
	int32 iPlayerLife;

public:
	UFUNCTION(BlueprintCallable, Category = "Player")
	int32 getPlayerLife();

	UFUNCTION(BlueprintCallable, Category = "Player")
	void setPlayerLife(int32 _iLife);

protected:
	//
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BOSS")
	eBossSelect eNowSelectBoss;

public:
	UFUNCTION(BlueprintCallable, Category = "BOSS")
	eBossSelect getNowSelect();

	UFUNCTION(BlueprintCallable, Category = "BOSS")
	void NextSelect();

	UFUNCTION(BlueprintCallable, Category = "BOSS")
	void PrevSelect();

protected:
	//�v���C���[HUD�@Switch
	bool bPlayerWidgetSwitch;

public:
	UFUNCTION(BlueprintCallable, Category = "Widget")
	void SetPlayerWidgetON();

	UFUNCTION(BlueprintCallable, Category = "Widget")
	void SetPlayerWidgetOFF();
};
