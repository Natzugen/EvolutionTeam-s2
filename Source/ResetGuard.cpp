/*-------------------------------------------------------*/
/*				Project Evolution Team Season 2          */
/*   Version GS 1.00.18 & GS-CS 1.00.19 Protocol Eng     */
/*             http://evolution-team.eu                  */
/*-------------------------------------------------------*/
/*                    Code By Th3AnG3L                   */
/*             http://evolution-team.eu                  */
/*-------------------------------------------------------*/
#include "StdAfx.h"
#include "GameServer.h"

// Reset Guard
CResetGuard ResetGuard;

void CResetGuard::Init(char* File)
{
	this->m_Enabled = GetPrivateProfileInt("NPC","EnableResetGuard",0,NPCFILE_PATH);
	this->m_Info = 0;
	this->m_ReqInfo = 0;

	if(this->m_Enabled == 1)
	{
		LoadFile(File);
	}
}

void CResetGuard::LoadFile(char* File)
{
	SMDFile = fopen(File,"r");

	if(SMDFile == 0)
	{
		MessageBoxA(0,"Unable to load EResetGuard.ini - File not found.","Error",MB_OK);
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

					this->m_ResetInfo[m_Info].m_Class = TokenNumber;

					iToken = GetToken();
					this->m_ResetInfo[m_Info].m_KeepStat = TokenNumber;

					iToken = GetToken();
					this->m_ResetInfo[m_Info].m_AddStat = TokenNumber;

					iToken = GetToken();
					this->m_ResetInfo[m_Info].m_ExtraStat = TokenNumber;

					iToken = GetToken();
					this->m_ResetInfo[m_Info].m_ResetLevel = TokenNumber;

					iToken = GetToken();
					this->m_ResetInfo[m_Info].m_NewLevel = TokenNumber;

					iToken = GetToken();
					this->m_ResetInfo[m_Info].m_ReqPrice = TokenNumber;

					iToken = GetToken();
					this->m_ResetInfo[m_Info].m_Price = TokenNumber;

					iToken = GetToken();
					this->m_ResetInfo[m_Info].m_ResetCounter = TokenNumber;

					this->m_Info++;
				}
			}
			else if(SubClass == 1)
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

					this->m_ResetInfo[m_ReqInfo].m_Class = TokenNumber;

					iToken = GetToken();
					this->m_ResetInfo[m_ReqInfo].m_ReqItem = TokenNumber;

					iToken = GetToken();
					this->m_ResetInfo[m_ReqInfo].m_ItemType = TokenNumber;

					iToken = GetToken();
					this->m_ResetInfo[m_ReqInfo].m_ItemIndex = TokenNumber;

					this->m_ReqInfo++;
				}
			}
		}
	}

	fclose(SMDFile);
}

void CResetGuard::ResetStats(int aIndex,int Class)
{
	switch(Class)
	{
	// Wizard
	case 0x00:
	case 0x01:
		gObj_Write(aIndex,gObjStrength,18);
		gObj_Write(aIndex,gObjAgility,18);
		gObj_Write(aIndex,gObjVitality,15);
		gObj_Write(aIndex,gObjEnergy,30);
		break;
	// Knight
	case 0x16:
	case 0x17:
		gObj_Write(aIndex,gObjStrength,28);
		gObj_Write(aIndex,gObjAgility,20);
		gObj_Write(aIndex,gObjVitality,25);
		gObj_Write(aIndex,gObjEnergy,10);
		break;
	// Elf
	case 0x32:
	case 0x33:
		gObj_Write(aIndex,gObjStrength,22);
		gObj_Write(aIndex,gObjAgility,25);
		gObj_Write(aIndex,gObjVitality,20);
		gObj_Write(aIndex,gObjEnergy,15);
		break;
	// Gladiator
	case 0x48:
		gObj_Write(aIndex,gObjStrength,26);
		gObj_Write(aIndex,gObjAgility,26);
		gObj_Write(aIndex,gObjVitality,26);
		gObj_Write(aIndex,gObjEnergy,26);
		break;
	// Dark Lord
	case 0x64:
		gObj_Write(aIndex,gObjStrength,26);
		gObj_Write(aIndex,gObjAgility,20);
		gObj_Write(aIndex,gObjVitality,20);
		gObj_Write(aIndex,gObjEnergy,15);
		gObj_Write(aIndex,gObjCommand,25);
		break;
	default:
		break;
	}
}

