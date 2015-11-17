//======================================
// Reedlan Customs
// Coder : SmallHabit
// Recoder : MaMoHT
// Start Date : 07.09.2009
//======================================
#include "StdAfx.h"
#include "OffTrade.h"
#include "Protocolos.h"
#include <WinSock2.h>
#include "USER.h"
#include "Utilidades.h"
#include "SQLX.h"
//========================================================================================================================
CRITICAL_SECTION criti;
COFFTrade OFFTrade;
OFFLINETRADE OfflineShop[OBJECT_MAX];
//========================================================================================================================
void COFFTrade::Init()
{


	 BYTE cFixMapLoad4[] = {0xEB, 0x33, 0x04 };
	 memcpy((int*)0x005CDDA1,cFixMapLoad4,sizeof(cFixMapLoad4));
	 for(int i=0;i<OBJECT_MAX;i++)
		 OfflineShop[i].IsOffTrade = 0;
}
//========================================================================================================================
void COFFTrade::CreateOfflineTrade(int aIndex)
{
	


	int OfftradeMapN = GetPrivateProfileInt("OffTrade","OfftradeMap",0,"..\\EData\\EOffTrade.ini");
	int OfftradeSendAll = GetPrivateProfileInt("OffTrade","OfftradeSendAll",0,"..\\EData\\EOffTrade.ini");
	char OfftradeShopM[50];
	OBJECTSTRUCT *gObj = (OBJECTSTRUCT*)OBJECT_POINTER(aIndex);
    if(gObj->m_bPShopOpen == false)
    {
        MsgNormal(aIndex,"First Open you Store!");
        return;
    }
	if(gObj->MapNumber != OfftradeMapN)
	{
		MsgNormal(aIndex,"OffTrade can be only in %s",GetMapName(OfftradeMapN));
		return;
	}
	if (gObj->OffTradeCoin == 1)
	{
		char TextShop[36] = "<<COIN SHOP>>";	
			PMSG_ANS_PSHOP_TEXT_CHANGED pMsg;
			PHeadSubSetB((LPBYTE)&pMsg, 0x3F, 0x10, sizeof(pMsg));
			pMsg.NumberH = SET_NUMBERH(aIndex);
			pMsg.NumberL = SET_NUMBERL(aIndex);
			memcpy(gObj->m_szPShopText, TextShop, sizeof(pMsg.btPShopText));
			memcpy(pMsg.btPShopText, TextShop, sizeof(pMsg.btPShopText));
			memcpy(pMsg.btName, gObj->Name, sizeof(pMsg.btName));
			DataSendB(aIndex, (char*)&pMsg, pMsg.h.size);
			MsgAll("[OffTrade] %s now state in %s X:%d Y:%d Exchange:COIN",gObj->Name,GetMapName(gObj->MapNumber),gObj->X,gObj->Y);
	}
	if (gObj->OffTradeZen == 1)
	{
		char TextShop[36] = "<<ZEN SHOP>>";
			PMSG_ANS_PSHOP_TEXT_CHANGED pMsg;
			PHeadSubSetB((LPBYTE)&pMsg, 0x3F, 0x10, sizeof(pMsg));
			pMsg.NumberH = SET_NUMBERH(aIndex);
			pMsg.NumberL = SET_NUMBERL(aIndex);
			memcpy(gObj->m_szPShopText, TextShop, sizeof(pMsg.btPShopText));
			memcpy(pMsg.btPShopText, TextShop, sizeof(pMsg.btPShopText));
			memcpy(pMsg.btName, gObj->Name, sizeof(pMsg.btName));
			DataSendB(aIndex, (char*)&pMsg, pMsg.h.size);
			MsgAll("[OffTrade] %s now state in %s:X %d Y:%d Exchange:COIN",gObj->Name,GetMapName(gObj->MapNumber),gObj->X,gObj->Y);
	}
	if (gObj->OffTradeCred == 1)
	{
		char TextShop[36] = "<<Credits SHOP>>";
			PMSG_ANS_PSHOP_TEXT_CHANGED pMsg;
			PHeadSubSetB((LPBYTE)&pMsg, 0x3F, 0x10, sizeof(pMsg));
			pMsg.NumberH = SET_NUMBERH(aIndex);
			pMsg.NumberL = SET_NUMBERL(aIndex);
			memcpy(gObj->m_szPShopText, TextShop, sizeof(pMsg.btPShopText));
			memcpy(pMsg.btPShopText, TextShop, sizeof(pMsg.btPShopText));
			memcpy(pMsg.btName, gObj->Name, sizeof(pMsg.btName));
			DataSendB(aIndex, (char*)&pMsg, pMsg.h.size);
			MsgAll("[OffTrade] %s now state in %s:X %d Y:%d Exchange:Credits",gObj->Name,GetMapName(gObj->MapNumber),gObj->X,gObj->Y);
	}

	OfflineShop[aIndex].IsOffTrade=1;
    CloseClientF(aIndex);

}



