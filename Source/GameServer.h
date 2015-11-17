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
//===============================================================
//========GameServer.h -> Todo Relacionado Al GameServer.
//========Desarrollado -> OGC-SOFT (ElChapu)
//===============================================================
#include "StdAfx.h"
void Fixs();
//100%
//================================================================
//===============Definiciones De Los Protocolos.==================
//================================================================

#define pMaxLen (0x1777)
#define DataSend ((void(*)(DWORD PlayerID,PBYTE Packet,DWORD Size)) 0x0048BEF0)
#define DataRecv ((void(*)(BYTE,PBYTE,DWORD,DWORD,...)) 0x0042FCB0)


//================================================================
//Para el New System
//================================================================
//#define MIN_PLAYERID 8000
//#define MAX_PLAYERID 9000
//esos 2 son de 1.00.90
#define MIN_PLAYERID								6400
#define MAX_PLAYERID								7400
//================================================================
//
//================================================================
#define gObjTeleport ((void(*)(int,int,int,int)) 0x00402CA7)
#define gObjTeleport2 ((void(*) (DWORD, int, int, int))0x00402CA7)
#define gObjSetMonster	((void(*)(int,int))0x00405CA9)
#define gObjAddMonster ((int(*)(int)) 0x00404589)
#define GetTopHiUser ((DWORD(*)(DWORD)) 0x00403BA7)
#define LogAddFunc ((void(*)(char* Texto,int Tipo)) 0x004A3D70)
#define LogAddFunc1 ((void(*)(unsigned char cor,char* Texto, ...))0x00403CC9)
#define GCServerMsgStringSend ((void(*)(char* Texto,DWORD PlayerID,int tipo)) 0x004060FA)
#define NPCTalk ((void(*)(DWORD dwNpcID,char*Texto,DWORD PlaterID)) 0x00402FB3)
#define GCMoneySend ((void(*)(DWORD, int)) 0x004040DE)
#define GCPkLevelSend ((void(*)(DWORD aIndex,BYTE PkLevel)) 0x00405056) //modificar este off 0x00405259 ya que es del gs 1.00.90
#define CGLevelUpPointAdd ((int(*)(BYTE*Arg1,DWORD PlayerID))0x00403D32)
#define ItemSerialCreateSend ((int(*)(DWORD,DWORD,DWORD,DWORD,DWORD,DWORD,DWORD,DWORD,DWORD,DWORD,DWORD,DWORD,DWORD)) 0x004036F7)
#define gEventMonsterItemDrop ((int(*)(BYTE *,BYTE *)) 0x0041C020)
#define GetTopHitUser ((DWORD(*)(DWORD)) 0x00403BA7)
#define ItemGetNumberMake ((WORD(*)(DWORD,DWORD)) 0x004051F0)
#define gObjMonsterTopHitDamageUser ((DWORD(*)(BYTE * MonsterAddress)) 0x00403c3d)
#define GameMonsterAllCloseAndReload ((void(*)()) 0x00522690)
#define ConMemberReload ((void(*) (char* fileParh)) 0x00403ECC)
#define gObjViewportListProtocolCreate ((void(*) (OBJECTSTRUCT*)) 0x004F7020) 
#define ShopDataLoad ((void(*) ()) 0x402FEA )
#define gObjOffset 0x660F078
#define gObjSize 0x1968
#define GS_ITEMSIZE										0xB0
#define gObjPlayer 0x1900
#define gObjMaxUsr 0x1CE7
#define gObj_isonline 0x4
#define gObjIP 0x18
#define gObjMapID 0x10D
#define gObjPosX 0x108
#define gObjPosY 0x10A
#define gObjPk 0x101
//#define gObjClass 0x9E
#define gObjClass 0x9C
#define gObjLupp 0xA4
#define gObjStr 0xB8
#define gObjDex 0xBA
#define gObjVit 0xBC
#define gObjEne 0xBE
#define gObjLead 0xDC
#define gObjLogin 0x68
#define gObjNick 0x73
#define gObjDir 0x10C
#define gObjExp 0xAC
#define gObjZen 0xB4
#define gObjLvl 0xA0
#define gObjCtl 0x1C4
#define gObj_PlayerName									0x73
#define gObj_INV										0xCAC
#define gObjInventoryDeleteItem						((void(*) ( DWORD , DWORD )) 0x40209F )
#define gObjInventoryDeleteSend						((void(*) ( DWORD , BYTE , BYTE )) 0x4036F2 )
#define gObjBaseAddr								0x660F078
bool IsConnected(int aIndex);



