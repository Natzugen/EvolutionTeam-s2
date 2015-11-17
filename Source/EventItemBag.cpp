#include "StdAfx.h"
#include "EventItemBag.h"
#include "Log.h"

// Event Item Bag
CEventItemBag * HatcheryDrop;

void CEventItemBag::Init(char* File)
{
	this->m_bLoad = FALSE;
	this->m_sEventName[0] = 0;
	this->m_iEventItemType = -1;
	this->m_iEventItemLevel = 0;
	this->m_iEventItemDropRate = 0;
	this->m_iItemDropRate = 0;
	this->m_iExItemDropRate = 0;
	this->m_iBagObjectCount = 0;

	this->LoadFile(File);
}

void CEventItemBag::LoadFile(char* File)
{
	SMDFile = fopen(File,"r");

	if(SMDFile == 0)
	{
		char szTemp[256];
		wsprintf(szTemp,"Unable to load %s - File not found.",File);
		MessageBoxA(0,szTemp,"Error",MB_OK);
		return;
	}

	int iToken = 0;
	int n = 0;
	this->m_bLoad = FALSE;

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

					int Map = TokenNumber;

					if (MAX_MAP_RANGE(Map) == FALSE)
					{
						char szTemp[256];
						wsprintf(szTemp,"EventItemBag Loaded Wrong Data in: [%s]",File);
						MessageBoxA(0,szTemp,"Error",MB_OK);
						return;
					}

					iToken = GetToken();
					this->DropMapInfo[Map].m_bIsDrop = TokenNumber;

					iToken = GetToken();
					this->DropMapInfo[Map].m_MinMonsterLevel = TokenNumber;

					iToken = GetToken();
					this->DropMapInfo[Map].m_MaxMonsterLevel = TokenNumber;
				}
			}

			if(SubClass == 1)
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

					strcpy(this->m_sEventName, TokenString);

					iToken = GetToken();
					this->m_iEventItemDropZen = TokenNumber;

					iToken = GetToken();
					int ItemType = TokenNumber;

					iToken = GetToken();
					int ItemIndex = TokenNumber;

					this->m_iEventItemType = ITEMGET(ItemType, ItemIndex);

					iToken = GetToken();
					this->m_iEventItemLevel = TokenNumber;

					iToken = GetToken();
					this->m_iEventItemDropRate = TokenNumber;

					iToken = GetToken();
					this->m_iItemDropRate = TokenNumber;

					iToken = GetToken();
					this->m_iExItemDropRate = TokenNumber;

					char szTemp[256];
					wsprintf(szTemp,"[%s] Eventitemnum = %d,EventItemLevel = %d,EventItemDropRate = %d,ItemDropRate = %d,ExItemDropRate = %d",this->m_sEventName,this->m_iEventItemType,this->m_iEventItemLevel,this->m_iEventItemDropRate,this->m_iItemDropRate,this->m_iExItemDropRate);
					Log.AddTime(szTemp);
				}
			}

			if(SubClass == 2)
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

					this->EventBagObject[n].m_Type = TokenNumber;

					iToken = GetToken();
					this->EventBagObject[n].m_Index = TokenNumber;

					iToken = GetToken();
					this->EventBagObject[n].m_MinLevel = TokenNumber;

					iToken = GetToken();
					this->EventBagObject[n].m_MaxLevel = TokenNumber;

					iToken = GetToken();
					this->EventBagObject[n].m_IsSkill = TokenNumber;

					iToken = GetToken();
					this->EventBagObject[n].m_IsLuck = TokenNumber;

					iToken = GetToken();
					this->EventBagObject[n].m_IsOption = TokenNumber;

					iToken = GetToken();
					this->EventBagObject[n].m_IsExcItem = TokenNumber;

					n++;

					this->m_iBagObjectCount++;

					if (this->m_iBagObjectCount > 150-1)
					{
						break;
					}
				}
			}
		}
	}

	fclose(SMDFile);
	this->m_bLoad = TRUE;
}

