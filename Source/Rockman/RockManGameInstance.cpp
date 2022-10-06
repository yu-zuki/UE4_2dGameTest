// Fill out your copyright notice in the Description page of Project Settings.


#include "RockManGameInstance.h"

URockManGameInstance::URockManGameInstance()
{
	//����������
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

	//Life 0�̎�GameOver
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

	//���̗񋓂Ɉړ�
	Next += (uint8)1;
	if (Next > (uint8)5)	{
		Next = (uint8)0;
	}
	
	//���
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
		//���̗񋓂Ɉړ�
		Next -= (uint8)1;
	}

	//���
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
