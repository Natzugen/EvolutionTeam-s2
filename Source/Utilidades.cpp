/*-------------------------------------------------------*/
/*				Project Evolution Team Season 2          */
/*   Version GS 1.00.18 & GS-CS 1.00.19 Protocol Eng     */
/*             http://evolution-team.eu                  */
/*-------------------------------------------------------*/
/*                    Code By Th3AnG3L                   */
/*             http://evolution-team.eu                  */
/*-------------------------------------------------------*/

#include "Utilidades.h"
#include "Protocolos.h"
#include "GameServer.h"
#include "struct.h"
#include "user.h"
#include "MSSQL.h"

void LogLine(char*formatstring, ...){

va_list args;
va_start(args, formatstring);
char msg[0x1770];
memset(msg, 0, sizeof(msg));
FILE *logfile = fopen(".\\LOG\\Evolution.log","a+");
_vsnprintf(msg, sizeof(msg), formatstring, args);
fputs(msg, logfile);
fclose(logfile);
}

// log del post
void LogPost(char*formatstring, ...){

SYSTEMTIME now;
GetLocalTime(&now);
va_list args;
va_start(args, formatstring);
char msg[0x1770];
char logString[512];
memset(msg, 0, sizeof(msg));
FILE *logfile;
wsprintf(logString,"LOG_POST\\%02d%02d%02d_POST.txt", now.wYear, now.wMonth,now.wDay );
logfile=fopen(logString, "a+");
_vsnprintf(msg, sizeof(msg), formatstring, args);
fprintf(logfile,"%02d:%02d:%02d %s\n", now.wHour, now.wMinute, now.wSecond, msg);
fclose(logfile);
}


//log del gs
void LogGS(char*formatstring, ...){

SYSTEMTIME now;
GetLocalTime(&now);
va_list args;
va_start(args, formatstring);
char msg[0x1770];
char logString[512];
memset(msg, 0, sizeof(msg));
FILE *logfile;
wsprintf(logString,"\\LOG\\%02d%02d%02dEvolution.log", now.wYear, now.wMonth,now.wDay);
logfile=fopen(logString, "a+");
_vsnprintf(msg, sizeof(msg), formatstring, args);
fprintf(logfile,"%02d:%02d:%02d %s\n", now.wHour, now.wMinute, now.wSecond, msg);
fclose(logfile);
}


//Log de GMS

void LogGM(char*formatstring, ...){

SYSTEMTIME now;
GetLocalTime(&now);
va_list args;
va_start(args, formatstring);
char msg[0x1770];
char logString[512];
memset(msg, 0, sizeof(msg));
FILE *logfile;
wsprintf(logString,"LOG_GMS\\%02d%02d%02d_GMS.txt", now.wYear, now.wMonth,now.wDay );
logfile=fopen(logString, "a+");
_vsnprintf(msg, sizeof(msg), formatstring, args);
fprintf(logfile,"%02d:%02d:%02d %s\n", now.wHour, now.wMinute, now.wSecond, msg);
fclose(logfile);
}

void LogReset(char*formatstring, ...){

SYSTEMTIME now;
GetLocalTime(&now);
va_list args;
va_start(args, formatstring);
char msg[0x1770];
char logString[512];
memset(msg, 0, sizeof(msg));
FILE *logfile;
wsprintf(logString,"LOG_RESET\\%02d%02d%02d_RESET.txt", now.wYear, now.wMonth,now.wDay );
logfile=fopen(logString, "a+");
_vsnprintf(msg, sizeof(msg), formatstring, args);
fprintf(logfile,"%02d:%02d:%02d %s\n", now.wHour, now.wMinute, now.wSecond, msg);
fclose(logfile);
}

