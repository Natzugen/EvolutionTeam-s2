/*-------------------------------------------------------*/
/*				Project Evolution Team Season 2          */
/*   Version GS 1.00.18 & GS-CS 1.00.19 Protocol Eng     */
/*             http://evolution-team.eu                  */
/*-------------------------------------------------------*/
/*                    Code By Th3AnG3L                   */
/*             http://evolution-team.eu                  */
/*-------------------------------------------------------*/
#include "Fixs.h"
#include "Utilidades.h"
#include "Configs.h"
#include "Protocolos.h"
#include "DropItens.h"
#include "NewsSystem.h"
#include "struct.h"
#include "GameServer.h"
#include "Drops.h"
#include "Shops.h"
#include "offTrade.h"
#include "seguridad.h"
#include "HpMob.h"
#include <windows.h>
#define GS_BASE (0x401000)


int IsNews = GetPrivateProfileIntA("Settings","Evo_NewsSystem",1,NEWSISTEMFILE_PATH);
void EvoTimer();
extern "C" _declspec(dllexport) void Inicio()
{
DWORD OldProtect;
if(VirtualProtect(LPVOID(GS_BASE),3543191,PAGE_EXECUTE_READWRITE,& OldProtect))
{
Fixs(); //load fixes
//EvolutionCustoms(); //Evolution Customs
LoadIni(); //load inis
IniciaIni(); //load inis
Drop.t_LoadSystem(); //For DropSystem
NewsON(IsNews); //For NewSystem
EvoTimer(); //Reload vip
//AssemblyExcShops(); //For Exc items in Shops xD
FixMaxStats(); //max stats 65k
ReadCommonServerInfoEx();
OFFTrade.Init();

//MessageBoxA(0, "GS Powered By OGC-Files \n Version Free V.1.0.9!", "Project V 1.0", 0);
//Version Free no necesita comprabar el serial.
int Seccr;

	if(CheckMAC())
	{
		Seccr = 1;
	}

	if(!CheckMAC())
	{
		Seccr = 0;
	}

	if(Seccr == 0)::ExitProcess(0);
	//hasta aca!
// SQL Connection
SQL.InitConnection();

// Vip System
VipSystem.Init();

// Firewall
LoadIPBlock();

//Exchanger.Init();

//InitMapExplorer();

// Golden Archer
GoldenArcher.Init(GOLDERARCHFILE_PATH);

// Wheel of Fortune
Fortune.Init(FORTUNEFILE_PATH);

//GuildSystem.Init(); //Guild System

// PK Guard
//PKGuard.Init(PKGUARD_PATH);
	
// Reset Guard
//ResetGuard.Init(RESETGUARD_PATH);

//HappyHour__ReadFile(HAPPYHOUR_PATH); // HappyHour

// GameMaster System
LoadGMSystem();


_asm
{
Mov Dword Ptr Ds:[00600060H],Offset ProtocolServer
Mov Dword Ptr DS:[00600064H],Offset ProtocolClient
//ANTIHACK ATTACK SPEED
mov word  ptr ds:[AGInit_HACK_AttackSpeed_01], 9090h
mov word  ptr ds:[AGInit_HACK_AttackSpeed_02], 0C2E9h
mov dword ptr ds:[AGInit_HACK_AttackSpeed_03], 90000000h
}
HookThis((DWORD)&ProtocolCore,0x00403314);
HookThis((DWORD)&MygEventMonsterItemDrop,0x00404E4E);
HookThis((DWORD)&MonsterDropCall,0x00404E4E); // Hookeamos DropSystem

// GameServer Load/Reload Addon
		//*(DWORD*)(0x004058CB+1) = (DWORD)&EvolutionCustoms - (0x004058CB+5);
// Custom Vip System
		*(DWORD*)(0x004E2C20+1) = (DWORD)&MonsterExpSingleEx - (0x004E2C20+5);
		*(BYTE*)(0x004E2C20) = 0xE9;
		*(DWORD*)(0x004E3315+1) = (DWORD)&MonsterExpPartyEx - (0x004E3315+5);
		*(BYTE*)(0x004E3315) = 0xE9;
		// NPC Manager
		HookThis((DWORD)&gObjSetMonsterEx,0x00405CA9);
		//agregado para el fix del icono del gm
		//HookProc(0x00405c68, (DWORD)(ExternalgObjSetCharacter)); //este es para el gscs
		HookThis((DWORD)&ExternalgObjSetCharacter, 0x004057EA);
		HookThis((DWORD)&CGSellRequestRecv_Hook,0x0040723E);
		HookThis((DWORD)&CGPShopReqBuyItem_Hook,0x00406DD9);
		HookThis((DWORD)&GCDamageSend,0x0040383C);// Monster HP Bar (Fixed for gs .18)

HANDLE hTm;
hTm = CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)EvoTimer,NULL,0,0);

// Create Folders
	_mkdir("LOG");
	_mkdir("LOG_POST");
	_mkdir("LOG_GMS");
	_mkdir("LOG_RESET");

// Handlers
HANDLE Timer;
Timer = CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)Counter,NULL,0,0);
LoadIni();
}
else
{
MessageBoxA(NULL,"can not start the dll","Evolution.dll",MB_OK);
::ExitProcess(0);
}
}