//========================================================================================================================
void CGPShopAnsCloseHook(int aIndex, BYTE btResult)
{
    if(OfflineShop[aIndex].IsOffTrade)
		gObjDelF(aIndex);
	
	CGPShopAnsClose(aIndex,btResult);
}
//========================================================================================================================
void CloseClientHook(int aIndex)
{	
	if ( aIndex >= OBJECT_MIN && aIndex < OBJECT_MAX )
    {
		OBJECTSTRUCT *gObj = (OBJECTSTRUCT*)OBJECT_POINTER(aIndex);

		if ( aIndex < 0 || aIndex > OBJECT_MAX-1 )
			return;

		if(gObj->Connected == 3)
		{
			if(gObj->Life <= 0)
			{
				//Log.outError("ResponErrorCloseClientHook");
				return;
			}
		}

		if(OfflineShop[aIndex].IsOffTrade != 0)
			return; 

		

		if ( gObj->Connected == PLAYER_EMPTY )
			return;

		if ( gObj->m_socket != INVALID_SOCKET )
		{
			closesocket(gObj->m_socket );
			gObj->m_socket = INVALID_SOCKET;
		}
	}
}
//========================================================================================================================
void ResponErrorCloseClientHook(int aIndex)
{	
	if ( aIndex >= OBJECT_MIN && aIndex < OBJECT_MAX )
    {
		OBJECTSTRUCT *gObj = (OBJECTSTRUCT*) OBJECT_POINTER(aIndex);

		if ( aIndex < 0 || aIndex > OBJECT_MAX-1 )
			return;

		if(gObj->Connected == 3)
		{
			if(gObj->Life <= 0)
			{
				//Log.outError("ResponErrorCloseClientHook");
				return;
			}
		}

		if(OfflineShop[aIndex].IsOffTrade != 0)
			return; 

		if (gObj->Connected == PLAYER_EMPTY )
			return;

		closesocket(gObj->m_socket);
		gObj->m_socket = INVALID_SOCKET;

		gObjDelF(aIndex);
	}
}
//========================================================================================================================
void CloseClient2Hook(_PER_SOCKET_CONTEXT * lpPerSocketContext, int result)
{
    int index = -1;
    index = lpPerSocketContext->nIndex ;    

    if ( index >= OBJECT_MIN && index < OBJECT_MAX )
    {	
		OBJECTSTRUCT *gObj = (OBJECTSTRUCT*) OBJECT_POINTER(index);

		if(gObj->Connected == 3)
		{
			if(gObj->Life <= 0)
			{
				//Log.outError("ResponErrorCloseClientHook");
				return;
			}
		}

        if(OfflineShop[index].IsOffTrade != 0)
            return;

        if ( gObj->m_socket != INVALID_SOCKET )
        {
            if (closesocket(gObj->m_socket) == -1 )
            {
                if ( WSAGetLastError() != WSAENOTSOCK )
                    return;
            }
            gObj->m_socket = INVALID_SOCKET;

	
        }
        gObjDelF(index);
    }
}
//========================================================================================================================
/*void OffTradeLoginCheck(LPBYTE aRecv,int aIndex)
{
    PMSG_IDPASS *pMsg = (PMSG_IDPASS*)aRecv;
               
    char LoginID[11];
 
    LoginID[10]=0;
    memcpy(LoginID, pMsg->Id, sizeof(pMsg->Id));
    BuxConvert(LoginID, 10);
 
    for(int i=OBJECT_MIN;i<OBJECT_MAX;i++)
    {
        OBJECTSTRUCT *sObj = (OBJECTSTRUCT*)OBJECT_POINTER(i);
       
        if(sObj->Connected == 3)
            if(strcmp(LoginID,sObj->AccountID)==0)
                if(OfflineShop[i].IsOffTrade)
                {
                   CloseClient(aIndex);
 
                    if(OfflineShop[i].IsOffTrade)
                        gObjDel(i);
                   
                    OfflineShop[i].IsOffTrade=0;
                }
    }
}*/
//========================================================================================================================
/*void OffTradeLogin(int aIndex,LPBYTE aRecv)
{
	PMSG_IDPASS *lpMsg = (PMSG_IDPASS*)aRecv;

	char AccountID[11];
	AccountID[10] = 0;
	memcpy(AccountID,lpMsg->Id,sizeof(lpMsg->Id));
	BuxConvert(AccountID,10);

	for(int i = OBJECT_MIN; i<OBJECT_MAX;i++)
	{
		OBJECTSTRUCT *lpObj = (OBJECTSTRUCT*)OBJECT_POINTER(i);

		if(lpObj->Connected == 3)
		{
			if(!strcmp(AccountID,lpObj->AccountID))
			{
				if(OfflineShop[i].IsOffTrade == 1)
				{
					GJPUserClose(lpObj->AccountID);
					g_Console.ConsoleOutput(4,"[OFFTRADE][%s][%s] Close Offline Shop",lpObj->AccountID,lpObj->Name);
					//LogAdder ("OFFTRADE","Close Offline Shop",i);
					gObjDel(i);
					OfflineShop[i].IsOffTrade = 0;
					//SQL.OffTradeOff(aIndex);
				
				}
			}
		}


	
	}
}*/
void OffTradeLogin(int aIndex,LPBYTE aRecv)
{
	PMSG_IDPASS *lpMsg = (PMSG_IDPASS*)aRecv;

	char AccountID[11];
	AccountID[10] = 0;
	memcpy(AccountID,lpMsg->Id,sizeof(lpMsg->Id));
	BuxConvert(AccountID,10);

	for(int i = OBJECT_MIN; i<OBJECT_MAX;i++)
	{
		OBJECTSTRUCT *lpObj = (OBJECTSTRUCT*)OBJECT_POINTER(i);

		if(lpObj->Connected == 3)
		{
			if(!strcmp(AccountID,lpObj->AccountID))
			{
				if(OfflineShop[i].IsOffTrade == 1)
				{
					GJPUserClose(lpObj->AccountID);
					//g_Console.ConsoleOutput(4,"[OFFTRADE][%s][%s] Close Offline Shop",lpObj->AccountID,lpObj->Name);
					//LogAdder ("OFFTRADE","Close Offline Shop",i);
					gObjDelF(i);
					OfflineShop[i].IsOffTrade = 0;
					//SQL.OffTradeOff(aIndex);
				}
			}
		}
	}
}
//========================================================================================================================
void Login_Timer(void * lpParam)
{
	while(true)
	{	
		Sleep(4000);
	
		for(int i=OBJECT_MIN;i<OBJECT_MAX;i++)
		{
			if(OfflineLogin[i].aIndex != -1)
			{	
				PMSG_IDPASS *lpMsg = (PMSG_IDPASS *)OfflineLogin[i].aRecv;
				GCSPJoinIdPassRequest(lpMsg,OfflineLogin[i].aIndex);
				
				OfflineLogin[i].aIndex = -1;
				_endthread();
			}
		}
	}
	_endthread();
}
//========================================================================================================================
void CSPJoinIdPassRequest(LPBYTE aRecv,int aIndex)
{
	char id[11];
	int isOff = 0;

	PMSG_IDPASS *lpMsg = (PMSG_IDPASS *)aRecv;

	id[10]=0;
	memcpy(id, lpMsg->Id, sizeof(lpMsg->Id));
	BuxConvert(id, MAX_ACCOUNT_LEN);

	for(int i=OBJECT_MIN;i<OBJECT_MAX;i++)
	{	
		OBJECTSTRUCT *gObj = (OBJECTSTRUCT*)OBJECT_POINTER(i);
		if(gObj->Connected == 3)
		{
			if(_tcsstr(gObj->AccountID, id))
			{	
				if(OfflineShop[i].IsOffTrade != 0)
				{	
					OfflineShop[i].IsOffTrade = 1;
					ObjGameClose(i);
					CloseClientF(i);
					isOff=1;
					
				}
			//	Log.outError("Already here[%d]",i);
			}
		}
	}


	if(isOff)
	{	
		OfflineLogin[aIndex].aRecv = aRecv;
		OfflineLogin[aIndex].aIndex = aIndex;
		_beginthread( Login_Timer, 0, NULL  );
	}
	else
	{
		GCSPJoinIdPassRequest(lpMsg,aIndex);
	}
}
//========================================================================================================================
bool IsItem(int aIndex,int pos)
{
	OBJECTSTRUCT * gObj = (OBJECTSTRUCT*) OBJECT_POINTER (aIndex);

	if (gObj->pInventory1->m_Type < 0)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}
//========================================================================================================================
