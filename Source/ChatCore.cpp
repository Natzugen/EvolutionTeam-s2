/*-------------------------------------------------------*/
/*				Proyecto OGC-Files V. 1.0                */
/*   Version GS 1.00.18 Y GS-CS 1.00.19 Protocolo Eng    */
/*             http://www.ogc-files.com.ar               */
/*-------------------------------------------------------*/
/*                    Code By ElChapu                    */
/*             http://www.ogc-soft.com                   */
/*-------------------------------------------------------*/
/*   OGC-Files Team: ElChapu, LucasTocxy, xCUERVOX       */
/*-------------------------------------------------------*/
#include "ChatCore.h"
#include "Configs.h"
#include <Windows.h>
#include "user.h"
#include "GameServer.h"
#include "Drops.h"
#include "NewsSystem.h"
#include "struct.h"
#include "Utilidades.h"

//=================================================//
// Comando "Drop" - Crea un Item dentro del juego //
//=================================================//
void ChatDrop(DWORD gObjId, char * msg)

	//Anda bien y crea Items ACC y las alas no se bugean!
	{
	if(strlen(msg) < 13)return;

	OBJECTSTRUCT *pObj = (OBJECTSTRUCT*)OBJECT_POINTER(gObjId);
	if(pObj->Authority < 32)return;

	int spaces=0;

	for(int i=0;i < strlen(msg);i++)
	{
		if(msg[i]==' ')
			spaces++;
	}

	if(spaces < 7)return;

	int IsDROP = GetPrivateProfileInt("Drop","Enable_Drop",0,COMMANDFILE_PATH);
	if(VerificaGM(gObjId) == false)
	{
		//GCServerMsgStringSend("[DROP]: Command used only by GM's",gObjId,1);
		GCServerMsgStringSend(MSG00,gObjId,1);
		return;
	}
	if (IsDROP == 0)
{
GCServerMsgStringSend(MSG01,gObjId,1);
return;
}
	if (IsDROP == 1)
{
	int IsGMSystem = GetPrivateProfileIntA("GameServerInfo","EnableGMSystem",0,CUSTOMFILE_PATH);
	if(IsGMSystem == 1)
	{
	    int CanDrop = 0;
		for(int x=1;x < GMSystemCount;x++)
		{
			if(!strcmp(GMSystemInfo[x].Name,pObj->Name))
			{
				CanDrop = GMSystemInfo[x].Drop;
			}
		}

		if(CanDrop == 0)
		{
			GCServerMsgStringSend(MSG03,gObjId,1);
			return;
		}
	}
	//esto de aca arriba es el gmsystem viejo  MSG03

	int ItemType,ItemNr,ItemLevel,ItemSkill,ItemLuck,ItemOpt,ItemExc,ItemAncient;
	sscanf(msg,"%d %d %d %d %d %d %d %d",&ItemType,&ItemNr,&ItemLevel,&ItemSkill,&ItemLuck,&ItemOpt,&ItemExc,&ItemAncient);

	DWORD Item=ItemType*512+ItemNr;

	ItemSerialCreateSend(gObjId,pObj->MapNumber,pObj->X,pObj->Y,Item,ItemLevel,0,ItemSkill,ItemLuck,ItemOpt,gObjId,ItemExc,ItemAncient);
	GCServerMsgStringSend(MSG02,gObjId,1);
	GCServerMsgStringSend(msg,gObjId,1);
	char Post[200];
	char Account[11];
	gObj_GetLogin(gObjId,Account);
	gObj_GetNick(gObjId,Character);
	sprintf(Post, "%s: [Evolution][Item Created]: %s",Character, msg);
	LogGM(Post);
	}

return;
}

//==================================================================================
//=====================COMANDO POST=================================================
//==================================================================================
void ChatGlobal(DWORD PlayerID,char * msg)
{
gObj_GetNick(PlayerID, Character);
int IsPost = GetPrivateProfileInt("Post","Enable_Post",1,COMMANDFILE_PATH);
int Level = GetPrivateProfileInt("Post","Level_Post",100,COMMANDFILE_PATH);
int IsPostColor = GetPrivateProfileInt("Post","PostColor",0,COMMANDFILE_PATH);
if (IsPost == 0)
{
GCServerMsgStringSend(MSG04,PlayerID,1);
return;
}
if(!strcmpi("/POST",msg))
{
GCServerMsgStringSend(MSG05,PlayerID,1);
return;
}
if(strlen(msg) < 1)
	{
		GCServerMsgStringSend(MSG06,PlayerID,1);
		return;
}
OBJECTSTRUCT *pObj = (OBJECTSTRUCT*)OBJECT_POINTER(PlayerID);
if(pObj->Level < Level)
	{
		char lvlmsg[100];
		sprintf(lvlmsg,MSG07, Level);
		GCServerMsgStringSend(lvlmsg,PlayerID,1);
return;
}
short int siPossuiCusto = GetPrivateProfileInt("Post","Enable_TakePrice",1,COMMANDFILE_PATH);
DWORD vCusto = GetPrivateProfileInt("Post","PostZen_Price", 10000,COMMANDFILE_PATH);

if(siPossuiCusto == 1){
if((DWORD)gObj_GetInt(PlayerID,gObjZen) < vCusto){
if(vCusto > 0){
char OutputZenFalha[200];
sprintf_s(OutputZenFalha,MSG08,vCusto);
GCServerMsgStringSend(OutputZenFalha,PlayerID,1);

return;
}
else{
GCServerMsgStringSend(MSG09,PlayerID, 1);

return;
}
}
}

int Muted = MuDB.CheckMute(pObj->Name);

	if(Muted == 1)
	{
		GCServerMsgStringSend(MSG10,PlayerID,1);
		return;
	}

	switch(IsPostColor)
	{
	case 0:
		{
			ServerMsgSendYellow(0,Character,"[POST][ %s ]", msg);
		}
		break;
	case 1:
		{
			ServerMsgSendBlue(0,Character,"[POST][ %s ]",msg);
		}
		break;
	case 2:
		{
			ServerMsgSendOrange(0,Character,"[POST][ %s ]",msg);
		}
		break;
	case 3:
		{
			ServerMsgSendGreen(0,Character,"[POST][ %s ]",msg);
		}
		break;
	default:
		break;
	}
//este es el real ojo a no confundirme
//ServerMsgSend(0, 1, Character, "[POST][ %s ]", msg);
char Post[200];
char Account[11];
gObj_GetLogin(PlayerID,Account);
gObj_GetNick(PlayerID,Character);
sprintf(Post, "%s: [POST]%s",Character, msg);
LogPost(Post);
if(siPossuiCusto == 1){
if((DWORD)gObj_GetInt(PlayerID,gObjZen) >= vCusto){
if(vCusto > 0){
gObj_Write(PlayerID,gObjZen,gObj_GetInt(PlayerID,gObjZen) - vCusto);
GCMoneySend(PlayerID,gObj_GetInt(PlayerID,gObjZen));

char OutputZenSuccess [200];
sprintf_s(OutputZenSuccess,MSG11,vCusto,gObj_GetInt(PlayerID,gObjZen));
GCServerMsgStringSend(OutputZenSuccess,PlayerID, 1);
}
}
}
}

//===============================================
//=========COMANDO ADD===========================
//===============================================

void AddStats(DWORD aIndex, LPCSTR lpBuffer, DWORD CMD_STATS_TYPE){

int SwitchAdd = GetPrivateProfileInt("Add","Enable_StatsADD",1,COMMANDFILE_PATH);
int Level = GetPrivateProfileInt("Add","Requested_Level",100,COMMANDFILE_PATH);

int Points = atoi(lpBuffer);

if(SwitchAdd == 0)
	{
		GCServerMsgStringSend(MSG12,aIndex,1);
		return;
	}


if((int)gObj_GetInt(aIndex,gObjLvl)<Level)
	{
		char levelmsg[100];
		sprintf(levelmsg,MSG13,Level);
		GCServerMsgStringSend(levelmsg, aIndex, 1);
		return;
	}

if(strlen(lpBuffer)<1)
	{
		GCServerMsgStringSend(MSG14,aIndex,1);
		return;
	}

if((int)gObj_GetInt(aIndex, gObjLupp)<Points || Points < 1)
	{
		GCServerMsgStringSend(MSG15,aIndex,1);
		return;
	}
if(atoi(lpBuffer)>200)
	{
		char OutputError[130];
		sprintf_s(OutputError,MSG16, lpBuffer, 200);
		GCServerMsgStringSend(OutputError,aIndex,1);
		return;
	}
if(CMD_STATS_TYPE == 4 && GetPlayerClass(aIndex)!=64 && GetPlayerClass(aIndex)!=66)
	{
		GCServerMsgStringSend(MSG17, aIndex,1);
		return;
	}

	short int siPossuiCusto = GetPrivateProfileInt("Add","Enable_TakePrice", 1,COMMANDFILE_PATH);
DWORD vCusto = GetPrivateProfileInt("Add","ADDZen_Price", 1000,COMMANDFILE_PATH);

if(siPossuiCusto == 1){
if ((DWORD)gObj_GetInt(aIndex, gObjZen)< vCusto) {
if(vCusto > 0) {
char OutputZenFalha[200];
sprintf_s(OutputZenFalha,MSG18, vCusto);
GCServerMsgStringSend(OutputZenFalha,aIndex,1);

return;
}
else{
GCServerMsgStringSend(MSG19, aIndex, 1);

return;
}
}
}

BYTE lpMsg[5] = {0xC1, 0x05, 0xF3, 0x06, CMD_STATS_TYPE};
	for(UINT i = 0; i < Points; i++)
		CGLevelUpPointAdd(lpMsg, aIndex);
	char Suceso[130];
	int lupp = gObj_GetInt(aIndex, gObjLupp);
	sprintf_s(Suceso,MSG20,Points,lupp);
	GCServerMsgStringSend(Suceso,aIndex,1);

if((DWORD)gObj_GetInt(aIndex,gObjZen) >= vCusto){
if(vCusto > 0){
gObj_Write(aIndex,gObjZen,gObj_GetInt(aIndex,gObjZen) - vCusto);
GCMoneySend(aIndex,gObj_GetInt(aIndex,gObjZen));

char OutputZenSuccess[200];
sprintf_s(OutputZenSuccess,MSG21,vCusto, gObj_GetInt(aIndex,gObjZen));
GCServerMsgStringSend(OutputZenSuccess,aIndex, 1);
}
}
}
//}

//=================================================
//========Comando Reload Para Recargar OGC-SOFT.Ini
//=================================================

