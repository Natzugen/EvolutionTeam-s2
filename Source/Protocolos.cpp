/*-------------------------------------------------------*/
/*				Project Evolution Team Season 2          */
/*   Version GS 1.00.18 & GS-CS 1.00.19 Protocol Eng     */
/*             http://evolution-team.eu                  */
/*-------------------------------------------------------*/
/*                    Code By Th3AnG3L                   */
/*             http://evolution-team.eu                  */
/*-------------------------------------------------------*/
#include "Protocolos.h"
#include "Gameserver.h"
#include "Global.h"
#include "ChatCore.h"
#include "Fixs.h"
#include "user.h"
#include "ChaosMachine.h"
#include "MSSQL.h"


//100%
OFFLINETRADELOGIN OfflineLogin[OBJECT_MAX];
BYTE ProtocolServer (BYTE Tipo){
switch(Tipo){

case 0x1D: return 0xD4;
case 0xD6: return 0x15;
case 0xDC: return 0x11;
}
return Tipo;
}


BYTE ProtocolClient (BYTE Tipo){
switch(Tipo){

case 0xD4: return 0x1D;
case 0x15: return 0xD6;
case 0x11: return 0xDC;
}
return Tipo;
}


bool ProtocolCore(BYTE protoNum,LPBYTE aRecv,DWORD aLen,DWORD aIndex,DWORD Encrypt,int Serial)
{
	OBJECTSTRUCT *pObj = (OBJECTSTRUCT*)OBJECT_POINTER(aIndex);
BYTE ProtocolType = aRecv[0];
switch(ProtocolType)
{
case 0xC1:
switch(BYTE(protoNum))
{
case 0xDB:
protoNum = 0xD7;
aRecv[2] = 0xD7;
break;
}
}
switch(BYTE(protoNum))
{

	//========
		// Guild Event
		//===========
		// CGGuildMasterInfoSave
		// Guild System
		case 0x55:
			GuildSystem.Check(aIndex, (PMSG_GUILDINFOSAVE *)aRecv);
			return true;
			break;

case 0x00:
ChatDataSend(aIndex,aRecv);
break;
case 0x03:
//PlayerConnected(aIndex,aRecv);
CN(aIndex);
CNGM(aIndex);
VipSystem.Load(aIndex);
break;
// OffTrade
case 0xF1:
OffTradeLogin(aIndex,aRecv);
CheckIP(aIndex);
break;
// New Jewels
case 0x26:
CustomJewels.CGUseItemRecv((PMSG_USEITEM*)aRecv,aIndex);
break;
case 0x30:
NPC.Talk(aIndex,(aRecv[4] + aRecv[3] * 256));
Exchanger.Talk(aIndex,(aRecv[4] + aRecv[3] * 256));
if(ClickOnNPC(aIndex,aRecv))
	return true;
break;
case 0x95:
GoldenArcher.Act(aIndex);
break;
case 0x86:
			//ChaosMachine.ChaosBoxHook(aIndex,aRecv[3]);
			break;
case 0xBC:
		if(pObj[aIndex].TargetNumber != -1 && pObj[aIndex].pTransaction == 1)
		{

			GCServerMsgStringSend("Duping is not allowed here.",aIndex,0);
			CloseClient(aIndex);
		}
		else 
		break;
}

DataRecv(protoNum,aRecv,aLen,aIndex,Encrypt,Serial);

return true;
}

