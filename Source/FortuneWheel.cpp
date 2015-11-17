/*-------------------------------------------------------*/
/*				Project Evolution Team Season 2          */
/*   Version GS 1.00.18 & GS-CS 1.00.19 Protocol Eng     */
/*             http://evolution-team.eu                  */
/*-------------------------------------------------------*/
/*                    Code By Th3AnG3L                   */
/*             http://evolution-team.eu                  */
/*-------------------------------------------------------*/
#include "StdAfx.h"

// Wheel of Fortune
CFortune Fortune;

void CFortune::Init(char* File)
{
	this->m_Enabled = GetPrivateProfileInt("Settings","EnableFortuneWheel",1,FORTUNEFILE_PATH);
	this->m_MaxUsage = GetPrivateProfileInt("Settings","MaxUsagePerDay",1,FORTUNEFILE_PATH);

	if(this->m_Enabled == 1)
	{
		this->LoadFile(File);
	}
}

void CFortune::LoadFile(char* File)
{
	SMDFile = fopen(File,"r");

	if(SMDFile == 0)
	{
		MessageBoxA(0,"Unable to load EFortuneWheel.ini - File not found.","Error",MB_OK);
		this->m_Enabled = 0;
		return;
	}

	int iToken = 0;

	while(true)
	{
		iToken = GetToken();

		if(iToken == 2)
		{
			break;
		}

		if(iToken == 1)
		{
			int SubClass = TokenNumber;

			if(SubClass == 0)
			{
				while (true)
				{
					iToken = GetToken();

					if(iToken == 0)
					{
						if(strcmp("end",TokenString) == 0)
						{
							break;
						}
					}
					
					this->m_SpinRate = TokenNumber;

					iToken = GetToken();
					this->m_RewardAmount = TokenNumber;
				}
			}
		}
	}

	fclose(SMDFile);
}

void CFortune::Reward(int aIndex)
{
	OBJECTSTRUCT *pObj = (OBJECTSTRUCT*)OBJECT_POINTER(aIndex);
	int Reward = pObj->Money + this->m_RewardAmount;

	if(Reward > 2000000000)
	{
		Reward = 2000000000;
	}
	
	gObj_Write(aIndex,gObjZen,Reward);
	GCMoneySend(aIndex,Reward);
}

void CFortune::Act(int aIndex)
{
	OBJECTSTRUCT *pObj = (OBJECTSTRUCT*)OBJECT_POINTER(aIndex);
	SYSTEMTIME LocalTime;
	GetLocalTime(&LocalTime);

	if(this->m_Enabled == 0)
	{
		return;
	}

	int FortuneDay = MuDB.GetFortuneDay(pObj->AccountID);
	int FortuneUsage = MuDB.GetFortuneInfo(pObj->AccountID);

	if(FortuneDay != LocalTime.wDay)
	{
		MuDB.UpdateFortuneDay(pObj->AccountID);
		MuDB.ResetFortuneInfo(pObj->AccountID);
	}

	if(FortuneDay == LocalTime.wDay && FortuneUsage >= this->m_MaxUsage)
	{
		MsgOutput(aIndex,"You've already used all your spins for today.");
		return;
	}

	int FortuneWin = MuDB.GetFortuneWin();

	if(FortuneWin == 1)
	{
		MsgOutput(aIndex,"Today's pot from the daily spin has been claimed already.");
		return;
	}

	if((rand() % 10000) < this->m_SpinRate)
	{
		this->Reward(aIndex);
		MuDB.UpdateFortuneWin(pObj->Name);
		GCFireworkSend(aIndex,pObj->X,pObj->Y,3);
		
		for(int i = OBJECT_MIN; i < OBJECT_MAX; i++)
		{
			MsgOutputGlobal(i,"[Wheel of Fortune] %s has just won the daily spin!",pObj->Name);
		}
		
		MsgOutput(aIndex,"You just won %d from the of wheel of fortune' daily spin!",this->m_RewardAmount);
	}
	else
	{
		MsgOutput(aIndex,"Unfortunately you missed today's pot, better luck next time.");
	}

	MuDB.UpdateFortuneInfo(pObj->AccountID);
}