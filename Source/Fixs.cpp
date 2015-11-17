/*-------------------------------------------------------*/
/*				Project Evolution Team Season 2          */
/*   Version GS 1.00.18 & GS-CS 1.00.19 Protocol Eng     */
/*             http://evolution-team.eu                  */
/*-------------------------------------------------------*/
/*                    Code By Th3AnG3L                   */
/*             http://evolution-team.eu                  */
/*-------------------------------------------------------*/
#include "Utilidades.h"
#include "Fixs.h"
#include "configs.h"
#include "user.h"
#include "GameServer.h"
#include "HatcheryEvent.h"
#include "EventItemBag.h"
#include "struct.h"
#include <time.h>

void Fixs()
{
SetByte(0x0052D6DA,0xEB);
SetByte(0x0042FD6D,0xEB);

//memset((PBYTE) 0x00403DFF,0xC3,1 );		//CObjUseSkill::SpeedHackCheck (Disable)
//memset((PBYTE) 0x00403E00,0x90,4 );		//CObjUseSkill::SpeedHackCheck (Disable)
//memset((PBYTE) 0x0044A0DC,0x90,6 );		//Attack Speed Is Wrong Fix
//SetNop(0x004294B8,2);					//Max Option +28 Fix
//SetNop(0x00514EA4,2);					//Max Option +28 Fix
//SetNop(0x004D2E48,2);					//Enable Save of Jewel Options
//SetByte((0x0041A9E1+3),0x00);			//Dragon Event Jewel Durability

//=======FIX DE POTION BUG==================
SetNop(0x00429711,8);//Hp Potion Fix
SetNop(0x004D304E,8);//Mp Potion Fix
//SetByte(0x004D30EE,0xEB); //SG Potion Fix

//=======FIX DE GUILD ID==================
SetNop(0x0044521A,6); //delete guild
SetNop(0x00445370,2); //salir de guild fix no password

//=======FIX DE CHARACTER ID==============
SetByte(0x00434524,0xEB);

//==============VARIOS FIXS===============
SetRetn(0x004021E4); //CheckSum In Game
SetRetn(0x00402B9E); //DestroyGlocp
SetRetn(0x0040635C); //Error de Memoria 0x0000
SetByte(0x00431C38,0xEB);//Check Sum

//=====FIX DE ChaosCardPtobability.txt=========
SetNop(0x005264C5,29);

//===================================================================
//============EVITAR MENSAJE DE ERROR DE NO SE ENCUENTRA EL DRIVE M:\
//===================================================================

SetByte(0x0052D6DA,0xEB);


//===================================================================
//===============Prevenir Error De Socket Serial=====================
//===================================================================

SetByte(0x0042FD6D,0xEB);

//===================================================================
//=================MENSAJE DE ERROR DE ANTI-HACK=====================
//===================================================================

SetByte(0x00437E69,0xEB); //Serial 0 cuando un item es dropeado
//SetByte(0x0043D05C,0xEB); //Serial 0 Cuando un item es vendido.
//SetByte(0x004404B5,0xEB); //serial 0 en el shop personal.
//SetByte(0x0044213E,0xEB); //serial 0 cuando compra en el shop personal.
//SetByte(0x0044D391,0xEB); //serial 0 cuandp usa un item.
SetByte(0x004EA82C,0xEB); //serial 0 cuando mueve un item.
SetByte(0x004ED004,0xEB); //serial 0 en trade 1
//SetByte(0x004ED661,0xEB); //serial 0 en trade  2 //este tiene problemas en el shop personal
//SetByte(0x00437E69,0xEB); //serial 0 item (NOSE POR QUE ESTA REPETIDO !!OJO!!)
//SetByte(0x0050A99A,0xEB); //serial 0 en mescla de jewels
//SetByte(0x0050B14A,0xEB); //serial 0 Desmesclando jewels.
//SetByte(0x00431C38,0xEB); //serial 0 Check Sum.
//SetByte(0x0043185E,0xEB); //velocidad de ataque en cliente.
//SetByte(0x00431879,0xEB); //velocidad 2
//SetByte(0x0043187B,0xEB); //velocidad 3

/*SetByte(0x00437E69,0xEB);//Serial 0 When Item Drop
SetByte(0x004EA82C,0xEB);//Serial 0 When Move Item
SetByte(0x004ED004,0xEB);//serial 0 Trade 1
SetByte(0x004ED661,0xEB);//Serial 0 Trade 2
SetByte(0x00508721,0xEB);//Serial 0 Item
SetByte(0x0050A99A,0xEB);//Serial 0 Mix Jewel
SetByte(0x0050B14A,0xEB);//Serial 0 UnMix Jewel
SetByte(0x004E5FFB,0xEB);//Serial 0 When Trade Jewel 1
SetByte(0x004E624B,0xEB);//Serial 0 When Trade Jewel 2
SetByte(0x0043185E,0xEB);//Client Hack Detected : Editing AttackSpeed*/

//===================================================================
//=======Mensajes de error:[Monster Al Element] FindAiElement() Error
//===================================================================

SetByte(0x0055DF9C,0xFF); // MonsterAI Fix

//===================================================================
//===================PK BUG SIN PROBAR==NO ANDA SE CAE EL GS=========
//===================================================================

//SetByte(0x004B638A,0xEB);
      //0x004B638A
//SetByte(0x004B665C,0xEB);
      //0x004B665C
//SetByte(0x004B6687,0xEB);
      //0x004B6687



//PK FIX [CObjBaseAttack::PkCheck]
			WriteMemoryInt(AGInit_FIX_PK_01, 0xEB, 0xFF, 1);
			WriteMemoryInt(AGInit_FIX_PK_02, 0xEB, 0xFF, 1);
			WriteMemoryInt(AGInit_FIX_PK_03, 0xEB, 0xFF, 1);
//===================================================================
//=====================Potion Bug - Para SG==========================
//===================================================================

SetByte(0x004D30EE,0xEB);

//===================================================================
//==========Option +28 (Subir Items Con Jewel Of Life Hasta + 28
//===================================================================

//SetNop(0x004294B8,2);
//SetNop(0x00514EA4,2);
//SetByte(0x004FF1E7,0x7);
//SetByte(0x004D2E85,0x7);

//FIX +28
			WriteMemoryInt(AGInit_FIX_Z28_01+0, 0x90, 0xFF, 1);
			WriteMemoryInt(AGInit_FIX_Z28_01+1, 0x90, 0xFF, 1);

			WriteMemoryInt(AGInit_FIX_Z28_02+0, 0x07, 0xFF, 1);

			WriteMemoryInt(AGInit_FIX_Z28_03+0, 0x90, 0xFF, 1);
			WriteMemoryInt(AGInit_FIX_Z28_03+1, 0x90, 0xFF, 1);

			WriteMemoryInt(AGInit_FIX_Z28_04+0, 0x07, 0xFF, 1);
			
			WriteMemoryInt(AGInit_FIX_Z28_05+0, 0x90, 0xFF, 1);
			WriteMemoryInt(AGInit_FIX_Z28_05+1, 0x90, 0xFF, 1);
			//FIX +28

	//[DaRKav][March 12, 2008][ASCII "[%s][%s] User Die Item Drop, ItemName:%s"] PK ITEM DROP FIX 
			//004DECD0  |. /0F 85 1C 02 00 00 JNZ gameserv.004DEEF2
			//004DECD0     /E9 1D 02 00 00 90 JMP gameserv.004DEEF2
			*(BYTE*)(AGInit_FIX_PK_DROP+0) = 0xE9;
			*(BYTE*)(AGInit_FIX_PK_DROP+1) = 0x1D;
			*(BYTE*)(AGInit_FIX_PK_DROP+2) = 0x02;
			*(BYTE*)(AGInit_FIX_PK_DROP+3) = 0x00;
			*(BYTE*)(AGInit_FIX_PK_DROP+4) = 0x00;
			*(BYTE*)(AGInit_FIX_PK_DROP+5) = 0x90;
}
bool PartyZenFix (char * ini)
/*{
BYTE PTZenFix[] = {
0x8B,0x4D,0x0C,0x33,0xC0,0x8A,0x41,0x64,0x83,0xF8, 0x02,0x74,0x05,0x83,0xF8,0x03,
0x75,0x20,0x8B,0x91,0xB4,0x00,0x00,0x00,0x89,0x55, 0xF8,0xDB,0x45,0xF8,0xD8,0x0D,
0xC8,0x18,0x6E,0x00,0xE8,0x1C,0x55,0x0B,0x00,0x8B, 0x4D,0x0C,0x89,0x81,0xB4,0x00,
0x00,0x00,0x5F,0x5E,0x5B,0x8B,0xE5,0x5D,0xC3 } ;

if ( GetPrivateProfileInt("Party","OGC-PartyZenFix", 0,CUSTOMFILE_PATH) )
{
memcpy ( (int *) GS_PARTY_ZEN_FIX , PTZenFix , sizeof(PTZenFix) );
return 1;
}
return 0;
}*/
{
if (GetPrivateProfileInt("Party" ,"PartyZenFix",1, CUSTOMFILE_PATH)){
BYTE PartyZenFix[57] = { 
0x8B,0x4D,0x0C,0x33,0xC0,0x8A,0x41,0x64,0x83,0xF8, 0x02,0x74,0x05,0x83,0xF8,0x03,
0x75,0x20,0x8B,0x91,0xB4,0x00,0x00,0x00,0x89,0x55, 0xF8,0xDB,0x45,0xF8,0xD8,0x0D,
0xC8,0x18,0x6E,0x00,0xE8,0x1C,0x55,0x0B,0x00,0x8B, 0x4D,0x0C,0x89,0x81,0xB4,0x00,
0x00,0x00,0x5F,0x5E,0x5B,0x8B,0xE5,0x5D,0xC3 } ;

memcpy ((int *) (0x4E3437), &PartyZenFix[0], 57 ) ;
return 1;
}
return 0;
}

