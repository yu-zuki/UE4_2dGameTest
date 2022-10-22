// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "RockmanGameMode.h"
#include "RockmanCharacter.h"

ARockmanGameMode::ARockmanGameMode()
{
	// Set default pawn class to our character
	DefaultPawnClass = ARockmanCharacter::StaticClass();	

	eStageFlow = EStageFlow::stageNone;
	fGameStartTime = 2.0f;
}


EStageFlow ARockmanGameMode::GetNowStep() const
{
	return eStageFlow;
}

float ARockmanGameMode::GetGameStartTime() const
{
	return fGameStartTime;
}

void ARockmanGameMode::NextStep()
{
	uint8 NowStep = (uint8)eStageFlow;

	//NextStep
	NowStep += (uint8)1;

	if (NowStep > (uint8)EStageFlow::stageEnd)
	{ 
		NowStep = (uint8)2;
	}
	
	eStageFlow = (EStageFlow)NowStep;
}