void ToHex(unsigned char* out, unsigned char* data, int c_len){
string s,t;
char cBuff[5001];
c_len = c_len & 0xff;
memset(cBuff, 0, 5000);
for(int i=0;i<c_len;i++){
wsprintf(cBuff+(i*3),"%02X,",data[i]);
}
strcat(cBuff, "\r\n");
memcpy(out,cBuff,(c_len*3)+2);
}
void HookThis(DWORD dwMyFuncOffset, DWORD dwJmpOffset){
*(DWORD*)(dwJmpOffset+1) = dwMyFuncOffset - (dwJmpOffset+5);
}
void SetNop(DWORD dwOffset, int Size){
for(int n=0; n < Size; n++){
*(BYTE*)(dwOffset+n) = 0x90;
}
}
void SetRetn(DWORD dwOffset){
*(BYTE*)(dwOffset) = 0xC3;
}
void SetByte(DWORD dwOffset,BYTE btValue){
*(BYTE*)(dwOffset) = btValue;
}

//=================================================
//=====================VERIFICA SI EL PJ ES GM O NO
//=================================================

bool VerificaGM(DWORD gObjId)
{
	if(*(short int*)(gObjId * gObjSize + gObjOffset + gObjCtl) == 32 || *(short int*)(gObjId * gObjSize + gObjOffset + gObjCtl) == 8)
	{
		return true;
	}
	else
	{
		return false;
	}
}
//=============================================
//======RETORNAR INDEX DEL PJ
//=============================================
DWORD gObjByNick ( char * nick )
{
for ( DWORD i = gObjPlayer; i < gObjMaxUsr; i ++)
{
char * Name= (char*)( gObjOffset + (gObjSize * i)+ gObjNick);
if (memcmp (nick,Name, 10) == 0)
{
return i;
}
}
return 0xFFFF;
}

DWORD gObjByNick1 ( char *nick )
{
	for ( DWORD i = MIN_PLAYERID ; i < MAX_PLAYERID ; i ++ )
	{
		char * pnick = (char*) ( gObjBaseAddr + ( gObjSize * i ) + gObj_PlayerName );
		if ( memcmp ( nick , pnick , strlen(nick) ) == 0 )
		{
			return i;
		}
	}
	return 0xFFFF;
}
//Definir Char
void *GetPlayerAddress(unsigned int PlayerID)
{
return (void *)(gObjOffset + (PlayerID*gObjSize));
}
void gObj_GetNick (DWORD gObjId, char * nick)
{
//memcpy (nick,( char *)(gObjOffset + (gObjSize * gObjId) + gObjNick), 10);
memcpy (nick, (char*)(gObjOffset+(gObjSize * gObjId)+gObjNick),10);
}
void gObj_GetLogin (WORD gObjId,char * login)
{
memcpy (login,(char*)(gObjOffset + (gObjSize * gObjId) + gObjLogin), 10);
}
DWORD gObj_GetMoney(WORD gObjId)
{
return *(DWORD*)(gObjOffset + (gObjSize * gObjId) + gObjZen);
}
//Pegar Level
WORD gObj_GetLevel(DWORD PlayerID)
{
BYTE *Player = (BYTE *)GetPlayerAddress(PlayerID);
WORD level=0;
memcpy(&level,Player+gObjLvl,sizeof(WORD));
return level;
}
//Pegar pontos que o char possui para distribuir
DWORD gObj_GetLevelUpPoints ( WORD gObjId )
{
	return *(DWORD*)( gObjOffset + ( gObjSize * gObjId) + gObjLupp );
}
//pegar cordenadas y mapa
char gObj_GetMap (WORD gObjId)
{
char * map = (char*)(gObjOffset + (gObjSize * gObjId) + gObjMapID);
return *map;
}
char gObj_GetPosX (WORD gObjId)
{
		char * PosX = (char*)( gObjOffset + ( gObjSize * gObjId) + gObjPosX );
	return *PosX;
}
char gObj_GetPosY (WORD gObjId)
{
char *PosY = (char*)(gObjOffset + (gObjSize * gObjId) + gObjPosY);
return *PosY;
}
//pegar Classe del pj
int GetPlayerClass(DWORD PlayerID)
{
	BYTE *Player = (BYTE*)GetPlayerAddress(PlayerID);
	BYTE Class=0;
	memcpy(&Class, Player+gObjClass, sizeof(BYTE));
	return Class;
}
void gObj_Write(int PlayerID,int gObjParam,long int Value){
*(long int*)(PlayerID * gObjSize + gObjOffset + gObjParam) = Value;
}

