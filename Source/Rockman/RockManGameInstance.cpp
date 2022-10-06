// Fill out your copyright notice in the Description page of Project Settings.


#include "RockManGameInstance.h"

URockManGameInstance::URockManGameInstance()
{
	//èâä˙âªèàóù
	iPlayerLife = 5;
	bPlayerWidgetSwitch = false;

	eNowSelectBoss = eBossSelect::CutMan;
}

int32 URockManGameInstance::getPlayerLife()
{
	return iPlayerLife;
}

void URockManGameInstance::setPlayerLife(int32 _iLife)
{
	iPlayerLife = _iLife;

	//Life 0ÇÃéûGameOver
	if (iPlayerLife <= 0)
	{
		IsGameOver();
	}
}

eBossSelect URockManGameInstance::getNowSelect()
{
	return eNowSelectBoss;
}

//////////////////////////////////////////////////////////////////////////
// NextSelect

void URockManGameInstance::NextSelect()
{
	uint8 Next = (uint8)eNowSelectBoss;

	//éüÇÃóÒãìÇ…à⁄ìÆ
	Next += (uint8)1;
	if (Next > (uint8)5)	{
		Next = (uint8)0;
	}
	
	//ë„ì¸
	eNowSelectBoss = (eBossSelect)Next;
}

//////////////////////////////////////////////////////////////////////////
// PrevSelect

void URockManGameInstance::PrevSelect()
{
	uint8 Next = (uint8)eNowSelectBoss;

	if (Next <= (uint8)0) {
		Next = (uint8)5;
	}
	else {
		//éüÇÃóÒãìÇ…à⁄ìÆ
		Next -= (uint8)1;
	}

	//ë„ì¸
	eNowSelectBoss = (eBossSelect)Next;
}

void URockManGameInstance::SetPlayerWidgetON()
{
	bPlayerWidgetSwitch = true;
}

void URockManGameInstance::SetPlayerWidgetOFF()
{
	bPlayerWidgetSwitch = false;
}
