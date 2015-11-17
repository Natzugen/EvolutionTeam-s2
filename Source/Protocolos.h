/*-------------------------------------------------------*/
/*				Project Evolution Team Season 2          */
/*   Version GS 1.00.18 & GS-CS 1.00.19 Protocol Eng     */
/*             http://evolution-team.eu                  */
/*-------------------------------------------------------*/
/*                    Code By Th3AnG3L                   */
/*             http://evolution-team.eu                  */
/*-------------------------------------------------------*/
#include "StdAfx.h"
__declspec (dllexport) BYTE ProtocolServer (BYTE Tipo);
__declspec (dllexport) BYTE ProtocolClient (BYTE Tipo);
bool ProtocolCore(BYTE protoNum,LPBYTE aRecv,DWORD aLen,DWORD aIndex,DWORD Encrypt,int Serial);



struct PBMSG_HEAD2	// Packet - Byte Type
{

public:
	BYTE c;
	BYTE size;
	BYTE headcode;
	BYTE subcode;
};
struct PMSG_REQ_BUYITEM_FROM_PSHOP
{
	PBMSG_HEAD2 h;
	BYTE NumberH;	// 4
	BYTE NumberL;	// 5
	BYTE btName[10];	// 6
	BYTE btItemPos;	// 10
};


struct PMSG_SELLRESULT 
{ 
PBMSG_HEAD2 h; // C1:33 
BYTE Result; // 3 
DWORD Money; // 4 
}; 



struct PMSG_SELLREQUEST 
{ 
PBMSG_HEAD2 h; 
BYTE Pos; // 3 
BYTE Info[4]; // reedlan 
}; 



struct PMSG_ANS_PSHOP_TEXT_CHANGED
{
	PBMSG_HEAD2 h;
	BYTE NumberH;
	BYTE NumberL;
	BYTE btPShopText[36];
	BYTE btName[10];
};


struct PMSG_MAGICATTACK_RESULT
{
	PBMSG_HEAD2 h;	// C3:19
	BYTE MagicNumber;	// 3
	BYTE SourceNumberH;	// 4
	BYTE SourceNumberL;	// 5
	BYTE TargetNumberH;	// 6
	BYTE TargetNumberL;	// 7
};

struct PMSG_ATTACKRESULT
{
	PBMSG_HEAD	h; // C1:DC
	BYTE		NumberH; // 3
	BYTE		NumberL; // 4
	BYTE		DamageH; // 5
	BYTE		DamageL; // 6
	BYTE		DamageType; // 7
	BYTE		btShieldDamageH; // 8
	BYTE		btShieldDamageL; // 9
	float		Life; //A
	float		MaxLife; //E
	float		AddLife; //fix inner
};


struct PBMSG_HEADIT
{
	BYTE c;
	BYTE size;
	BYTE headcode;
};
struct PMSG_IDPASS
{
	PBMSG_HEADIT h;
	BYTE subcode;	// 3
	char Id[10];	// 4
	char Pass[10];	// E
	DWORD TickCount;	// 18
	BYTE CliVersion[5];	// 1C
	BYTE CliSerial[16];	// 21  
};

struct OFFLINETRADE{
	int IsOffTrade;

}; extern OFFLINETRADE OfflineShop[OBJECT_MAX];
//========================================================================================================================
struct OFFLINETRADELOGIN{
	int aIndex;
	LPBYTE aRecv;
}; extern OFFLINETRADELOGIN OfflineLogin[OBJECT_MAX];


void CGSellRequestRecv_Hook(PMSG_SELLREQUEST* lpMsg, int aIndex);
void CGPShopReqBuyItem_Hook(PMSG_REQ_BUYITEM_FROM_PSHOP * lpMsg, int aIndex);
void BuxConvert(char* buf, int size);
void GCCashPointH(OBJECTSTRUCT *lpObj,DWORD dwCashPoint);
void PHeadSetB(LPBYTE lpBuf, BYTE head, int size);