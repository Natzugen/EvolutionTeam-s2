/*-------------------------------------------------------*/
/*				Project Evolution Team Season 2          */
/*   Version GS 1.00.18 & GS-CS 1.00.19 Protocol Eng     */
/*             http://evolution-team.eu                  */
/*-------------------------------------------------------*/
/*                    Code By Th3AnG3L                   */
/*             http://evolution-team.eu                  */
/*-------------------------------------------------------*/
#include "StdAfx.h"

// Golden Archer
CGoldenArcher GoldenArcher;

void CGoldenArcher::Init(char* File)
{
	this->m_Enabled = GetPrivateProfileInt("GoldenArcher","EnableGoldenArcher",0,NPCFILE_PATH);
	this->m_RenaCount = GetPrivateProfileInt("GoldenArcher","GoldenArcherRenaCount",1,NPCFILE_PATH);
	this->m_TotalDrops = 0;

	if(this->m_Enabled == 1)
	{
		this->LoadFile(File);
	}
}

void CGoldenArcher::LoadFile(char* File)
{
	SMDFile = fopen(File,"r");

	if(SMDFile == 0)
	{
		MessageBoxA(0,"Unable to load EGoldenArcher.ini - File not found.","Error",MB_OK);
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

					this->m_RewardInfo[m_TotalDrops].m_DropType = TokenNumber;

					iToken = GetToken();
					this->m_RewardInfo[m_TotalDrops].m_DropIndex = TokenNumber;

					iToken = GetToken();
					this->m_RewardInfo[m_TotalDrops].m_DropLevel = TokenNumber;

					iToken = GetToken();
					this->m_RewardInfo[m_TotalDrops].m_DropOption = TokenNumber;

					iToken = GetToken();
					this->m_RewardInfo[m_TotalDrops].m_DropLuck = TokenNumber;

					iToken = GetToken();
					this->m_RewardInfo[m_TotalDrops].m_DropSkill = TokenNumber;

					iToken = GetToken();
					this->m_RewardInfo[m_TotalDrops].m_DropDurability = TokenNumber;

					iToken = GetToken();
					this->m_RewardInfo[m_TotalDrops].m_DropExcellent = TokenNumber;

					iToken = GetToken();
					this->m_RewardInfo[m_TotalDrops].m_DropRate = TokenNumber;

					this->m_TotalDrops++;
				}
			}
		}
	}

	fclose(SMDFile);
}

int CGoldenArcher::RandomizeDrop(int aIndex)
{
	OBJECTSTRUCT *pObj = (OBJECTSTRUCT*)OBJECT_POINTER(aIndex);
	if(this->m_TotalDrops == 0)
	{
		return true;
	}

	for(int i = 0; i < this->m_TotalDrops; i++)
	{
		if((rand() % 10000) < this->m_RewardInfo[i].m_DropRate)
		{
			int iType = ITEMGET(this->m_RewardInfo[i].m_DropType,this->m_RewardInfo[i].m_DropIndex);

			int Excellent = 0;
	
			if(this->m_RewardInfo[i].m_DropExcellent == 1)
			{
				Excellent = rand() % 6;
				Excellent++;
			}
			ItemSerialCreateSend(aIndex,pObj->MapNumber,pObj->X,pObj->Y,iType,this->m_RewardInfo[i].m_DropLevel,this->m_RewardInfo[i].m_DropDurability,this->m_RewardInfo[i].m_DropSkill,this->m_RewardInfo[i].m_DropLuck,this->m_RewardInfo[i].m_DropOption,aIndex,Excellent,0);
			return true;
		}
	}

	return false;
}

int CGoldenArcher::CheckRena(int aIndex)
{
	OBJECTSTRUCT *pObj = (OBJECTSTRUCT*)OBJECT_POINTER(aIndex);
	for(int i = 12; i < 76; i++)
	{
		if(pObj->pInventory[i].m_Type == 0x1C15 && pObj->pInventory[i].m_Level == 0)
		{
			return true;
		}
	}

	return false;
}

void CGoldenArcher::Act(int aIndex)
{
	OBJECTSTRUCT *pObj = (OBJECTSTRUCT*)OBJECT_POINTER(aIndex);
	if(this->m_Enabled == 0)
	{
		return;
	}

	
	if(gObjIsConnected(aIndex) == 0)
	{
		return;
	}

	if(this->CheckRena(aIndex))
	{
		unsigned short* RenaCount = (unsigned short*) &pObj[aIndex].m_Quest[8];

		if(*RenaCount == 0xFFFF)
		{
			*RenaCount = 0;
		}

		*RenaCount += 1;
		
		if(*RenaCount == this->m_RenaCount)
		{
			this->RandomizeDrop(aIndex);
			*RenaCount = *RenaCount - this->m_RenaCount;
			GCServerMsgStringSend("Rena registered successfully.",aIndex,1);
		}

		unsigned char lpMsg[7] = {0xC1,0x07,0x94,0x00};
		memcpy(&lpMsg[4],RenaCount,2);
		DataSend(aIndex,lpMsg,7);

	}
}

void CGoldenArcher::Npc(int aIndex,int Monster)
{
	OBJECTSTRUCT *pObj = (OBJECTSTRUCT*)OBJECT_POINTER(aIndex);
	ChatTargetSend(&pObj[Monster],"I am collecting Renas, bring them to me if you find one.",aIndex);

	unsigned char lpMsg[7] = {0xC1,0x07,0x94,0x00};
	memcpy(&lpMsg[4],&pObj[aIndex].m_Quest[8],2);
	DataSend(aIndex,lpMsg,7);
}