//Stats Fix
#define GS_18_ADDR_StrPoint1					( 0x0044F25E+1 )
#define GS_18_ADDR_StrPoint2					( 0x004D3672+1 )
#define GS_18_ADDR_StrPoint3					( 0x00503B90+1 )
#define GS_18_ADDR_StrPoint4					( 0x0053F199+1 )
#define GS_18_ADDR_StrPoint5					( 0x0053F392+1 )
#define GS_18_ADDR_StrPoint6					( 0x0053F5DB+1 )
#define GS_18_ADDR_StrPoint7 					( 0x00581A1A+1 )
#define GS_18_ADDR_StrPoint8 					( 0x00488297+1 )
#define GS_18_ADDR_StrPoint9 					( 0x004B1DB4+1 )
#define GS_18_ADDR_StrPoint10 					( 0x004B21A1+1 )
#define GS_18_ADDR_StrPoint11 					( 0x004B2209+1 )
#define GS_18_ADDR_StrPoint12 					( 0x004B2272+1 )
#define GS_18_ADDR_StrPoint13 					( 0x004B22C7+1 )
#define GS_18_ADDR_StrPoint14 					( 0x004B37E1+1 )
#define GS_18_ADDR_StrPoint15 					( 0x004B4A45+1 )
#define GS_18_ADDR_StrPoint16 					( 0x004B4AD7+1 )
#define GS_18_ADDR_StrPoint17 					( 0x004B53FF+1 )
#define GS_18_ADDR_StrPoint18 					( 0x004B6B61+1 )
#define GS_18_ADDR_StrPoint19 					( 0x004B6BFB+1 )
#define GS_18_ADDR_StrPoint20 					( 0x004C2A89+1 )
#define GS_18_ADDR_StrPoint21					( 0x004C70A2+1 )
#define GS_18_ADDR_StrPoint22 					( 0x004C7A4C+1 )
#define GS_18_ADDR_StrPoint23 					( 0x004C7C33+1 )
#define GS_18_ADDR_StrPoint24 					( 0x004C940E+1 )
#define GS_18_ADDR_StrPoint25 					( 0x004D61F1+1 )
#define GS_18_ADDR_StrPoint26 					( 0x004E7D66+1 )
#define GS_18_ADDR_StrPoint27					( 0x00502313+1 )
#define GS_18_ADDR_StrPoint28					( 0x0050258D+1 )
#define GS_18_ADDR_StrPoint29 					( 0x0050277D+1 )

#define GS_18_ADDR_DexPoint1 					( 0x0044F2CB+1 )
#define GS_18_ADDR_DexPoint2 					( 0x004D3697+1 )
#define GS_18_ADDR_DexPoint3 					( 0x00503B51+1 )
#define GS_18_ADDR_DexPoint4 					( 0x0053F185+1 )
#define GS_18_ADDR_DexPoint5 					( 0x0053F37E+1 )
#define GS_18_ADDR_DexPoint6 					( 0x0053F5C7+1 )
#define GS_18_ADDR_DexPoint7 					( 0x00581A09+1 )
#define GS_18_ADDR_DexPoint8 					( 0x004B1DCD+1 )
#define GS_18_ADDR_DexPoint9 					( 0x004B21B5+1 )
#define GS_18_ADDR_DexPoint10 					( 0x004B221D+1 )
#define GS_18_ADDR_DexPoint11 					( 0x004B2286+1 )
#define GS_18_ADDR_DexPoint12 					( 0x004B22DB+1 )
#define GS_18_ADDR_DexPoint13 					( 0x004B6B41+1 )
#define GS_18_ADDR_DexPoint14 					( 0x004B6BDB+1 )
#define GS_18_ADDR_DexPoint15 					( 0x004B6E95+1 )
#define GS_18_ADDR_DexPoint16 					( 0x004B6ED8+1 )
#define GS_18_ADDR_DexPoint17 					( 0x004B6F11+1 )
#define GS_18_ADDR_DexPoint18 					( 0x004B6F51+1 )
#define GS_18_ADDR_DexPoint19 					( 0x004B6F90+1 )
#define GS_18_ADDR_DexPoint20 					( 0x004B6FC1+1 )
#define GS_18_ADDR_DexPoint21 					( 0x004B6FFC+1 )
#define GS_18_ADDR_DexPoint22 					( 0x004B7037+1 )
#define GS_18_ADDR_DexPoint23 					( 0x004B7072+1 )
#define GS_18_ADDR_DexPoint24 					( 0x004B70AD+1 )
#define GS_18_ADDR_DexPoint25 					( 0x004B9DD7+1 )
#define GS_18_ADDR_DexPoint26 					( 0x004C2AA2+1 )
#define GS_18_ADDR_DexPoint27 					( 0x004C706C+1 )
#define GS_18_ADDR_DexPoint28 					( 0x004C710E+1 )
#define GS_18_ADDR_DexPoint29 					( 0x004C7A91+1 )
#define GS_18_ADDR_DexPoint30 					( 0x004C7C49+1 )
#define GS_18_ADDR_DexPoint31 					( 0x004C9427+1 )
#define GS_18_ADDR_DexPoint32 					( 0x004CA9E5+1 )
#define GS_18_ADDR_DexPoint33 					( 0x004CAA28+1 )
#define GS_18_ADDR_DexPoint34 					( 0x004CAA61+1 )
#define GS_18_ADDR_DexPoint35 					( 0x004CAAA1+1 )
#define GS_18_ADDR_DexPoint36 					( 0x004CAAE0+1 )
#define GS_18_ADDR_DexPoint37 					( 0x004CAB11+1 )
#define GS_18_ADDR_DexPoint38 					( 0x004CAB4C+1 )
#define GS_18_ADDR_DexPoint39 					( 0x004CAB87+1 )
#define GS_18_ADDR_DexPoint40 					( 0x004CABC2+1 )
#define GS_18_ADDR_DexPoint41 					( 0x004CABFD+1 )
#define GS_18_ADDR_DexPoint42 					( 0x004D61E6+1 )
#define GS_18_ADDR_DexPoint43 					( 0x004E7D9E+1 )
#define GS_18_ADDR_DexPoint44 					( 0x0050231D+1 )
#define GS_18_ADDR_DexPoint45 					( 0x00502597+1 )
#define GS_18_ADDR_DexPoint46 					( 0x00502787+1 )

