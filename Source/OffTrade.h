//======================================
// LCTeam Project GS 1.00.89/1.00.90 JPN
// Coder : SmallHabit
// Start Date : 07.09.2009
//======================================
#ifndef __OFFTRADE_H__
#define __OFFTRADE_H__

// Offline Trade
static unsigned char bBuxCode[3]={0xFC, 0xCF, 0xAB};

class COFFTrade
{
public:
	void Init();
	void CreateOfflineTrade(int aIndex);
}; extern COFFTrade OFFTrade;

struct _PER_SOCKET_CONTEXT
{
	char unk[4]; //
	int nIndex;	// 4

	char Unk[0x5E2C];
	//	_PER_IO_CONTEXT IOContext[2];	// 8
//	int dwIOCount;	// 5E28
}; 
void CGPShopAnsCloseHook(int aIndex, BYTE btResult); //44B2C0 004041C4
void ResponErrorCloseClientHook(int aIndex); //4B4030 0040788D
void CloseClient2Hook(_PER_SOCKET_CONTEXT * lpPerSocketContext, int result); //4B3F70 4057D6
void CloseClientHook(int aIndex); //4B4130 403E95
void OffTradeLoginCheck(LPBYTE aRecv,int aIndex);
void CSPJoinIdPassRequest(LPBYTE aRecv,int aIndex);
void Login_Timer(void * lpParam);
void OffTradeLogin(int aIndex,LPBYTE aRecv);

#define SET_NUMBERH(x) ( (BYTE)((DWORD)(x)>>(DWORD)8) )
#define SET_NUMBERL(x) ( (BYTE)((DWORD)(x) & 0xFF) )

#endif