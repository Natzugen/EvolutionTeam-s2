/*-------------------------------------------------------*/
/*				Project Evolution Team Season 2          */
/*   Version GS 1.00.18 & GS-CS 1.00.19 Protocol Eng     */
/*             http://evolution-team.eu                  */
/*-------------------------------------------------------*/
/*                    Code By Th3AnG3L                   */
/*             http://evolution-team.eu                  */
/*-------------------------------------------------------*/
#pragma once
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <iostream>
#include <time.h>
#include <conio.h>
#include <stdio.h>
#include <tchar.h>
#include <math.h>
#include <stdlib.h>
#include <rpc.h> //protecion
#include <rpcdce.h> //protecion
#include <process.h> //protecion
// SQL Header Files
#include <sql.h>
#include <sqlext.h>
#include "CQuery.h"
#include "CMuOnline.h"
#include "VipSystem.h"
#include "user.h"
#include "Utilidades.h"
#include "ResetGuard.h"
#include "Global.h"
#include "ReadScript.h"
#include "NPC.h"
#include "GameServer.h"
#include "Firewall.h"
#include "GoldenArcher.h"
#include "FortuneWheel.h"
#include "GMSystem.h"
#include "Mapping.h"
#include <direct.h>
#include <fstream> 
//#include <strsafe.h>
#include <vector> 
#include "ChaosMachine.h"
#include "Chash.h"
#include "GuildSystem.h"
#include "StoneExchanger.h"
#include "CustomJewels.h"
#include "HatcheryEvent.h"
#include "EventManager.h"
#include "EventItemBag.h"
#include "Structures.h"
#include "OffTrade.h"
#include "HpMob.h"
using namespace std;
#include <winsock2.h>
#pragma comment(lib,"ws2_32.lib")
#pragma comment(lib,"rpcrt4.lib") //protecion


static HMENU MyMenu;
static DWORD OldProtect;
static UINT_PTR MyMenuTimerID;
static UINT_PTR cPluginsTimer;

static HWND cWND;
static HINSTANCE hlnst;

#pragma warning(disable : 4010)
#pragma warning(disable : 4101)
#pragma warning(disable : 4311)
#pragma warning(disable : 4312)
#pragma warning(disable : 4482)
#pragma warning(disable : 4700)
#pragma warning(disable : 4996)
#pragma warning(disable: 4018 4244 4717 4805 4995 4996)
//typedef BYTE OBJECTSTRUCT;


typedef enum{
Preto = 1,
Vermelho = 2,
Verde = 3,
Azul = 4,
Vermelho2 = 5,
Azul2 = 6,
Rosa = 7
}LogColors;

// Local Path Headers


#define EVENTSFILE_PATH "..\\OGCFiles\\OGC-EventsReward.ini"





#define PKGUARDFILE_PATH "..\\OGCFiles\\OGC-PKGuard.ini"
#define RESETGUARDFILE_PATH "..\\OGCFiles\\OGC-ResetGuard.ini"





#define COMMONFILE_PATH "..\\Data\\CommonServer.cfg"

//New
#define NEWSISTEMFILE_PATH "..\\EData\\ENews.ini"
#define VIPFILE_PATH "..\\EData\\EVipSystem.ini"
#define SQLFILE_PATH "..\\EData\\ESQL.ini"
#define CUSTOMFILE_PATH "..\\EData\\ECommon.ini"
#define NPCFILE_PATH "..\\EData\\ENPC.ini"
#define TRANSFORM_RINGS_PATH "..\\EData\\ERings.ini"
#define SUMMON_ORB_PATH "..\\EData\\EOrbs.ini"
#define JEWELPRICES_PATH "..\\EData\\EPrices.ini"
#define CHAOSCASTLE_REWARDS_PATH "..\\EData\\Events\\EChaosCastle.ini"
#define JEWELS_SUCC_PATH "..\\EData\\EJewels.ini"
#define BLOODCASTLE_REWARDS_PATH "..\\EData\\Events\\EBloodCastle.ini"
#define REDDRAGON_REWARDS_PATH "..\\EData\\Events\\ERedDragon.ini"
#define WHITEWIZZARD_REWARDS_PATH "..\\EData\\Events\\EWhiteWizzard.ini"
#define DLPETS_PATH "..\\EData\\EPets.ini"
#define LEVELUP_POINTS_PATH "..\\EData\\EPoints.ini"
#define SKILLS_CHARS_PATH "..\\EData\\ESkills.ini"
#define CHAOS_MIXES_PATH "..\\EData\\EChaosMix.ini"
#define MENSAJESFILE_PATH "..\\EData\\EMessages.ini"
#define COMMANDFILE_PATH  "..\\EData\\ECommands.ini"
#define HAPPYHOUR_PATH "..\\EData\\Events\\EHappyHour.ini"
#define RESETGUARD_PATH "..\\EData\\EResetGuard.ini"
#define PKGUARD_PATH "..\\EData\\EPKGuard.ini"
#define GUILDSYSTEM_PATH "..\\EData\\EGuildSystem.ini"
#define FORTUNEFILE_PATH "..\\EData\\EFortuneWheel.ini"
#define BANIPFILE_PATH "..\\EData\\EIPBan.ini"
#define ITEMDROPFILE_PATH "..\\EData\\EItemDropRate.ini"
#define GMSISTEMFILE_PATH "..\\EData\\EGMSystem.ini"
#define GOLDERARCHFILE_PATH "..\\EData\\EGoldenArcher.ini"
#define NPCSTONEEXCHANGER_PATH "..\\EData\\EStoneExchanger.ini"
#define OFFTRADER_PATH "..\\EData\\EOffTrade.ini"