BYTE CEventItemBag::GetLevel(int n)
{
	if (n <0 || n > 150-1)
	{
		return 0;
	}

	if (this->EventBagObject[n].m_MinLevel == this->EventBagObject[n].m_MaxLevel)
	{
		return this->EventBagObject[n].m_MinLevel;
	}

	int sub = (this->EventBagObject[n].m_MaxLevel - this->EventBagObject[n].m_MinLevel) + 1;
	int level = this->EventBagObject[n].m_MinLevel + (rand()%sub);

	return level;
}

BYTE CEventItemBag::GetMinLevel(int n)
{
	if (n<0 || n > 150-1)
		return 0;

	return this->EventBagObject[n].m_MinLevel;
}

BYTE CEventItemBag::GetMaxLevel(int n)
{
	if (n<0 || n > 150-1)
		return 0;

	return this->EventBagObject[n].m_MaxLevel;
}

BOOL CEventItemBag::IsEnableEventItemDrop(int aIndex)
{
	OBJECTSTRUCT* gObj = (OBJECTSTRUCT*)(aIndex * OBJECT_SIZE + OBJECT_BASE);

	int iMapNumber = gObj->MapNumber;

	if (this->DropMapInfo[iMapNumber].m_bIsDrop == FALSE)
	{
		return false;
	}

	int iLevel = gObj->Level;

	if  (iLevel < this->DropMapInfo[iMapNumber].m_MinMonsterLevel || iLevel > this->DropMapInfo[iMapNumber].m_MaxMonsterLevel)
	{
		return false;
	}

	return true;
}

BOOL CEventItemBag::DropEventItem(int aIndex)
{
	if (this->m_bLoad == FALSE)
	{
		return false;
	}

	if (this->IsEnableEventItemDrop(aIndex) == FALSE)
	{
		return false;
	}

	OBJECTSTRUCT* gObj = (OBJECTSTRUCT*)(aIndex * OBJECT_SIZE + OBJECT_BASE);

	if ((rand()%1000) < this->m_iEventItemDropRate)
	{
		int ei;
		int eil;
		int x;
		int y;
		float dur = 0;
		dur = 255.0;

		x = gObj->X;
		y = gObj->Y;
		eil = this->m_iEventItemLevel;
		ei = this->m_iEventItemType;

		int thdu = gObjMonsterTopHitDamageUser2(gObj);
		ItemSerialCreateSend(gObj->m_Index,gObj->MapNumber,x,y,ei,eil,dur,0,0,0,thdu,0,0);
		Log.AddTime("[%s][%s] [%s] MonsterEventItemDrop (%d)(%d/%d)",gObj->AccountID,gObj->Name,this->m_sEventName,gObj->MapNumber,x,y);
		return true;
	}

	return false;
}