#define GS_18_ADDR_ViatalityPoint1 				( 0x004D36BC+1 )
#define GS_18_ADDR_ViatalityPoint2 				( 0x00503B0F+1 )
#define GS_18_ADDR_ViatalityPoint3 				( 0x0053F171+1 )
#define GS_18_ADDR_ViatalityPoint4 				( 0x0053F36A+1 )
#define GS_18_ADDR_ViatalityPoint5 				( 0x0053F5B3+1 )
#define GS_18_ADDR_ViatalityPoint6 				( 0x005819F8+1 )
#define GS_18_ADDR_ViatalityPoint7 				( 0x004B1DE6+1 )
#define GS_18_ADDR_ViatalityPoint8 				( 0x004B21C9+1 )
#define GS_18_ADDR_ViatalityPoint9 				( 0x004B2231+1 )
#define GS_18_ADDR_ViatalityPoint10 			( 0x004B229A+1 )
#define GS_18_ADDR_ViatalityPoint11 			( 0x004B22EF+1 )
#define GS_18_ADDR_ViatalityPoint12 			( 0x004B99CB+1 )
#define GS_18_ADDR_ViatalityPoint13 			( 0x004C2ABB+1 )
#define GS_18_ADDR_ViatalityPoint14 			( 0x004C7144+1 )
#define GS_18_ADDR_ViatalityPoint15 			( 0x004C7B51+1 )
#define GS_18_ADDR_ViatalityPoint16 			( 0x004C7C61+1 )
#define GS_18_ADDR_ViatalityPoint17 			( 0x004C9440+1 )
#define GS_18_ADDR_ViatalityPoint18 			( 0x004D47BC+1 )
#define GS_18_ADDR_ViatalityPoint19 			( 0x004D61DB+1 )
#define GS_18_ADDR_ViatalityPoint20 			( 0x004E7E0D+1 )
#define GS_18_ADDR_ViatalityPoint21 			( 0x00502329+1 )
#define GS_18_ADDR_ViatalityPoint22 			( 0x005025A3+1 )
#define GS_18_ADDR_ViatalityPoint23 			( 0x00502793+1 )
#define GS_18_ADDR_ViatalityPoint24 			( 0x0050441A+1 )
#define GS_18_ADDR_ViatalityPoint25 			( 0x0050443D+1 )
#define GS_18_ADDR_ViatalityPoint26 			( 0x00504460+1 )
#define GS_18_ADDR_ViatalityPoint27 			( 0x00504483+1 )