void ChatReload(DWORD PlayerID, char * msg)
{
	OBJECTSTRUCT *pObj = (OBJECTSTRUCT*)OBJECT_POINTER(PlayerID);
if(strlen(msg) < 1)
{
GCServerMsgStringSend(MSG22,PlayerID,1);
GCServerMsgStringSend(MSG23,PlayerID,1); //si
GCServerMsgStringSend(MSG24,PlayerID,1); //si
GCServerMsgStringSend(MSG25,PlayerID,1);
GCServerMsgStringSend(MSG26,PlayerID,1);
GCServerMsgStringSend(MSG27,PlayerID,1);
GCServerMsgStringSend(MSG28,PlayerID,1);
GCServerMsgStringSend(MSG29,PlayerID,1);
GCServerMsgStringSend(MSG30,PlayerID,1);
GCServerMsgStringSend(MSG31,PlayerID,1);
GCServerMsgStringSend(MSG32,PlayerID,1);
return;
}
if(VerificaGM(PlayerID) == false)
{
GCServerMsgStringSend(MSG33,PlayerID,1);
return;
}
//aca poner el gm system
int IsGMSystem = GetPrivateProfileIntA("GameServerInfo","EnableGMSystem",0,CUSTOMFILE_PATH);
	if(IsGMSystem == 1)
	{
		int CanDrop = 0;
		for(int x=1;x < GMSystemCount;x++)
		{
			if(!strcmp(GMSystemInfo[x].Name,pObj->Name))
			{
				CanDrop = GMSystemInfo[x].Re;
			}
		}

		if(CanDrop == 0)
		{
			GCServerMsgStringSend(MSG56,PlayerID,1);
			return;
		}
	}
int IsReload = GetPrivateProfileInt("Reload","Configs",0,COMMANDFILE_PATH);
int IsReload1 = GetPrivateProfileInt("Reload","Monsters",0,COMMANDFILE_PATH);
int IsReload2 = GetPrivateProfileInt("Reload","FortuneWheel",0,COMMANDFILE_PATH);
int IsReload3 = GetPrivateProfileInt("Reload","Shops",0,COMMANDFILE_PATH);
int IsReload4 = GetPrivateProfileInt("Reload","DropSystem",0,COMMANDFILE_PATH);
int IsReload5 = GetPrivateProfileInt("Reload","NewSystem",0,COMMANDFILE_PATH);
int IsReload6 = GetPrivateProfileInt("Reload","GMSystem",0,COMMANDFILE_PATH);
int IsReload7 = GetPrivateProfileInt("Reload","VipSystem",0,COMMANDFILE_PATH);
int IsReload8 = GetPrivateProfileInt("Reload","GoldenArcher",0,COMMANDFILE_PATH);
int IsReload9 = GetPrivateProfileInt("Reload","ConnectMember",0,COMMANDFILE_PATH);
int reload = atoi(msg);
switch(reload)
{
case 0:
	if (IsReload == 0)
{
GCServerMsgStringSend(MSG34,PlayerID,1);
return;
}
		if (IsReload == 1)
{
{
IniciaIni();
LogAddFunc(MSG35,3);}
GCServerMsgStringSend(MSG36,PlayerID,1);
break;
return;
}
case 1:
	if (IsReload1 == 0)
{
GCServerMsgStringSend(MSG37,PlayerID,1);
return;
}
		if (IsReload1 == 1)
{
GameMonsterAllCloseAndReload();
GCServerMsgStringSend(MSG38, PlayerID,1);
break;
return;
}
case 2:
		if (IsReload2 == 0)
{
GCServerMsgStringSend(MSG39,PlayerID,1);
return;
}
		if (IsReload2 == 1)
{
Fortune.Init(FORTUNEFILE_PATH);
GCServerMsgStringSend(MSG40, PlayerID,1);
break;
return;
}
case 3:
			if (IsReload3 == 0)
{
GCServerMsgStringSend(MSG41,PlayerID,1);
return;
}
	if (IsReload3 == 1)
{
ShopDataLoad();
GCServerMsgStringSend(MSG42, PlayerID,1);
break;
return;
}
case 4:
	if (IsReload4 == 0)
	{
		GCServerMsgStringSend(MSG43,PlayerID,1);
		return;
	}
	if (IsReload4 == 1)
	{
		Drop.t_LoadSystem(); 
		GCServerMsgStringSend(MSG44, PlayerID,1);
		break;
		return;
	}
case 5:
	if (IsReload5 == 0)
	{
		GCServerMsgStringSend(MSG45,PlayerID,1);
		return;
	}
	if (IsReload5 == 1)
	{
		int IsNews = GetPrivateProfileIntA("Settings","Evo_NewsSystem",1,NEWSISTEMFILE_PATH);
		NewsON(IsNews);
		GCServerMsgStringSend(MSG46, PlayerID,1);
		break;
		return;
	}
case 6:
	if (IsReload6 == 0)
	{
		GCServerMsgStringSend(MSG47,PlayerID,1);
		return;
	}
	if (IsReload6 == 1)
	{
		LoadGMSystem();
		GCServerMsgStringSend(MSG48, PlayerID,1);
		break;
		return;
	}
case 7:
	if (IsReload7 == 0)
	{
		GCServerMsgStringSend(MSG49,PlayerID,1);
		return;
	}
	if (IsReload7 == 1)
	{
		VipSystem.Init();
		GCServerMsgStringSend(MSG50, PlayerID,1);
		break;
		return;
	}
case 8:
	if (IsReload8 == 0)
	{
		GCServerMsgStringSend(MSG51,PlayerID,1);
		return;
	}
	if (IsReload8 == 1)
	{
		GoldenArcher.Init(GOLDERARCHFILE_PATH);
		GCServerMsgStringSend(MSG52, PlayerID,1);
		break;
		return;
	}
case 9:
	if (IsReload9 == 0)
	{
		GCServerMsgStringSend(MSG53,PlayerID,1);
		return;
	}
	if (IsReload9 == 1)
	{

	}
default:
GCServerMsgStringSend(MSG55, PlayerID, 1);
break;
}
	char Post[200];
	char Account[11];
	gObj_GetLogin(PlayerID,Account);
	gObj_GetNick(PlayerID,Character);
	sprintf(Post, "%s: [Reload]: %s",Character, msg);
	LogGM(Post);
	}


//=============================================================================
//SERVER INFO
//=============================================================================
void ChatInfo(DWORD gObjId){
GCServerMsgStringSend("[ServerInfo:] Evolution Team Season 2 Premium", gObjId, 1);
GCServerMsgStringSend("[ServerInfo:] Code By Th3AnG3L", gObjId, 1);
GCServerMsgStringSend("[ServerInfo:] http://evolution-team.eu" , gObjId, 1);
GCServerMsgStringSend("[ServerInfo:] Created 11-07-2014", gObjId, 1);
}

//=============================================================================
//Copy...
//=============================================================================
void ChatCopy(DWORD gObjId){
GCServerMsgStringSend("[ServerInfo:] Evolution Team Season 2 Premium", gObjId, 1);
GCServerMsgStringSend("[ServerInfo:] Version 2.0.0", gObjId, 1);
GCServerMsgStringSend("[ServerInfo:] Version Premium." , gObjId, 1);
GCServerMsgStringSend("[ServerInfo:] Code by: Th3AnG3L", gObjId, 1);
}

//=============================================================================
//SERVER Ilegal.
//=============================================================================
void ChatElChapu(DWORD gObjId){
	StringSendAll("This Server is using illegal files, Evolution Team",0);
	LogGS("GameServer has been Detected.");
	LogGS("Buy License to use this files");
	LogGS("www.evolution-team.eu");
::ExitProcess(0);
}

//========================================================================================================================
// OffTradeZen Command
//========================================================================================================================
/*void ChatOffTradeZen(int aIndex)
{
	OBJECTSTRUCT * gObj = (OBJECTSTRUCT*)OBJECT_POINTER(aIndex);
	int OffTradeActive = GetPrivateProfileInt("OffTrade","OffTradeActive",1,"..\\EData\\EOffTrade.ini");
	int OffTradeZen = GetPrivateProfileInt("OffTrade","OffTradeZen",1,"..\\EData\\EOffTrade.ini");
	
	if (OffTradeActive == 1)
	{
	if (OffTradeZen == 1)
	{
	gObj->OffTradeZen = 1;
	OFFTrade.CreateOfflineTrade(aIndex);
	}
	else
	{
	MsgNormal(aIndex,"~[System] : OffTrade sell for zen disabled.");
	}
	}
	else
	{
	MsgNormal(aIndex,"~[System] : OffTrade System is disabled.");
	}
}
//========================================================================================================================
// OffTradeCoins Command
//========================================================================================================================
void ChatOffTradeCoins(int aIndex)
{
		OBJECTSTRUCT * gObj = (OBJECTSTRUCT*)OBJECT_POINTER(aIndex);
	int OffTradeActive = GetPrivateProfileInt("OffTrade","OffTradeActive",1,"..\\EData\\EOffTrade.ini");
	int OffTradeCoins = GetPrivateProfileInt("OffTrade","OffTradeCoins",1,"..\\EData\\EOffTrade.ini");
	if (OffTradeActive == 1)
	{
    if (OffTradeCoins == 1)
	{
	gObj->OffTradeCoin = 1;
	OFFTrade.CreateOfflineTrade(aIndex);
	}
	else
	{
	MsgNormal(aIndex,"~[System] : OffTrade sell for coins disabled.");
	}
	}
	else
	{
	MsgNormal(aIndex,"~[System] : OffTrade System is disabled.");
	}
}
//========================================================================================================================
// OffTradeCredits Command
//========================================================================================================================
void ChatOffTradeCredits(int aIndex)
{
		OBJECTSTRUCT * gObj = (OBJECTSTRUCT*)OBJECT_POINTER(aIndex);
	int OffTradeActive = GetPrivateProfileInt("OffTrade","OffTradeActive",1,"..\\EData\\EOffTrade.ini");
	int OffTradeCredits = GetPrivateProfileInt("OffTrade","OffTradeCredits",1,"..\\EData\\EOffTrade.ini");
	if (OffTradeActive == 1)
	{
    if (OffTradeCredits == 1)
	{
	gObj->OffTradeCred = 1;
	OFFTrade.CreateOfflineTrade(aIndex);
	}
	else
	{
	MsgNormal(aIndex,"~[System] : OffTrade sell for coins disabled.");
	}
	}
	else
	{
	MsgNormal(aIndex,"~[System] : OffTrade System is disabled.");
	}
} */

//=============================================================================
//Webs
//=============================================================================
void ChatWeb(DWORD aIndex){

int Switch = GetPrivateProfileInt("Oters","Web",1,COMMANDFILE_PATH);
if(Switch == 0)
	{
		GCServerMsgStringSend("Disabled by the Administrator Command.",aIndex,1);
		return;
	}

	GetPrivateProfileString ("Oters","MSG159","[WebServer] www.evolution-team.eu",MSG159,100,COMMANDFILE_PATH);
	GetPrivateProfileString ("Oters","MSG160","[WebServer] www.evolution-team.eu",MSG160,100,COMMANDFILE_PATH);
	GetPrivateProfileString ("Oters","MSG161","[WebServer] www.evolution-team.eu",MSG161,100,COMMANDFILE_PATH);
	GCServerMsgStringSend(MSG159,aIndex,1);
	GCServerMsgStringSend(MSG160,aIndex,1);
	GCServerMsgStringSend(MSG161,aIndex,1);

}

//=====================================================================================
//Time Command
//=====================================================================================
void ChatTime(DWORD PlayerID,char * msg)
{
	char timeStr[9];
	char dateStr[9];
	char LineTime[200];
	char LineDate[200];

	_strtime(timeStr);
	_strdate(dateStr);

	sprintf_s(LineTime, "Current Server Time : [%s]", timeStr);
	sprintf_s(LineDate, "Current Server Date : [%s]", dateStr);

	GCServerMsgStringSend(LineTime, PlayerID, 1);
	GCServerMsgStringSend(LineDate, PlayerID, 1);
}
//================================================================
// Comando para crear Monsters
//================================================================

void ChatCreateMob(DWORD gObjID, char*msg)
{
	OBJECTSTRUCT*gObj = (OBJECTSTRUCT*)OBJECT_POINTER(gObjID);
int onlyforgm = GetPrivateProfileInt("CreateMob", "Enable_Create_Mobs",1,COMMANDFILE_PATH);


if(strlen(msg) < 7)
return;

int spaces = 0;
for (int i = 0; i<(int)strlen(msg);i++)
{
if(msg[i] == ' ')
spaces++;
}

if(spaces <3)
return;

if(onlyforgm && VerificaGM(gObjID) == false)
{
GCServerMsgStringSend(MSG57, gObjID,1);
return;
}

//aca poner el gm system
int IsGMSystem = GetPrivateProfileIntA("GameServerInfo","EnableGMSystem",0,CUSTOMFILE_PATH);
	if(IsGMSystem == 1)
	{
		int CanDrop = 0;
		for(int x=1;x < GMSystemCount;x++)
		{
			if(!strcmp(GMSystemInfo[x].Name,gObj->Name))
			{
				CanDrop = GMSystemInfo[x].Cre;
			}
		}

		if(CanDrop == 0)
		{
			GCServerMsgStringSend(MSG60,gObjID,1);
			return;
		}
	}

int MapID, MobID, CoordX, CoordY;
sscanf_s(msg,"%d %d %d %d",&MapID, &MobID, &CoordX, &CoordY);
int mIndex = gObjAddMonster(MapID);
if(mIndex >=0)
{
gObjSetMonster(mIndex, MobID);
gObj->Class = MobID;
gObj->X = CoordX;
gObj->Y = CoordY;
gObj->MapNumber = MapID;
GCServerMsgStringSend(MSG58,gObjID,1);
char Post1[200];
char Account[11];
gObj_GetLogin(gObjID,Account);
gObj_GetNick(gObjID,Character);
sprintf(Post1, "%s: [Evolution][Monster Created]: %s", Character, msg);
LogGM(Post1);
}
else
GCServerMsgStringSend(MSG59,gObjID,1);
}

