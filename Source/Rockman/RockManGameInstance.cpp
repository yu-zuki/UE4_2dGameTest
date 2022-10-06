// Fill out your copyright notice in the Description page of Project Settings.


#include "RockManGameInstance.h"

URockManGameInstance::URockManGameInstance()
{
	iPlayerLife = 5;

	eNowSelectBoss = eBossSelect::CutMan;
}

int32 URockManGameInstance::getPlayerLife()
{
	return iPlayerLife;
}

void URockManGameInstance::setPlayerLife(int32 _iLife)
{
	iPlayerLife = _iLife;
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

	//次の列挙に移動
	Next += (uint8)1;
	if (Next > (uint8)5)	{
		Next = (uint8)0;
	}
	
	//代入
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
		//次の列挙に移動
		Next -= (uint8)1;
	}

	//代入
	eNowSelectBoss = (eBossSelect)Next;
}