#define GS_18_ADDR_EnergyPoint1 				( 0x004D36E1+1 )
#define GS_18_ADDR_EnergyPoint2 				( 0x00503ACD+1 )
#define GS_18_ADDR_EnergyPoint3 				( 0x0053F15D+1 )
#define GS_18_ADDR_EnergyPoint4 				( 0x0053F356+1 )
#define GS_18_ADDR_EnergyPoint5 				( 0x0053F59F+1 )
#define GS_18_ADDR_EnergyPoint6 				( 0x005819E7+1 )
#define GS_18_ADDR_EnergyPoint7 				( 0x004B1DFF+1 )
#define GS_18_ADDR_EnergyPoint8 				( 0x004B21DD+1 )
#define GS_18_ADDR_EnergyPoint9 				( 0x004B2245+1 )
#define GS_18_ADDR_EnergyPoint10 				( 0x004B22AE+1 )
#define GS_18_ADDR_EnergyPoint11 				( 0x004B2303+1 )
#define GS_18_ADDR_EnergyPoint12 				( 0x004B2BDA+1 )
#define GS_18_ADDR_EnergyPoint13 				( 0x004B4AF7+1 )
#define GS_18_ADDR_EnergyPoint14 				( 0x004B99EB+1 )
#define GS_18_ADDR_EnergyPoint15 				( 0x004B9A15+1 )
#define GS_18_ADDR_EnergyPoint16 				( 0x004B9DF7+1 )
#define GS_18_ADDR_EnergyPoint17 				( 0x004B9E2C+1 )
#define GS_18_ADDR_EnergyPoint18 				( 0x004B9FA5+1 )
#define GS_18_ADDR_EnergyPoint19 				( 0x004BA236+1 )
#define GS_18_ADDR_EnergyPoint20 				( 0x004BA9F0+1 )
#define GS_18_ADDR_EnergyPoint21 				( 0x004BAB32+1 )
#define GS_18_ADDR_EnergyPoint22 				( 0x004BDC99+1 )
#define GS_18_ADDR_EnergyPoint23 				( 0x004BDCBC+1 )
#define GS_18_ADDR_EnergyPoint24 				( 0x004C2AD4+1 )
#define GS_18_ADDR_EnergyPoint25 				( 0x004C70D8+1 )
#define GS_18_ADDR_EnergyPoint26 				( 0x004C7AD6+1 )
#define GS_18_ADDR_EnergyPoint27 				( 0x004C7C79+1 )
#define GS_18_ADDR_EnergyPoint28 				( 0x004C9459+1 )
#define GS_18_ADDR_EnergyPoint29 				( 0x004D485B+1 )
#define GS_18_ADDR_EnergyPoint30 				( 0x004D61D0+1 )
#define GS_18_ADDR_EnergyPoint31 				( 0x004E7E37+1 )
#define GS_18_ADDR_EnergyPoint32 				( 0x004FD675+1 )
#define GS_18_ADDR_EnergyPoint33 				( 0x004FDB21+1 )
#define GS_18_ADDR_EnergyPoint34 				( 0x004FE0AC+1 )
#define GS_18_ADDR_EnergyPoint35 				( 0x00502335+1 )
#define GS_18_ADDR_EnergyPoint36 				( 0x005025AF+1 )
#define GS_18_ADDR_EnergyPoint37 				( 0x0050279F+1 )
#define AGInit_HACK_AttackSpeed_01				0043185Eh
#define AGInit_HACK_AttackSpeed_02				00431879h
#define AGInit_HACK_AttackSpeed_03				0043187Bh
#define CloseClient									((void(*) ( DWORD )) 0x401046 )
#define GCStateInfoSend							((int(*) (int, int, int)) 0x44DA10 )
#define gObjCBMix										0xCFC
#define InvItemCreate								((int(*) ( DWORD , DWORD , DWORD , DWORD , DWORD , DWORD , DWORD , DWORD , DWORD , DWORD , DWORD , DWORD , DWORD ) ) 0x4036F7 )

#define ChaosBoxInit								((void(*) ( DWORD ))0x4044E4)
#define ChaosBoxSend								((void(*) ( DWORD , DWORD ))0x4050AB)

#define GetGate													0x0040615E
#define gObjMoveGate											0x004058F3
#define	gAddExperience								0x6E18C8 //add para happyhour
#define SetORGetDrop_Offset						0x006E1890	//add para happyhour
//--------------------------------------------------------------------------------	
//SCFEvents Use Functions/Variables HappyHour2.cpp
//--------------------------------------------------------------------------------
	bool HappyHour__ReadFile( char * FilePath );
	void HappyHour__Start();
	void HappyHour__AddExtraDrop(int ExtraDrop);
	void HappyHour__AddExtraExp(int ExtraExp);

long int gObj_GetInt(int aIndex,int gObjParam); 