//PRUEBA MAX STATS A 65K
void FixMaxStats()
{
	if( GetPrivateProfileInt("Stats","MaxStats", 0,CUSTOMFILE_PATH))
	{
		//ACA HACE LOS CAMBIOS
		SetByte(GS_18_ADDR_StrPoint1,0xB7);
		SetByte(GS_18_ADDR_StrPoint2,0xB7);
		SetByte(GS_18_ADDR_StrPoint3, 0xB7) ;
		SetByte(GS_18_ADDR_StrPoint4,0xB7);
		SetByte(GS_18_ADDR_StrPoint5,0xB7);
		SetByte(GS_18_ADDR_StrPoint6,0xB7);
		SetByte(GS_18_ADDR_StrPoint7,0xB7);
		SetByte(GS_18_ADDR_StrPoint8 ,0xB7);
		SetByte(GS_18_ADDR_StrPoint9 ,0xB7);
		SetByte(GS_18_ADDR_StrPoint10 ,0xB7);
		SetByte(GS_18_ADDR_StrPoint11 ,0xB7);
		SetByte(GS_18_ADDR_StrPoint12 ,0xB7);
		SetByte(GS_18_ADDR_StrPoint13,0xB7);
		SetByte(GS_18_ADDR_StrPoint14,0xB7);
		SetByte(GS_18_ADDR_StrPoint15,0xB7);
		SetByte(GS_18_ADDR_StrPoint16 ,0xB7);
		SetByte(GS_18_ADDR_StrPoint17 ,0xB7);
		SetByte(GS_18_ADDR_StrPoint18 ,0xB7);
		SetByte(GS_18_ADDR_StrPoint19 ,0xB7);
		SetByte(GS_18_ADDR_StrPoint20 ,0xB7);
		SetByte(GS_18_ADDR_StrPoint21 ,0xB7);
		SetByte(GS_18_ADDR_StrPoint22 ,0xB7);
		SetByte(GS_18_ADDR_StrPoint23 ,0xB7);
		SetByte(GS_18_ADDR_StrPoint24 ,0xB7);
		SetByte(GS_18_ADDR_StrPoint25 ,0xB7);
		SetByte(GS_18_ADDR_StrPoint26 ,0xB7);
		SetByte(GS_18_ADDR_StrPoint27 ,0xB7);
		SetByte(GS_18_ADDR_StrPoint28 ,0xB7);
		SetByte(GS_18_ADDR_StrPoint29 ,0xB7);

		//dex 1-46
		SetByte(GS_18_ADDR_DexPoint1 ,0xB7);
		SetByte(GS_18_ADDR_DexPoint2 ,0xB7);
		SetByte(GS_18_ADDR_DexPoint3 ,0xB7);
		SetByte(GS_18_ADDR_DexPoint4 ,0xB7);
		SetByte(GS_18_ADDR_DexPoint5 ,0xB7);
		SetByte(GS_18_ADDR_DexPoint6 ,0xB7);
		SetByte(GS_18_ADDR_DexPoint7 ,0xB7);
		SetByte(GS_18_ADDR_DexPoint8 ,0xB7);
		SetByte(GS_18_ADDR_DexPoint9 ,0xB7);
		SetByte(GS_18_ADDR_DexPoint10 ,0xB7);
		SetByte(GS_18_ADDR_DexPoint11 ,0xB7);
		SetByte(GS_18_ADDR_DexPoint12 ,0xB7);
		SetByte(GS_18_ADDR_DexPoint13 ,0xB7);
		SetByte(GS_18_ADDR_DexPoint14 ,0xB7);
		SetByte(GS_18_ADDR_DexPoint15 ,0xB7);
		SetByte(GS_18_ADDR_DexPoint16 ,0xB7);
		SetByte(GS_18_ADDR_DexPoint17 ,0xB7);
		SetByte(GS_18_ADDR_DexPoint18 ,0xB7);
		SetByte(GS_18_ADDR_DexPoint19 ,0xB7);
		SetByte(GS_18_ADDR_DexPoint20 ,0xB7);
		SetByte(GS_18_ADDR_DexPoint21 ,0xB7);
		SetByte(GS_18_ADDR_DexPoint22 ,0xB7);
		SetByte(GS_18_ADDR_DexPoint23 ,0xB7);
		SetByte(GS_18_ADDR_DexPoint24 ,0xB7);
		SetByte(GS_18_ADDR_DexPoint25 ,0xB7);
		SetByte(GS_18_ADDR_DexPoint26 ,0xB7);
		SetByte(GS_18_ADDR_DexPoint27 ,0xB7);
		SetByte(GS_18_ADDR_DexPoint28 ,0xB7);
		SetByte(GS_18_ADDR_DexPoint29 ,0xB7);
		SetByte(GS_18_ADDR_DexPoint30 ,0xB7);
		SetByte(GS_18_ADDR_DexPoint31 ,0xB7);
		SetByte(GS_18_ADDR_DexPoint32 ,0xB7);
		SetByte(GS_18_ADDR_DexPoint33 ,0xB7);
		SetByte(GS_18_ADDR_DexPoint34 ,0xB7);
		SetByte(GS_18_ADDR_DexPoint35 ,0xB7);
		SetByte(GS_18_ADDR_DexPoint36 ,0xB7);
		SetByte(GS_18_ADDR_DexPoint37 ,0xB7);
		SetByte(GS_18_ADDR_DexPoint38 ,0xB7);
		SetByte(GS_18_ADDR_DexPoint39 ,0xB7);
		SetByte(GS_18_ADDR_DexPoint40 ,0xB7);
		SetByte(GS_18_ADDR_DexPoint41 ,0xB7);
		SetByte(GS_18_ADDR_DexPoint42 ,0xB7);
		SetByte(GS_18_ADDR_DexPoint43 ,0xB7);
		SetByte(GS_18_ADDR_DexPoint44 ,0xB7);
		SetByte(GS_18_ADDR_DexPoint45 ,0xB7);
		SetByte(GS_18_ADDR_DexPoint46 ,0xB7);


		//Viatality 1-27
		SetByte(GS_18_ADDR_ViatalityPoint1 ,0xB7);
		SetByte(GS_18_ADDR_ViatalityPoint2 ,0xB7);
		SetByte(GS_18_ADDR_ViatalityPoint3 ,0xB7);
		SetByte(GS_18_ADDR_ViatalityPoint4 ,0xB7);
		SetByte(GS_18_ADDR_ViatalityPoint5 ,0xB7);
		SetByte(GS_18_ADDR_ViatalityPoint6 ,0xB7);
		SetByte(GS_18_ADDR_ViatalityPoint7 ,0xB7);
		SetByte(GS_18_ADDR_ViatalityPoint8 ,0xB7);
		SetByte(GS_18_ADDR_ViatalityPoint9 ,0xB7);
		SetByte(GS_18_ADDR_ViatalityPoint10 ,0xB7);
		SetByte(GS_18_ADDR_ViatalityPoint11 ,0xB7);
		SetByte(GS_18_ADDR_ViatalityPoint12 ,0xB7);
		SetByte(GS_18_ADDR_ViatalityPoint13 ,0xB7);
		SetByte(GS_18_ADDR_ViatalityPoint14 ,0xB7);
		SetByte(GS_18_ADDR_ViatalityPoint15 ,0xB7);
		SetByte(GS_18_ADDR_ViatalityPoint16 ,0xB7);
		SetByte(GS_18_ADDR_ViatalityPoint17 ,0xB7);
		SetByte(GS_18_ADDR_ViatalityPoint18 ,0xB7);
		SetByte(GS_18_ADDR_ViatalityPoint19 ,0xB7);
		SetByte(GS_18_ADDR_ViatalityPoint20 ,0xB7);
		SetByte(GS_18_ADDR_ViatalityPoint21 ,0xB7);
		SetByte(GS_18_ADDR_ViatalityPoint22 ,0xB7);
		SetByte(GS_18_ADDR_ViatalityPoint23 ,0xB7);
		SetByte(GS_18_ADDR_ViatalityPoint24 ,0xB7);
		SetByte(GS_18_ADDR_ViatalityPoint25 ,0xB7);
		SetByte(GS_18_ADDR_ViatalityPoint26 ,0xB7);
		SetByte(GS_18_ADDR_ViatalityPoint27 ,0xB7);


		//Energy 1-37
		SetByte(GS_18_ADDR_EnergyPoint1 ,0xB7);
		SetByte(GS_18_ADDR_EnergyPoint2 ,0xB7);
		SetByte(GS_18_ADDR_EnergyPoint3 ,0xB7);
		SetByte(GS_18_ADDR_EnergyPoint4 ,0xB7);
		SetByte(GS_18_ADDR_EnergyPoint5 ,0xB7);
		SetByte(GS_18_ADDR_EnergyPoint6 ,0xB7);
		SetByte(GS_18_ADDR_EnergyPoint7 ,0xB7);
		SetByte(GS_18_ADDR_EnergyPoint8 ,0xB7);
		SetByte(GS_18_ADDR_EnergyPoint9 ,0xB7);
		SetByte(GS_18_ADDR_EnergyPoint10 ,0xB7);
		SetByte(GS_18_ADDR_EnergyPoint11 ,0xB7);
		SetByte(GS_18_ADDR_EnergyPoint12 ,0xB7);
		SetByte(GS_18_ADDR_EnergyPoint13 ,0xB7);
		SetByte(GS_18_ADDR_EnergyPoint14 ,0xB7);
		SetByte(GS_18_ADDR_EnergyPoint15 ,0xB7);
		SetByte(GS_18_ADDR_EnergyPoint16 ,0xB7);
		SetByte(GS_18_ADDR_EnergyPoint17 ,0xB7);
		SetByte(GS_18_ADDR_EnergyPoint18 ,0xB7);
		SetByte(GS_18_ADDR_EnergyPoint19 ,0xB7);
		SetByte(GS_18_ADDR_EnergyPoint20 ,0xB7);
		SetByte(GS_18_ADDR_EnergyPoint21 ,0xB7);
		SetByte(GS_18_ADDR_EnergyPoint22 ,0xB7);
		SetByte(GS_18_ADDR_EnergyPoint23 ,0xB7);
		SetByte(GS_18_ADDR_EnergyPoint24 ,0xB7);
		SetByte(GS_18_ADDR_EnergyPoint25 ,0xB7);
		SetByte(GS_18_ADDR_EnergyPoint26 ,0xB7);
		SetByte(GS_18_ADDR_EnergyPoint27 ,0xB7);
		SetByte(GS_18_ADDR_EnergyPoint28 ,0xB7);
		SetByte(GS_18_ADDR_EnergyPoint29 ,0xB7);
		SetByte(GS_18_ADDR_EnergyPoint30 ,0xB7);
		SetByte(GS_18_ADDR_EnergyPoint31 ,0xB7);
		SetByte(GS_18_ADDR_EnergyPoint32 ,0xB7);
		SetByte(GS_18_ADDR_EnergyPoint33 ,0xB7);
		SetByte(GS_18_ADDR_EnergyPoint34 ,0xB7);
		SetByte(GS_18_ADDR_EnergyPoint35 ,0xB7);
		SetByte(GS_18_ADDR_EnergyPoint36 ,0xB7);
		SetByte(GS_18_ADDR_EnergyPoint37 ,0xB7);
		return;
	}
	}
