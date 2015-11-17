/*#include "StdAfx.h"

// PK Guard
CPKGuard PKGuard;

void CPKGuard::Init(char* File)
{
	this->m_Enabled = GetPrivateProfileInt("NPC","EnablePKClearGuard",0,NPCFILE_PATH);
	this->c_Price = 0;

	if(this->m_Enabled == 1)
	{
		this->LoadFile(File);
	}
}

void CPKGuard::LoadFile(char* File)
{
	SMDFile = fopen(File,"r");

	if(SMDFile == 0)
	{
		MessageBoxA(0,"Unable to load EPKGuard.ini - File not found.","Error",MB_OK);
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

					this->m_ClearType = TokenNumber;

					iToken = GetToken();
					this->m_Price = TokenNumber;
				}
			}
		}
	}

	fclose(SMDFile);
}

void CPKGuard::Act(int aIndex)
{
	if(this->m_Enabled == 0)
	{
		return;
	}

	if(OnlineStatus(aIndex) == 0)
	{
		return;
	}

	if(this->m_ClearType == 0)
	{
		this->c_Price = 0;
	}
	else if(this->m_ClearType == 1)
	{
		this->c_Price = this->m_Price;
	}
	else if(this->m_ClearType == 2)
	{
		this->c_Price = this->m_Price * (gObj[aIndex].m_PK_Level - 3);
	}
	else if(this->m_ClearType == 3)
	{
		this->c_Price = this->m_Price * gObj[aIndex].m_PK_Count;
	}
	else
	{
		this->c_Price = this->m_Price;
	}

	gObjWrite(aIndex,gObjZen,gObjGetInt(aIndex,gObjZen) - this->c_Price);
	GCMoneySend(aIndex,gObjGetInt(aIndex,gObjZen));
	gObjWrite(aIndex,gObjPK,3);
	GCPkLevelSend(aIndex,3);
	gObj[aIndex].m_PK_Count = 0;
	gObj[aIndex].m_PK_Time = 0;
	GCFireworkSend(aIndex,gObj[aIndex].X,gObj[aIndex].Y,1);
	GCServerMsgStringSend("PK status successfully cleared.",aIndex,1);
	//Log.AddTime("[PK Guard] (%s)(%s) Cleared PK Level, Map:[%d]",gObj[aIndex].AccountID,gObj[aIndex].Name,gObj[aIndex].MapNumber);
}

void CPKGuard::Npc(int aIndex,int Monster)
{
	if(gObj[aIndex].m_PK_Level < 4)
	{
		ChatTargetSend(&gObj[Monster],"You are already a commoner.",aIndex);
		return;
	}

	if(gObj[aIndex].Money < this->c_Price)
	{
		ChatTargetSend(&gObj[Monster],"You don't have enough zen.",aIndex);
		return;
	}

	this->Act(aIndex);
} */