int CResetGuard::CheckItem(int aIndex)
{
	OBJECTSTRUCT *gObj = (OBJECTSTRUCT*)OBJECT_POINTER(aIndex);
	for(int i = 0; i < this->m_ReqInfo; i++)
	{
		int iType = ITEMGET(this->m_ResetInfo[i].m_ItemType,this->m_ResetInfo[i].m_ItemIndex);
		
		for(int j = 12; j < 76; j++)
		{
			if(gObj[aIndex].pInventory[j].m_Type == iType && gObj[aIndex].pInventory[j].m_Level == 0)
			{
				gObjInventoryDeleteItem(aIndex,j);
				GCInventoryItemDeleteSend(aIndex,j,1);
				return true;
			}
		}
	}

	return false;
}

void CResetGuard::Act(int aIndex)
{
	OBJECTSTRUCT *gObj = (OBJECTSTRUCT*)OBJECT_POINTER(aIndex);
	if(this->m_Enabled == 0)
	{
		return;
	}

	if(VerificaGM(aIndex) == 0)
	{
		return;
	}

	for(int i = 0; i < this->m_Info; i++)
	{
		if(gObj[aIndex].Class == this->m_ResetInfo[i].m_Class)
		{
			if(this->m_ResetInfo[i].m_KeepStat == 0)
			{
				ResetStats(aIndex,gObj[aIndex].DbClass);
			}

			if(this->m_ResetInfo[i].m_AddStat == 1)
			{
				gObj[aIndex].LevelUpPoint += this->m_ResetInfo[i].m_ExtraStat;
			}

			if(this->m_ResetInfo[i].m_ResetCounter == 1)
			{
				MuDB.UpdateResets(gObj[aIndex].Name);
			}

			if(this->m_ResetInfo[i].m_ReqPrice == 1)
			{
				gObj_Write(aIndex,gObjZen,gObj_GetInt(aIndex,gObjZen) - this->m_ResetInfo[i].m_Price);
				GCMoneySend(aIndex,gObj_GetInt(aIndex,gObjZen));
			}

			gObj[aIndex].Level = this->m_ResetInfo[i].m_NewLevel;
			gObj[aIndex].Experience = 0;
		}
	}
	
	gObjCalCharacter(aIndex);
	GCReFillSend(gObj[aIndex].m_Index,gObj[aIndex].MaxLife + gObj[aIndex].AddLife,0xFE,0,gObj[aIndex].iMaxShield + gObj[aIndex].iAddShield);
	gObjSetBP(aIndex);
	GCManaSend(gObj[aIndex].m_Index,gObj[aIndex].MaxMana + gObj[aIndex].AddMana,0xFE,0,gObj[aIndex].MaxBP + gObj[aIndex].AddBP);
	GCLevelUpMsgSend(gObj[aIndex].m_Index,1);
	GCFireworkSend(aIndex,gObj[aIndex].X,gObj[aIndex].Y,1);
	GCServerMsgStringSend("You've reborn successfully.",aIndex,1);
	GCServerMsgStringSend("Relogging to finish the process..",aIndex,1);
	//gObjCloseSet(aIndex,1);
	CloseClient(aIndex);
	//Log.AddTime("[Reset Guard] (%s)(%s) Reborn, Map:[%d]",gObj[aIndex].AccountID,gObj[aIndex].Name,gObj[aIndex].MapNumber);
}

void CResetGuard::Npc(int aIndex,int Monster)
{
	OBJECTSTRUCT *gObj = (OBJECTSTRUCT*)OBJECT_POINTER(aIndex);
	for(int i = 0; i < this->m_Info; i++)
	{
		if(gObj[aIndex].Level < this->m_ResetInfo[i].m_ResetLevel)
		{
			ChatTargetSend(&gObj[Monster],"You are too low level to reborn.",aIndex);
			return;
		}

		if(this->m_ResetInfo[i].m_ReqPrice == 1 && gObj[aIndex].Money < this->m_ResetInfo[i].m_Price)
		{
			ChatTargetSend(&gObj[Monster],"You don't have enough zen.",aIndex);
			return;
		}

		for(int j = 0; j < this->m_ReqInfo; j++)
		{
			if(this->m_ResetInfo[j].m_ReqItem == 1 && this->CheckItem(aIndex) == 0)
			{
				ChatTargetSend(&gObj[Monster],"You don't have the reborn item.",aIndex);
				return;
			}
		}
	}
}