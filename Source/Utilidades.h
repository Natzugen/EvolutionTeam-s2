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
#include "StdAfx.h"
#include "Global.h"


void PlayerConnected(int aIndex,LPBYTE aRecv);
void LogLine(char*formatsting, ...);
void LogPost(char*formatsting, ...);
void LogGM(char*formatsting, ...);
void LogReset(char*formatsting, ...);
void LogGS(char*formatsting, ...);
void ToHex(unsigned char* out, unsigned char* data, int c_len);

void HookThis(DWORD dwMyFuncOffset, DWORD dwJmpOffset);
void SetNop(DWORD dwOffset, int Size);
void SetRetn(DWORD dwOffset);
void SetByte(DWORD dwOffset, BYTE btValue);

bool VerificaGM(DWORD gObjId);
DWORD gObjByNick (char * nick);
void *GetPlayerAddress(unsigned int PlayerID);
void gObj_GetNick(DWORD gObjId, char * nick);
void gObj_GetLogin(WORD gObjId, char * login);
DWORD gObj_GetMoney(WORD gObjId);
WORD gObj_GetLevel(DWORD PlayerID);
DWORD gObj_GetLevelUpPoints(WORD gObjId);
char gObj_GetMap(WORD gObjId);
char gObj_GetPosX(WORD gObjId);
char gObj_GetPosY(WORD gObjId);
int GetPlayerClass(DWORD PlayerID);
void gObj_Write(int PlayerID, int gObjParam, long int Value);
long int gObj_GetInt(int PlayerID, int gObjParam);
char* gObj_GetChar(int PlayerID, int gObjParam);
bool gObjIsConnected(DWORD wId);
void DataSendAll(unsigned char* Packet, int Length);
void ServerMsgSend(DWORD wId,int Type, char Sender[20],const char* Message,...);
void NPCSay(DWORD PlayerID,DWORD iNpcID, char *Texto);
void StringSendAll(char*Texto,int tipo);
DWORD gObj_GetPKStatus (DWORD gObjId ); 
void WriteMemoryInt(DWORD Offset, DWORD bValue, DWORD bValueMax, DWORD OffsetLen);
int DelPlayerAllItemNoInv ( DWORD PlayerID);
void MsgOutput(int aIndex,char* Message,...);
void GCFireworkSend(int aIndex,int X,int Y,int Amount);
void MsgOutputGlobal(int aIndex,char* Message,...);
typedef BYTE (*pgObjInventoryDeleteItem) (int,int);
DWORD gObjByNick1(char * nick);


typedef void (*pGCInventoryItemDeleteSend) (int,BYTE,unsigned char);
extern pGCInventoryItemDeleteSend GCInventoryItemDeleteSend;

typedef int (*pgObjCalCharacter)(int);
extern pgObjCalCharacter gObjCalCharacter;

typedef void (*pGCReFillSend) (int,WORD,BYTE,unsigned char,WORD);
extern pGCReFillSend GCReFillSend;
typedef void (*pgObjSetBP) (int);
extern pgObjSetBP gObjSetBP;
typedef void (*pGCManaSend) (int,short,BYTE,unsigned char,WORD);
extern pGCManaSend GCManaSend;
typedef void (*pGCLevelUpMsgSend)(int,int);
extern pGCLevelUpMsgSend GCLevelUpMsgSend;
typedef void (*pChatTargetSend) (OBJECTSTRUCT*,char*,int);
extern pChatTargetSend ChatTargetSend;
typedef int (*pgObjSetMonster) (int,int);
extern pgObjSetMonster gObjSetMonster1;
void ServerMsgSendBlue(int aIndex,char* Name,char* Message,...);
void ServerMsgSendOrange(int aIndex,char* Name,char* Message,...);
void ServerMsgSendGreen(int aIndex,char* Name,char* Message,...);
void ServerMsgSendYellow(int aIndex,char* Name,char* Message,...);
int DelPlayerAllItem ( DWORD PlayerID);
void gObj_GetIP (DWORD gObjId,char*Ip_Addr);
void SetDrop(DWORD Drop); //agregado para happyhour
int GetDrop(); //agregado para happyhour
int GetExp();//agregado para happyhour
LPSTR GetUser(DWORD PlayerID);//agregado para el login

void gObjWrite(int aIndex,int gObjParam,long int Value);
long int gObjGetInt(int aIndex,int gObjParam);
void MsgOutputSystem(int aIndex,char* Message,...);
void MsgNormal(int aIndex,char* szMsg,...);
void MaxLifeReFillSend(DWORD PlayerID);
void FunctionHook(DWORD NewOffset,DWORD JumpOffset);
void GCMagicAttackNumberSendH(OBJECTSTRUCT* gObj, BYTE MagicNumber, int usernumber,  unsigned char skillsuccess);
void PHeadSubSetB(LPBYTE lpBuf, BYTE head, BYTE sub, int size);
void MsgAll(char* szMsg,...);
void AllServerMsgSend(char *message);
char *GetMapName(int MapId);
void PHeadSetBE( LPBYTE lpBuf, BYTE head,int size);
int OnlineStatus(int aIndex);
bool ClickOnNPC(int aIndex,LPBYTE aRecv);
void ServerMsgSendAll(char* Message,...);
void ServerMsgSendMap(int Map,int Type,char* Message,...);
void MsgAllNormal(int aIndex,char* szMsg,...);

void MsgSendV2(OBJECTSTRUCT* gObj, unsigned char* Msg, int size);
void LogNotice(int type,char* szMsg,...);

//agregado para el fix del gm
typedef		BOOL(*pgObjSetCharacter)(LPBYTE lpdata, int aIndex);
extern		pgObjSetCharacter gObjSetCharacter;