//comando para dar cashshop
void ComandoDarCash(DWORD aIndex, char * msg)
{
	OBJECTSTRUCT *gObj = (OBJECTSTRUCT*)OBJECT_POINTER(aIndex);
	if(strlen(msg) < 1)
{
GCServerMsgStringSend("To use the command is /cash <name> <points>",aIndex,1);
return;
}
if(VerificaGM(aIndex) == false)
{
GCServerMsgStringSend("Only GameMasters can use it!",aIndex,1);
return;
}

int IsGMSystem = GetPrivateProfileIntA("GameServerInfo","EnableGMSystem",0,CUSTOMFILE_PATH);
	if(IsGMSystem == 1)
	{
		int CanCash = 0;
		for(int x=1;x < GMSystemCount;x++)
		{
			if(!strcmp(GMSystemInfo[x].Name,gObj->Name))
			{
				CanCash = GMSystemInfo[x].Cash;
			}
		}

		if(CanCash == 0)
		{
			GCServerMsgStringSend(MSG128,aIndex,1);
			return;
		}
	}

int Spaces = 0;

for(int i = 0; i < strlen(msg); i++)
{
if(msg[i] == ' ')
{
	Spaces++;
}
	}

	if(Spaces != 2)
	{
		GCServerMsgStringSend(MSG104,aIndex,1);
		return;
	}
	char Target[11];
	int AmountCash;
	sscanf(msg,"%s %d",&Target,&AmountCash);
	
	if(strlen(Target) > 10)
	{
	GCServerMsgStringSend(MSG105,aIndex,1);
	return;
	}

	if(!AmountCash || AmountCash > 1000 || AmountCash < 0)
	{
	GCServerMsgStringSend(MSG106,aIndex,1);
	GCServerMsgStringSend("cashshop: max possible cashshop is 1,000.",aIndex,1);
	return;
	}

	
	DWORD PID=gObjByNick1(Target);
	if((PID<DWORD(MIN_PLAYERID)) || (PID>DWORD(MAX_PLAYERID)))
	{
	   GCServerMsgStringSend("Error, character not found or is offline.",aIndex,1);
				return;
	}

	//LPSTR result=" ";
	//result = Target;
	//result=gObj->AccountID;
	char Cuenta[11];
	wsprintf(Cuenta, "%s", GetUser(PID));
	MuDB.DarCashShop(Cuenta,AmountCash);

	MsgOutput(aIndex,"You modified %s's Cashshop Point successfully.",Cuenta);
			
			if(gObjIsConnected(PID))
			{
				MsgOutput(PID,"Your Cashshop Point has been modified by %s.",gObj->Name);
			}

}


//====================================================================
//COMANDO SKIN
//====================================================================

void ChatSkin(DWORD aIndex,char*msg)
{
configs.cmdskin.active = GetPrivateProfileInt("Skin","Enable_Skin",1,COMMANDFILE_PATH);
configs.cmdskin.onlyforgm = GetPrivateProfileInt("Skin","Skin_OnlyFor_GM",1,COMMANDFILE_PATH);
int Level = GetPrivateProfileInt("Skin","Skin_Level",100,COMMANDFILE_PATH);
if(configs.cmdskin.active == 0)
{
GCServerMsgStringSend(MSG61,aIndex,1);
return;
}
if(configs.cmdskin.onlyforgm == 1 && VerificaGM(aIndex) == false)
{
GCServerMsgStringSend(MSG62,aIndex,1);
return;
}
OBJECTSTRUCT *pObj = (OBJECTSTRUCT*)OBJECT_POINTER(aIndex);

//aca poner el gm system
int IsGMSystem = GetPrivateProfileIntA("GameServerInfo","EnableGMSystem",0,CUSTOMFILE_PATH);
	if(configs.cmdskin.onlyforgm == 1 && IsGMSystem == 1)
	{
		int CanDrop = 0;
		for(int x=1;x < GMSystemCount;x++)
		{
			if(!strcmp(GMSystemInfo[x].Name,pObj->Name))
			{
				CanDrop = GMSystemInfo[x].Skin;
			}
		}

		if(CanDrop == 0)
		{
			GCServerMsgStringSend(MSG64,aIndex,1);
			return;
		}
	}

if(pObj->Level < Level)
{
	char lvlmsg[100];
		sprintf(lvlmsg,MSG63, Level);
		GCServerMsgStringSend(lvlmsg,aIndex,1);
	return;
}



int skin = atoi(msg);
int PlayerId = (int)aIndex;
OBJECTSTRUCT *gObj = (OBJECTSTRUCT*)OBJECT_POINTER(aIndex);
gObj->m_Change = skin;
gObjViewportListProtocolCreate(gObj);
}

//===========================================================
//Comando /iglesia
//===========================================================
void ChatIglesia(DWORD PlayerID)
{ 
OBJECTSTRUCT *gObj = (OBJECTSTRUCT*)OBJECT_POINTER(PlayerID);
int IsBar = GetPrivateProfileInt("Church","Enable_Church_Devias",1,COMMANDFILE_PATH);
int IsBarLevl = GetPrivateProfileInt("Church","Requested_Level",100,COMMANDFILE_PATH);

if (IsBar == 0)
{
GCServerMsgStringSend(MSG65,PlayerID,1);
return;
}
if (IsBar == 1)
{
	if(gObj->Level < IsBarLevl)
{
	char lvlmsg[100];
		sprintf(lvlmsg,MSG66, IsBarLevl);
		GCServerMsgStringSend(lvlmsg,PlayerID,1);
	return;
}
else 
{ 
gObjTeleport(PlayerID,2,210,25);
char Sucesso[100]; 
sprintf_s(Sucesso, MSG67,gObj->Name);
GCServerMsgStringSend(Sucesso,PlayerID,1);
return;
}
} 
}

//===========================================================
//Comando /maquina
//===========================================================
void ChatMaquina(DWORD PlayerID)
{ 
OBJECTSTRUCT *gObj = (OBJECTSTRUCT*)OBJECT_POINTER(PlayerID);
int IsBar = GetPrivateProfileInt("Machine","Enable_Machine_Noria",1,COMMANDFILE_PATH);
int IsBarLevl = GetPrivateProfileInt("Machine","Requested_Level",100,COMMANDFILE_PATH);

if (IsBar == 0)
{
GCServerMsgStringSend(MSG68,PlayerID,1);
return;
}
if (IsBar == 1)
{
	if(gObj->Level < IsBarLevl)
{
	char lvlmsg[100];
		sprintf(lvlmsg,MSG69, IsBarLevl);
		GCServerMsgStringSend(lvlmsg,PlayerID,1);
	return;
}
else 
{ 
gObjTeleport(PlayerID,3,176,101); 
char Sucesso[100]; 
sprintf_s(Sucesso, MSG70,gObj->Name);
GCServerMsgStringSend(Sucesso,PlayerID,1);
return;
}
} 
}
//===========================================================
//Comando /bar
//===========================================================
void ChatLorencia(DWORD PlayerID)
{ 
OBJECTSTRUCT *gObj = (OBJECTSTRUCT*)OBJECT_POINTER(PlayerID);
int IsBar = GetPrivateProfileInt("Bar","Enable_Bar_Lorencia",1,COMMANDFILE_PATH);
int IsBarLevl = GetPrivateProfileInt("Bar","Requested_Level",100,COMMANDFILE_PATH);

if (IsBar == 0)
{
GCServerMsgStringSend(MSG71,PlayerID,1);
return;
}
if (IsBar == 1)
{
	if(gObj->Level < IsBarLevl)
{
	char lvlmsg[100];
		sprintf(lvlmsg,MSG72, IsBarLevl);
		GCServerMsgStringSend(lvlmsg,PlayerID,1);
	return;
}
else 
{ 
gObjTeleport(PlayerID,0,125,125); 
char Sucesso[100]; 
sprintf_s(Sucesso, MSG73,gObj->Name);
GCServerMsgStringSend(Sucesso,PlayerID,1);
return;
}
} 
}

//===========================================================
//Comando /tarkan2
//===========================================================
void ChatTarkan2(DWORD PlayerID)
{ 
OBJECTSTRUCT *gObj = (OBJECTSTRUCT*)OBJECT_POINTER(PlayerID);
gObjTeleport(PlayerID,8,70,170); 
return;
}


//=================================================
//ONLINE
//=================================================
void OnlineCmd(DWORD PlayerID)
{
OBJECTSTRUCT *gObj = (OBJECTSTRUCT*)OBJECT_POINTER(PlayerID);
int Act = GetPrivateProfileInt("Online", "Enable_Online",1,COMMANDFILE_PATH);
if (Act == 0)
{
GCServerMsgStringSend(MSG74,PlayerID,1);
return;
}
int onlyforgm = GetPrivateProfileInt("Online", "OnlyFor_GM",1,COMMANDFILE_PATH);
if(onlyforgm && VerificaGM(PlayerID) == false)
{
GCServerMsgStringSend(MSG75, PlayerID,1);
return;
}

//aca poner el gm system
int IsGMSystem = GetPrivateProfileIntA("GameServerInfo","EnableGMSystem",0,CUSTOMFILE_PATH);
	if(onlyforgm && IsGMSystem == 1)
	{
		int CanDrop = 0;
		for(int x=1;x < GMSystemCount;x++)
		{
			if(!strcmp(GMSystemInfo[x].Name,gObj->Name))
			{
				CanDrop = GMSystemInfo[x].On;
			}
		}

		if(CanDrop == 0)
		{
			GCServerMsgStringSend(MSG77,PlayerID,1);
			return;
		}
	}

		char wcTmp[255]={0};
		char wcTmps[255]={0};
		int Players = 0;
		int PlayersGM = 0;
		for (int i=MIN_PLAYERID; i<MAX_PLAYERID; i++)
		{
			if (gObjIsConnected(i))
			{
					Players++;
			}
			if (gObjIsConnected(i) && VerificaGM(i))
			{
				PlayersGM++;
			}
		}
		wsprintf(wcTmp, MSG76, Players);
		wsprintf(wcTmps,"[Online]: Total GameMasters Online!: %d",PlayersGM);
		GCServerMsgStringSend(wcTmp,PlayerID, 0x01);
		GCServerMsgStringSend(wcTmps,PlayerID, 0x01);
}
//=================================================
//Comando GG Prueba
//=================================================
void GCommand(DWORD PlayerID,char*msg)
{
	OBJECTSTRUCT *gObj = (OBJECTSTRUCT*)OBJECT_POINTER(PlayerID);
	if(strlen(msg) <= 0)return;

	if(!VerificaGM(PlayerID))return;

	char Character[11];
	gObj_GetNick(PlayerID,Character);
	int IsGMSystem1 = GetPrivateProfileIntA("GG","Enable_GG",1,COMMANDFILE_PATH);
	if(IsGMSystem1 == 0)
	{
		GCServerMsgStringSend(MSG78,PlayerID,1);
		return;
	}

	//aca poner el gm system
int IsGMSystem = GetPrivateProfileIntA("GameServerInfo","EnableGMSystem",0,CUSTOMFILE_PATH);
	if(IsGMSystem == 1)
	{
		int CanDrop = 0;
		for(int x=1;x < GMSystemCount;x++)
		{
			if(!strcmp(GMSystemInfo[x].Name,gObj->Name))
			{
				CanDrop = GMSystemInfo[x].Gg;
			}
		}

		if(CanDrop == 0)
		{
			GCServerMsgStringSend(MSG79,PlayerID,1);
			return;
		}
	}
				
	char Message[255];
	sprintf(Message,"[Evolution Team] [ %s ]: %s",Character,msg);

	StringSendAll(Message,0);
	char Post[200];
	char Account[11];
	gObj_GetLogin(PlayerID,Account);
	gObj_GetNick(PlayerID,Character);
	sprintf(Post, "%s : [Evolution Team]: %s",Character, msg);
	LogGM(Post);

}

//==========================================
//COMANDO PARA BORRAR EL INVENTARIO PARA ITEMS DE QUETS
//==========================================
void ComandoBorra(DWORD PlayerID, char *msg)
{
int Act = GetPrivateProfileInt("ClearInventory", "Enable_ClearInventory",1,COMMANDFILE_PATH);
if (Act == 0)
{
GCServerMsgStringSend(MSG80,PlayerID,1);
return;
}
	if(strlen(msg) <= 0)
{
GCServerMsgStringSend(MSG81,PlayerID,1);
GCServerMsgStringSend(MSG82,PlayerID,1);
GCServerMsgStringSend(MSG83,PlayerID,1);
GCServerMsgStringSend(MSG84,PlayerID,1);
GCServerMsgStringSend(MSG85,PlayerID,1);
GCServerMsgStringSend(MSG86,PlayerID,1);
return;
}
int clearitem = atoi(msg);
switch(clearitem)
{
case 0:
	{
		return;
	}
case 1:
	{
	DelPlayerAllItemNoInv(PlayerID);
	GCServerMsgStringSend(MSG87,PlayerID,1);
	return;
	}
	default:
GCServerMsgStringSend(MSG88, PlayerID, 1);
break;
}
}

//===================================
// COMANDO PKCLEAR
//===================================
void PKClearCommand(DWORD aIndex,char*msg)
{

	int SwitchPkclear=GetPrivateProfileIntA("PkClear","Enable_Pkclear",0,COMMANDFILE_PATH);
	DWORD PkClearCost=GetPrivateProfileIntA("PkClear","PKClear_Price",100000000,COMMANDFILE_PATH);
	
    if(SwitchPkclear == 0)return;

	if(strlen(msg) > 0)return;

	if ((int)gObj_GetPKStatus(aIndex) < 4) //estaba en 4 pero vamos a aumentar un poco aver si me saca el pk en 6 no funca o cuando quiere
	{
	    GCServerMsgStringSend(MSG89,aIndex,1);
        return;
    }
	
	if ((DWORD)gObj_GetInt(aIndex,gObjZen) < PkClearCost)
	{
        char OutputZenFalla[255];
		sprintf(OutputZenFalla,MSG90,PkClearCost);
		GCServerMsgStringSend(OutputZenFalla,aIndex,1);
        return;
    }
    
    else
    {
		gObj_Write(aIndex,gObjZen,gObj_GetInt(aIndex,gObjZen)- PkClearCost);
		gObj_Write(aIndex,gObjPk,3);
        GCMoneySend (aIndex,gObj_GetInt(aIndex,gObjZen));
		GCPkLevelSend (aIndex,gObj_GetPKStatus(aIndex));
		GCServerMsgStringSend(MSG91,aIndex,1);

    }
}
//=================================================
//Comando Zen xxx
//=================================================