long int gObj_GetInt(int PlayerID, int gObjParam){
return *(long int*)(PlayerID * gObjSize + gObjOffset + gObjParam);
}

char* gObj_GetChar(int PlayerID, int gObjParam){
return (char*)(PlayerID * gObjSize + gObjOffset + gObjParam);
}

//veridica los conectados.
bool gObjIsConnected(DWORD wId)
{
gObj_GetNick(wId, Character);
if(wId < 6400 && wId > 7400) return false;
DWORD Status = gObj_GetInt(wId, gObj_isonline);
if(Status >= 3 && strcmpi(Character, "GoldenBudg") !=0) return true;
return false;
}
//enviar datos para todos
void DataSendAll(unsigned char* Packet,int Length)
{
for (int i=6400; i<7400; i++)
if(gObjIsConnected(i))
DataSend(i,Packet,Length);
}
//Enviar Mensaje Para Server
void ServerMsgSend(DWORD wId,int Type,char Sender[20],const char* Message,...)
{
char szBuffer[1024];
va_list pArguments;
va_start(pArguments,Message);
vsprintf(szBuffer,Message,pArguments);
va_end(pArguments);
BYTE *Packet;
Packet = (BYTE*) malloc(200);
memset(Packet, 0x00,200);
*Packet = 0xC1;
if(Type) *(Packet+2) = 0x02;
else *(Packet+2) = 0x00;
memcpy((Packet+3),Sender,strlen(Sender));
memcpy((Packet+13),szBuffer,strlen(szBuffer));
int Len = (strlen(szBuffer) + 0x13);
*(Packet+1) = Len;
if(!wId) DataSendAll(Packet,Len);
else
if(gObjIsConnected(wId))
DataSend(wId,Packet,Len);
free (Packet);
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
	if(gObjIsConnected(aIndex))
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
	if(gObjIsConnected(aIndex))
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
	if(gObjIsConnected(aIndex))
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
	if(gObjIsConnected(aIndex))
	DataSendAll(Packet,Packet[1]);
}
//recien es prueba
void NPCSay(DWORD PlayerID,DWORD iNpcID, char *Texto)
{
DWORD cNpcID = (DWORD)GetPlayerAddress(iNpcID);
NPCTalk(cNpcID,Texto,PlayerID);
}

//para el newsystem
void StringSendAll(char*Texto,int tipo)
{
	for (int i=MIN_PLAYERID;i<MAX_PLAYERID;i++)
	{
		if(gObjIsConnected(i))
		{
			GCServerMsgStringSend(Texto,i,tipo);
		}
	}
}


//para pkclear xd
DWORD gObj_GetPKStatus ( DWORD gObjId )
{
return *(DWORD*) ( gObjOffset + (gObjSize * gObjId) + gObjPk );
} 

void WriteMemoryInt(DWORD Offset, DWORD bValue, DWORD bValueMax, DWORD OffsetLen)
{
	HANDLE hProc = GetCurrentProcess();

	if(bValue > bValueMax) return;
	WriteProcessMemory(hProc, (LPVOID)Offset, &bValue, OffsetLen, NULL);
}

//prueba del clearinv

int DelPlayerAllItemNoInv ( DWORD PlayerID)
{
	DWORD * inv = (DWORD*) ( gObjBaseAddr + ( gObjSize * PlayerID) + gObj_INV );

	// CHECK WITHOUT PSHOP IN WHOLE INVENTORY
	for ( BYTE i = 12 ; i < 76 ; i ++ )
	{
		WORD * pitemId = (WORD*) ( ( i * GS_ITEMSIZE ) + *inv + 6 );
		gObjInventoryDeleteItem ( PlayerID , i );
		gObjInventoryDeleteSend ( PlayerID , i  , 1 );
	}

	return 0;
}