//hasta aca
//prueba
bool CN(DWORD aIndex)
{
	int Connect = GetPrivateProfileInt("GameServerInfo","ConnectNoticeYes",1,CUSTOMFILE_PATH);
 if(Connect == 1)
	{
	OBJECTSTRUCT *gObj = (OBJECTSTRUCT*)OBJECT_POINTER(aIndex);

		GetPrivateProfileStringA("GameServerInfo","ConnectNotice","%s Welcome to Evolution Team Season 2",ConnectNotice,200,CUSTOMFILE_PATH);
		char msg[200];
		sprintf_s(msg,ConnectNotice,gObj->Name);
		GCServerMsgStringSend(msg,aIndex,0);
		}
 return true;
		}

bool CNGM(DWORD aIndex)
{
	int Connect = GetPrivateProfileInt("GameServerInfo","ConnectNoticeGMS",1,CUSTOMFILE_PATH);
 if(Connect == 1)
	{
	OBJECTSTRUCT *gObj = (OBJECTSTRUCT*)OBJECT_POINTER(aIndex);

		GetPrivateProfileStringA("GameServerInfo","ConnectGM","[GM] GameMaster %s has Connected!",ConnectNotice2,200,CUSTOMFILE_PATH);
		char Message[255];
		if(gObj->Authority == 32){
		sprintf_s(Message,ConnectNotice2,gObj->Name);
		StringSendAll(Message,0);
		LogGM(Message);
		}
 return true;
		}
 return 0;
}