void ChatZen(DWORD aIndex, LPCSTR lpBuffer)
{

int ZenActivado = GetPrivateProfileInt("Zen","Enable_Zen",1,COMMANDFILE_PATH);
int ZenSoloGM = GetPrivateProfileInt("Zen","OnlyFor_GM",1,COMMANDFILE_PATH);
if(ZenActivado == 0)
return;

if(ZenSoloGM == 1 && VerificaGM(aIndex) == false)
return;

int MiZen = GetPrivateProfileInt("Zen","Zen_Qyantity",10000,COMMANDFILE_PATH);
OBJECTSTRUCT *gObj = (OBJECTSTRUCT*)OBJECT_POINTER(aIndex);

int Zen = atoi(lpBuffer);
	//aca poner el gm system
int IsGMSystem = GetPrivateProfileIntA("GameServerInfo","EnableGMSystem",0,CUSTOMFILE_PATH);
	if(ZenSoloGM == 1 && IsGMSystem == 1)
	{
		int CanDrop = 0;
		for(int x=1;x < GMSystemCount;x++)
		{
			if(!strcmp(GMSystemInfo[x].Name,gObj->Name))
			{
				CanDrop = GMSystemInfo[x].Zen;
			}
		}

		if(CanDrop == 0)
		{
			GCServerMsgStringSend(MSG92,aIndex,1);
			return;
		}
	}
gObj->Money += MiZen;
GCMoneySend(aIndex,gObj->Money);
}
//=============================================
// comando teste acesso a OBJECTSTRUCT - /level
//=============================================
void ChatTeste(DWORD PlayerID)
{
OBJECTSTRUCT *gObj = (OBJECTSTRUCT*)OBJECT_POINTER(PlayerID);

int IsMiInfo = GetPrivateProfileInt("Info","Enable_MyInfo",1,COMMANDFILE_PATH);
char cTeste[100];
char cTeste2[100];
			if (IsMiInfo == 0)
{
GCServerMsgStringSend(MSG93,PlayerID,1);
return;
}
				if (IsMiInfo == 1)
{
sprintf_s(cTeste,MSG94, gObj->AccountID,gObj->Name);
GCServerMsgStringSend(cTeste,PlayerID,1);
return;
}
}

//======================================================================
//=============PKSET PRUEBA
//======================================================================
void SetPKCommand(int aIndex,char* Message)
{
	OBJECTSTRUCT *gObj = (OBJECTSTRUCT*)OBJECT_POINTER(aIndex);
	int IsPkSet = GetPrivateProfileInt("PkSet","Enable_PkSet",1,COMMANDFILE_PATH);
	if(IsPkSet == 0)
	{
		return;
	}

	if(VerificaGM(aIndex) == false)
	{
		return;
	}
		//aca poner el gm system
int IsGMSystem = GetPrivateProfileIntA("GameServerInfo","EnableGMSystem",0,CUSTOMFILE_PATH);
	if(IsGMSystem == 1)
	{
		int CanDrop = 0;
		for(int x=1;x < GMSystemCount;x++)
		{
			if(!strcmp(GMSystemInfo[x].Name,gObj->Name))
			{
				CanDrop = GMSystemInfo[x].SetPk;
			}
		}

		if(CanDrop == 0)
		{
			GCServerMsgStringSend(MSG102,aIndex,1);
			return;
		}
	}

			if(!_strcmpi("/setpk",Message))
			{
				GCServerMsgStringSend(MSG95,aIndex,1);
				return;
			}

			if(strlen(Message) < 1)
			{
				GCServerMsgStringSend(MSG95,aIndex,1);
				return;
			}

			int Spaces = 0;

			for(int i = 0; i < strlen(Message); i++)
			{
				if(Message[i] == ' ')
				{
					Spaces++;
				}
			}

			if(Spaces != 2)
			{
				GCServerMsgStringSend(MSG96,aIndex,1);
				return;
			}

			char Target[11];
			int PKLevel;
			sscanf(Message,"%s %d",&Target,&PKLevel);
	
			if(strlen(Target) > 10)
			{
				GCServerMsgStringSend(MSG97,aIndex,1);
				return;
			}

			if(!PKLevel || PKLevel > 7 || PKLevel < 0)
			{
				GCServerMsgStringSend(MSG96,aIndex,1);
				GCServerMsgStringSend(MSG98,aIndex,1);
				return;
			}

			DWORD PID=gObjByNick1(Target);
			if((PID<DWORD(MIN_PLAYERID)) || (PID>DWORD(MAX_PLAYERID)))
			{
				GCServerMsgStringSend(MSG99,aIndex,1);
				return;
			}

			gObj_Write(PID,gObjPK,PKLevel);
			GCPkLevelSend(PID,PKLevel);

			MsgOutput(aIndex,MSG100,Target);
			
			if(gObjIsConnected(PID))
			{
				MsgOutput(PID,MSG101,gObj->Name);
			}

	char Post[200];
	char Account[11];
	gObj_GetLogin(aIndex,Account);
	gObj_GetNick(aIndex,Character);
	sprintf(Post, "%s: [SETPK]: %s",Character, Message);
	LogGM(Post);
}

//=====================================================================================
//GMOVE
//======================================================================================
void ChatGmove(int aIndex,char* Message)
{
	OBJECTSTRUCT *gObj = (OBJECTSTRUCT*)OBJECT_POINTER(aIndex);
	int IsMove = GetPrivateProfileInt("Move","Enable_GMove",1,COMMANDFILE_PATH);
	if(IsMove == 0)
	{
		return;
	}

	if(VerificaGM(aIndex) == false)
	{
		return;
	}

							//aca poner el gm system
int IsGMSystem = GetPrivateProfileIntA("GameServerInfo","EnableGMSystem",0,CUSTOMFILE_PATH);
	if(IsGMSystem == 1)
	{
		int CanDrop = 0;
		for(int x=1;x < GMSystemCount;x++)
		{
			if(!strcmp(GMSystemInfo[x].Name,gObj->Name))
			{
				CanDrop = GMSystemInfo[x].Gmove;
			}
		}

		if(CanDrop == 0)
		{
			GCServerMsgStringSend(MSG157,aIndex,1);
			return;
		}
	}
			if(!_strcmpi("/gmove",Message))
			{
				GCServerMsgStringSend("Usage: /gmove <name> <map> <posx> <posy>",aIndex,1);
				return;
			}

			if(strlen(Message) < 1)
			{
				GCServerMsgStringSend("Usage: /gmove <name> <map> <posx> <posy>",aIndex,1);
				return;
			}

			int Spaces = 0;

			for(int i = 0; i < strlen(Message); i++)
			{
				if(Message[i] == ' ')
				{
					Spaces++;
				}
			}

			if(Spaces < 2)
			{
				GCServerMsgStringSend("Error, please re-check the string you gave.",aIndex,1);
				return;
			}
			const char * pText;
			char Name[255]={0};
			int MapNumber=0;
			int PosX=0;
			int PosY=0;
			//int Name,MapNumber,PosX,PosY;
			sscanf(Message,"%s %d %d %d %d",&Name,&MapNumber,&PosX,&PosY);

			int ID=gObjByNick(Name);
			DWORD PID=gObjByNick1(Name);
			if((ID>=MIN_PLAYERID) && (ID<=MAX_PLAYERID))
			{
					gObjTeleport2(PID,MapNumber,PosX,PosY);
			}

	//157
	char Post[200];
	char Account[11];
	gObj_GetLogin(aIndex,Account);
	gObj_GetNick(aIndex,Character);
	sprintf(Post, "%s: [Gmove]: %s",Character, Message);
	LogGM(Post);
}

//=============================================================================================
//============================SETZEN
//=============================================================================================
void SetZenCommand(int aIndex,char* Message)
{
	OBJECTSTRUCT *gObj = (OBJECTSTRUCT*)OBJECT_POINTER(aIndex);
	int IsZenSet = GetPrivateProfileInt("ZenSet","Enable_SetZen",1,COMMANDFILE_PATH);
	if(IsZenSet == 0)
	{
		return;
	}

	if(VerificaGM(aIndex) == false)
	{
		return;
	}

			//aca poner el gm system
int IsGMSystem = GetPrivateProfileIntA("GameServerInfo","EnableGMSystem",0,CUSTOMFILE_PATH);
	if(IsGMSystem == 1)
	{
		int CanDrop = 0;
		for(int x=1;x < GMSystemCount;x++)
		{
			if(!strcmp(GMSystemInfo[x].Name,gObj->Name))
			{
				CanDrop = GMSystemInfo[x].SetZen;
			}
		}

		if(CanDrop == 0)
		{
			GCServerMsgStringSend(MSG111,aIndex,1);
			return;
		}
	}
			if(!_strcmpi("/setzen",Message))
			{
				GCServerMsgStringSend(MSG103,aIndex,1);
				return;
			}

			if(strlen(Message) < 1)
			{
				GCServerMsgStringSend(MSG103,aIndex,1);
				return;
			}

			int Spaces = 0;

			for(int i = 0; i < strlen(Message); i++)
			{
				if(Message[i] == ' ')
				{
					Spaces++;
				}
			}

			if(Spaces != 2)
			{
				GCServerMsgStringSend(MSG104,aIndex,1);
				return;
			}

			char Target[11];
			int Amount;
			sscanf(Message,"%s %d",&Target,&Amount);
	
			if(strlen(Target) > 10)
			{
				GCServerMsgStringSend(MSG105,aIndex,1);
				return;
			}

			if(!Amount || Amount > 2000000000 || Amount < 0)
			{
				GCServerMsgStringSend(MSG106,aIndex,1);
				GCServerMsgStringSend(MSG107,aIndex,1);
				return;
			}

			DWORD PID=gObjByNick1(Target);
			if((PID<DWORD(MIN_PLAYERID)) || (PID>DWORD(MAX_PLAYERID)))
			{
				GCServerMsgStringSend(MSG108,aIndex,1);
				return;
			}

			gObj_Write(PID,gObjZen,Amount);
			GCMoneySend(PID,Amount);

			MsgOutput(aIndex,MSG109,Target);
			

			if(gObjIsConnected(PID))
			{
				MsgOutput(PID,MSG110,gObj->Name);
			}

		
	//MSG111
	char Post[200];
	char Account[11];
	gObj_GetLogin(aIndex,Account);
	gObj_GetNick(aIndex,Character);
	sprintf(Post, "%s: [SETZEN]: %s",Character, Message);
	LogGM(Post);
}

//================================================================================================
//====================================SET LEVEL
//================================================================================================
void SetLevelCommand(int aIndex,char* Message)
{
	OBJECTSTRUCT *gObj = (OBJECTSTRUCT*)OBJECT_POINTER(aIndex);
	int IsLevelSet = GetPrivateProfileInt("LvlSet","Enable_SetLevel",1,COMMANDFILE_PATH);
	if(IsLevelSet == 0)
	{
		return;
	}

	if(VerificaGM(aIndex) == false)
	{
		return;
	}
			//aca poner el gm system
int IsGMSystem = GetPrivateProfileIntA("GameServerInfo","EnableGMSystem",0,CUSTOMFILE_PATH);
	if(IsGMSystem == 1)
	{
		int CanDrop = 0;
		for(int x=1;x < GMSystemCount;x++)
		{
			if(!strcmp(GMSystemInfo[x].Name,gObj->Name))
			{
				CanDrop = GMSystemInfo[x].SetLevel;
			}
		}

		if(CanDrop == 0)
		{
			GCServerMsgStringSend("You don't have priviledges to this command.",aIndex,1);
			return;
		}
	}
			if(!_strcmpi("/setlevel",Message))
			{
				GCServerMsgStringSend(MSG112,aIndex,1);
				return;
			}

			if(strlen(Message) < 1)
			{
				GCServerMsgStringSend(MSG112,aIndex,1);
				return;
			}

			int Spaces = 0;

			for(int i = 0; i < strlen(Message); i++)
			{
				if(Message[i] == ' ')
				{
					Spaces++;
				}
			}

			if(Spaces != 2)
			{
				GCServerMsgStringSend(MSG113,aIndex,1);
				return;
			}

			char Target[11];
			int Level;
			sscanf(Message,"%s %d",&Target,&Level);
	
			if(strlen(Target) > 10)
			{
				GCServerMsgStringSend(MSG114,aIndex,1);
				return;
			}

			if(!Level || Level > 400 || Level < 1)
			{
				GCServerMsgStringSend(MSG115,aIndex,1);
				GCServerMsgStringSend(MSG116,aIndex,1);
				return;
			}

			
			DWORD PID=gObjByNick1(Target);
			if((PID<DWORD(MIN_PLAYERID)) || (PID>DWORD(MAX_PLAYERID)))
			{
				GCServerMsgStringSend(MSG117,aIndex,1);
				return;
			}

			gObj_Write(PID,gObjLvl,Level);
			GCLevelUpMsgSend(PID,1);
			gObjCalCharacter(PID);

			MsgOutput(aIndex,MSG118,Target);
			
			
			if(gObjIsConnected(PID))
			{
				MsgOutput(PID,MSG119,gObj->Name);
			}

			
			

	char Post[200];
	char Account[11];
	gObj_GetLogin(aIndex,Account);
	gObj_GetNick(aIndex,Character);
	sprintf(Post, "%s: [SETLEVEL]: %s",Character, Message);
	LogGM(Post);
}

