/*-------------------------------------------------------*/
/*				Project Evolution Team Season 2          */
/*   Version GS 1.00.18 & GS-CS 1.00.19 Protocol Eng     */
/*             http://evolution-team.eu                  */
/*-------------------------------------------------------*/
/*                    Code By Th3AnG3L                   */
/*             http://evolution-team.eu                  */
/*-------------------------------------------------------*/
#include "StdAfx.h"

// Vip System
CVipSystem VipSystem;

void CVipSystem::Init()
{
	this->m_Enabled = GetPrivateProfileInt("Settings","Evo_EnableVipSystem",1,VIPFILE_PATH);
	this->m_Exp = GetPrivateProfileInt("GameServerInfo","AddExperience",1,COMMONFILE_PATH);
	this->m_BronzeExp = GetPrivateProfileInt("Settings","Evo_AddExperienceBronze",3,VIPFILE_PATH);
	this->m_BronzeDrop = GetPrivateProfileInt("Settings","Evo_ItemDropPerBonusBronze",3,VIPFILE_PATH);
	this->m_PlatinumExp = GetPrivateProfileInt("Settings","Evo_AddExperiencePlatinum",7,VIPFILE_PATH);
	this->m_PlatinumDrop = GetPrivateProfileInt("Settings","Evo_ItemDropPerBonusPlatinum",7,VIPFILE_PATH);
	this->m_GoldExp = GetPrivateProfileInt("Settings","Evo_AddExperienceGold",15,VIPFILE_PATH);
	this->m_GoldDrop = GetPrivateProfileInt("Settings","Evo_ItemDropPerBonusGold",15,VIPFILE_PATH);
}

void CVipSystem::Load(int aIndex)
{
	OBJECTSTRUCT *pObj = (OBJECTSTRUCT*)OBJECT_POINTER(aIndex);
	if(this->m_Enabled == 1)
	{
		Vip[pObj[aIndex].m_Index - OBJECT_MIN] = MuDB.CheckVip(pObj->AccountID);
		ApplyVip(aIndex);
	}
}

void CVipSystem::ApplyVip(int aIndex)
{
	OBJECTSTRUCT *pObj = (OBJECTSTRUCT*)OBJECT_POINTER(aIndex);
	if(Vip[pObj[aIndex].m_Index - OBJECT_MIN] == 0)
	{
		char lvlmsg[100];
		sprintf(lvlmsg,"[Free] Welcome back, [ %s ].", pObj->AccountID);
		GCServerMsgStringSend(lvlmsg,aIndex,1);
	}
	if(Vip[pObj[aIndex].m_Index - OBJECT_MIN] == 1)
	{
		pObj[aIndex].m_wItemDropRate += this->m_PlatinumDrop;
		char lvlmsg[100];
		sprintf(lvlmsg,"[Bronze VIP] Welcome back, [ %s ].", pObj->AccountID);
		GCServerMsgStringSend(lvlmsg,aIndex,1);
	}
	else if(Vip[pObj[aIndex].m_Index - OBJECT_MIN] == 2)
	{
		pObj[aIndex].m_wItemDropRate += this->m_PlatinumDrop;
		char lvlmsg[100];
		sprintf(lvlmsg,"[Platinum VIP] Welcome back, [ %s ].", pObj->AccountID);
		GCServerMsgStringSend(lvlmsg,aIndex,1);
	}
	else if(Vip[pObj[aIndex].m_Index - OBJECT_MIN] == 3)
	{
		pObj[aIndex].m_wItemDropRate += this->m_GoldDrop;
		char lvlmsg[100];
		sprintf(lvlmsg,"[Gold VIP] Welcome back, [ %s ].", pObj->AccountID);
		GCServerMsgStringSend(lvlmsg,aIndex,1);
	}
}

long ExpCalculator(OBJECTSTRUCT* pObj,int Experience)
{
	float BonusExperience = 0;

	if(VipSystem.Vip[pObj->m_Index - OBJECT_MIN] == 1)
	{
		BonusExperience = VipSystem.m_BronzeExp;
	}
	else if(VipSystem.Vip[pObj->m_Index - OBJECT_MIN] == 2)
	{
		BonusExperience = VipSystem.m_PlatinumExp;
	}
	else if(VipSystem.Vip[pObj->m_Index - OBJECT_MIN] == 3)
	{
		BonusExperience = VipSystem.m_GoldExp;
	}
	else
	{
		BonusExperience = VipSystem.m_Exp;
	}

	return (Experience * BonusExperience);
}

__declspec(naked) void MonsterExpSingleEx()
{
    _asm
	{
		MOV EAX,DWORD PTR SS:[EBP-0x04];
		PUSH EAX;
		MOV EDX,DWORD PTR SS:[EBP+0x08];
		PUSH EDX;
		CALL [ExpCalculator];
		MOV DWORD PTR SS:[EBP-0x04],EAX;
		MOV EBX,0x004E2C66;
        JMP EBX;
	}
}

__declspec(naked) void MonsterExpPartyEx()
{
    _asm
	{
        MOV EAX,DWORD PTR SS:[EBP-0x08];
		PUSH EAX;
		MOV EDX,DWORD PTR SS:[EBP-0x54];
		PUSH EDX;
		CALL [ExpCalculator];
		MOV DWORD PTR SS:[EBP-0x08],EAX;
		MOV EBX,0x004E335B;
		JMP EBX;
	}
}