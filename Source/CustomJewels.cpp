#include "StdAfx.h"
#include "Mapping.h"

// Custom Jewels
CCustomJewels CustomJewels;

void CCustomJewels::CGUseItemRecv(PMSG_USEITEM *lpMsg, int aIndex)
{
	OBJECTSTRUCT *gObj = (OBJECTSTRUCT*)OBJECT_POINTER(aIndex);

	// Jewel Of Wind [Luck in weapons]
	if (gObj->pInventory[lpMsg->inventoryPos].m_Type == ITEMGET(14,45))
	{
		BYTE btSuccessRate = 40; // Success rate (Max: 100)

		if(gObj->pInventory[lpMsg->inventoryTarget].m_Option2 != 1)
		{
			if ((rand() % 100) < btSuccessRate)
			{
				gObj->pInventory[lpMsg->inventoryTarget].m_Option2 = 1;
				gObjInventoryItemSet(aIndex,lpMsg->inventoryPos, -1);
				ItemClear(aIndex,lpMsg->inventoryPos);
				GCInventoryItemOneSend(aIndex, lpMsg->inventoryTarget);
				GCInventoryItemDeleteSend(aIndex, lpMsg->inventoryPos, 1);	
			}
			else 
			{
				gObjInventoryItemSet(aIndex,lpMsg->inventoryPos, -1);
				ItemClear(aIndex,lpMsg->inventoryPos);
				GCInventoryItemOneSend(aIndex, lpMsg->inventoryTarget);
				GCInventoryItemDeleteSend(aIndex, lpMsg->inventoryPos, 1);	
			}
		}
		else
		{
			GCServerMsgStringSend("Jewel Of Wind is not applicable to this item !", aIndex, 1);
			return;
		}
	}

	// Jewel Of Fire [Skill in weapons]
	if (gObj->pInventory[lpMsg->inventoryPos].m_Type == ITEMGET(14,46))
	{	
		BYTE btSuccessRate = 60; // Success rate (Max: 100)

		if((gObj->pInventory[lpMsg->inventoryTarget].m_Type == ITEMGET(0,3) || gObj->pInventory[lpMsg->inventoryTarget].m_Type == ITEMGET(0,4)  || 
			gObj->pInventory[lpMsg->inventoryTarget].m_Type == ITEMGET(0,5) || gObj->pInventory[lpMsg->inventoryTarget].m_Type == ITEMGET(0,6)  || 
			gObj->pInventory[lpMsg->inventoryTarget].m_Type == ITEMGET(0,7) || gObj->pInventory[lpMsg->inventoryTarget].m_Type == ITEMGET(0,8)  ||
			gObj->pInventory[lpMsg->inventoryTarget].m_Type == ITEMGET(0,9) || gObj->pInventory[lpMsg->inventoryTarget].m_Type == ITEMGET(0,10) ||
			gObj->pInventory[lpMsg->inventoryTarget].m_Type == ITEMGET(0,11)|| gObj->pInventory[lpMsg->inventoryTarget].m_Type == ITEMGET(0,12) ||
			gObj->pInventory[lpMsg->inventoryTarget].m_Type == ITEMGET(0,13)|| gObj->pInventory[lpMsg->inventoryTarget].m_Type == ITEMGET(0,14) ||
			gObj->pInventory[lpMsg->inventoryTarget].m_Type == ITEMGET(0,15)|| gObj->pInventory[lpMsg->inventoryTarget].m_Type == ITEMGET(0,16) ||
			gObj->pInventory[lpMsg->inventoryTarget].m_Type == ITEMGET(0,17)|| gObj->pInventory[lpMsg->inventoryTarget].m_Type == ITEMGET(0,18) ||
			gObj->pInventory[lpMsg->inventoryTarget].m_Type == ITEMGET(0,19)|| gObj->pInventory[lpMsg->inventoryTarget].m_Type == ITEMGET(0,20) ||
			gObj->pInventory[lpMsg->inventoryTarget].m_Type == ITEMGET(0,21)|| gObj->pInventory[lpMsg->inventoryTarget].m_Type == ITEMGET(0,22) ||
			gObj->pInventory[lpMsg->inventoryTarget].m_Type == ITEMGET(0,23)|| gObj->pInventory[lpMsg->inventoryTarget].m_Type == ITEMGET(0,24) ||
			gObj->pInventory[lpMsg->inventoryTarget].m_Type == ITEMGET(0,25)|| gObj->pInventory[lpMsg->inventoryTarget].m_Type == ITEMGET(0,31) ||

			gObj->pInventory[lpMsg->inventoryTarget].m_Type == ITEMGET(1,2)|| gObj->pInventory[lpMsg->inventoryTarget].m_Type == ITEMGET(1,3) ||
			gObj->pInventory[lpMsg->inventoryTarget].m_Type == ITEMGET(1,5)|| gObj->pInventory[lpMsg->inventoryTarget].m_Type == ITEMGET(1,6) ||
			gObj->pInventory[lpMsg->inventoryTarget].m_Type == ITEMGET(1,7)|| gObj->pInventory[lpMsg->inventoryTarget].m_Type == ITEMGET(1,8) ||
			gObj->pInventory[lpMsg->inventoryTarget].m_Type == ITEMGET(2,1)|| gObj->pInventory[lpMsg->inventoryTarget].m_Type == ITEMGET(2,3) ||
			gObj->pInventory[lpMsg->inventoryTarget].m_Type == ITEMGET(2,4)|| gObj->pInventory[lpMsg->inventoryTarget].m_Type == ITEMGET(2,5) ||
			gObj->pInventory[lpMsg->inventoryTarget].m_Type == ITEMGET(2,6)|| gObj->pInventory[lpMsg->inventoryTarget].m_Type == ITEMGET(2,8) ||
			gObj->pInventory[lpMsg->inventoryTarget].m_Type == ITEMGET(2,9)|| gObj->pInventory[lpMsg->inventoryTarget].m_Type == ITEMGET(2,10) ||
			gObj->pInventory[lpMsg->inventoryTarget].m_Type == ITEMGET(2,11)|| gObj->pInventory[lpMsg->inventoryTarget].m_Type == ITEMGET(2,12) ||
			gObj->pInventory[lpMsg->inventoryTarget].m_Type == ITEMGET(2,13)|| gObj->pInventory[lpMsg->inventoryTarget].m_Type == ITEMGET(2,14) ||
			gObj->pInventory[lpMsg->inventoryTarget].m_Type == ITEMGET(2,15)|| gObj->pInventory[lpMsg->inventoryTarget].m_Type == ITEMGET(3,0) ||
			gObj->pInventory[lpMsg->inventoryTarget].m_Type == ITEMGET(3,4)|| gObj->pInventory[lpMsg->inventoryTarget].m_Type == ITEMGET(3,7) ||
			gObj->pInventory[lpMsg->inventoryTarget].m_Type == ITEMGET(3,8)|| gObj->pInventory[lpMsg->inventoryTarget].m_Type == ITEMGET(3,9) ||
			gObj->pInventory[lpMsg->inventoryTarget].m_Type == ITEMGET(3,10)|| gObj->pInventory[lpMsg->inventoryTarget].m_Type == ITEMGET(4,0) || 
			gObj->pInventory[lpMsg->inventoryTarget].m_Type == ITEMGET(4,1) ||gObj->pInventory[lpMsg->inventoryTarget].m_Type == ITEMGET(4,2) ||
			gObj->pInventory[lpMsg->inventoryTarget].m_Type == ITEMGET(4,3) || gObj->pInventory[lpMsg->inventoryTarget].m_Type == ITEMGET(4,4) || 
			gObj->pInventory[lpMsg->inventoryTarget].m_Type == ITEMGET(4,5) || gObj->pInventory[lpMsg->inventoryTarget].m_Type == ITEMGET(4,6) ||
			gObj->pInventory[lpMsg->inventoryTarget].m_Type == ITEMGET(4,8) || gObj->pInventory[lpMsg->inventoryTarget].m_Type == ITEMGET(4,9) ||
			gObj->pInventory[lpMsg->inventoryTarget].m_Type == ITEMGET(4,10) || gObj->pInventory[lpMsg->inventoryTarget].m_Type == ITEMGET(4,11)||
			gObj->pInventory[lpMsg->inventoryTarget].m_Type == ITEMGET(4,12) || gObj->pInventory[lpMsg->inventoryTarget].m_Type == ITEMGET(4,13)||
			gObj->pInventory[lpMsg->inventoryTarget].m_Type == ITEMGET(4,14) || gObj->pInventory[lpMsg->inventoryTarget].m_Type == ITEMGET(4,16)||
			gObj->pInventory[lpMsg->inventoryTarget].m_Type == ITEMGET(4,17) || gObj->pInventory[lpMsg->inventoryTarget].m_Type == ITEMGET(4,18)||
			gObj->pInventory[lpMsg->inventoryTarget].m_Type == ITEMGET(4,19) || gObj->pInventory[lpMsg->inventoryTarget].m_Type == ITEMGET(4,20)||
			gObj->pInventory[lpMsg->inventoryTarget].m_Type == ITEMGET(4,21) || gObj->pInventory[lpMsg->inventoryTarget].m_Type == ITEMGET(4,22)||
			gObj->pInventory[lpMsg->inventoryTarget].m_Type == ITEMGET(6,4)  || gObj->pInventory[lpMsg->inventoryTarget].m_Type == ITEMGET(6,5) ||
			gObj->pInventory[lpMsg->inventoryTarget].m_Type == ITEMGET(6,6)  || gObj->pInventory[lpMsg->inventoryTarget].m_Type == ITEMGET(6,7)||
			gObj->pInventory[lpMsg->inventoryTarget].m_Type == ITEMGET(6,8) || gObj->pInventory[lpMsg->inventoryTarget].m_Type == ITEMGET(6,9)||
			gObj->pInventory[lpMsg->inventoryTarget].m_Type == ITEMGET(6,10) || gObj->pInventory[lpMsg->inventoryTarget].m_Type == ITEMGET(6,11) ||
			gObj->pInventory[lpMsg->inventoryTarget].m_Type == ITEMGET(6,12) || gObj->pInventory[lpMsg->inventoryTarget].m_Type == ITEMGET(6,13)) &&
			(gObj->pInventory[lpMsg->inventoryTarget].m_Option1 < 1))
		{
			if ((rand() % 100) < btSuccessRate)
			{
				gObj->pInventory[lpMsg->inventoryTarget].m_Option1 = 1;
				gObjInventoryItemSet(aIndex,lpMsg->inventoryPos, -1);
				ItemClear(aIndex,lpMsg->inventoryPos);
				GCInventoryItemOneSend(aIndex, lpMsg->inventoryTarget);
				GCInventoryItemDeleteSend(aIndex, lpMsg->inventoryPos, 1);	
			}
			else
			{
				gObjInventoryItemSet(aIndex,lpMsg->inventoryPos, -1);
				ItemClear(aIndex,lpMsg->inventoryPos);
				GCInventoryItemOneSend(aIndex, lpMsg->inventoryTarget);
				GCInventoryItemDeleteSend(aIndex, lpMsg->inventoryPos, 1);
			}
		}
		else
		{
			GCServerMsgStringSend("Jewel Of Fire is not applicable to this item !", aIndex, 1);
			return;
		}
	}
}