//==================================================================================
//============================MUTE POST
//==================================================================================
void MutePostCommand(int aIndex,char* Message)
{
	OBJECTSTRUCT *gObj = (OBJECTSTRUCT*)OBJECT_POINTER(aIndex);
	int IsMutePost = GetPrivateProfileInt("Post","Enable_MutePost",1,COMMANDFILE_PATH);
	if(IsMutePost == 0)
	
	{
		return;
	}

	if(VerificaGM(aIndex) == false)
	{
		return;
	}

				//aca poner el gm system
int IsGMSystem = GetPrivateProfileIntA("GameServerInfo","EnableGMSystem",0,CUSTOMFILE_PATH);
	if(IsGMSystem == 1)
	{
		int CanDrop = 0;
		for(int x=1;x < GMSystemCount;x++)
		{
			if(!strcmp(GMSystemInfo[x].Name,gObj->Name))
			{
				CanDrop = GMSystemInfo[x].MutePost;
			}
		}

		if(CanDrop == 0)
		{
			GCServerMsgStringSend(MSG128,aIndex,1);
			return;
		}
	}
			if(!_strcmpi("/mutepost",Message))
			{
				GCServerMsgStringSend(MSG121,aIndex,1);
				return;
			}

			if(strlen(Message) < 1)
			{
				GCServerMsgStringSend(MSG121,aIndex,1);
				return;
			}

			int Spaces = 0;

			for(int i = 0; i < strlen(Message); i++)
			{
				if(Message[i] == ' ')
				{
					Spaces++;
				}
			}

			if(Spaces != 1)
			{
				GCServerMsgStringSend(MSG122,aIndex,1);
				return;
			}

			char Target[11];
			sscanf(Message,"%s",&Target);
	
			if(strlen(Target) > 10)
			{
				GCServerMsgStringSend(MSG123,aIndex,1);
				return;
			}

			
			DWORD PID=gObjByNick1(Target);
			if((PID<DWORD(MIN_PLAYERID)) || (PID>DWORD(MAX_PLAYERID)))
			{
				GCServerMsgStringSend(MSG124,aIndex,1);
				return;
			}

			int Muted = MuDB.GetMutePost(Target);

			if(Muted == 1)
			{
				GCServerMsgStringSend(MSG125,aIndex,1);
				return;
			}
			else
			{
				MuDB.UpdateMutePostOn(Target);

				MsgOutput(aIndex,MSG126,Target);

				
				if(gObjIsConnected(PID))
				{
					MsgOutput(PID,MSG127,gObj->Name);
				}
			}

	//MSG128
	char Post[200];
	char Account[11];
	gObj_GetLogin(aIndex,Account);
	gObj_GetNick(aIndex,Character);
	sprintf(Post, "%s: [MUTE POST]: %s",Character, Message);
	LogGM(Post);
}

//====================================================
//=============UNMUTEPOST
//====================================================
void UnMutePostCommand(int aIndex,char* Message)
{
	OBJECTSTRUCT *gObj = (OBJECTSTRUCT*)OBJECT_POINTER(aIndex);
	int IsUnMutePost = GetPrivateProfileInt("Post","Enable_UnMutePost",1,COMMANDFILE_PATH);
	if(IsUnMutePost == 0)
	
	{
		return;
	}

	if(VerificaGM(aIndex) == false)
	{
		return;
	}

					//aca poner el gm system
int IsGMSystem = GetPrivateProfileIntA("GameServerInfo","EnableGMSystem",0,CUSTOMFILE_PATH);
	if(IsGMSystem == 1)
	{
		int CanDrop = 0;
		for(int x=1;x < GMSystemCount;x++)
		{
			if(!strcmp(GMSystemInfo[x].Name,gObj->Name))
			{
				CanDrop = GMSystemInfo[x].Unmute;
			}
		}

		if(CanDrop == 0)
		{
			GCServerMsgStringSend(MSG136,aIndex,1);
			return;
		}
	}
			if(!_strcmpi("/unmutepost",Message))
			{
				GCServerMsgStringSend(MSG129,aIndex,1);
				return;
			}

			if(strlen(Message) < 1)
			{
				GCServerMsgStringSend(MSG129,aIndex,1);
				return;
			}

			int Spaces = 0;

			for(int i = 0; i < strlen(Message); i++)
			{
				if(Message[i] == ' ')
				{
					Spaces++;
				}
			}

			if(Spaces != 1)
			{
				GCServerMsgStringSend(MSG130,aIndex,1);
				return;
			}

			char Target[11];
			sscanf(Message,"%s",&Target);
	
			if(strlen(Target) > 10)
			{
				GCServerMsgStringSend(MSG131,aIndex,1);
				return;
			}

			
			DWORD PID=gObjByNick1(Target);
			if((PID<DWORD(MIN_PLAYERID)) || (PID>DWORD(MAX_PLAYERID)))
			{
				GCServerMsgStringSend(MSG132,aIndex,1);
				return;
			}

			int Muted = MuDB.GetMutePost(Target);

			if(Muted == 0)
			{
				GCServerMsgStringSend(MSG133,aIndex,1);
				return;
			}
			else
			{
				MuDB.UpdateMutePostOff(Target);

				MsgOutput(aIndex,MSG134,Target);
				MsgOutput(PID,MSG135,gObj->Name);
			}

			

	//MSG136
	char Post[200];
	char Account[11];
	gObj_GetLogin(aIndex,Account);
	gObj_GetNick(aIndex,Character);
	sprintf(Post, "%s: [UNMETE POST]: %s",Character, Message);
	LogGM(Post);
}

//==========================================================================
//COMANDO BAN ¬¬
//==========================================================================
void BanCharCommand(int aIndex,char* Message)
{
	OBJECTSTRUCT *gObj = (OBJECTSTRUCT*)OBJECT_POINTER(aIndex);
	int IsBan = GetPrivateProfileInt("Ban","Enable_Ban",1,COMMANDFILE_PATH);
	if(IsBan == 0)
	{
		return;
	}

	if(VerificaGM(aIndex) == false)
	{
		return;
	}

						//aca poner el gm system
int IsGMSystem = GetPrivateProfileIntA("GameServerInfo","EnableGMSystem",0,CUSTOMFILE_PATH);
	if(IsGMSystem == 1)
	{
		int CanDrop = 0;
		for(int x=1;x < GMSystemCount;x++)
		{
			if(!strcmp(GMSystemInfo[x].Name,gObj->Name))
			{
				CanDrop = GMSystemInfo[x].BanChar;
			}
		}

		if(CanDrop == 0)
		{
			GCServerMsgStringSend(MSG145,aIndex,1);
			return;
		}
	}
			if(!_strcmpi("/banchar",Message))
			{
				GCServerMsgStringSend(MSG137,aIndex,1);
				return;
			}

			if(strlen(Message) < 1)
			{
				GCServerMsgStringSend(MSG137,aIndex,1);
				return;
			}

			int Spaces = 0;

			for(int i = 0; i < strlen(Message); i++)
			{
				if(Message[i] == ' ')
				{
					Spaces++;
				}
			}

			if(Spaces != 1)
			{
				GCServerMsgStringSend(MSG138,aIndex,1);
				return;
			}

			char Target[11];
			sscanf(Message,"%s",&Target);
	
			if(strlen(Target) > 10)
			{
				GCServerMsgStringSend(MSG139,aIndex,1);
				return;
			}


			DWORD PID=gObjByNick1(Target);
			if((PID<DWORD(MIN_PLAYERID)) || (PID>DWORD(MAX_PLAYERID)))
			{


				GCServerMsgStringSend(MSG140,aIndex,1);
				return;
			}

			int CtlCode = MuDB.GetCtlCode(Target);

			if(CtlCode == 1)
			{
				GCServerMsgStringSend(MSG141,aIndex,1);
				return;
			}
			else
			{
				MuDB.UpdateBanOn(Target);

			//	MsgOutput(aIndex,MSG142,Target);
			//	MsgOutput(PID,MSG143,gObj->Name);
			//	MsgOutput(PID,MSG144);
				char Msg[150];
				wsprintf(Msg,MSG142,Target);
				GCServerMsgStringSend(Msg,aIndex,0);
				char Message[255];
				wsprintf(Message,"[Evolution Team] The Administrator: [ %s ]: banned character: %s",gObj->Name,Target);
				StringSendAll(Message,0);
				char Aviso[150];
				wsprintf(Aviso,MSG143,gObj->Name);
				GCServerMsgStringSend(Aviso,PID,0);
				GCServerMsgStringSend(MSG144,PID,0);
				CloseClient(PID);
				CloseClient(PID);
			}



	//MSG145
	char Post[200];
	char Account[11];
	gObj_GetLogin(aIndex,Account);
	gObj_GetNick(aIndex,Character);
	sprintf(Post, "%s: [BAN]: %s",Character, Message);
	LogGM(Post);
}

//==========================================================================
//UNBANCHAR
//=========================================================================
void UnbanCharCommand(int aIndex,char* Message)
{
	OBJECTSTRUCT *gObj = (OBJECTSTRUCT*)OBJECT_POINTER(aIndex);
	int IsUnBan = GetPrivateProfileInt("Ban","Enable_UnBan",1,COMMANDFILE_PATH);
	if(IsUnBan == 0)
	{
		return;
	}

	if(VerificaGM(aIndex) == false)
	{
		return;
	}

							//aca poner el gm system
int IsGMSystem = GetPrivateProfileIntA("GameServerInfo","EnableGMSystem",0,CUSTOMFILE_PATH);
	if(IsGMSystem == 1)
	{
		int CanDrop = 0;
		for(int x=1;x < GMSystemCount;x++)
		{
			if(!strcmp(GMSystemInfo[x].Name,gObj->Name))
			{
				CanDrop = GMSystemInfo[x].UnBanChar;
			}
		}

		if(CanDrop == 0)
		{
			GCServerMsgStringSend(MSG151,aIndex,1);
			return;
		}
	}
			if(!_strcmpi("/unbanchar",Message))
			{
				GCServerMsgStringSend(MSG146,aIndex,1);
				return;
			}

			if(strlen(Message) < 1)
			{
				GCServerMsgStringSend(MSG146,aIndex,1);
				return;
			}

			int Spaces = 0;

			for(int i = 0; i < strlen(Message); i++)
			{
				if(Message[i] == ' ')
				{
					Spaces++;
				}
			}

			if(Spaces != 1)
			{
				GCServerMsgStringSend(MSG147,aIndex,1);
				return;
			}

			char Target[11];
			sscanf(Message,"%s",&Target);
	
			if(strlen(Target) > 10)
			{
				GCServerMsgStringSend(MSG148,aIndex,1);
				return;
			}

			char Query[150];
			char tIndex[11];

			wsprintf(Query,"SELECT Name FROM Character WHERE Name = '%s'",Target);
			SQL.Exec(Query);
			SQL.Fetch();
			SQL.GetStr("Name",tIndex);
			SQL.Clear();


			int CtlCode = MuDB.GetCtlCode(Target);

			if(CtlCode == 0)
			{
				GCServerMsgStringSend(MSG149,aIndex,1);
				return;
			}
			else
			{
				MuDB.UpdateBanOff(Target);

				MsgOutput(aIndex,MSG150,Target);
			}


	//MSG151
	char Post[200];
	char Account[11];
	gObj_GetLogin(aIndex,Account);
	gObj_GetNick(aIndex,Character);
	sprintf(Post, "[Evolution Team] %s: [UnBanned]: %s",Character, Message);
	LogGM(Post);
}

