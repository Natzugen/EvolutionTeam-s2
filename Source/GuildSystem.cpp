#include "StdAfx.h"
#include "SQLX.h"

void MsgOutputSystem(int aIndex,char* Message,...)
{
	char szPacket[1024];
	va_list pArguments;
	va_start(pArguments,Message);
	vsprintf(szPacket,Message,pArguments);
	va_end(pArguments);
	BYTE Packet[0xFF] = {0};
	BYTE Len = (strlen(szPacket) + 0x13);
	Packet[0] = 0xC1;
	Packet[1] = Len+15;
	Packet[2] = 0x00;
	Packet[13] = 0x40;
	strncpy((char*)&Packet[14],szPacket,strlen(szPacket));
	DataSend(aIndex,Packet,Packet[1]);
/*

	char szPacket[1024];
	va_list pArguments;
	va_start(pArguments,Message);
	vsprintf(szPacket,Message,pArguments);
	va_end(pArguments);
	BYTE Packet[0xFF] = {0};
	BYTE Len = (strlen(szPacket) + 0x13);
	Packet[0] = 0xC1;
	Packet[1] = Len+15;
	Packet[2] = 0x00;
	Packet[13] = 0x7E;
	strncpy((char*)&Packet[14],szPacket,strlen(szPacket));
	DataSend(aIndex,Packet,Packet[1]);*/
}

void gObjWrite2(int aIndex,int gObjParam,long int Value)
{
	*(long int*)(aIndex * OBJECT_SIZE + OBJECT_BASE + gObjParam) = Value;
}

long int gObjGetInt2(int aIndex,int gObjParam)
{
	return *(long int*)(aIndex * OBJECT_SIZE + OBJECT_BASE + gObjParam);
}

pCGGuildMasterInfoSave CGGuildMasterInfoSave = (pCGGuildMasterInfoSave) 0x00562830; // OK

// Guild System
CGuildSystem GuildSystem;

void CGuildSystem::Init()
{
	this->m_Enabled = GetPrivateProfileInt("GuildSystem","Enabled",1,"..\\EData\\EGuildSystem.ini");
	this->m_Price = GetPrivateProfileInt("GuildSystem","CreatePrice",1000000,"..\\EData\\EGuildSystem.ini");
	this->m_MaxGuilds = GetPrivateProfileInt("GuildSystem","MaxGuildCount",15,"..\\EData\\EGuildSystem.ini");
}

void CGuildSystem::Check(int aIndex, PMSG_GUILDINFOSAVE *lpMsg)
{
	OBJECTSTRUCT *gObj = (OBJECTSTRUCT*)OBJECT_POINTER(aIndex);

	MySQL.Execute("SELECT count(*) FROM Guild");
	int Count = MySQL.GetInt();

	if(Count >= this->m_MaxGuilds)
	{
		MsgOutputSystem(aIndex,"Sorry but the server has enough guilds!");
		return;
	}

	if(gObj->Money < this->m_Price)
	{
		MsgOutputSystem(aIndex,"To create a guild requires %d Zen.",this->m_Price);
		return;
	}

	gObjWrite2(aIndex,gObjZen,gObjGetInt2(aIndex,gObjZen) - this->m_Price);
	GCMoneySend(aIndex,gObjGetInt2(aIndex,gObjZen));
	CGGuildMasterInfoSave(aIndex, lpMsg);
}