//pCloseClient CloseClient = (pCloseClient) 0x00401046;

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

void GCFireworkSend(int aIndex,int X,int Y,int Amount)
{
	BYTE Packet[7] = {0xC1,0x07,0xF3,0x40,0x00,X,Y};

	for(int i = 0; i < Amount; i++)
	{
		DataSend(aIndex,Packet,Packet[1]);
	}
}

pGCInventoryItemDeleteSend GCInventoryItemDeleteSend = (pGCInventoryItemDeleteSend) 0x004036F2;
pgObjCalCharacter gObjCalCharacter = (pgObjCalCharacter) 0x004C2650; 
pGCReFillSend GCReFillSend = (pGCReFillSend) 0x00404994; 
pgObjSetBP gObjSetBP = (pgObjSetBP) 0x00401C99; 
pGCManaSend GCManaSend = (pGCManaSend) 0x004029B4;
pGCLevelUpMsgSend GCLevelUpMsgSend = (pGCLevelUpMsgSend) 0x004060C3;
pChatTargetSend ChatTargetSend = (pChatTargetSend) 0x00402A27;
pgObjSetMonster gObjSetMonster1 = (pgObjSetMonster) 0x004D6E90;
//para el fix del gm
pgObjSetCharacter				gObjSetCharacter				= (pgObjSetCharacter)0x4D3990;

int DelPlayerAllItem ( DWORD PlayerID)
{
	DWORD * inv = (DWORD*) ( gObjBaseAddr + ( gObjSize * PlayerID) + gObj_INV );

	// CHECK WITHOUT PSHOP IN WHOLE INVENTORY
	for ( BYTE i = 0 ; i < 76 ; i ++ )
	{
		WORD * pitemId = (WORD*) ( ( i * GS_ITEMSIZE ) + *inv + 6 );
		gObjInventoryDeleteItem ( PlayerID , i );
		gObjInventoryDeleteSend ( PlayerID , i  , 1 );
	}

	return 0;
}

void gObj_GetIP (DWORD gObjId,char*Ip_Addr)
{
	memcpy (Ip_Addr,(char*)(gObjOffset+(gObjSize*gObjId)+gObjIP),16);
}

//agregado para el happyhour

void SetDrop(DWORD Drop)
{
	__asm
	{
		MOV EAX,Drop
		MOV DWORD PTR DS:[SetORGetDrop_Offset],EAX
	}
}

//agregado para el happyhour

int GetDrop()
{
	int retr=0;
	_asm
	{
		MOV ECX, DWORD PTR DS: [SetORGetDrop_Offset]
		MOV retr, ECX
	}
	return retr;
}
//agregado para el happyhour
int GetExp()
{
	float * EXPERIENCE = (float *)(gAddExperience); 
	int retr = *EXPERIENCE;
	return retr;
}

//prueba para recuper el login
LPSTR GetUser(DWORD PlayerID)
{
	LPSTR result=" ";
	if ((PlayerID>=MIN_PLAYERID)&&(PlayerID<MAX_PLAYERID))
	{
		//OBJECTSTRUCT *gObj = (OBJECTSTRUCT*)OBJECT_POINTER(aIndex);
		OBJECTSTRUCT *pObj = (OBJECTSTRUCT*)(PlayerID*gObjSize + gObjBaseAddr);
		result=pObj->AccountID;
	}
	return result;
}

void gObjWrite(int aIndex,int gObjParam,long int Value)
{
	*(long int*)(aIndex * OBJECT_SIZE + OBJECT_BASE + gObjParam) = Value;
}
long int gObjGetInt(int aIndex,int gObjParam)
{
	return *(long int*)(aIndex * OBJECT_SIZE + OBJECT_BASE + gObjParam);
}

void MsgNormal(int aIndex,char* szMsg,...)
{
	char szTemp[1024];

	va_list pArguments;
	va_start(pArguments,szMsg);
	vsprintf(szTemp,szMsg,pArguments);
	va_end(pArguments);
	
	GCServerMsgStringSend(szTemp, aIndex,1);


}
void FunctionHook(DWORD NewOffset,DWORD JumpOffset)
{
	*(DWORD*)(JumpOffset+1) = NewOffset - (JumpOffset+5);
}

