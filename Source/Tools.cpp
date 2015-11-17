#include "StdAfx.h"
#include "Tools.h"
#include "Global.h"
#include "Utilidades.h"
#include "Mapping.h"
#include "Offset.h"
void SetByte(DWORD NewOffset,BYTE NewByte)
{
	*(BYTE*)(NewOffset) = NewByte;
}

void SetJNZ(DWORD NewOffset)
{
	*(BYTE*)(NewOffset) = 0x75;
}

void SetJE(DWORD NewOffset)
{
	*(BYTE*)(NewOffset) = 0x74;
}

void SetJMP(DWORD NewOffset)
{
	*(BYTE*)(NewOffset) = 0xEB;
}


void SetNop(DWORD NewOffset,int Size)
{
	for(int n = 0; n < Size; n++)
	{
		*(BYTE*)(NewOffset+n) = 0x90;
	}
}

void SetRetn(DWORD NewOffset)
{
	*(BYTE*)(NewOffset) = 0xC3;
}

void FunctionHook(DWORD NewOffset,DWORD JumpOffset)
{
	*(DWORD*)(JumpOffset+1) = NewOffset - (JumpOffset+5);
}

int VerifyGM(int aIndex)
{
	if(*(short int*)(aIndex * OBJECT_SIZE + OBJECT_BASE + gObjCtl) == 32 || *(short int*)(aIndex * OBJECT_SIZE + OBJECT_BASE + gObjCtl) == 8)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

void gObjGetNick(int aIndex,char* Nick)
{
	memcpy(Nick,(char*)(OBJECT_BASE + (OBJECT_SIZE * aIndex) + gObjNick),11);
}

long int gObjGetInt(int aIndex,int gObjParam)
{
	return *(long int*)(aIndex * OBJECT_SIZE + OBJECT_BASE + gObjParam);
}

void gObjWrite(int aIndex,int gObjParam,long int Value)
{
	*(long int*)(aIndex * OBJECT_SIZE + OBJECT_BASE + gObjParam) = Value;
}

int OnlineStatus(int iIndex)
{
	if(iIndex >= OBJECT_MIN && iIndex < OBJECT_MAX)
	{
		if(gObj[iIndex].Connected == 3)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}
}

int gObjGetIndex(char* Target)
{
	for(int n = OBJECT_MIN; n < OBJECT_MAX; n++)
	{
		if(gObj[n].Connected >= 3)
		{
			if(gObj[n].Name[0] == *Target)
			{
				if(strcmp(&gObj[n].Name[0],Target) == 0)
				{
					return n;
				}
			}
		}
	}

	return 0;
}

void MsgOutput(int aIndex,char* Message,...)
{
	char Packet[512]="";
	va_list pArguments;
	va_start(pArguments,Message);
	vsprintf(&Packet[0],Message,pArguments);
	va_end(pArguments);
	GCServerMsgStringSend(&Packet[0],aIndex,1);
}

void MsgOutputGlobal(int aIndex,char* Message,...)
{
	char Packet[512]="";
	va_list pArguments;
	va_start(pArguments,Message);
	vsprintf(&Packet[0],Message,pArguments);
	va_end(pArguments);
	GCServerMsgStringSend(&Packet[0],aIndex,0);
}

void ServerMsgSendYellow(int aIndex,char* Name,char* Message,...)
{
	char szPacket[1024];
	va_list pArguments;
	va_start(pArguments,Message);
	vsprintf(szPacket,Message,pArguments);
	va_end(pArguments);
	BYTE Packet[0xFF] = {0};
	BYTE Len = (strlen(szPacket) + 0x13);
	Packet[0] = 0xC1;
	Packet[1] = Len+16;
	Packet[2] = 0x00;
	strncpy((char*)&Packet[3],Name,10);
	Packet[13] = 0x40;
	Packet[14] = 0x40;
	strncpy((char*)&Packet[15],szPacket,strlen(szPacket));
	if(!aIndex)DataSendAll(Packet,Packet[1]);
	else
	if(OnlineStatus(aIndex))
	DataSendAll(Packet,Packet[1]);
}

void ServerMsgSendBlue(int aIndex,char* Name,char* Message,...)
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
	strncpy((char*)&Packet[3],Name,10);
	Packet[13] = 0x7E;
	strncpy((char*)&Packet[14],szPacket,strlen(szPacket));
	if(!aIndex)DataSendAll(Packet,Packet[1]);
	else
	if(OnlineStatus(aIndex))
	DataSendAll(Packet,Packet[1]);
}

void ServerMsgSendOrange(int aIndex,char* Name,char* Message,...)
{
	char szPacket[1024];
	va_list pArguments;
	va_start(pArguments,Message);
	vsprintf(szPacket,Message,pArguments);
	va_end(pArguments);
	BYTE Packet[0xFF] = {0};
	BYTE Len = (strlen(szPacket) + 0x13);
	Packet[0] = 0xC1;
	Packet[1] = Len+14;
	Packet[2] = 0x02;
	strncpy((char*)&Packet[3],Name,10);
	strncpy((char*)&Packet[13],szPacket,strlen(szPacket));
	if(!aIndex)DataSendAll(Packet,Packet[1]);
	else
	if(OnlineStatus(aIndex))
	DataSendAll(Packet,Packet[1]);
}

void ServerMsgSendGreen(int aIndex,char* Name,char* Message,...)
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
	strncpy((char*)&Packet[3],Name,10);
	Packet[13] = 0x40;
	strncpy((char*)&Packet[14],szPacket,strlen(szPacket));
	if(!aIndex)DataSendAll(Packet,Packet[1]);
	else
	if(OnlineStatus(aIndex))
	DataSendAll(Packet,Packet[1]);
}

void ServerMsgSendAll(char* Message,...)
{
	for(int i = OBJECT_MIN; i < OBJECT_MAX; i++)
	{
		if(OnlineStatus(i))
		{
			GCServerMsgStringSend(Message,i,0);
		}
	}
}

void DataSendAll(unsigned char* Packet,int Length)
{
	for(int i = OBJECT_MIN; i < OBJECT_MAX; i++)
	{
		if(OnlineStatus(i))
		{
			DataSend(i,Packet,Length);
		}
	}
}

void GCFireworkSend(int aIndex,int X,int Y,int Amount)
{
	BYTE Packet[7] = {0xC1,0x07,0xF3,0x40,0x00,X,Y};

	for(int i = 0; i < Amount; i++)
	{
		DataSend(aIndex,Packet,Packet[1]);
	}
}