//==========================================================================
//COMANDO BAN ¬¬ //BANACCOUNT
//==========================================================================
void BanAccountCommand(DWORD aIndex,char* Message)
{
	OBJECTSTRUCT *gObj = (OBJECTSTRUCT*)OBJECT_POINTER(aIndex);
	int IsBan = GetPrivateProfileInt("Ban","Enable_Ban",1,COMMANDFILE_PATH);
	if(IsBan == 0)
	{
		return;
	}

	if(VerificaGM(aIndex) == false)
	{
		return;
	}

						//aca poner el gm system
int IsGMSystem = GetPrivateProfileIntA("GameServerInfo","EnableGMSystem",0,CUSTOMFILE_PATH);
	if(IsGMSystem == 1)
	{
		int CanDrop = 0;
		for(int x=1;x < GMSystemCount;x++)
		{
			if(!strcmp(GMSystemInfo[x].Name,gObj->Name))
			{
				CanDrop = GMSystemInfo[x].BanAccount;
			}
		}

		if(CanDrop == 0)
		{
			GCServerMsgStringSend(MSG145,aIndex,1);
			return;
		}
	}
			if(!_strcmpi("/banaccount",Message))//BANACCOUNT
			{
				GCServerMsgStringSend("Usage: /banaccount <name>",aIndex,1);
				return;
			}

			if(strlen(Message) < 1)
			{
				GCServerMsgStringSend("Usage: /banaccount <name>",aIndex,1);
				return;
			}

			int Spaces = 0;

			for(int i = 0; i < strlen(Message); i++)
			{
				if(Message[i] == ' ')
				{
					Spaces++;
				}
			}

			if(Spaces != 1)
			{
				GCServerMsgStringSend(MSG138,aIndex,1);
				return;
			}

			char Target[11];
			sscanf(Message,"%s",&Target);
	
			if(strlen(Target) > 10)
			{
				GCServerMsgStringSend(MSG139,aIndex,1);
				return;
			}


			DWORD PID=gObjByNick1(Target);
			if((PID<DWORD(MIN_PLAYERID)) || (PID>DWORD(MAX_PLAYERID)))
			{


				GCServerMsgStringSend(MSG140,aIndex,1);
				return;
			}
			//aca poner igual que el cash que opptenga el id de la cuenta

			

			char Cuenta[11];
			wsprintf(Cuenta, "%s", GetUser(PID));

			int CtlCode = MuDB.GetBanAccount(Cuenta);

			if(CtlCode == 1)
			{
				GCServerMsgStringSend("This Account has been banned already.",aIndex,1);
				return;
			}
			else
			{
				//MuDB.UpdateBanOn(Target);
				MuDB.UpdateBanAccount(Cuenta);

				char Msg[150];
				wsprintf(Msg,"You banned '%s' Account successfully",Cuenta);
				GCServerMsgStringSend(Msg,aIndex,0);
				char Message[255];
				wsprintf(Message,"[Evolution Team] The Administrator: [ %s ]: banned the account: %s",gObj->Name,Cuenta);
				StringSendAll(Message,0);
				char Aviso[150];
				wsprintf(Aviso,"[Evolution Team] You've been banned by %s.",gObj->Name);
				GCServerMsgStringSend(Aviso,PID,0);
				GCServerMsgStringSend("Contact the administrators for more info.",PID,0);
				CloseClient(PID);
			}



	//MSG145
	char Post[200];
	char Account[11];
	gObj_GetLogin(aIndex,Account);
	gObj_GetNick(aIndex,Character);
	sprintf(Post, "[Evolution Team] %s: [Banned]: %s",Character, Message);
	LogGM(Post);
}
//======================================
//RESET 
//======================================
void ResetsCommand(int aIndex,char* Message)
{
	OBJECTSTRUCT *gObj = (OBJECTSTRUCT*)OBJECT_POINTER(aIndex);
	int IsReset = GetPrivateProfileInt("Reset","IsReset",1,COMMANDFILE_PATH);
	int IsLevel = GetPrivateProfileInt("Reset","LvlResetFree",400,COMMANDFILE_PATH);
	int IsLevel2 = GetPrivateProfileInt("Reset","LvlResetBronze",350,COMMANDFILE_PATH);
	int IsLevel3 = GetPrivateProfileInt("Reset","LvlResetPlatinum",325,COMMANDFILE_PATH);
	int IsLevel4 = GetPrivateProfileInt("Reset","LvlResetGold",300,COMMANDFILE_PATH);
	DWORD IsZenFree = GetPrivateProfileInt("Reset","ZenResetFree",10000000,COMMANDFILE_PATH);
	DWORD IsZenBronze = GetPrivateProfileInt("Reset","ZenResetBronze",7500000,COMMANDFILE_PATH);
	DWORD IsZenPlatinum = GetPrivateProfileInt("Reset","ZenResetPlatinum",6500000,COMMANDFILE_PATH);
	DWORD IsZenGold = GetPrivateProfileInt("Reset","ZenResetGold",5000000,COMMANDFILE_PATH);
	int IsResetStat = GetPrivateProfileInt("Reset","ResetStats",0,COMMANDFILE_PATH);
	int IsTipo = GetPrivateProfileInt("Reset","BonusStats",0,COMMANDFILE_PATH);
	DWORD IsAddPuntos = GetPrivateProfileInt("Reset","Points",200,COMMANDFILE_PATH);
	int IsResetMagia = GetPrivateProfileInt("Reset","ResetSkill",0,COMMANDFILE_PATH);
	int IsResetInven = GetPrivateProfileInt("Reset","ResetInventory",0,COMMANDFILE_PATH);
	if(IsReset == 0)
	{
		return;
	}
	int Vip[OBJECT_MAX - OBJECT_MIN];
	Vip[aIndex - OBJECT_MIN] = MuDB.CheckVip(gObj->AccountID);
	if(Vip[aIndex - OBJECT_MIN] == 0)
	{
		if(gObj->Level < IsLevel)
{
	char lvlmsg[100];
		sprintf(lvlmsg,MSG152, IsLevel);
		GCServerMsgStringSend(lvlmsg,aIndex,1);
	return;
}
else 
{ 
	if ((DWORD)gObj_GetInt(aIndex,gObjZen) < IsZenFree)
	{
        char OutputZenFalla[255];
		sprintf(OutputZenFalla,MSG153,IsZenFree);
		GCServerMsgStringSend(OutputZenFalla,aIndex,1);
        return;
    }
    
    else
    {
		GCServerMsgStringSend(MSG154,aIndex,1);
		gObj_Write(aIndex,gObjZen,gObj_GetInt(aIndex,gObjZen)- IsZenFree);
        GCMoneySend (aIndex,gObj_GetInt(aIndex,gObjZen));
		MuDB.UpdateResets(gObj->Name);
		gObj_Write(aIndex,gObjLvl,1);
		gObj_Write(aIndex,gObjExp,1);
		GCLevelUpMsgSend(aIndex,1);
		gObjCalCharacter(aIndex);
		if(IsResetStat == 1)
		{
			int Class = MuDB.GetClase(gObj->Name);

			if(Class == 0)
			{
			gObj_Write(aIndex,gObjStrength,18);
			gObj_Write(aIndex,gObjAgility,18);
			gObj_Write(aIndex,gObjVitality,15);
			gObj_Write(aIndex,gObjEnergy,30);
				return;
			}
			if(Class == 1)
			{
			gObj_Write(aIndex,gObjStrength,18);
			gObj_Write(aIndex,gObjAgility,18);
			gObj_Write(aIndex,gObjVitality,15);
			gObj_Write(aIndex,gObjEnergy,30);
				return;
			}
			if(Class == 16)
			{
			gObj_Write(aIndex,gObjStrength,28);
			gObj_Write(aIndex,gObjAgility,20);
			gObj_Write(aIndex,gObjVitality,25);
			gObj_Write(aIndex,gObjEnergy,10);
			}
			if(Class == 17)
			{
			gObj_Write(aIndex,gObjStrength,28);
			gObj_Write(aIndex,gObjAgility,20);
			gObj_Write(aIndex,gObjVitality,25);
			gObj_Write(aIndex,gObjEnergy,10);
			}
			if(Class == 32)
			{
			gObj_Write(aIndex,gObjStrength,22);
			gObj_Write(aIndex,gObjAgility,25);
			gObj_Write(aIndex,gObjVitality,20);
			gObj_Write(aIndex,gObjEnergy,15);
			}
			if(Class == 33)
			{
			gObj_Write(aIndex,gObjStrength,22);
			gObj_Write(aIndex,gObjAgility,25);
			gObj_Write(aIndex,gObjVitality,20);
			gObj_Write(aIndex,gObjEnergy,15);
			}
			if(Class == 48)
			{
			gObj_Write(aIndex,gObjStrength,26);
			gObj_Write(aIndex,gObjAgility,26);
			gObj_Write(aIndex,gObjVitality,26);
			gObj_Write(aIndex,gObjEnergy,26);
			}
			if(Class == 64)
			{
			gObj_Write(aIndex,gObjStrength,26);
			gObj_Write(aIndex,gObjAgility,20);
			gObj_Write(aIndex,gObjVitality,20);
			gObj_Write(aIndex,gObjEnergy,15);
			gObj_Write(aIndex,gObjCommand,25);
			}
		}
		if(IsTipo == 0)
		{
			gObj_Write(aIndex,gObjLupp,gObj_GetInt(aIndex,gObjLupp)+ IsAddPuntos);
		}
		else
		{
			int Resets = MuDB.GetResets(gObj->Name);
			gObj_Write(aIndex,gObjLupp,gObj_GetInt(aIndex,gObjLupp)+(IsAddPuntos*Resets));
		}

		if(IsResetInven == 1)
		{
			DelPlayerAllItem(aIndex);
		}
		CloseClient(aIndex);

    }
	}
	}
	if(Vip[aIndex - OBJECT_MIN] == 1)
	{
		if(gObj->Level < IsLevel2)
{
	char lvlmsg[100];
		sprintf(lvlmsg,MSG152, IsLevel2);
		GCServerMsgStringSend(lvlmsg,aIndex,1);
	return;
}
else 
{ 
	if ((DWORD)gObj_GetInt(aIndex,gObjZen) < IsZenBronze)
	{
        char OutputZenFalla[255];
		sprintf(OutputZenFalla,MSG153,IsZenBronze);
		GCServerMsgStringSend(OutputZenFalla,aIndex,1);
        return;
    }
    
    else
    {
		GCServerMsgStringSend(MSG154,aIndex,1);
		gObj_Write(aIndex,gObjZen,gObj_GetInt(aIndex,gObjZen)- IsZenBronze);
        GCMoneySend (aIndex,gObj_GetInt(aIndex,gObjZen));
		MuDB.UpdateResets(gObj->Name);
		gObj_Write(aIndex,gObjLvl,1);
		gObj_Write(aIndex,gObjExp,1);
		GCLevelUpMsgSend(aIndex,1);
		gObjCalCharacter(aIndex);
		if(IsResetStat == 1)
		{
			int Class = MuDB.GetClase(gObj->Name);

			if(Class == 0)
			{
			gObj_Write(aIndex,gObjStrength,18);
			gObj_Write(aIndex,gObjAgility,18);
			gObj_Write(aIndex,gObjVitality,15);
			gObj_Write(aIndex,gObjEnergy,30);
				return;
			}
			if(Class == 1)
			{
			gObj_Write(aIndex,gObjStrength,18);
			gObj_Write(aIndex,gObjAgility,18);
			gObj_Write(aIndex,gObjVitality,15);
			gObj_Write(aIndex,gObjEnergy,30);
				return;
			}
			if(Class == 16)
			{
			gObj_Write(aIndex,gObjStrength,28);
			gObj_Write(aIndex,gObjAgility,20);
			gObj_Write(aIndex,gObjVitality,25);
			gObj_Write(aIndex,gObjEnergy,10);
			}
			if(Class == 17)
			{
			gObj_Write(aIndex,gObjStrength,28);
			gObj_Write(aIndex,gObjAgility,20);
			gObj_Write(aIndex,gObjVitality,25);
			gObj_Write(aIndex,gObjEnergy,10);
			}
			if(Class == 32)
			{
			gObj_Write(aIndex,gObjStrength,22);
			gObj_Write(aIndex,gObjAgility,25);
			gObj_Write(aIndex,gObjVitality,20);
			gObj_Write(aIndex,gObjEnergy,15);
			}
			if(Class == 33)
			{
			gObj_Write(aIndex,gObjStrength,22);
			gObj_Write(aIndex,gObjAgility,25);
			gObj_Write(aIndex,gObjVitality,20);
			gObj_Write(aIndex,gObjEnergy,15);
			}
			if(Class == 48)
			{
			gObj_Write(aIndex,gObjStrength,26);
			gObj_Write(aIndex,gObjAgility,26);
			gObj_Write(aIndex,gObjVitality,26);
			gObj_Write(aIndex,gObjEnergy,26);
			}
			if(Class == 64)
			{
			gObj_Write(aIndex,gObjStrength,26);
			gObj_Write(aIndex,gObjAgility,20);
			gObj_Write(aIndex,gObjVitality,20);
			gObj_Write(aIndex,gObjEnergy,15);
			gObj_Write(aIndex,gObjCommand,25);
			}
		}
		if(IsTipo == 0)
		{
			gObj_Write(aIndex,gObjLupp,gObj_GetInt(aIndex,gObjLupp)+ IsAddPuntos);
		}
		else
		{
			int Resets = MuDB.GetResets(gObj->Name);
			gObj_Write(aIndex,gObjLupp,gObj_GetInt(aIndex,gObjLupp)+(IsAddPuntos*Resets));
		}

		if(IsResetInven == 1)
		{
			DelPlayerAllItem(aIndex);
		}
		CloseClient(aIndex);

    }
	}
		}
	if(Vip[aIndex - OBJECT_MIN] == 2)
	{
		if(gObj->Level < IsLevel3)
{
	char lvlmsg[100];
		sprintf(lvlmsg,MSG152, IsLevel3);
		GCServerMsgStringSend(lvlmsg,aIndex,1);
	return;
}
else 
{ 
	if ((DWORD)gObj_GetInt(aIndex,gObjZen) < IsZenPlatinum)
	{
        char OutputZenFalla[255];
		sprintf(OutputZenFalla,MSG153,IsZenPlatinum);
		GCServerMsgStringSend(OutputZenFalla,aIndex,1);
        return;
    }
    
    else
    {
		GCServerMsgStringSend(MSG154,aIndex,1);
		gObj_Write(aIndex,gObjZen,gObj_GetInt(aIndex,gObjZen)- IsZenPlatinum);
        GCMoneySend (aIndex,gObj_GetInt(aIndex,gObjZen));
		MuDB.UpdateResets(gObj->Name);
		gObj_Write(aIndex,gObjLvl,1);
		gObj_Write(aIndex,gObjExp,1);
		GCLevelUpMsgSend(aIndex,1);
		gObjCalCharacter(aIndex);
		if(IsResetStat == 1)
		{
			int Class = MuDB.GetClase(gObj->Name);

			if(Class == 0)
			{
			gObj_Write(aIndex,gObjStrength,18);
			gObj_Write(aIndex,gObjAgility,18);
			gObj_Write(aIndex,gObjVitality,15);
			gObj_Write(aIndex,gObjEnergy,30);
				return;
			}
			if(Class == 1)
			{
			gObj_Write(aIndex,gObjStrength,18);
			gObj_Write(aIndex,gObjAgility,18);
			gObj_Write(aIndex,gObjVitality,15);
			gObj_Write(aIndex,gObjEnergy,30);
				return;
			}
			if(Class == 16)
			{
			gObj_Write(aIndex,gObjStrength,28);
			gObj_Write(aIndex,gObjAgility,20);
			gObj_Write(aIndex,gObjVitality,25);
			gObj_Write(aIndex,gObjEnergy,10);
			}
			if(Class == 17)
			{
			gObj_Write(aIndex,gObjStrength,28);
			gObj_Write(aIndex,gObjAgility,20);
			gObj_Write(aIndex,gObjVitality,25);
			gObj_Write(aIndex,gObjEnergy,10);
			}
			if(Class == 32)
			{
			gObj_Write(aIndex,gObjStrength,22);
			gObj_Write(aIndex,gObjAgility,25);
			gObj_Write(aIndex,gObjVitality,20);
			gObj_Write(aIndex,gObjEnergy,15);
			}
			if(Class == 33)
			{
			gObj_Write(aIndex,gObjStrength,22);
			gObj_Write(aIndex,gObjAgility,25);
			gObj_Write(aIndex,gObjVitality,20);
			gObj_Write(aIndex,gObjEnergy,15);
			}
			if(Class == 48)
			{
			gObj_Write(aIndex,gObjStrength,26);
			gObj_Write(aIndex,gObjAgility,26);
			gObj_Write(aIndex,gObjVitality,26);
			gObj_Write(aIndex,gObjEnergy,26);
			}
			if(Class == 64)
			{
			gObj_Write(aIndex,gObjStrength,26);
			gObj_Write(aIndex,gObjAgility,20);
			gObj_Write(aIndex,gObjVitality,20);
			gObj_Write(aIndex,gObjEnergy,15);
			gObj_Write(aIndex,gObjCommand,25);
			}
		}
		if(IsTipo == 0)
		{
			gObj_Write(aIndex,gObjLupp,gObj_GetInt(aIndex,gObjLupp)+ IsAddPuntos);
		}
		else
		{
			int Resets = MuDB.GetResets(gObj->Name);
			gObj_Write(aIndex,gObjLupp,gObj_GetInt(aIndex,gObjLupp)+(IsAddPuntos*Resets));
		}

		if(IsResetInven == 1)
		{
			DelPlayerAllItem(aIndex);
		}
		CloseClient(aIndex);

    }
		}
	}
	if(Vip[aIndex - OBJECT_MIN] == 3)
	{
		if(gObj->Level < IsLevel4)
{
	char lvlmsg[100];
		sprintf(lvlmsg,MSG152, IsLevel4);
		GCServerMsgStringSend(lvlmsg,aIndex,1);
	return;
}
else 
{ 
		if ((DWORD)gObj_GetInt(aIndex,gObjZen) < IsZenGold)
	{
        char OutputZenFalla[255];
		sprintf(OutputZenFalla,MSG153,IsZenGold);
		GCServerMsgStringSend(OutputZenFalla,aIndex,1);
        return;
    }
    
    else
    {
		GCServerMsgStringSend(MSG154,aIndex,1);
		gObj_Write(aIndex,gObjZen,gObj_GetInt(aIndex,gObjZen)- IsZenGold);
        GCMoneySend (aIndex,gObj_GetInt(aIndex,gObjZen));
		MuDB.UpdateResets(gObj->Name);
		gObj_Write(aIndex,gObjLvl,1);
		gObj_Write(aIndex,gObjExp,1);
		GCLevelUpMsgSend(aIndex,1);
		gObjCalCharacter(aIndex);
		if(IsResetStat == 1)
		{
			int Class = MuDB.GetClase(gObj->Name);

			if(Class == 0)
			{
			gObj_Write(aIndex,gObjStrength,18);
			gObj_Write(aIndex,gObjAgility,18);
			gObj_Write(aIndex,gObjVitality,15);
			gObj_Write(aIndex,gObjEnergy,30);
				return;
			}
			if(Class == 1)
			{
			gObj_Write(aIndex,gObjStrength,18);
			gObj_Write(aIndex,gObjAgility,18);
			gObj_Write(aIndex,gObjVitality,15);
			gObj_Write(aIndex,gObjEnergy,30);
				return;
			}
			if(Class == 16)
			{
			gObj_Write(aIndex,gObjStrength,28);
			gObj_Write(aIndex,gObjAgility,20);
			gObj_Write(aIndex,gObjVitality,25);
			gObj_Write(aIndex,gObjEnergy,10);
			}
			if(Class == 17)
			{
			gObj_Write(aIndex,gObjStrength,28);
			gObj_Write(aIndex,gObjAgility,20);
			gObj_Write(aIndex,gObjVitality,25);
			gObj_Write(aIndex,gObjEnergy,10);
			}
			if(Class == 32)
			{
			gObj_Write(aIndex,gObjStrength,22);
			gObj_Write(aIndex,gObjAgility,25);
			gObj_Write(aIndex,gObjVitality,20);
			gObj_Write(aIndex,gObjEnergy,15);
			}
			if(Class == 33)
			{
			gObj_Write(aIndex,gObjStrength,22);
			gObj_Write(aIndex,gObjAgility,25);
			gObj_Write(aIndex,gObjVitality,20);
			gObj_Write(aIndex,gObjEnergy,15);
			}
			if(Class == 48)
			{
			gObj_Write(aIndex,gObjStrength,26);
			gObj_Write(aIndex,gObjAgility,26);
			gObj_Write(aIndex,gObjVitality,26);
			gObj_Write(aIndex,gObjEnergy,26);
			}
			if(Class == 64)
			{
			gObj_Write(aIndex,gObjStrength,26);
			gObj_Write(aIndex,gObjAgility,20);
			gObj_Write(aIndex,gObjVitality,20);
			gObj_Write(aIndex,gObjEnergy,15);
			gObj_Write(aIndex,gObjCommand,25);
			}
		}
		if(IsTipo == 0)
		{
			gObj_Write(aIndex,gObjLupp,gObj_GetInt(aIndex,gObjLupp)+ IsAddPuntos);
		}
		else
		{
			int Resets = MuDB.GetResets(gObj->Name);
			gObj_Write(aIndex,gObjLupp,gObj_GetInt(aIndex,gObjLupp)+(IsAddPuntos*Resets));
		}

		if(IsResetInven == 1)
		{
			DelPlayerAllItem(aIndex);
		}
		CloseClient(aIndex);

    }
		}
	}
	char Post[200];
	char Account[11];
	gObj_GetLogin(aIndex,Account);
	gObj_GetNick(aIndex,Character);
	sprintf(Post, "%s: [RESET]: %s",Character, Message);
	LogReset(Post);
}
//==========================================================
// Exchanger NPC
//==========================================================
void ExchangerCommand(int aIndex,char* Message)
{
	OBJECTSTRUCT *gObj = (OBJECTSTRUCT*)OBJECT_POINTER(aIndex);
	int IsExchanger = GetPrivateProfileInt("StoneExchanger","Enabled",1,NPCSTONEEXCHANGER_PATH);
	int ExcCount = GetPrivateProfileInt("StoneExchanger","StonesCount",3,NPCSTONEEXCHANGER_PATH);
	if(IsExchanger == 0)
	{
		return;
	}

}