void PHeadSubSetB(LPBYTE lpBuf, BYTE head, BYTE sub, int size)
{
	lpBuf[0] =0xC1; // Packets
	lpBuf[1] =size;
	lpBuf[2] =head;
	lpBuf[3] =sub;
}
void AllServerMsgSend(char *message)
{
	for(int i = OBJECT_MIN; i < OBJECT_MAX; i++)
	{
		OBJECTSTRUCT *gObj = (OBJECTSTRUCT*)OBJECT_POINTER(i);
		if(gObj->Connected == 3)
			GCServerMsgStringSend(message, i, 0);
	}
}
void MsgAll(char* szMsg,...)
{
	char szTemp[1024];

	va_list pArguments;
	va_start(pArguments,szMsg);
	vsprintf(szTemp,szMsg,pArguments);
	va_end(pArguments);

	AllServerMsgSend(szTemp);
}
char *GetMapName(int MapId)
{
	switch (MapId)
	{
		case 0:
			return "Lorencia";
		case 1:
			return "Dungeon";
		case 2:
			return "Devais";
		case 3:
			return "Noria";
		case 4:
			return "Lost Tower";
		case 5:
			return "Exile";
		case 6:
			return "Arena";
		case 7:
			return "Atlans";
		case 8:
			return "Tarkan";
		case 9:
			return "Devil Square";
		case 10:
			return "Icarus";
		case 30:
			return "Valley of Loren";
		case 31:
			return "Land of Trial";
		case 32:
			return "Devil Square";
		case 33:
			return "Aida";
		case 34:
			return "Crywolf";
		case 35:
			return "Null";
		case 36:
			return "Kalima";
		case 37:
			return "Kantru1";
		case 38:
			return "Kantru2";
		case 39:
			return "Kantru3";
		case 40:
			return "Silent";
		case 41:
			return "Barracks";
		case 42:
			return "Refuge";
		case 43:
			return "Null";
		case 44:
			return "Null";
		case 51:
			return "Elbeland";
		case 52:
			return "Blood Castle";
		case 53:
			return "Chaos Castle";
		case 56:
			return "Swamp of Calmness";
		case 57:
			return "Raklion";
		case 58:
			return "Raklion";
	}
	if (MapId >= 11 && MapId <= 17)
		return "Blood Castle";

	if (MapId >= 18 && MapId <= 23)
		return "Chaos Castle";

	if (MapId >= 24 && MapId <= 29)
		return "Kalima";

	if (MapId >= 45 && MapId <= 50)
		return "Illusion Temple";
	
	return "Unknown";
}
void PHeadSetB(LPBYTE lpBuf, BYTE head, int size)
{
	lpBuf[0] =0xC1;		// Packets
	lpBuf[1] =size;
	lpBuf[2] =head;
}