BOOL CEventItemBag::DropItem(int aIndex)
{
	if (this->m_bLoad == FALSE)
	{
		return false;
	}

	OBJECTSTRUCT* lpObj = &gObj[aIndex];

	int Type;
	int Level;
	int CordX;
	int CordY;
	int szSkill	= 0;
	int szLuck = 0;
	int szAddOpt = 0;
	int ExOption = 0;
	int RandomExe = 0;
	int IsExeOption[6] = {0,0,0,0,0,0};
	int DropItemNum = rand()%this->GetBagCount();
	float Durability;

	if (this->GetBagCount() > 0)
	{
		if ((rand()%100) < this->m_iItemDropRate)
		{
			ITEM_ATTRIBUTE *ItemAttrTable = (ITEM_ATTRIBUTE*) ITEMATTR_BASE;

			if ((rand() % 100 ) < this->m_iExItemDropRate)
			{
				DropItemNum = rand()%this->GetBagCount();
				Durability = 0;
				CordX = lpObj->X;
				CordY = lpObj->Y;
				Level = this->GetLevel(DropItemNum);
				Type = ITEMGET(this->EventBagObject[DropItemNum].m_Type, this->EventBagObject[DropItemNum].m_Index);

				if (Type == -1)
				{
					return false;
				}

				if (this->EventBagObject[DropItemNum].m_IsSkill != 0)
				{
					szSkill = rand()%2;
				}

				if (this->EventBagObject[DropItemNum].m_IsLuck != 0)
				{
					szLuck = rand()%2;
				}

				if (this->EventBagObject[DropItemNum].m_IsOption != 0)
				{
					if (rand()%5 < 1)
					{
						szAddOpt = 3;
					}
					else
					{
						szAddOpt = rand()%3;
					}
				}

				if (this->EventBagObject[DropItemNum].m_IsExcItem != 0)
				{
					ExOption = NewOptionRand(0);
					szSkill = 1;
				}

				// --- Chaos, Bless, Soul, Life, Creation, Harmony & Loch Feather
				if (Type == ITEMGET(12,15) || Type == ITEMGET(14,13) || 
					Type == ITEMGET(14,14) || Type == ITEMGET(14,16) ||
					Type == ITEMGET(14,31) || Type == ITEMGET(14,42) ||
					Type == ITEMGET(13,14))
				{
					szSkill	= 0;
					szLuck = 0;
					szAddOpt = 0;
					Level = 0;
					ExOption = 0;
				}

				if (Type >= ITEMGET(13,0) && Type <= ITEMGET(13,5) ||
					Type >= ITEMGET(13,8)   && Type <= ITEMGET(13,13) ||
					Type >= ITEMGET(13,20)  && Type <= ITEMGET(13,28) ||
					Type == ITEMGET(13,64) || Type == ITEMGET(13,65) ||
					Type == ITEMGET(13,67) || Type == ITEMGET(13,68) ||
					Type == ITEMGET(13,76) || Type == ITEMGET(13,80) ||
					Type == ITEMGET(14,85) || Type == ITEMGET(14,86) ||
					Type == ITEMGET(14,87) || Type == ITEMGET(14,88) ||
					Type == ITEMGET(14,89) || Type == ITEMGET(14,90))
				{
					Level = 0;
				}
			}
			else
			{
				DropItemNum =  rand()%this->GetBagCount();
				Durability = 0;
				CordX = lpObj->X;
				CordY = lpObj->Y;
				Level = this->GetLevel(DropItemNum);
				Type = ITEMGET(this->EventBagObject[DropItemNum].m_Type, this->EventBagObject[DropItemNum].m_Index);

				if (Type == -1)
				{
					return false;
				}

				if (this->EventBagObject[DropItemNum].m_IsSkill != 0)
				{
					szSkill = rand()%2;
				}

				if (this->EventBagObject[DropItemNum].m_IsLuck != 0)
				{
					szLuck = rand()%2;
				}

				if (this->EventBagObject[DropItemNum].m_IsOption != 0)
				{
					if (rand()%5 < 1)
					{
						szAddOpt = 3;
					}
					else
					{
						szAddOpt = rand()%3;
					}
				}

				// --- 
				ExOption = 0;

				// --- Chaos, Bless, Soul, Life, Creation, Harmony & Loch Feather
				if (Type == ITEMGET(12,15) || Type == ITEMGET(14,13) || 
					Type == ITEMGET(14,14) || Type == ITEMGET(14,16) ||
					Type == ITEMGET(14,31) || Type == ITEMGET(14,42) ||
					Type == ITEMGET(13,14))
				{
					szSkill	= 0;
					szLuck = 0;
					szAddOpt = 0;
					Level = 0;
					ExOption = 0;
				}

				if (Type >= ITEMGET(13,0) && Type <= ITEMGET(13,5) ||
					Type >= ITEMGET(13,8)   && Type <= ITEMGET(13,13) ||
					Type >= ITEMGET(13,20)  && Type <= ITEMGET(13,28) ||
					Type == ITEMGET(13,64) || Type == ITEMGET(13,65) ||
					Type == ITEMGET(13,67) || Type == ITEMGET(13,68) ||
					Type == ITEMGET(13,76) || Type == ITEMGET(13,80) ||
					Type == ITEMGET(14,85) || Type == ITEMGET(14,86) ||
					Type == ITEMGET(14,87) || Type == ITEMGET(14,88) ||
					Type == ITEMGET(14,89) || Type == ITEMGET(14,90))
				{
					Level = 0;
				}
			}

			ItemSerialCreateSend(lpObj->m_Index, lpObj->MapNumber, CordX, CordY, Type, Level, Durability, szSkill, szLuck, szAddOpt, lpObj->m_Index, ExOption, 0);
			Log.AddTime("[%s][%s][%s Event Item Drop]: (%d)(X:%d/Y:%d) Item:%d(%s) Level:%d Skill:%d Luck:%d AddOpt:%d Exc:%d", lpObj->AccountID, lpObj->Name, this->m_sEventName, lpObj->MapNumber, CordX, CordY, Type, ItemAttrTable[Type].Name, Level, szSkill, szLuck, szAddOpt, ExOption);
			return true;
		}
	}
	else
	{
		CordX = lpObj->X;
		CordY = lpObj->Y;
		//MapC[lpObj->MapNumber].MoneyItemDrop(this->m_IBDropZen, CordX, CordY);
	}

	return true;
}