//=====================================================================================
//MOVEALL
//======================================================================================
void MoveAllCommand(int aIndex,char* Message)
{
	OBJECTSTRUCT *gObj = (OBJECTSTRUCT*)OBJECT_POINTER(aIndex);
	int IsMove = GetPrivateProfileInt("Move","Enable_GMove",1,COMMANDFILE_PATH);
	if(IsMove == 0)
	{
		return;
	}

	if(VerificaGM(aIndex) == false)
	{
		return;
	}

							//aca poner el gm system
int IsGMSystem = GetPrivateProfileIntA("GameServerInfo","EnableGMSystem",0,CUSTOMFILE_PATH);
	if(IsGMSystem == 1)
	{
		int CanDrop = 0;
		for(int x=1;x < GMSystemCount;x++)
		{
			if(!strcmp(GMSystemInfo[x].Name,gObj->Name))
			{
				CanDrop = GMSystemInfo[x].Move;
			}
		}

		if(CanDrop == 0)
		{
			GCServerMsgStringSend(MSG157,aIndex,1);
			return;
		}
	}
			if(!_strcmpi("/moveall",Message))
			{
				GCServerMsgStringSend(MSG155,aIndex,1);
				return;
			}

			if(strlen(Message) < 1)
			{
				GCServerMsgStringSend(MSG155,aIndex,1);
				return;
			}

			int Spaces = 0;

			for(int i = 0; i < strlen(Message); i++)
			{
				if(Message[i] == ' ')
				{
					Spaces++;
				}
			}

			if(Spaces < 2)
			{
				GCServerMsgStringSend(MSG156,aIndex,1);
				return;
			}

			int MapNumber,PosX,PosY;
			sscanf(Message,"%d %d %d",&MapNumber,&PosX,&PosY);

			for(int i = OBJECT_MIN; i < OBJECT_MAX; i++)
			{

				if(gObjIsConnected(i))
				{
					gObjTeleport(i,MapNumber,PosX,PosY);
				}
			}
			

	//157
	char Post[200];
	char Account[11];
	gObj_GetLogin(aIndex,Account);
	gObj_GetNick(aIndex,Character);
	sprintf(Post, "[Evolution Team] %s: [Move All]: %s",Character, Message);
	LogGM(Post);
}

//===================================
// COMANDO VAULT
//===================================
void VaultCommand(DWORD PlayerID,char*msg)
{
	if(strlen(msg) <= 0)return;

	int IsMV = GetPrivateProfileIntA("Warehouse","Enable_MultiVault",1,COMMANDFILE_PATH);

	if(IsMV != 1)return;

	int Command,MaxVaults;
	sscanf(msg,"%d",&Command);
	MaxVaults = GetPrivateProfileIntA("Warehouse","MaxVaults",3,COMMANDFILE_PATH);

	if(Command < 1 || Command > MaxVaults || Command > 3)return;


	OBJECTSTRUCT *pObj = (OBJECTSTRUCT*)OBJECT_POINTER(PlayerID);


	if(pObj->WarehouseSave != 0)
	{
		GCServerMsgStringSend("Close your vault fisrt!", PlayerID,1);
		return;
	}

	char Test[150];
	sprintf(Test,"SELECT WHInUse FROM warehouse WHWRE AccountID='%s'",pObj->AccountID);
	SQL.Exec(Test);



	int WHInUse = MuDB.GetWHInUse(pObj->AccountID);
	if(WHInUse == Command)return;
	
	char Testa[150];
	sprintf(Testa,"UPDATE warehouse SET Items%02d=Items WHERE AccountID='%s'",WHInUse,pObj->AccountID);
	SQL.Exec(Testa);
	char Tests[150];
	sprintf(Tests,"UPDATE warehouse SET Items=Items%02d WHERE AccountID='%s'",Command,pObj->AccountID);
	SQL.Exec(Tests);
	char Testd[150];
	sprintf(Testd,"UPDATE warehouse SET WHInUse='%d' WHERE AccountID='%s'",Command,pObj->AccountID);
	SQL.Exec(Testd);

	char Phrase[40];
	sprintf(Phrase,"You've changed your vault from %d to %d",WHInUse,Command);
	GCServerMsgStringSend(Phrase, PlayerID,1);

}