int OnlineStatus(int aIndex)
{
	if(aIndex >= OBJECT_MIN && aIndex < OBJECT_MAX)
	{
		if(gObj[aIndex].Connected == 3)
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
bool ClickOnNPC(int aIndex,LPBYTE aRecv)
{
	if(aIndex > OBJECT_MAX)
		return true;

	if((aRecv[4] + aRecv[3] * 256) > OBJECT_MAX)
		return true;

	OBJECTSTRUCT *gObjNPC = (OBJECTSTRUCT*)OBJECT_POINTER((aRecv[4] + aRecv[3] * 256));

		int ZECordX = GetPrivateProfileInt("StoneExchanger","CordX",100,"..\\EData\\EStoneExchanger.ini");
		int ZECordY = GetPrivateProfileInt("StoneExchanger","CordY",100,"..\\EData\\EStoneExchanger.ini");
		int ZEMapN  = GetPrivateProfileInt("StoneExchanger","MaNumber",0,"..\\EData\\EStoneExchanger.ini");


	if(gObjNPC->Class == 247 && gObjNPC->X == ZECordX && gObjNPC->Y == ZECordY && gObjNPC->MapNumber == ZEMapN )
	{
		NPC.Talk(aIndex,(aRecv[4] + aRecv[3] * 256));
	}


	if (gObjNPC->Class == 385) //Illusion Temple
	{
		OBJECTSTRUCT *gObj = (OBJECTSTRUCT*)OBJECT_POINTER(aIndex);

		gObj->TargetNumber = gObjNPC->Class;
	}

	return false;
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
void ServerMsgSendMap(int Map,int Type,char* Message,...)
{
	for(int i = OBJECT_MIN; i < OBJECT_MAX; i++)
	{
		if(OnlineStatus(i))
		{
			if (gObj[i].MapNumber == Map)
			{
				GCServerMsgStringSend(Message,i,Type);
			}
		}
	}
}

void BuxConvert(char* buf, int size)
{
	for (int n = 0; n < size; n++)
	{
		buf[n]^=bBuxCode[n%3];
	}
}

void PlayerConnected(int aIndex,LPBYTE aRecv)
{

//========================================================================================================================
	OBJECTSTRUCT *gObj = (OBJECTSTRUCT*) OBJECT_POINTER (aIndex);
	
	gObj->OffTradeCoin = 0;
	gObj->OffTradeZen = 0;
	gObj->OffTradeCred = 0;
}
void MsgAllNormal(int aIndex,char* szMsg,...)
{
	char Message[1024];
	va_list pArguments;
    va_start(pArguments,szMsg);
	vsprintf_s(Message,sizeof(Message), szMsg, pArguments);
	va_end(pArguments);
	BYTE *Packet;
	Packet = (BYTE*) malloc(200);
	memset(Packet, 0x00, 200);
	*Packet = 0xC1;
	*(Packet+2) = 0x00;
	memcpy((Packet+13), Message, strlen(Message));
	int Len = (strlen(Message) + 0x13);
	*(Packet+1) = Len;
	DataSendAll(Packet, Len);
	free (Packet);
	}

void LogNotice(int type,char* szMsg,...)
{
	char szTemp[1024];

	va_list pArguments;
	va_start(pArguments,szMsg);
	vsprintf(szTemp,szMsg,pArguments);
	va_end(pArguments);

	LogAddFuncColor(type,szTemp);
}
void  GCMagicAttackNumberSendH(OBJECTSTRUCT*  gObj, BYTE MagicNumber, int usernumber,  unsigned char skillsuccess)
{
	PMSG_MAGICATTACK_RESULT pAttack;
	
	PHeadSetBE((LPBYTE)&pAttack, 0x19, sizeof(pAttack));
	pAttack.MagicNumber = MagicNumber;
	pAttack.SourceNumberH = SET_NUMBERH(gObj->m_Index);
	pAttack.SourceNumberL = SET_NUMBERL(gObj->m_Index);
	pAttack.TargetNumberH = SET_NUMBERH(usernumber);
	pAttack.TargetNumberL = SET_NUMBERL(usernumber);
	pAttack.TargetNumberH &= 0x7F;

	if ( skillsuccess )
		pAttack.TargetNumberH |= 0x80;


	DataSend(gObj->m_Index, (LPBYTE)&pAttack, pAttack.h.size);
	MsgSendV2(gObj, (LPBYTE)&pAttack, pAttack.h.size);
}
void PHeadSetBE( LPBYTE lpBuf, BYTE head,int size)
{
	lpBuf[0] =0xC3;
	lpBuf[1] =size;
	lpBuf[2] =head;
}
void MsgSendV2(OBJECTSTRUCT* gObj, unsigned char* Msg, int size)
{
	for ( int n=0;n<75;n++)
	{
		if ( gObj->VpPlayer2[n].type == OBJECT_USER )
		{
			if ( gObj->VpPlayer2[n].state != 0 )
			{
				DataSend(gObj->VpPlayer2[n].number, Msg, size);
			}
		}
	}
}