//fix icono del gm
BOOL  ExternalgObjSetCharacter(LPBYTE lpdata, int aIndex)
{ 
	OBJECTSTRUCT *gObj = (OBJECTSTRUCT*)OBJECT_POINTER(aIndex);
	BOOL ret = gObjSetCharacter ( lpdata, aIndex );
	if ((gObj->Authority & 8) == 8 || 
		(gObj->Authority & 32) == 32 ||
		(gObj->Authority & 2) == 2)
	{
		gObj->m_ViewSkillState |= 0x1000000;
		GCStateInfoSend(aIndex, 1, gObj->m_ViewSkillState);
	}
	return ret;
}
//=================================================
//For connectmember
//=================================================
void EvoTimer()
{
if(configs.cmember.active)
{
if(configs.cmember.pasttime == configs.cmember.time*60)
{
ConMemberReload("..\\data\\ConnectMember.txt");
configs.cmember.pasttime = 0;
}
else
{
configs.cmember.pasttime++;
}
}

Sleep(1000);
}

// Common Timer
void Counter()
{
	SYSTEMTIME LocalTime;
	GetLocalTime(&LocalTime);

	int WinDay = MuDB.GetFortuneWinDay();

	if(WinDay != LocalTime.wDay)
	{
		MuDB.ResetFortune();
	}
	
	Sleep(3600000);
	Counter();
}

// GameServer Load Addon
void ReadCommonServerInfoEx()
{
	// Chaos Machine
	//ChaosMachine.Init();

	// Stone Exchanger
	Exchanger.Init();
	//OffTrade.Init();

	// Hatchery Event Drop
	/*if (HatcheryDrop != NULL)
	{
		delete HatcheryDrop;
	}

	HatcheryDrop = new CEventItemBag; 
	if (HatcheryDrop == NULL)
	{
		MessageBoxA(0,"Memory allocation error","Error",MB_OK);
		return;
	} */

	//HatcheryDrop->Init("..\\EData\\Events\\EHatcheryEvent.txt");
	// Guild System
	//GuildSystem.Init();
	//HatcheryEvent.Init("..\\EData\\Events\\HatcheryEvent.dat");
	//EventManagement.Init("..\\data\\EventManagement.dat");
}