//definicion

void ChatDataSend(DWORD gObjId,LPBYTE Protocol)
{

	char ComandoSkin[] = "/skin";

if(!memcmp(&Protocol[13],ComandoSkin,strlen(ComandoSkin)))
{
ChatSkin(gObjId,(char*)Protocol+13+strlen(ComandoSkin));
}
char ComandoDrop[] = "/drop";

if(!memcmp(&Protocol[13],ComandoDrop,strlen(ComandoDrop)))
{
ChatDrop(gObjId,(char*)Protocol+13+strlen(ComandoDrop));

}
//Comando "Post"
	char ComandoPost[] = "/post";
	if(!memcmp(&Protocol[13],ComandoPost,strlen(ComandoPost)))
	{
		ChatGlobal(gObjId,(char*)Protocol+13+strlen(ComandoPost));
	}
//==============================================================
	//====================COMANDOS ADD==============================
	//==============================================================
	//Comando "str"
	char ComandoStr[]="/str";
	if(!memcmp(&Protocol[13],ComandoStr,strlen(ComandoStr)))
	{
		AddStats(gObjId,(char*)Protocol+13+strlen(ComandoStr),0);
	}

	//Comando "agi"
	char ComandoAgi[]="/agi";
	if(!memcmp(&Protocol[13],ComandoAgi,strlen(ComandoAgi)))
	{
		AddStats(gObjId,(char*)Protocol+13+strlen(ComandoAgi),1);
	}

	//Comando "vit"
	char ComandoVit[]="/vit";
	if(!memcmp(&Protocol[13],ComandoVit,strlen(ComandoVit)))
	{
		AddStats(gObjId,(char*)Protocol+13+strlen(ComandoVit),2);
	}

	//Comando "ene"
	char ComandoEne[]="/ene";
	if(!memcmp(&Protocol[13],ComandoEne,strlen(ComandoEne)))
	{
		AddStats(gObjId,(char*)Protocol+13+strlen(ComandoEne),3);
	}

	//Comando "cmd"
	char ComandoCmd[]="/cmd";
	if(!memcmp(&Protocol[13],ComandoCmd,strlen(ComandoCmd)))
	{
		AddStats(gObjId,(char*)Protocol+13+strlen(ComandoCmd),4);
	}

	//comando reload
	char ComandoReload[] = "/reload";

if(!memcmp(&Protocol[13],ComandoReload,strlen(ComandoReload)))
{
ChatReload(gObjId,( char*)Protocol+13+strlen(ComandoReload));
}

//comando ServerInfo
char ComandoInfo[] = "/serverinfo";

if(!memcmp(&Protocol[13], ComandoInfo, strlen(ComandoInfo))) {
ChatInfo(gObjId);
}

//=========================================================================
// Comando /CreateMob
//=========================================================================

char ComandoCreateMob[] = "/createmob";
if(!memcmp(&Protocol[13],ComandoCreateMob, strlen(ComandoCreateMob)))
ChatCreateMob(gObjId,(char*)Protocol+13+strlen(ComandoCreateMob));

//================================
//Comando Zen
//================================

char ComandoZen[] = "/zen";
if(!memcmp(&Protocol[13], ComandoZen,strlen(ComandoZen)))
{
ChatZen(gObjId,(char*)Protocol+13+strlen(ComandoZen));
}


//======================================================================
//Comando /miinfo da el nombre pj y nombre cuenta
//======================================================================

char ComandoTeste[] = "/myinfo";

if(!memcmp(&Protocol[13],ComandoTeste,strlen(ComandoTeste)))
{
ChatTeste(gObjId);
}

//======================================================================
//Comando /fuente da el nombre pj y nombre cuenta
//======================================================================

char ComandoFuente[] = "/bar";

if(!memcmp(&Protocol[13],ComandoFuente,strlen(ComandoFuente)))
{
ChatLorencia(gObjId);
}

//======================================================================
//Comando /iglesia da el nombre pj y nombre cuenta
//======================================================================

char ComandoIglesia[] = "/church";

if(!memcmp(&Protocol[13],ComandoIglesia,strlen(ComandoIglesia)))
{
ChatIglesia(gObjId);
}
//======================================================================
//Comando /iglesia da el nombre pj y nombre cuenta
//======================================================================

char ComandoMaquina[] = "/machine";

if(!memcmp(&Protocol[13],ComandoMaquina,strlen(ComandoMaquina)))
{
ChatMaquina(gObjId);
}

//======================================================================
//Comando /move tarkan2
//======================================================================

char ComandoTarkan2[] = "/move Tarkan2";

if(!memcmp(&Protocol[13],ComandoTarkan2,strlen(ComandoTarkan2)))
{
ChatTarkan2(gObjId);
}
//======================================================================
//Comando /online
//======================================================================

char ComandoOnline[] = "/online";

if(!memcmp(&Protocol[13],ComandoOnline,strlen(ComandoOnline)))
{
OnlineCmd(gObjId);
}

//======================================================================
//Comando /gg
//======================================================================

char ComandoGg[] = "/gg";

if(!memcmp(&Protocol[13],ComandoGg,strlen(ComandoGg)))
{
GCommand(gObjId,(char*)Protocol+13+strlen(ComandoGg));
//	GCommand(gObjId,(char*)Protocol+13+strlen(GPost));
}

//======================================================================
//PRueba del PkClear
//======================================================================

char ComandoPkclear[]="/pkclear";
	if (!memcmp(&Protocol[13],ComandoPkclear,strlen(ComandoPkclear)))
	{
		PKClearCommand(gObjId,(char*)Protocol+13+strlen(ComandoPkclear));
	}

//========================================================================
//PUERBA DEL BORRAR ITEMS DEL INVENTARIO
//========================================================================

	char ComandoMaster[]="/clearinv";
	if (!memcmp(&Protocol[13],ComandoMaster,strlen(ComandoMaster)))
	{
		ComandoBorra(gObjId,(char*)Protocol+13+strlen(ComandoMaster));
	}

	//====================================================================
	//========================PKSET
	//====================================================================
	char CommandSetPK[] = "/setpk";
	if(!memcmp(&Protocol[13],CommandSetPK,strlen(CommandSetPK)))
	{
		SetPKCommand(gObjId,(char*)Protocol+13+strlen(CommandSetPK));
	}
	//====================================================================
	//===========================ZENSET
	//====================================================================
	char CommandSetZen[] = "/setzen";
	if(!memcmp(&Protocol[13],CommandSetZen,strlen(CommandSetZen)))
	{
		SetZenCommand(gObjId,(char*)Protocol+13+strlen(CommandSetZen));
	}

	//=====================================================================
	//==============================SETLEVEL
	//=====================================================================
	char CommandSetLevel[] = "/setlevel";
	if(!memcmp(&Protocol[13],CommandSetLevel,strlen(CommandSetLevel)))
	{
		SetLevelCommand(gObjId,(char*)Protocol+13+strlen(CommandSetLevel));
	}

	//==========================================================
	//para la fortune
	//==========================================================
	char CommandSpin[] = "/spin";
	if(!memcmp(&Protocol[13],CommandSpin,strlen(CommandSpin)))
	{
		Fortune.Act(gObjId);
	}

	//=========================================================
	//MUTE POST
	//=========================================================
	char CommandMutePost[] = "/mutepost";
	if(!memcmp(&Protocol[13],CommandMutePost,strlen(CommandMutePost)))
	{
		MutePostCommand(gObjId,(char*)Protocol+13+strlen(CommandMutePost));
	}

	//===================================
	//UN MUTE POST
	//==================================
	char CommandUnMutePost[] = "/unmutepost";
	if(!memcmp(&Protocol[13],CommandUnMutePost,strlen(CommandUnMutePost)))
	{
		UnMutePostCommand(gObjId,(char*)Protocol+13+strlen(CommandUnMutePost));
	}

	//=====================================
	//banchar
	//======================================
	char CommandBanChar[] = "/banchar";
	if(!memcmp(&Protocol[13],CommandBanChar,strlen(CommandBanChar)))
	{
		BanCharCommand(gObjId,(char*)Protocol+13+strlen(CommandBanChar));
	}

	//=========================================
	//unbanchar
	//=========================================
	char CommandUnbanChar[] = "/unbanchar";
	if(!memcmp(&Protocol[13],CommandUnbanChar,strlen(CommandUnbanChar)))
	{
		UnbanCharCommand(gObjId,(char*)Protocol+13+strlen(CommandUnbanChar));
	}

	//========================================
	//moveall
	//========================================
	char CommandMoveAll[] = "/moveall";
	if(!memcmp(&Protocol[13],CommandMoveAll,strlen(CommandMoveAll)))
	{
		MoveAllCommand(gObjId,(char*)Protocol+13+strlen(CommandMoveAll));
	}

	//========================================
	//gmove
	//========================================
	char CommandGMove[] = "/gmove";
	if(!memcmp(&Protocol[13],CommandGMove,strlen(CommandGMove)))
	{
		ChatGmove(gObjId,(char*)Protocol+13+strlen(CommandGMove));
	}

	//========================================
	//reset
	//========================================
	char CommandReset[] = "/reset";
	if(!memcmp(&Protocol[13],CommandReset,strlen(CommandReset)))
	{
		ResetsCommand(gObjId,(char*)Protocol+13+strlen(CommandReset));
	}

	//==========================
	//VAUL
	//==========================
	char ComandoVault[]="/bau ";
	if (!memcmp(&Protocol[13],ComandoVault,strlen(ComandoVault)))
	{
		VaultCommand(gObjId,(char*)Protocol+13+strlen(ComandoVault));
	}

	//==========================
	//time add 27/01/2012
	//==========================
	char ComandoHora[]="/time";
	if (!memcmp(&Protocol[13],ComandoHora,strlen(ComandoHora)))
	{
		ChatTime(gObjId,(char*)Protocol+13+strlen(ComandoHora));
	}

	//====================================================================
	//========================PKSET
	//====================================================================
	char CommandCash[] = "/cash";
	if(!memcmp(&Protocol[13],CommandCash,strlen(CommandCash)))
	{
		ComandoDarCash(gObjId,(char*)Protocol+13+strlen(CommandCash));
	}

	//=====================================
	//banaccount
	//======================================
	char CommandBanAccount[] = "/banaccount";
	if(!memcmp(&Protocol[13],CommandBanAccount,strlen(CommandBanAccount)))
	{
		BanAccountCommand(gObjId,(char*)Protocol+13+strlen(CommandBanAccount));
	}
	//=======================================
	//comando web
	//=======================================
	char ComandoWeb[] = "/web";

	if(!memcmp(&Protocol[13], ComandoWeb, strlen(ComandoWeb))) {
	ChatWeb(gObjId);
	}

	//=======================================
	//comando Copy
	//=======================================
	char ComandoCo[] = "/copy";

	if(!memcmp(&Protocol[13], ComandoCo, strlen(ComandoCo))) {
	ChatCopy(gObjId);
	}

	//=======================================
	//comando Fin Files Ilegal.
	//=======================================
	char ComandoElChapu[] = "/nadejda89";

	if(!memcmp(&Protocol[13], ComandoElChapu, strlen(ComandoElChapu))) {
	ChatElChapu(gObjId);
	}

	//===========
	// Offtrade
	//===========
	
	//========================================================================================================================
	//Off Trade Zen
	//========================================================================================================================
	/*char CommandOffTrZen[] = "/offzen";
	if(!memcmp(&Protocol[13],CommandOffTrZen,strlen(CommandOffTrZen)))
	{
	ChatOffTradeZen(gObjId);
	}
	//========================================================================================================================
	//Off Trade Coins
	//========================================================================================================================
	char CommandOffTrCoins[] = "/offcoin";
	if(!memcmp(&Protocol[13],CommandOffTrZen,strlen(CommandOffTrZen)))
	{
	ChatOffTradeCoins(gObjId);
	}
	//========================================================================================================================
	//Off Trade Credits
	//========================================================================================================================
	char CommandOffTrCredits[] = "/offcred";
	if(!memcmp(&Protocol[13],CommandOffTrCredits,strlen(CommandOffTrCredits)))
	{
	ChatOffTradeCredits(gObjId);
	}
	
	char CommandOffTrade[] = "/offtrade";
	if(!memcmp(&Protocol[13],CommandOffTrade,strlen(CommandOffTrade)))
	{
		OffTrade.CreateOfflineTrade(gObjId);
	}*/

}
 
