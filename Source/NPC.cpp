#include "StdAfx.h"

// NPC Manager
CNPC NPC;

void CNPC::Init()
{
	this->Archer_Enabled = GetPrivateProfileInt("GoldenArcher","EnableGoldenArcher",1,NPCFILE_PATH);
	this->PKGuard_Enabled = GetPrivateProfileInt("NPC","EnablePKClearGuard",1,NPCFILE_PATH);
	this->ResetGuard_Enabled = GetPrivateProfileInt("NPC","EnableResetGuard",1,NPCFILE_PATH);
	this->m_Enabled = GetPrivateProfileInt("GameServerInfo","EnableHatcheryEvent",1,CUSTOMFILE_PATH);
	//this->m_Count = GetPrivateProfileInt("StoneExchanger","StonesCount",3,NPCSTONEEXCHANGER_PATH);
}

void CNPC::Talk(int aIndex,int Monster)
{
	if(gObj[Monster].Class == 236) // Golden Archer
	{
		if(this->Archer_Enabled == 1)
		{
			GoldenArcher.Npc(aIndex,Monster);
		}
	}

	if(gObj[Monster].Class == 249) // PK Guard
	{
		if(this->PKGuard_Enabled == 1)
		{
			//PKGuard.Npc(aIndex,Monster);
		}
	}

	if(gObj[Monster].Class == 371) // Reset Guard
	{
		if(this->ResetGuard_Enabled == 1)
		{
			ResetGuard.Npc(aIndex,Monster);
		}
	}
	if(gObj[Monster].Class == 239) // Exchange Guard
	{
		if(this->m_Enabled == 1)
		{
			HatcheryEvent.Npc(aIndex,Monster);
		}
	}
}

int gObjSetMonsterEx(int aIndex,int Monster)
{
	if(gObjSetMonster1(aIndex,Monster) == true)
	{
		if(Monster == 371) // Reset Guard
		{
			gObj[aIndex].Type = 3;
		}

		return true;
	}

	return false;
}