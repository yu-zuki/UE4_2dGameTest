// Fill out your copyright notice in the Description page of Project Settings.


#include "RockManGameInstance.h"

URockManGameInstance::URockManGameInstance()
{
	PlayerLife = 5;

	eNowSelectBoss = eBossSelect::CutMan;
}

int32 URockManGameInstance::getPlayerLife()
{
	return PlayerLife;
}

void URockManGameInstance::NextSelect()
{
	uint8 Next = (uint8)eNowSelectBoss;

	Next += 1;
	if (Next > 5)	{
		Next = 0;
	}

	eNowSelectBoss = (eBossSelect)Next;
}

void URockManGameInstance::PrevSelect()
{
	uint8 Next = (uint8)eNowSelectBoss;

	Next -= 1;
	if (Next < 0) {
		Next = 5;
	}
}