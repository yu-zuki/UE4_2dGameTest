// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "RockmanGameMode.generated.h"

UENUM(BlueprintType)
enum class EStageFlow : uint8
{

	stageNone = 0x0,
	stageStart,
	stagePlaying,
	stageEnd

};

/**
 * The GameMode defines the game being played. It governs the game rules, scoring, what actors
 * are allowed to exist in this game type, and who may enter the game.
 *
 * This game mode just sets the default pawn to be the MyCharacter asset, which is a subclass of RockmanCharacter
 */
UCLASS(minimalapi)
class ARockmanGameMode : public AGameModeBase
{
	GENERATED_BODY()
protected:
	EStageFlow eStageFlow;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stage")
	float fGameStartTime;
public:
	ARockmanGameMode();

	UFUNCTION(BlueprintCallable, Category = "Stage")
	EStageFlow GetNowStep() const;

	UFUNCTION(BlueprintCallable, Category = "Stage")
	float GetGameStartTime() const;

	UFUNCTION(BlueprintCallable, Category = "Stage")
	void NextStep();
};