BOOL CEventItemBag::MapDropItem(int aIndex, BYTE btMapNumber, BYTE cX, BYTE cY)
{
	if (this->m_bLoad == FALSE)
	{
		return false;
	}

	OBJECTSTRUCT* lpObj = &gObj[aIndex];

	int Type;
	int Level;
	int CordX;
	int CordY;
	int szSkill	= 0;
	int szLuck = 0;
	int szAddOpt = 0;
	int ExOption = 0;
	int RandomExe = 0;
	int IsExeOption[6] = {0,0,0,0,0,0};
	int DropItemNum = rand()%this->GetBagCount();
	float Durability;

	if (this->GetBagCount() > 0)
	{
		if ((rand()%100) < this->m_iItemDropRate)
		{
			ITEM_ATTRIBUTE *ItemAttrTable = (ITEM_ATTRIBUTE*) ITEMATTR_BASE;

			if ((rand() % 100 ) < this->m_iExItemDropRate)
			{
				DropItemNum =  rand()%this->GetBagCount();
				Durability = 0;
				CordX = lpObj->X;
				CordY = lpObj->Y;
				Level = this->GetLevel(DropItemNum);
				Type = ITEMGET(this->EventBagObject[DropItemNum].m_Type, this->EventBagObject[DropItemNum].m_Index);

				if (Type == -1)
				{
					return false;
				}

				if (this->EventBagObject[DropItemNum].m_IsSkill != 0)
				{
					szSkill = rand()%2;
				}

				if (this->EventBagObject[DropItemNum].m_IsLuck != 0)
				{
					szLuck = rand()%2;
				}

				if (this->EventBagObject[DropItemNum].m_IsOption != 0)
				{
					if (rand()%5 < 1)
					{
						szAddOpt = 3;
					}
					else
					{
						szAddOpt = rand()%3;
					}
				}

				if (this->EventBagObject[DropItemNum].m_IsExcItem != 0)
				{
					ExOption = NewOptionRand(0);
					szSkill = 1;
				}

				// --- Chaos, Bless, Soul, Life, Creation, Harmony & Loch Feather
				if (Type == ITEMGET(12,15) || Type == ITEMGET(14,13) || 
					Type == ITEMGET(14,14) || Type == ITEMGET(14,16) ||
					Type == ITEMGET(14,31) || Type == ITEMGET(14,42) ||
					Type == ITEMGET(13,14))
				{
					szSkill	= 0;
					szLuck = 0;
					szAddOpt = 0;
					Level = 0;
					ExOption = 0;
				}

				if (Type >= ITEMGET(13,0) && Type <= ITEMGET(13,5) ||
					Type >= ITEMGET(13,8)   && Type <= ITEMGET(13,13) ||
					Type >= ITEMGET(13,20)  && Type <= ITEMGET(13,28) ||
					Type == ITEMGET(13,64) || Type == ITEMGET(13,65) ||
					Type == ITEMGET(13,67) || Type == ITEMGET(13,68) ||
					Type == ITEMGET(13,76) || Type == ITEMGET(13,80) ||
					Type == ITEMGET(14,85) || Type == ITEMGET(14,86) ||
					Type == ITEMGET(14,87) || Type == ITEMGET(14,88) ||
					Type == ITEMGET(14,89) || Type == ITEMGET(14,90))
				{
					Level = 0;
				}
			}
			else
			{
				DropItemNum =  rand()%this->GetBagCount();
				Durability = 0;
				Level = this->GetLevel(DropItemNum);
				Type = ITEMGET(this->EventBagObject[DropItemNum].m_Type, this->EventBagObject[DropItemNum].m_Index);

				if (Type == -1)
				{
					return false;
				}

				if (this->EventBagObject[DropItemNum].m_IsSkill != 0)
				{
					szSkill = rand()%2;
				}

				if (this->EventBagObject[DropItemNum].m_IsLuck != 0)
				{
					szLuck = rand()%2;
				}

				if (this->EventBagObject[DropItemNum].m_IsOption != 0)
				{
					if (rand()%5 < 1)
					{
						szAddOpt = 3;
					}
					else
					{
						szAddOpt = rand()%3;
					}
				}

				// --- 
				ExOption = 0;

				// --- Chaos, Bless, Soul, Life, Creation, Harmony & Loch Feather
				if (Type == ITEMGET(12,15) || Type == ITEMGET(14,13) || 
					Type == ITEMGET(14,14) || Type == ITEMGET(14,16) ||
					Type == ITEMGET(14,31) || Type == ITEMGET(14,42) ||
					Type == ITEMGET(13,14))
				{
					szSkill	= 0;
					szLuck = 0;
					szAddOpt = 0;
					Level = 0;
					ExOption = 0;
				}

				if (Type >= ITEMGET(13,0) && Type <= ITEMGET(13,5) ||
					Type >= ITEMGET(13,8)   && Type <= ITEMGET(13,13) ||
					Type >= ITEMGET(13,20)  && Type <= ITEMGET(13,28) ||
					Type == ITEMGET(13,64) || Type == ITEMGET(13,65) ||
					Type == ITEMGET(13,67) || Type == ITEMGET(13,68) ||
					Type == ITEMGET(13,76) || Type == ITEMGET(13,80) ||
					Type == ITEMGET(14,85) || Type == ITEMGET(14,86) ||
					Type == ITEMGET(14,87) || Type == ITEMGET(14,88) ||
					Type == ITEMGET(14,89) || Type == ITEMGET(14,90))
				{
					Level = 0;
				}
			}

			if (cX == 0 && cY == 0)
			{
				CordX = lpObj->X;
				CordY = lpObj->Y;
			}
			else
			{
				CordX = cX;
				CordY = cY;
			}

			ItemSerialCreateSend(lpObj->m_Index, lpObj->MapNumber, CordX, CordY, Type, Level, Durability, szSkill, szLuck, szAddOpt, lpObj->m_Index, ExOption, 0);
			//Log.Add("[ KANTURU ][ Reward ] Nightmare Item Drop [%s][%s] : (%d)(%d/%d) Item:(%s)%d Level:%d Skill:%d Luck:%d AddOpt:%d Exc:%d",lpObj->AccountID, lpObj->Name, this->m_sEventName, lpObj->MapNumber, CordX, CordY, Type, ItemAttrTable[Type].Name, Level, szSkill, szLuck, szAddOpt, ExOption);
			return true;
		}
	}

	return true;
}

BYTE NewOptionRand(int level)
{
	BYTE NOption = 0;
	NOption = 1 << (rand() % 6);

	if ( (NOption &2) != 0 )
	{
		if ( (rand()%2) != 0 )
		{
			NOption = 1 << (rand()%6);
		}
	}

	if ( (rand()% 4) == 0 )
	{
		NOption |= 1 << (rand()%6);
	}

	return NOption;
}