void CCustomJewels::ItemClear(int aIndex, int Pos)	
{	
	OBJECTSTRUCT * gObj = (OBJECTSTRUCT*) OBJECT_POINTER (aIndex);

	memset(gObj->pInventory[Pos].m_Special, 0, sizeof(gObj->pInventory[Pos].m_Special));
	memset(gObj->pInventory[Pos].m_SpecialValue, 0, sizeof(gObj->pInventory[Pos].m_SpecialValue));
	memset(gObj->pInventory[Pos].m_Resistance, 0, sizeof(gObj->pInventory[Pos].m_Resistance));

	gObj->pInventory[Pos].m_Type =-1;
	gObj->pInventory[Pos].m_Level =0;
	gObj->pInventory[Pos].m_Part=0;
	gObj->pInventory[Pos].m_Class=0;
	gObj->pInventory[Pos].m_TwoHand=0;
	gObj->pInventory[Pos].m_AttackSpeed=0;
	gObj->pInventory[Pos].m_DamageMin=0;
	gObj->pInventory[Pos].m_DamageMax=0;
	gObj->pInventory[Pos].m_SuccessfulBlocking=0;
	gObj->pInventory[Pos].m_Defense=0;
	gObj->pInventory[Pos].m_MagicDefense =0;
	gObj->pInventory[Pos].m_Durability=0;
	gObj->pInventory[Pos].m_SpecialNum=0;
	gObj->pInventory[Pos].m_Value=0;
	gObj->pInventory[Pos].m_Option1 =0;      
	gObj->pInventory[Pos].m_Option2 =0;  
	gObj->pInventory[Pos].m_SetOption =0;   
	gObj->pInventory[Pos].m_Number =0;
	gObj->pInventory[Pos].m_DurabilitySmall =0;
	gObj->pInventory[Pos].m_iPShopValue=-1;
	gObj->pInventory[Pos].m_bItemExist=true;
	gObj->pInventory[Pos].m_CurrentDurabilityState=-1;
	gObj->pInventory[Pos].m_SetOption=0;
	gObj->pInventory[Pos].m_QuestItem=false;
	gObj->pInventory[Pos].m_IsLoadPetItemInfo=0;
	gObj->pInventory[Pos].m_PetItem_Level =1;
	gObj->pInventory[Pos].m_PetItem_Exp =0;
	gObj->pInventory[Pos].m_Leadership=0;
	gObj->pInventory[Pos].m_JewelOfHarmonyOption = 0;
	gObj->pInventory[Pos].m_ItemOptionEx = 0;
}