//========================================================================================================================
//CGSellRequestRecv_Hook
//========================================================================================================================
void CGSellRequestRecv_Hook(PMSG_SELLREQUEST * lpMsg, int aIndex) 
{ 
OBJECTSTRUCT *gObj = (OBJECTSTRUCT*)OBJECT_POINTER(aIndex); 
if (OfflineShop[aIndex].IsOffTrade == 1)
{

PMSG_SELLRESULT pResult; 
PHeadSetB((LPBYTE)&pResult, 0x33, sizeof(pResult)); 
pResult.Result = false; 
pResult.Money = gObj->Money; 

int iAddSum = gObj->pInventory[lpMsg->Pos].m_SellMoney;


if ( gObj->CloseType != -1 ) 
{ 
DataSend(aIndex, (LPBYTE)&pResult, pResult.h.size); 
return; 
} 

if ( gObj->m_IfState.use > 0 && gObj->m_IfState.type != 3 ) 
{ 
DataSend(aIndex, (LPBYTE)&pResult, pResult.h.size); 
return; 
} 

if ( gObj->pTransaction == 1 ) 
{ 
return; 
} 

if ( lpMsg->Pos > MAIN_INVENTORY_SIZE-1 ) 
{ 
DataSend(aIndex, (LPBYTE)&pResult, pResult.h.size); 
return; 
} 

//unsigned short gems = iAddSum; 
unsigned short gems = 50; 
//SQL.UpdateCashOffExpSystem(gObj->AccountID,gems);
//g_Console.ConsoleOutput(2,"[ DEBUG ]  Offline Trade Cash send");
gObjInventoryDeleteItem(aIndex, lpMsg->Pos); 
GCInventoryItemDeleteSend(aIndex, lpMsg->Pos, 1); 

pResult.Result = true; 
DataSend(aIndex, (LPBYTE)&pResult, pResult.h.size); 
return; 

}
CGSellRequestRecv(lpMsg, aIndex); 
}
//========================================================================================================================
//CGPShopReqBuyItem_Hook
//========================================================================================================================
void CGPShopReqBuyItem_Hook(PMSG_REQ_BUYITEM_FROM_PSHOP * lpMsg, int aIndex) 
{
	OBJECTSTRUCT *pObj = (OBJECTSTRUCT*)OBJECT_POINTER(MAKE_NUMBERW(lpMsg->NumberH, lpMsg->NumberL));
	OBJECTSTRUCT *gObj = (OBJECTSTRUCT*)OBJECT_POINTER(aIndex);
	DWORD dwCost = 0;
    DWORD Coins = 0;
	DWORD Credits = 0;
	DWORD Procent = 0;
	float  OfftradeProcent = GetPrivateProfileInt("OffTrade","OfftradeProcent",0.3,"..\\EData\\EOffTrade.ini");
	dwCost = pObj->pInventory1[lpMsg->btItemPos].m_iPShopValue;
    Coins = SQLX.GetCoinsPlayer(gObj->AccountID);
	Credits = SQLX.GetCreditsPlayer(gObj->AccountID);
	if (OfftradeProcent == 0.0)
	{
		Procent = 0;
	}
	else
	{
		Procent = dwCost*OfftradeProcent;
	}
	
	if (pObj->OffTradeCoin == 1)
	{
		if (Coins < pObj->pInventory1[lpMsg->btItemPos].m_iPShopValue)
		{
		MsgNormal(aIndex,"no required amount");
		return;
		}
	//	dwCost -= dwCost%5;
                SQLX.UpdateCashOffExpSystemPlus(pObj->AccountID,dwCost-Procent);
				LogNotice(1,"[OffTradeCoin] Character %s succesful sell item for %d coins",pObj->Name,dwCost);
				SQLX.UpdateCashOffExpSystemMinus(gObj->AccountID,dwCost);
				LogNotice(1,"[OffTradeCoin] Character %s succesful buy item for %d coins",gObj->Name,dwCost);
				 gObj->Money += dwCost;
			   	 pObj->Money -= dwCost;
			
				GCMoneySend(aIndex, gObj->Money);
				GCMoneySend(pObj->m_Index, pObj->Money);

	
	
	}

	//Credits
	if (pObj->OffTradeCred == 1)
	{
		if (Credits < pObj->pInventory1[lpMsg->btItemPos].m_iPShopValue)
		{
		MsgNormal(aIndex,"no required amount");
		return;
		}
	//	dwCost -= dwCost%5;
                SQLX.UpdateCashOffExpSystemPlusCredit(pObj->AccountID,dwCost-Procent);
				LogNotice(1,"[OffTradeCredits] Character %s succesful sell item for %d credits",pObj->Name,dwCost);
				SQLX.UpdateCashOffExpSystemMinusCredit(gObj->AccountID,dwCost);
				LogNotice(1,"[OffTradeCredits] Character %s succesful buy item for %d credits",gObj->Name,dwCost);
				 gObj->Money += dwCost;
			   	 pObj->Money -= dwCost;
			
				GCMoneySend(aIndex, gObj->Money);
				GCMoneySend(pObj->m_Index, pObj->Money);

	
	
	}

CGPShopReqBuyItem(lpMsg,aIndex);
}