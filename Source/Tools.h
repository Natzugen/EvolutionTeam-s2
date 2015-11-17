#ifndef __TOOLS_H__
#define __TOOLS_H__

// Function Headers
void SetByte(DWORD NewOffset,BYTE NewByte);
void SetJNZ(DWORD NewOffset);
void SetJE(DWORD NewOffset);
void SetJMP(DWORD NewOffset);
void SetNop(DWORD NewOffset,int Size);
void SetRetn(DWORD NewOffset);
void FunctionHook(DWORD NewOffset,DWORD JumpOffset);
int VerifyGM(int aIndex);
void gObjGetNick(int aIndex,char* Nick);
long int gObjGetInt(int aIndex,int gObjParam);
void gObjWrite(int aIndex,int gObjParam,long int Value);
int OnlineStatus(int iIndex);
int gObjGetIndex(char* Target);
void MsgOutput(int aIndex,char* Message,...);
void MsgOutputGlobal(int aIndex,char* Message,...);
void ServerMsgSendYellow(int aIndex,char* Name,char* Message,...);
void ServerMsgSendBlue(int aIndex,char* Name,char* Message,...);
void ServerMsgSendOrange(int aIndex,char* Name,char* Message,...);
void ServerMsgSendGreen(int aIndex,char* Name,char* Message,...);
void ServerMsgSendAll(char* Message,...);
void DataSendAll(unsigned char* Packet,int Length);
void GCFireworkSend(int aIndex,int X,int Y,int Amount);

#endif