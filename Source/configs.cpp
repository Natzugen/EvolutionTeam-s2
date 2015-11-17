/*-------------------------------------------------------*/
/*				Project Evolution Team Season 2          */
/*   Version GS 1.00.18 & GS-CS 1.00.19 Protocol Eng     */
/*             http://evolution-team.eu                  */
/*-------------------------------------------------------*/
/*                    Code By Th3AnG3L                   */
/*             http://evolution-team.eu                  */
/*-------------------------------------------------------*/
#include "Offset.h"
#include "Global.h"
#include "struct.h"
#include <string.h>
#include <windows.h>
#include "user.h"

void LoadIni()
{


SMDfile = fopen(CUSTOMFILE_PATH,"rb");
if (SMDfile!=0)
{
fclose(SMDfile);
GetPrivateProfileString("GameServerInfo","ConnectNotice","%s Welcome to Evolution Team S2",ConnectNotice,200,CUSTOMFILE_PATH);
}
else
{
	char msg[400];
sprintf(msg, "%s was not found and cant start GameServer",CUSTOMFILE_PATH);
MessageBox(NULL,msg,"Evolution.dll",NULL);
	::ExitProcess(0);
}
}


/////////////////////////////////////////////////////////////////
//Message NPC Guard											   //
/////////////////////////////////////////////////////////////////
bool NPCTalk1 ( char * ini )
{
	char npc[50];
	DWORD *offset = (DWORD*)(0x006B3D10);
	GetPrivateProfileString("GameServerInfo","GuardSay","Evolution Team",npc,50,ini);
	
	memset(&offset[0],0,50);
	memcpy(&offset[0],npc,strlen(npc));
	int Is15Item = GetPrivateProfileIntA("Items","EnableItem+15",0,CUSTOMFILE_PATH);
	int Item14Rate = GetPrivateProfileIntA("Rates","ItemCBMix14",90,CUSTOMFILE_PATH);
	int Item15Rate = GetPrivateProfileIntA("Rates","ItemCBMix15",90,CUSTOMFILE_PATH);
	return 1;
}

/////////////////////////////////////////////////////////////////
//Name Server       										   //
/////////////////////////////////////////////////////////////////
bool GameServer(char*ini)
{
	char tmp[500];
	DWORD*offset=(DWORD*)(0x006BF098); //ACTUALIZAR EL OFFSET
	GetPrivateProfileString("GSBara","GSTitle","[ Evolution S2 ]",tmp,25,ini);
	memset(&offset[0],0,18);
	memcpy(&offset[0],tmp,strlen(tmp));
	
	return 1;
}

//=================================================================
//====================ANILLOS DE TRANSFORMACION====================
//=================================================================

bool TransformRing ( char * ini)
{
DWORD Ring;
Ring = GetPrivateProfileInt("Rings","Transform_Ring1",2,ini);
*(unsigned int*) GS_RING1 = Ring;
Ring = GetPrivateProfileInt("Rings","Transform_Ring2",7,ini);
*(unsigned int*) GS_RING2 = Ring;
Ring = GetPrivateProfileInt("Rings","Transform_Ring3",14,ini);
*(unsigned int*) GS_RING3 = Ring;
Ring = GetPrivateProfileInt("Rings","Transform_Ring4",8,ini);
*(unsigned int*) GS_RING4 = Ring;
Ring = GetPrivateProfileInt("Rings","Transform_Ring5",9,ini);
*(unsigned int*) GS_RING5 = Ring;
Ring = GetPrivateProfileInt("Rings","Transform_Ring6",41,ini);
*(unsigned int*) GS_RING6 = Ring;
return 1;
}
//========HASTA ACA LOS ANILLOS=====================================

//======================================================
//================Orbs Of Summon - Elfs=================
//======================================================

bool OrbSummon ( char * ini)
{

BYTE Orb;
Orb = GetPrivateProfileInt("Summon","Summon_Orb0",26,ini);
*(unsigned char*) GS_ORB0 = Orb;
Orb = GetPrivateProfileInt("Summon","Summon_Orb1",32,ini);
*(unsigned char*) GS_ORB1 = Orb;
Orb = GetPrivateProfileInt("Summon","Summon_Orb2",21,ini);
*(unsigned char*) GS_ORB2 = Orb;
Orb = GetPrivateProfileInt("Summon","Summon_Orb3",20,ini);
*(unsigned char*) GS_ORB3 = Orb;
Orb = GetPrivateProfileInt("Summon","Summon_Orb4",10,ini);
*(unsigned char*) GS_ORB4 = Orb;
Orb = GetPrivateProfileInt("Summon","Summon_Orb5",150,ini);
*(unsigned char*) GS_ORB5 = Orb;
Orb = GetPrivateProfileInt("Summon","Summon_Orb6",151,ini);
*(unsigned char*) GS_ORB6 = Orb;

return 1;

}
//=========HASTA ACA LOS ORBS DE ELF======================

//===================================================
//=============PRECIOS JAWELS========================
//===================================================

bool JewelPrice ( char * ini )
{
DWORD zen;
zen = GetPrivateProfileInt("JewelPrices","Bless_Price",6000000,ini);
*(unsigned int*) GS_BLESS_PRICE = zen ;
zen = GetPrivateProfileInt("JewelPrices","Soul_Price",9000000,ini);
*(unsigned int*) GS_SOUL_PRICE = zen ;
zen = GetPrivateProfileInt("JewelPrices","Chaos_Price",810000,ini);
*(unsigned int*) GS_CHAOS_PRICE = zen ;
zen = GetPrivateProfileInt("JewelPrices","Life_Price",45000000,ini);
*(unsigned int*) GS_LIFE_PRICE = zen ;
zen = GetPrivateProfileInt("JewelPrices","Creation_Price",36000000,ini);
*(unsigned int*) GS_CREATION_PRICE = zen ;
zen = GetPrivateProfileInt("JewelPrices","Guardian_Price",60000000,ini);
*(unsigned int*) GS_GUARDIAN_PRICE = zen ;
return 1;
}
//====================HASTA ACA LOS JEWELS==============================

//============================================
//=====JUGADORES PARA EL CHAOS CLASTLE========
//============================================

bool CCPlayer ( char * ini )
{
BYTE CC1;
//DWORD CC1;
CC1 = GetPrivateProfileInt("Customs","ChaosCastleMinPlayers",2,ini);
*(unsigned char*) GS_CCPlayer = CC1;

	BYTE RewardType,RewardID;
	DWORD Code;

	RewardType = GetPrivateProfileInt("ChaosCastle","Reward1Type",14,CHAOSCASTLE_REWARDS_PATH);
	RewardID = GetPrivateProfileInt("ChaosCastle","Reward1ItemID",14,CHAOSCASTLE_REWARDS_PATH);
	Code = DWORD((RewardType * 512) + RewardID);
	*(unsigned int*) GS_CCREWARD1 = Code;

	RewardType = GetPrivateProfileInt("ChaosCastle","Reward2Type",14,CHAOSCASTLE_REWARDS_PATH);
	RewardID = GetPrivateProfileInt("ChaosCastle","Reward2ItemID",22,CHAOSCASTLE_REWARDS_PATH);
	Code = DWORD((RewardType * 512) + RewardID);
	*(unsigned int*) GS_CCREWARD2 = Code;

	RewardType = GetPrivateProfileInt("ChaosCastle","Reward3Type",14,CHAOSCASTLE_REWARDS_PATH);
	RewardID = GetPrivateProfileInt("ChaosCastle","Reward3ItemID",13,CHAOSCASTLE_REWARDS_PATH);
	Code = DWORD((RewardType * 512) + RewardID);
	*(unsigned int*) GS_CCREWARD3 = Code;

	RewardType = GetPrivateProfileInt("ChaosCastle","Reward4Type",14,CHAOSCASTLE_REWARDS_PATH);
	RewardID = GetPrivateProfileInt("ChaosCastle","Reward4ItemID",16,CHAOSCASTLE_REWARDS_PATH);
	Code = DWORD((RewardType * 512) + RewardID);
	*(unsigned int*) GS_CCREWARD4 = Code;
return 1 ;
}

//===============HASTA ACA EL CC PLAYER=======================================

//===========================================
//=============Elf Soldier===================
//===========================================

bool ElfSoldier ( char * ini )
{
DWORD Elf;
BYTE Amount;

Elf = GetPrivateProfileInt("Customs","ElfSoldier_MaxLevel",100,ini);
*(unsigned int*) GS_Elf_Soldier = Elf;

Amount = GetPrivateProfileInt("Customs","ElfBufferDefenseFormula",50,ini);
*(unsigned char*) GS_BUFFERDEFENSEFORMULA = Amount;

Amount = GetPrivateProfileInt("Customs","ElfBufferAttackFormula",45,ini);
*(unsigned char*) GS_BUFFERATTACKFORMULA = Amount;

return 1;
}

void GSCheckSum(char* File)
{
	if(GetPrivateProfileInt("GameServerInfo","EnableGSCheckSum",0,CUSTOMFILE_PATH))
	{
		#if(GS_CASTLE)
		SetByte(0x00434BF8,0x74);
		#else
		SetByte(0x00431C38,0x74);
		#endif	
	}
}

void PersonalID(char* File)
{
	if(GetPrivateProfileInt("GameServerInfo","DisablePersonalID",0,CUSTOMFILE_PATH))
	{
		#if(GS_CASTLE)
		SetByte(0x004374E4,0xEB); // Delete Character
		SetNop(0x0044837D,2); // Leave Guild
		SetNop(0x004481CC,6); // Delete Guild
		#else
		SetByte(0x00434524,0xEB); // Delete Character
		SetNop(0x00445370,2); // Leave Guild
		SetNop(0x0044521A,6); // Delete Guild
		#endif
		
	}
}

//==========================================
//==============Guild Alianzas==============
//==========================================

bool GuildAlliance ( char * ini )
{
BYTE Alliance;
Alliance = GetPrivateProfileInt("Customs","GuildAlliance",20,ini);
*(unsigned char*) GS_GuildAlliance = Alliance;
return 1;
}

//==========================================
//================PUERTO GS=================
//==========================================

bool UDPort ( char * ini )
{
DWORD Port;
Port = GetPrivateProfileInt("GameServerInfo","UDP_Port",60006,ini);
*(unsigned int*) GS_UDP_PORT = Port;
return 1;
}

//==========================================
//================RATE DE JEWELS============
//==========================================

bool JewelRate ( char * ini )
{
BYTE Jewel2;
Jewel2 = GetPrivateProfileInt("Jewels","SoulSucces",55,ini);
*(unsigned char*) GS_SOUL_RATE = Jewel2;
Jewel2 = GetPrivateProfileInt("Jewels","SoulLuckSucces",70,ini);
*(unsigned char*) GS_SOUL_LUCK_RATE = Jewel2;
Jewel2 = GetPrivateProfileInt("Jewels","LifeSucces",50,ini);
*(unsigned char*) GS_LIFE_RATE = Jewel2;
return 1;
}

//==========================================
//==============PREMIO BC===================
//==========================================

bool BcDropIni ( char * ini )
{

BYTE Reward;

	//Reward = GetPrivateProfileInt("BloodCastle","OGC_RewardType",12,EVENTSFILE_PATH);
	//*(unsigned char*) GS_BCREWARDTYPE  = Reward;

	//Reward = GetPrivateProfileInt("BloodCastle","OGC_RewardItemID",15,EVENTSFILE_PATH);
	//*(unsigned char*) GS_BCREWARDITEMID  = Reward;
	//New
	Reward = GetPrivateProfileInt("BloodCastle","RewardItemID",15,BLOODCASTLE_REWARDS_PATH);
	*(unsigned char*) GS_18_ADDR_BCRewardID  = Reward;

	Reward = GetPrivateProfileInt("BloodCastle","RewardType",15,BLOODCASTLE_REWARDS_PATH);
	*(unsigned char*) GS_18_ADDR_BCRewardType  = Reward;

	Reward = GetPrivateProfileInt("BloodCastle","RewardOpt1",15,BLOODCASTLE_REWARDS_PATH);
	*(unsigned char*) GS_18_ADDR_BCRewardOpt1  = Reward;

	Reward = GetPrivateProfileInt("BloodCastle","RewardOpt2",15,BLOODCASTLE_REWARDS_PATH);
	*(unsigned char*) GS_18_ADDR_BCRewardOpt2  = Reward;

	Reward = GetPrivateProfileInt("BloodCastle","RewardOpt3",15,BLOODCASTLE_REWARDS_PATH);
	*(unsigned char*) GS_18_ADDR_BCRewardOpt3  = Reward;

	Reward = GetPrivateProfileInt("BloodCastle","RewardOpt4",15,BLOODCASTLE_REWARDS_PATH);
	*(unsigned char*) GS_18_ADDR_BCRewardOpt4  = Reward;

	Reward = GetPrivateProfileInt("BloodCastle","RewardOpt5",15,BLOODCASTLE_REWARDS_PATH);
	*(unsigned char*) GS_18_ADDR_BCRewardOpt5  = Reward;
return 1;
}

//=========================================
//==========RED DRAGON=====================
//=========================================
bool RedDragon (char * ini)
{
	BYTE Reward;

	Reward = GetPrivateProfileInt("RedDragon","Reward1Type",14,REDDRAGON_REWARDS_PATH);
	*(BYTE*) GS_REDDRAGONREWARDTYPE1 = BYTE(Reward);

	Reward = GetPrivateProfileInt("RedDragon","Reward1ItemID",13,REDDRAGON_REWARDS_PATH);
	*(BYTE*) GS_REDDRAGONREWARDID1 = BYTE(Reward);

	Reward = GetPrivateProfileInt("RedDragon","Reward2Type",14,REDDRAGON_REWARDS_PATH);
	*(BYTE*) GS_REDDRAGONREWARDTYPE2 = BYTE(Reward);

	Reward = GetPrivateProfileInt("RedDragon","Reward2ItemID",14,REDDRAGON_REWARDS_PATH);
	*(BYTE*) GS_REDDRAGONREWARDID2 = BYTE(Reward);
	return 1;
}

//=========================================
//============WHITE WIZARD=================
//=========================================
bool WhiteWizard(char* File)
{
	BYTE Reward;

	Reward = GetPrivateProfileInt("WhiteWizard","RewardType",13,WHITEWIZZARD_REWARDS_PATH);
	*(BYTE*) GS_WHITEWIZREWARDTYPE = BYTE(Reward);

	Reward = GetPrivateProfileInt("WhiteWizard","RewardItemID",20,WHITEWIZZARD_REWARDS_PATH);
	*(BYTE*) GS_WHITEWIZREWARDID = BYTE(Reward);
	return 1;
}
//==========================================
//==============LEVEL MAXIMO================
//==========================================

bool MaxLevelIni ( char * ini )
{
DWORD Level;
Level = GetPrivateProfileInt("GameServerInfo","Max_Level",400,ini);
*(unsigned int*) GS_MAX_LEVEL1 = Level;
*(unsigned int*) GS_MAX_LEVEL2 = Level;
*(unsigned int*) GS_MAX_LEVEL3 = Level;
*(unsigned int*) GS_MAX_LEVEL4 = Level;
*(unsigned int*) GS_MAX_LEVEL5 = Level;
return 1;
}

//==========================================
//===============DL PETS====================
//==========================================

bool DarkHorseSuccesso ( char * ini )
{
DWORD dHorse;
dHorse = GetPrivateProfileInt("DLPets","DarkHorseMix",60,ini);
*(unsigned int*) GS_DARK_HORSE = dHorse;
dHorse = GetPrivateProfileInt("DLPets","DarkHorsePrice",5000000,ini);
*(unsigned int*) GS_DARK_HORSE_PRICE = dHorse;

DWORD Durability;

	Durability = GetPrivateProfileInt("DLPets","DarkRavenEndurance",800,ini);
	*(unsigned int*) GS_DARKRAVENDURABILITY = Durability;
return 1;
}

bool DarkSpiritSuccesso ( char * ini )
{
DWORD dSpirit;
dSpirit = GetPrivateProfileInt("DLPets","DarkSpiritMix",60,ini);
*(unsigned int*) GS_DARK_SPIRIT = dSpirit;
dSpirit = GetPrivateProfileInt("DLPets","DarkSpiritPrice",1000000,ini);
*(unsigned int*) GS_DARK_SPIRIT_PRICE = dSpirit;
return 1;
}

//============================================
//==========DROP ITEMS========================
//============================================

bool ItemDropIni ( char * ini )
{
DWORD Item;
Item = (100 - GetPrivateProfileInt("DropItems","ItemExc",20,ini)) * 20 + 2;
*(unsigned int*) GS_EXC_DROP_RATE = Item;
Item = GetPrivateProfileInt("DropItems","ItemExcSkill",100,ini);
*(unsigned int*) GS_EXC_SKILL_RATE = Item;
Item = GetPrivateProfileInt("DropItems","ItemExcLuck",1,ini);
*(unsigned int*) GS_EXC_LUCK_RATE = Item;
Item = GetPrivateProfileInt("DropItems","ItemNormalSkill",6,ini);
*(unsigned int*) GS_SKILL_RATE = Item;
Item = GetPrivateProfileInt("DropItems","ItemNormalLuck",4,ini);
*(unsigned int*) GS_LUCK_RATE = Item;
return 1;
}


//============================================
//=============PUNTOS POR LEVEL===============
//============================================

bool LevelUp ( char * ini )
{

BYTE GenPoints = GetPrivateProfileInt("LevelUpPoints","Points_BK_ME_SM",5,ini);
	*(unsigned char*) GS_GENPOINTS1 = GenPoints; // Normal
	*(unsigned char*) GS_GENPOINTS2 = GenPoints; // Blood Castle
	*(unsigned char*) GS_GENPOINTS3 = GenPoints; // Chaos Castle
	*(unsigned char*) GS_GENPOINTS4 = GenPoints; // Crywolf

	BYTE MGPoints = GetPrivateProfileInt("LevelUpPoints","Points_MG",7,ini);
	*(unsigned char*) GS_MGPOINTS1 = MGPoints; // Normal
	*(unsigned char*) GS_MGPOINTS2 = MGPoints; // Blood Castle
	*(unsigned char*) GS_MGPOINTS3 = MGPoints; // Chaos Castle
	*(unsigned char*) GS_MGPOINTS4 = MGPoints; // Crywolf

	BYTE DLPoints = GetPrivateProfileInt("LevelUpPoints","Points_DL",7,ini);
	*(unsigned char*) GS_DLPOINTS1 = DLPoints; // Normal
	*(unsigned char*) GS_DLPOINTS2 = DLPoints; // Blood Castle
	*(unsigned char*) GS_DLPOINTS3 = DLPoints; // Chaos Castle
	*(unsigned char*) GS_DLPOINTS4 = DLPoints; // Crywolf

	BYTE MarlonPoints = GetPrivateProfileInt("LevelUpPoints","MarlonExtraPoints",1,ini);
	*(unsigned char*) GS_MARLONPOINTS1 = MarlonPoints; // Normal
	*(unsigned char*) GS_MARLONPOINTS2 = MarlonPoints; // Blood Castle
	*(unsigned char*) GS_MARLONPOINTS3 = MarlonPoints; // Chaos Castle
	*(unsigned char*) GS_MARLONPOINTS4 = MarlonPoints; // Crywolf
return 1;
}


//============================================
//===============ZEN MAXIMO===================
//============================================

bool MaxZen ( char * ini )
{
	DWORD Money;

	Money = GetPrivateProfileInt("Customs","MAX_ZenInventory",2000000000,ini);
	*(unsigned int*) GS_MAX_INVENTORY = Money;

	Money = GetPrivateProfileInt("Customs","MAX_ZenVault",100000000,ini);
	*(unsigned int*) GS_MAX_VAULT1 = Money;
	*(unsigned int*) GS_MAX_VAULT2 = Money;
	*(unsigned int*) GS_MAX_VAULT3 = Money;
return 1;
}

//=============================================
//==================LEVEL maximo Exp===========
//=============================================

bool MaxLevel2 ( char * ini )
{
BYTE maxlvl2;
maxlvl2 = GetPrivateProfileInt("GameServerInfo","LevelNoEXP",400,ini);
*(unsigned char*) GS_MaxLevel2 = maxlvl2;
return 1;
}

//==================================================
//Mana Shield
//==================================================
bool DwSoulBarrierInit ( char * ini)
{
	DWORD Amount;

	Amount = GetPrivateProfileInt("ManaShield","ManaShieldAgility",50,ini);
	*(unsigned int*) GS_MANASHIELDA = Amount;
	//formula de agilidad
	//65k (65000 / 50 = 1300) que seria el Valor en 1300

	Amount = GetPrivateProfileInt("ManaShield","ManaShieldEnergy",200,ini);
	*(unsigned int*) GS_MANASHIELDB = Amount;
	//formula de la Energia.
	//65k (65000 / 50 = 1300) que seria el valor en 1300

	Amount = GetPrivateProfileInt("ManaShield","ManaShieldDivider",40,ini); //los segundos que dura el mana ver como hacer la formula
	*(unsigned int*) GS_MANASHIELDC = Amount;
	DWORD dwTmp ;


	return 1;
}

//=================================================
// reflect
//=================================================
bool ReflectInit ( char * ini)
{
	DWORD Amount;
//prueba del damege reflect
	Amount = GetPrivateProfileInt("Reflect","DamageRefDiv1",42,ini);
	*(unsigned int*) GS_DAMAGEREF_DIV1 = Amount;

	Amount = GetPrivateProfileInt("Reflect","DamageRefDiv2",25,ini);
	*(unsigned int*) GS_DAMAGEREF_DIV2 = Amount;

	return 1;
}

//==================================================
//Inert del Bk
//==================================================
bool DkGreaterFortitudeInit ( char * ini)
{
	DWORD Amount;

	Amount = GetPrivateProfileInt("GreaterFortitude","FortitudeVitality",100,ini);
	*(unsigned int*) GS_FORTITUDEA = Amount;

	Amount = GetPrivateProfileInt("GreaterFortitude","FortitudeEnergy",20,ini);
	*(unsigned int*) GS_FORTITUDED = Amount;
	return 1;
}


//==================================================
//===========ANCIENT================================
//==================================================
bool Ancient(char* File)
{
	DWORD AllowExc = GetPrivateProfileInt("Ancient","EnableAncient+ExcOpt",0,File);
	DWORD AllowJoH = GetPrivateProfileInt("Ancient","EnableAncient+JoHOpt",0,File);

	if(AllowExc == 1)
	{
		*(BYTE*)(GS_ANCIENTEXC) = 0xEB;
	}
	
	if(AllowJoH == 1)
	{
		*(BYTE*)(GS_ANCIENTJOH) = 0xEB;
	}
	return 1;
}

//==================================================
//==================POTION RECOVERY=================
//==================================================
bool PotionRecovery(char* File)
{
	DWORD AmountHP;
	BYTE AmountMP;

	AmountHP = GetPrivateProfileInt("Recovery","AppleRecovery",10,File);
	*(unsigned int*) GS_HP_RECOVERY1 = AmountHP;

	AmountHP = GetPrivateProfileInt("Recovery","SmallHealingPotionRecovery",20,File);
	*(unsigned int*) GS_HP_RECOVERY2 = AmountHP;

	AmountHP = GetPrivateProfileInt("Recovery","MediumHealingPotionRecovery",30,File);
	*(unsigned int*) GS_HP_RECOVERY3 = AmountHP;

	AmountHP = GetPrivateProfileInt("Recovery","LargeHealingPotionRecovery",40,File);
	*(unsigned int*) GS_HP_RECOVERY4 = AmountHP;

	AmountMP = GetPrivateProfileInt("Recovery","SmallManaPotionRecovery",20,File);
	*(unsigned char*) GS_MP_RECOVERY1 = AmountMP;

	AmountMP = GetPrivateProfileInt("Recovery","MediumManaPotionRecovery",30,File);
	*(unsigned char*) GS_MP_RECOVERY2 = AmountMP;

	AmountMP = GetPrivateProfileInt("Recovery","LargeManaPotionRecovery",40,File);
	*(unsigned char*) GS_MP_RECOVERY3 = AmountMP;
	return 1;
}
//==================================================
//COMBO SKILL
//==================================================

bool CommonSkills( char * ini )
{

	BYTE LevelReq;

	LevelReq = GetPrivateProfileInt("Skill","TwistingSlashLevelReq",80,ini);
	*(unsigned int*) GS_TWISTINGSLASHLVLREQ = LevelReq;

	LevelReq = GetPrivateProfileInt("Skill","RagefulBlowLevelReq",170,ini);
	*(unsigned int*) GS_RAGEFULBLOWLVLREQ = LevelReq;

	LevelReq = GetPrivateProfileInt("Skill","DeathStabLevelReq",160,ini);
	*(unsigned int*) GS_DEATHSTABLVLREQ = LevelReq;

	LevelReq = GetPrivateProfileInt("Skill","GreaterFortitudeLevelReq",120,ini);
	*(unsigned int*) GS_FORTITUDELVLREQ = LevelReq;

	LevelReq = GetPrivateProfileInt("Skill","PenetrationLevelReq",130,ini);
	*(unsigned int*) GS_PENETRATIONLVLREQ = LevelReq;
	
	return 1;
}

//==========================================
//==========Party Zen=======================
//==========================================

bool FixPartyExp (char * ini)
{

	DWORD Exp;

	Exp = GetPrivateProfileInt("PartyExp","Party2Exp",160,ini);
	*(unsigned int*) GS_PARTYBONUS1 = Exp;
	*(unsigned int*) GS_PARTYBONUS8 = Exp;

	Exp = GetPrivateProfileInt("PartyExp","Party3Exp",190,ini);
	*(unsigned int*) GS_PARTYBONUS2 = Exp;
	*(unsigned int*) GS_PARTYBONUS9 = Exp;

	Exp = GetPrivateProfileInt("PartyExp","Party4Exp",220,ini);
	*(unsigned int*) GS_PARTYBONUS3 = Exp;
	*(unsigned int*) GS_PARTYBONUS10 = Exp;

	Exp = GetPrivateProfileInt("PartyExp","Party5Exp",250,ini);
	*(unsigned int*) GS_PARTYBONUS4 = Exp;
	*(unsigned int*) GS_PARTYBONUS11 = Exp;
	
	Exp = GetPrivateProfileInt("PartyExp","SetParty3Exp",240,ini);
	*(unsigned int*) GS_PARTYBONUS5 = Exp;
	*(unsigned int*) GS_PARTYBONUS12 = Exp;

	Exp = GetPrivateProfileInt("PartyExp","SetParty4Exp",280,ini);
	*(unsigned int*) GS_PARTYBONUS6 = Exp;
	*(unsigned int*) GS_PARTYBONUS13 = Exp;

	Exp = GetPrivateProfileInt("PartyExp","SetParty5Exp",320,ini);
	*(unsigned int*) GS_PARTYBONUS7 = Exp;
	*(unsigned int*) GS_PARTYBONUS14 = Exp;
	return 1;
}

//==================================================
//MAQUINA DE CHAOS RATE
//==================================================

bool CBMixInit ( char * ini )
{
	DWORD dwTmp ;
	BYTE cTmp ;

	dwTmp = GetPrivateProfileInt("ChaosMachine", "Mix+10",50, ini) ;
	*(unsigned int *) GS_18_ADDR_CBmix10= dwTmp ;

	dwTmp = GetPrivateProfileInt("ChaosMachine", "Mix+11",45, ini) ;
	*(unsigned int *) GS_18_ADDR_CBmix11= dwTmp ;

	dwTmp = GetPrivateProfileInt("ChaosMachine", "Mix+12",45, ini) ;
	*(unsigned int *) GS_18_ADDR_CBmix12= dwTmp ;

	dwTmp = GetPrivateProfileInt("ChaosMachine", "Mix+13",45, ini) ;
	*(unsigned int *) GS_18_ADDR_CBmix13= dwTmp ;

	cTmp = GetPrivateProfileInt("ChaosMachine", "MixMaxRate",75, ini) ;
	*(unsigned char *) GS_18_ADDR_CBmixMaxRate1= cTmp ;

	dwTmp = GetPrivateProfileInt("ChaosMachine","MixMaxRate",75, ini) ;
	*(unsigned int *) GS_18_ADDR_CBmixMaxRate2= dwTmp ;

	cTmp = GetPrivateProfileInt("ChaosMachine","MixLuckAddRate",20,ini);
	*(unsigned char*) GS_CHAOSMIX_LUCKADD = cTmp;

	cTmp = GetPrivateProfileInt("ChaosMachine","CapeMixMaxSuccessRate",90,ini);
	*(unsigned char*) GS_CAPEMIXRATE1 = cTmp;

	dwTmp = GetPrivateProfileInt("ChaosMachine","CapeMixMaxSuccessRate",90,ini);
	*(unsigned int*) GS_CAPEMIXRATE2 = dwTmp;

	cTmp = GetPrivateProfileInt("ChaosMachine","WingLvl1MixMaxSuccessRate",100,ini);
	*(unsigned char*) GS_WINGLVL1MIXRATE1 = cTmp;
												
	dwTmp = GetPrivateProfileInt("ChaosMachine","WingLvl1MaxSuccessRate",100,ini);
	*(unsigned int*) GS_WINGLVL1MIXRATE2 = dwTmp;

	cTmp = GetPrivateProfileInt("ChaosMachine","WingLvl2MixMaxSuccessRate",100,ini);
	*(unsigned char*) GS_WINGLVL2MIXRATE1 = cTmp;

	dwTmp = GetPrivateProfileInt("ChaosMachine","WingLvl2MaxSuccessRate",100,ini);
	*(unsigned int*) GS_WINGLVL2MIXRATE2 = dwTmp;
	return 1 ;
}

//==================================================
//Items Time en el Suelo
//==================================================
bool TimeItems ( char * ini )
{
	DWORD dwTmp ;
	dwTmp = DWORD(1000 * GetPrivateProfileInt("Items", "ItemsDurationTime", 60, ini));
	*(unsigned int *) GS_18_ADDR_ItemsinTheFloor1  = dwTmp ;
	*(unsigned int *) GS_18_ADDR_ItemsinTheFloor2  = dwTmp ;
	return 1 ;

}
//==================================================
//Carga los valores de la struct para el conectmember
//==================================================

bool LoadStruct(char* ini)
{
configs.cmember.active = GetPrivateProfileInt("ConnectMember","CMemberReloadActive",1,ini);
configs.cmember.time = GetPrivateProfileInt("ConnectMember","CMemberReloadTimeMin",1,ini);

return true;

}

bool LoadZen(char* ini)
{

return 1;
}



//======================================================
//==========MOVE GMS/ [1 = KEY M | 0 /Move]=============
//======================================================
bool GMMoveWay(char* File)
{
	if(GetPrivateProfileInt("GameServerInfo","Fix_MoveGM",0,CUSTOMFILE_PATH))
	{
		
		SetByte(0x0051B716,0x07);
	
	}
	return 1;
}
//Bless,Soul Mix
// Prices
bool BlessSoulMix (char * ini)
{
	DWORD BlessSoulM;
	BlessSoulM = GetPrivateProfileInt("Custom","BlessWaterPrice",10000,ini) ;
	*(unsigned int*) GS_18_ADDR_BlessWaterPrice = BlessSoulM ;

	BlessSoulM = GetPrivateProfileInt("Custom","SoulWaterPrice",20000,ini) ;
	*(unsigned int*) GS_18_ADDR_SoulWaterPrice = BlessSoulM ;

	BlessSoulM = GetPrivateProfileInt("Custom","BlessMixPrice",30000,ini) ;
	*(unsigned int*) GS_18_ADDR_BlessMixPrice = BlessSoulM ;

	BlessSoulM = GetPrivateProfileInt("Custom","SoulMixPrice",40000,ini) ;
	*(unsigned int*) GS_18_ADDR_SoulMixPrice = BlessSoulM ;
	return 1;
}

//=====================================================================================
//Potion of Bless and Soul Mix Rate add 27/01/2012
//=====================================================================================
bool PotionBSMix ( char*ini )
{
	DWORD PotionMix;
	PotionMix = GetPrivateProfileInt("Customs", "BlessPotionMixRate",100,ini) ;
    *(unsigned int*) BlessPotionMix = PotionMix ;

	PotionMix = GetPrivateProfileInt("Customs", "SoulPotionMixRate",100,ini) ;
    *(unsigned int*) SoulPotionMix = PotionMix ;
	return 1;
}
//=====================================================================================
//Potion of Soul and Bless Price add 27/01/2012
//=====================================================================================
bool PotionBSPrice ( char*ini )
{
	DWORD PotionPrice;
    PotionPrice = GetPrivateProfileInt("Customs","PotionOfBlessPrice", 900000,ini) ;
    *(unsigned int *) BlessPotionPrice = PotionPrice ;

    PotionPrice = GetPrivateProfileInt("Customs","PotionOfSoulPrice", 450000,ini) ;
    *(unsigned int *) SoulPotionPrice = PotionPrice ;
	return 1;
}

//=====================================================================================
//Set Item Mix Rate add 27/01/2012
//=====================================================================================
bool SetItemMixRate ( char*ini )
{
	BYTE SetItem;
	SetItem = GetPrivateProfileInt("ChaosMachine","SetItemMixRate",90,ini) ;
    *(unsigned char *) SetItemRate1 = SetItem ;
    *(unsigned char *) SetItemRate2 = SetItem ;
	return 1;
}
//=====================================================================================
//Dinorant Mix Success Rate add 27/01/2012
//=====================================================================================
bool DinorantMixSuccess ( char*ini )
{
	BYTE Dino;
	Dino = GetPrivateProfileInt("ChaosMachine","DinorantMixRate",70,ini) ;
    *(unsigned char *) DinorantMix = Dino ;
	return 1;
}
//=====================================================================================
//Life Stone Mix Success Rate add 27/01/2012
//=====================================================================================
bool LifeStoneMixRate ( char*ini )
{
	BYTE LifeRate;
	LifeRate = GetPrivateProfileInt("ChaosMachine","LifeStoneMixRate",100,ini) ;
    *(unsigned char *) LifeStoneMix = LifeRate ;
	return 1;
}

//=====================================================================================
//Interface Options add 27/01/2012
//=====================================================================================
bool InterfaceColor ( char*ini )
{
	DWORD Color;
	Color = GetPrivateProfileInt("Evolution","MenuBarColor",0x000000,ini);
	*(unsigned int*) MenuColorNormal= Color;

	Color = GetPrivateProfileInt("Evolution","MenuColorNoDataserver",0x000000,ini); //FA6E6E
	*(unsigned int*) MenuColorDSDisconnected= Color;

	Color = GetPrivateProfileInt("Evolution","MenuBarTextColor",0x00FF00,ini);
	*(unsigned int*) MenuTextColor= Color;
	return 1;
}

//=====================================================================================
//Message System	
//=====================================================================================
bool MessageSystem ()
{
	GetPrivateProfileString("Messages", "Evolution-MSG00", "[DROP]: Command used only by GM's", MSG00, 500,MENSAJESFILE_PATH);
	GetPrivateProfileString("Messages", "Evolution-MSG01", "[DROP]: Off command.", MSG01, 500,MENSAJESFILE_PATH);
	GetPrivateProfileString("Messages", "Evolution-MSG02", "[Drop]: Item successfully created!", MSG02, 500,MENSAJESFILE_PATH);
	GetPrivateProfileString("Messages", "Evolution-MSG03", "[Drop]: No Priviligios de GM", MSG03, 500,MENSAJESFILE_PATH);
	GetPrivateProfileString("Messages", "Evolution-MSG04", "[POST]: Off command.", MSG04, 500,MENSAJESFILE_PATH);
	GetPrivateProfileString("Messages", "Evolution-MSG05", "[POST]: Use Command: /post <Message>", MSG05, 500,MENSAJESFILE_PATH);
	GetPrivateProfileString("Messages", "Evolution-MSG06", "[POST]: The command is: /post <Message>", MSG06, 500,MENSAJESFILE_PATH);
	GetPrivateProfileString("Messages", "Evolution-MSG07", "[POST]: To use the /post you must be over [%d].", MSG07, 500,MENSAJESFILE_PATH);
	GetPrivateProfileString("Messages", "Evolution-MSG08", "[POST]: Necessary [%i] of Zen to use the command.", MSG08, 500,MENSAJESFILE_PATH);
	GetPrivateProfileString("Messages", "Evolution-MSG09", "[POST]: Incorrect setting on OGC-Comandos.ini!!", MSG09, 500,MENSAJESFILE_PATH);
	GetPrivateProfileString("Messages", "Evolution-MSG10", "[POST]: You are under a temporary mute from global post.", MSG10, 500,MENSAJESFILE_PATH);
	GetPrivateProfileString("Messages", "Evolution-MSG11", "[POST]: Was collected [%i] of Zen, you're left [%i] of Zen in your inventory.", MSG11, 500,MENSAJESFILE_PATH);
	GetPrivateProfileString("Messages", "Evolution-MSG12", "[ADD]: Disabled by the Administrator Command.", MSG12, 500,MENSAJESFILE_PATH);
	GetPrivateProfileString("Messages", "Evolution-MSG13", "[ADD]: The Level must be greater than [%d].", MSG13, 500,MENSAJESFILE_PATH);
	GetPrivateProfileString("Messages", "Evolution-MSG14", "[ADD]: Type a number after the command.", MSG14, 500,MENSAJESFILE_PATH);
	GetPrivateProfileString("Messages", "Evolution-MSG15", "[ADD]: You have not enough points to increase.", MSG15, 500,MENSAJESFILE_PATH);
	GetPrivateProfileString("Messages", "Evolution-MSG16", "[ADD]: You can not increase [%s] Point at a time. The limit is [%d].", MSG16, 500,MENSAJESFILE_PATH);
	GetPrivateProfileString("Messages", "Evolution-MSG17", "[ADD]: Only DarkLord or LordEmperor can use the /cmd.", MSG17, 500,MENSAJESFILE_PATH);
	GetPrivateProfileString("Messages", "Evolution-MSG18", "[ADD]: Necessary [%id] Zen To use the command!", MSG18, 500,MENSAJESFILE_PATH);
	GetPrivateProfileString("Messages", "Evolution-MSG19", "[ADD]:Incorrect setting on OGC-Comandos.ini!!", MSG19, 500,MENSAJESFILE_PATH);
	GetPrivateProfileString("Messages", "Evolution-MSG20", "[Add]: [You used] [%d] points. you have [%d] points.", MSG20, 500,MENSAJESFILE_PATH);
	GetPrivateProfileString("Messages", "Evolution-MSG21", "[ADD]:was collected [%i] of Zen, you have left(m) [%i] of Zen in your inventory.", MSG21, 500,MENSAJESFILE_PATH);
	GetPrivateProfileString("Messages", "Evolution-MSG22", "[Reload]Sintexis Del Comando /reload <num>.", MSG22, 500,MENSAJESFILE_PATH);
	GetPrivateProfileString("Messages", "Evolution-MSG23", "[Reload]<0> setting the OGC-Files.ini", MSG23, 500,MENSAJESFILE_PATH);
	GetPrivateProfileString("Messages", "Evolution-MSG24", "[Reload]<1> Reload Monsters", MSG24, 500,MENSAJESFILE_PATH);
	GetPrivateProfileString("Messages", "Evolution-MSG25", "[Reload]<2> Reload OGC_FortuneWheel.ini", MSG25, 500,MENSAJESFILE_PATH);
	GetPrivateProfileString("Messages", "Evolution-MSG26", "[Reload]<3> Reload Shops", MSG26, 500,MENSAJESFILE_PATH);
	GetPrivateProfileString("Messages", "Evolution-MSG27", "[Reload]<4> Reload OGC-DropSystem.txt", MSG27, 500,MENSAJESFILE_PATH);
	GetPrivateProfileString("Messages", "Evolution-MSG28", "[Reload]<5> Reload OGC-NewSystem.txt", MSG28, 500,MENSAJESFILE_PATH);
	GetPrivateProfileString("Messages", "Evolution-MSG29", "[Reload]<6> Reload OGC_GMSystem.ini", MSG29, 500,MENSAJESFILE_PATH);
	GetPrivateProfileString("Messages", "Evolution-MSG30", "[Reload]<7> Reload OGC_VipSystem.ini", MSG30, 500,MENSAJESFILE_PATH);
	GetPrivateProfileString("Messages", "Evolution-MSG31", "[Reload]<8> Reload OGC_GoldenArcher.ini", MSG31, 500,MENSAJESFILE_PATH);
	GetPrivateProfileString("Messages", "Evolution-MSG32", "[Reload]<9> Reload ConnectMember.txt", MSG32, 500,MENSAJESFILE_PATH);
	GetPrivateProfileString("Messages", "Evolution-MSG33", "[Reload] You're Not GM.", MSG33, 500,MENSAJESFILE_PATH);
	GetPrivateProfileString("Messages", "Evolution-MSG34", "[Reload 0]: Off command.", MSG34, 500,MENSAJESFILE_PATH);
	GetPrivateProfileString("Messages", "Evolution-MSG35", "[Reload]: Configurations Recharged With Success", MSG35, 500,MENSAJESFILE_PATH);
	GetPrivateProfileString("Messages", "Evolution-MSG36", "[Reload]: OGC-Files.ini Was loaded successfully", MSG36, 500,MENSAJESFILE_PATH);
	GetPrivateProfileString("Messages", "Evolution-MSG37", "[Reload 1]: Off command.", MSG37, 500,MENSAJESFILE_PATH);
	GetPrivateProfileString("Messages", "Evolution-MSG38", "[Reload] Monsters properly recharged", MSG38, 500,MENSAJESFILE_PATH);
	GetPrivateProfileString("Messages", "Evolution-MSG39", "[Reload 2]: Off command.", MSG39, 500,MENSAJESFILE_PATH);
	GetPrivateProfileString("Messages", "Evolution-MSG40", "[Reload 2] FortuneWheel properly recharged", MSG40, 500,MENSAJESFILE_PATH);
	GetPrivateProfileString("Messages", "Evolution-MSG41", "[Reload 3]: Off command.", MSG41, 500,MENSAJESFILE_PATH);
	GetPrivateProfileString("Messages", "Evolution-MSG42", "[Reload] Shops properly recharged", MSG42, 500,MENSAJESFILE_PATH);
	GetPrivateProfileString("Messages", "Evolution-MSG43", "[Reload 4]: Off command.", MSG43, 500,MENSAJESFILE_PATH);
	GetPrivateProfileString("Messages", "Evolution-MSG44", "[Reload] DropSystem properly recharged", MSG44, 500,MENSAJESFILE_PATH);
	GetPrivateProfileString("Messages", "Evolution-MSG45", "[Reload 5]: Off command.", MSG45, 500,MENSAJESFILE_PATH);
	GetPrivateProfileString("Messages", "Evolution-MSG46", "[Reload] News reloaded correctly", MSG46, 500,MENSAJESFILE_PATH);
	GetPrivateProfileString("Messages", "Evolution-MSG47", "[Reload 6]: Off command.", MSG47, 500,MENSAJESFILE_PATH);
	GetPrivateProfileString("Messages", "Evolution-MSG48", "[Reload] GMSystem reloaded correctly", MSG48, 500,MENSAJESFILE_PATH);
	GetPrivateProfileString("Messages", "Evolution-MSG49", "[Reload 7]: Off command.", MSG49, 500,MENSAJESFILE_PATH);
	GetPrivateProfileString("Messages", "Evolution-MSG50", "[Reload] VipSystem reloaded correctly", MSG50, 500,MENSAJESFILE_PATH);
	GetPrivateProfileString("Messages", "Evolution-MSG51", "[Reload 8]: Off command.", MSG51, 500,MENSAJESFILE_PATH);
	GetPrivateProfileString("Messages", "Evolution-MSG52", "[Reload] GoldenArcher reloaded correctly", MSG52, 500,MENSAJESFILE_PATH);
	GetPrivateProfileString("Messages", "Evolution-MSG53", "[Reload 9]: Off command.", MSG53, 500,MENSAJESFILE_PATH);
	GetPrivateProfileString("Messages", "Evolution-MSG54", "[Reload] ConnectMember reloaded correctly", MSG54, 500,MENSAJESFILE_PATH);
	GetPrivateProfileString("Messages", "Evolution-MSG55", "[Reload] This option does not exist", MSG55, 500,MENSAJESFILE_PATH);
	GetPrivateProfileString("Messages", "Evolution-MSG56", "[GMSystem]: No Privilegio en /reload comando", MSG56, 500,MENSAJESFILE_PATH);
	GetPrivateProfileString("Messages", "Evolution-MSG57", "[Crear Mobs]: Command only to GMs and ADMs.", MSG57, 500,MENSAJESFILE_PATH);
	GetPrivateProfileString("Messages", "Evolution-MSG58", "[Crear Mobs]: Monster Created Successfully!", MSG58, 500,MENSAJESFILE_PATH);
	GetPrivateProfileString("Messages", "Evolution-MSG59", "[Crear Mobs]: Failed to Create Monster!", MSG59, 500,MENSAJESFILE_PATH);
	GetPrivateProfileString("Messages", "Evolution-MSG60", "[GMSystem]: No Privilegio de /createmob", MSG60, 500,MENSAJESFILE_PATH);
	GetPrivateProfileString("Messages", "Evolution-MSG61", "[Skin]: Commands disabled.", MSG61, 500,MENSAJESFILE_PATH);
	GetPrivateProfileString("Messages", "Evolution-MSG62", "[Skin]: Only commands for GMs.", MSG62, 500,MENSAJESFILE_PATH);
	GetPrivateProfileString("Messages", "Evolution-MSG63", "[Skin]: To use the /skin have to be more than [%d].", MSG63, 500,MENSAJESFILE_PATH);
	GetPrivateProfileString("Messages", "Evolution-MSG64", "[GMSystem]: No Privilegio para /skin comando.", MSG64, 500,MENSAJESFILE_PATH);
	GetPrivateProfileString("Messages", "Evolution-MSG65", "[Move]: Off command.", MSG65, 500,MENSAJESFILE_PATH);
	GetPrivateProfileString("Messages", "Evolution-MSG66", "[Move]: To use the /iglesia you have to be more than [%d].", MSG66, 500,MENSAJESFILE_PATH);
	GetPrivateProfileString("Messages", "Evolution-MSG67", "[%s] You have successfully moved to Devias Iglesia.", MSG67, 500,MENSAJESFILE_PATH);
	GetPrivateProfileString("Messages", "Evolution-MSG68", "[Move]: Off command.", MSG68, 500,MENSAJESFILE_PATH);
	GetPrivateProfileString("Messages", "Evolution-MSG69", "[Move]: To use the /maquina you have to be more than [%d]", MSG69, 500,MENSAJESFILE_PATH);
	GetPrivateProfileString("Messages", "Evolution-MSG70", "[%s] You have successfully moved to Noria Machine.", MSG70, 500,MENSAJESFILE_PATH);
	GetPrivateProfileString("Messages", "Evolution-MSG71", "[Move]: Off command.", MSG71, 500,MENSAJESFILE_PATH);
	GetPrivateProfileString("Messages", "Evolution-MSG72", "[Move]: To use the /bar you have to be more than [%d].", MSG72, 500,MENSAJESFILE_PATH);
	GetPrivateProfileString("Messages", "Evolution-MSG73", "[%s] You have successfully moved to Lorencia Bar.", MSG73, 500,MENSAJESFILE_PATH);
	GetPrivateProfileString("Messages", "Evolution-MSG74", "[Online]: Off command.", MSG74, 500,MENSAJESFILE_PATH);
	GetPrivateProfileString("Messages", "Evolution-MSG75", "[Online]: Command only to GMs and ADMs.", MSG75, 500,MENSAJESFILE_PATH);
	GetPrivateProfileString("Messages", "Evolution-MSG76", "[Online]: Total Characters Online!: %d", MSG76, 500,MENSAJESFILE_PATH);
	GetPrivateProfileString("Messages", "Evolution-MSG77", "[GMSystem]: No Privilegio para /online comando", MSG77, 500,MENSAJESFILE_PATH);
	GetPrivateProfileString("Messages", "Evolution-MSG78", "[GG]: Off command.", MSG78, 500,MENSAJESFILE_PATH);
	GetPrivateProfileString("Messages", "Evolution-MSG79", "[GMSystem]: No priviledgi for /gg comannds.", MSG79, 500,MENSAJESFILE_PATH);
	GetPrivateProfileString("Messages", "Evolution-MSG80", "[Clear Item]: Off command.", MSG80, 500,MENSAJESFILE_PATH);
	GetPrivateProfileString("Messages", "Evolution-MSG81", "[Clear Item]: Sintexis Del Comando /bitemq <n>.", MSG81, 500,MENSAJESFILE_PATH);
	GetPrivateProfileString("Messages", "Evolution-MSG82", "[Clear Item]<0> no borrara nada.", MSG82, 500,MENSAJESFILE_PATH);
	GetPrivateProfileString("Messages", "Evolution-MSG83", "[Clear Item]<1> Borrara los items de quets", MSG83, 500,MENSAJESFILE_PATH);
	GetPrivateProfileString("Messages", "Evolution-MSG84", "de tu Inventario, pero tambien", MSG84, 500,MENSAJESFILE_PATH);
	GetPrivateProfileString("Messages", "Evolution-MSG85", "borrara todos los items que tengas", MSG85, 500,MENSAJESFILE_PATH);
	GetPrivateProfileString("Messages", "Evolution-MSG86", "en tu inventario, pero no los items puesto", MSG86, 500,MENSAJESFILE_PATH);
	GetPrivateProfileString("Messages", "Evolution-MSG87", "[Clear Item]: Items Borrados Exitosamente.", MSG87, 500,MENSAJESFILE_PATH);
	GetPrivateProfileString("Messages", "Evolution-MSG88", "[Clear Item] Esta Opcion No Existe", MSG88, 500,MENSAJESFILE_PATH);
	GetPrivateProfileString("Messages", "Evolution-MSG89", "[PKCLEAR]: You are not PK!!", MSG89, 500,MENSAJESFILE_PATH);
	GetPrivateProfileString("Messages", "Evolution-MSG90", "[PKCLEAR]: To use /pkclear requires of zen: %ld", MSG90, 500,MENSAJESFILE_PATH);
	GetPrivateProfileString("Messages", "Evolution-MSG91", "[PKCLEAR]: You have deleted the Pk Successfully!!", MSG91, 500,MENSAJESFILE_PATH);
	GetPrivateProfileString("Messages", "Evolution-MSG92", "[GMSystem]: No Privilegio /zen comando!!", MSG92, 500,MENSAJESFILE_PATH);
	GetPrivateProfileString("Messages", "Evolution-MSG93", "[Info]: Off command.", MSG93, 500,MENSAJESFILE_PATH);
	GetPrivateProfileString("Messages", "Evolution-MSG94", "[Info]: Su Cuenta es:  %s. - y - Su Personaje es: %s.", MSG94, 500,MENSAJESFILE_PATH);
	GetPrivateProfileString("Messages", "Evolution-MSG95", "Usage: /setpk <name> <amount>", MSG95, 500,MENSAJESFILE_PATH);
	GetPrivateProfileString("Messages", "Evolution-MSG96", "Error, please re-check the string you gave.", MSG96, 500,MENSAJESFILE_PATH);
	GetPrivateProfileString("Messages", "Evolution-MSG97", "Error, name can be only 10 characters long.", MSG97, 500,MENSAJESFILE_PATH);
	GetPrivateProfileString("Messages", "Evolution-MSG98", "Reminder: PK Level goes from 0 to 7.", MSG98, 500,MENSAJESFILE_PATH);
	GetPrivateProfileString("Messages", "Evolution-MSG99", "Error, character not found or is offline.", MSG99, 500,MENSAJESFILE_PATH);
	GetPrivateProfileString("Messages", "Evolution-MSG100", "You modified %s's PK status successfully.", MSG100, 500,MENSAJESFILE_PATH);
	GetPrivateProfileString("Messages", "Evolution-MSG101", "Your PK status has been modified by %s.", MSG101, 500,MENSAJESFILE_PATH);
	GetPrivateProfileString("Messages", "Evolution-MSG102", "You don't have priviledges to this command.", MSG102, 500,MENSAJESFILE_PATH);
	GetPrivateProfileString("Messages", "Evolution-MSG103", "Usage: /setzen <name> <amount>", MSG103, 500,MENSAJESFILE_PATH);
	GetPrivateProfileString("Messages", "Evolution-MSG104", "Error, please re-check the string you gave.", MSG104, 500,MENSAJESFILE_PATH);
	GetPrivateProfileString("Messages", "Evolution-MSG105", "Error, name can be only 10 characters long.", MSG105, 500,MENSAJESFILE_PATH);
	GetPrivateProfileString("Messages", "Evolution-MSG106", "Error, please re-check the string you gave.", MSG106, 500,MENSAJESFILE_PATH);
	GetPrivateProfileString("Messages", "Evolution-MSG107", "Reminder: max possible money is 2,000,000,000.", MSG107, 500,MENSAJESFILE_PATH);
	GetPrivateProfileString("Messages", "Evolution-MSG108", "Error, character not found or is offline.", MSG108, 500,MENSAJESFILE_PATH);
	GetPrivateProfileString("Messages", "Evolution-MSG109", "You modified %s's money successfully.", MSG109, 500,MENSAJESFILE_PATH);
	GetPrivateProfileString("Messages", "Evolution-MSG110", "Your money has been modified by %s.", MSG110, 500,MENSAJESFILE_PATH);
	GetPrivateProfileString("Messages", "Evolution-MSG111", "You don't have priviledges to this command.", MSG111, 500,MENSAJESFILE_PATH);
	GetPrivateProfileString("Messages", "Evolution-MSG112", "Usage: /setlevel <name> <amount>", MSG112, 500,MENSAJESFILE_PATH);
	GetPrivateProfileString("Messages", "Evolution-MSG113", "Error, please re-check the string you gave.", MSG113, 500,MENSAJESFILE_PATH);
	GetPrivateProfileString("Messages", "Evolution-MSG114", "Error, name can be only 10 characters long.", MSG114, 500,MENSAJESFILE_PATH);
	GetPrivateProfileString("Messages", "Evolution-MSG115", "Error, please re-check the string you gave.", MSG115, 500,MENSAJESFILE_PATH);
	GetPrivateProfileString("Messages", "Evolution-MSG116", "Reminder: Level goes from 1 to 400.", MSG116, 500,MENSAJESFILE_PATH);
	GetPrivateProfileString("Messages", "Evolution-MSG117", "Error, character not found or is offline.", MSG117, 500,MENSAJESFILE_PATH);
	GetPrivateProfileString("Messages", "Evolution-MSG118", "You modified %s's level successfully.", MSG118, 500,MENSAJESFILE_PATH);
	GetPrivateProfileString("Messages", "Evolution-MSG119", "Your level has been modified by %s.", MSG119, 500,MENSAJESFILE_PATH);
	GetPrivateProfileString("Messages", "Evolution-MSG120", "You don't have priviledges to this command.", MSG120, 500,MENSAJESFILE_PATH);
	GetPrivateProfileString("Messages", "Evolution-MSG121", "Usage: /mutepost <name>", MSG121, 500,MENSAJESFILE_PATH);
	GetPrivateProfileString("Messages", "Evolution-MSG122", "Error, please re-check the string you gave.", MSG122, 500,MENSAJESFILE_PATH);
	GetPrivateProfileString("Messages", "Evolution-MSG123", "Error, name can be only 10 characters long.", MSG123, 500,MENSAJESFILE_PATH);
	GetPrivateProfileString("Messages", "Evolution-MSG124", "Error, character not found or is offline.", MSG124, 500,MENSAJESFILE_PATH);
	GetPrivateProfileString("Messages", "Evolution-MSG125", "This player has been muted already.", MSG125, 500,MENSAJESFILE_PATH);
	GetPrivateProfileString("Messages", "Evolution-MSG126", "You muted %s successfully.", MSG126, 500,MENSAJESFILE_PATH);
	GetPrivateProfileString("Messages", "Evolution-MSG127", "You've been given a temporary mute to global post by %s.", MSG127, 500,MENSAJESFILE_PATH);
	GetPrivateProfileString("Messages", "Evolution-MSG128", "You don't have priviledges to this command.", MSG128, 500,MENSAJESFILE_PATH);
	GetPrivateProfileString("Messages", "Evolution-MSG129", "Usage: /unmutepost <name>", MSG129, 500,MENSAJESFILE_PATH);
	GetPrivateProfileString("Messages", "Evolution-MSG130", "Error, please re-check the string you gave.", MSG130, 500,MENSAJESFILE_PATH);
	GetPrivateProfileString("Messages", "Evolution-MSG131", "Error, name can be only 10 characters long.", MSG131, 500,MENSAJESFILE_PATH);
	GetPrivateProfileString("Messages", "Evolution-MSG132", "Error, character not found or is offline.", MSG132, 500,MENSAJESFILE_PATH);
	GetPrivateProfileString("Messages", "Evolution-MSG133", "This player is not muted.", MSG133, 500,MENSAJESFILE_PATH);
	GetPrivateProfileString("Messages", "Evolution-MSG134", "You lifted %s's mute successfully.", MSG134, 500,MENSAJESFILE_PATH);
	GetPrivateProfileString("Messages", "Evolution-MSG135", "Your global post mute has been lifted by %s.", MSG135, 500,MENSAJESFILE_PATH);
	GetPrivateProfileString("Messages", "Evolution-MSG136", "You don't have priviledges to this command.", MSG136, 500,MENSAJESFILE_PATH);
	GetPrivateProfileString("Messages", "Evolution-MSG137", "Usage: /banchar <name>", MSG137, 500,MENSAJESFILE_PATH);
	GetPrivateProfileString("Messages", "Evolution-MSG138", "Error, please re-check the string you gave.", MSG138, 500,MENSAJESFILE_PATH);
	GetPrivateProfileString("Messages", "Evolution-MSG139", "Error, name can be only 10 characters long.", MSG139, 500,MENSAJESFILE_PATH);
	GetPrivateProfileString("Messages", "Evolution-MSG140", "Error, character not found or is offline.", MSG140, 500,MENSAJESFILE_PATH);
	GetPrivateProfileString("Messages", "Evolution-MSG141", "This player has been banned already.", MSG141, 500,MENSAJESFILE_PATH);
	GetPrivateProfileString("Messages", "Evolution-MSG142", "You banned '%s' character successfully.", MSG142, 500,MENSAJESFILE_PATH);
	GetPrivateProfileString("Messages", "Evolution-MSG143", "You've been banned by %s.", MSG143, 500,MENSAJESFILE_PATH);
	GetPrivateProfileString("Messages", "Evolution-MSG144", "Contact the administrators for more info.", MSG144, 500,MENSAJESFILE_PATH);
	GetPrivateProfileString("Messages", "Evolution-MSG145", "You don't have priviledges to this command.", MSG145, 500,MENSAJESFILE_PATH);
	GetPrivateProfileString("Messages", "Evolution-MSG146", "Usage: /unbanchar <name>", MSG146, 500,MENSAJESFILE_PATH);
	GetPrivateProfileString("Messages", "Evolution-MSG147", "Error, please re-check the string you gave.", MSG147, 500,MENSAJESFILE_PATH);
	GetPrivateProfileString("Messages", "Evolution-MSG148", "Error, name can be only 10 characters long.", MSG148, 500,MENSAJESFILE_PATH);
	GetPrivateProfileString("Messages", "Evolution-MSG149", "This player is not banned.", MSG149, 500,MENSAJESFILE_PATH);
	GetPrivateProfileString("Messages", "Evolution-MSG150", "You unbanned '%s' character successfully.", MSG150, 500,MENSAJESFILE_PATH);
	GetPrivateProfileString("Messages", "Evolution-MSG151", "You don't have priviledges to this command.", MSG151, 500,MENSAJESFILE_PATH);
	GetPrivateProfileString("Messages", "Evolution-MSG152", "[RESET]: No Tienes Los [%d] Levels Requerido para el Reset", MSG152, 500,MENSAJESFILE_PATH);
	GetPrivateProfileString("Messages", "Evolution-MSG153", "[RESET]: To use /reset requires of zen: %l", MSG153, 500,MENSAJESFILE_PATH);
	GetPrivateProfileString("Messages", "Evolution-MSG154", "[RESET]: Resetiaste Correctamente!.", MSG154, 500,MENSAJESFILE_PATH);
	GetPrivateProfileString("Messages", "Evolution-MSG155", "Usage: /moveall <map> <posx> <posy>", MSG155, 500,MENSAJESFILE_PATH);
	GetPrivateProfileString("Messages", "Evolution-MSG156", "Error, please re-check the string you gave.", MSG156, 500,MENSAJESFILE_PATH);
	GetPrivateProfileString("Messages", "Evolution-MSG157", "You don't have priviledges to this command.", MSG157, 500,MENSAJESFILE_PATH);
	GetPrivateProfileString ("Oters","MSG159","[WebServer] www.evolution-team.eu",MSG159,100,COMMANDFILE_PATH);
	GetPrivateProfileString ("Oters","MSG160","[WebServer] www.evolution-team.eu",MSG160,100,COMMANDFILE_PATH);
	GetPrivateProfileString ("Oters","MSG161","[WebServer] www.evolution-team.eu",MSG161,100,COMMANDFILE_PATH);
	int IsReset = GetPrivateProfileInt("Reset","IsReset",1,COMMANDFILE_PATH);
	int IsLevel = GetPrivateProfileInt("Reset","LvlResetFree",400,COMMANDFILE_PATH);
	int IsLevel2 = GetPrivateProfileInt("Reset","LvlResetBronze",350,COMMANDFILE_PATH);
	int IsLevel3 = GetPrivateProfileInt("Reset","LvlResetPlatinum",325,COMMANDFILE_PATH);
	int IsLevel4 = GetPrivateProfileInt("Reset","LvlResetGold",300,COMMANDFILE_PATH);
	DWORD IsZenFree = GetPrivateProfileInt("Reset","ZenResetFree",10000000,COMMANDFILE_PATH);
	DWORD IsZenBronze = GetPrivateProfileInt("Reset","ZenResetBronze",7500000,COMMANDFILE_PATH);
	DWORD IsZenPlatinum = GetPrivateProfileInt("Reset","ZenResetPlatinum",6500000,COMMANDFILE_PATH);
	DWORD IsZenGold = GetPrivateProfileInt("Reset","ZenResetGold",5000000,COMMANDFILE_PATH);
	int IsResetStat = GetPrivateProfileInt("Reset","ResetStats",0,COMMANDFILE_PATH);
	int IsTipo = GetPrivateProfileInt("Reset","BonusStats",0,COMMANDFILE_PATH);
	DWORD IsAddPuntos = GetPrivateProfileInt("Reset","Points",200,COMMANDFILE_PATH);
	int IsResetMagia = GetPrivateProfileInt("Reset","ResetSkill",0,COMMANDFILE_PATH);
	int IsResetInven = GetPrivateProfileInt("Reset","ResetInventory",0,COMMANDFILE_PATH);
return 1;
}


bool IniciaIni()
{
//char aini[] = ".\\OGC-Servers.ini";
bool rResultado;
rResultado = TransformRing ( TRANSFORM_RINGS_PATH );
rResultado = OrbSummon ( SUMMON_ORB_PATH );
rResultado = JewelPrice ( JEWELPRICES_PATH );
rResultado = CCPlayer ( CUSTOMFILE_PATH );
rResultado = ElfSoldier ( CUSTOMFILE_PATH );
rResultado = GuildAlliance ( CUSTOMFILE_PATH );
rResultado = UDPort ( CUSTOMFILE_PATH );
rResultado = JewelRate ( JEWELS_SUCC_PATH );
rResultado = BcDropIni ( BLOODCASTLE_REWARDS_PATH );
rResultado = RedDragon ( REDDRAGON_REWARDS_PATH );
rResultado = WhiteWizard ( WHITEWIZZARD_REWARDS_PATH );
rResultado = MaxLevelIni ( CUSTOMFILE_PATH );
rResultado = DarkHorseSuccesso ( DLPETS_PATH );
rResultado = DarkSpiritSuccesso ( DLPETS_PATH );
rResultado = ItemDropIni ( CUSTOMFILE_PATH );
rResultado = LevelUp ( LEVELUP_POINTS_PATH );
rResultado = MaxZen ( CUSTOMFILE_PATH );
rResultado = MaxLevel2 ( CUSTOMFILE_PATH );
rResultado = GameServer ( CUSTOMFILE_PATH );
rResultado = NPCTalk1 ( CUSTOMFILE_PATH );
rResultado = LoadZen (COMMANDFILE_PATH);
rResultado = DwSoulBarrierInit ( SKILLS_CHARS_PATH );
rResultado = DkGreaterFortitudeInit ( SKILLS_CHARS_PATH );
rResultado = CBMixInit ( CHAOS_MIXES_PATH );
rResultado = CommonSkills ( SKILLS_CHARS_PATH );
rResultado = TimeItems ( CUSTOMFILE_PATH );
rResultado = FixPartyExp ( CUSTOMFILE_PATH );
rResultado = LoadStruct ( CUSTOMFILE_PATH );
rResultado = Ancient ( CUSTOMFILE_PATH );
rResultado = PotionRecovery ( CUSTOMFILE_PATH );
rResultado = GMMoveWay ( CUSTOMFILE_PATH );
rResultado = MessageSystem();
rResultado = PotionBSPrice( CUSTOMFILE_PATH );//add 27/01/2012
rResultado = PotionBSMix( CUSTOMFILE_PATH );//add 27/01/2012
rResultado = SetItemMixRate(CHAOS_MIXES_PATH);//add 27/01/2012
rResultado = LifeStoneMixRate(CHAOS_MIXES_PATH);//add 27/01/2012
rResultado = DinorantMixSuccess(CHAOS_MIXES_PATH);//add 27/01/2012
rResultado = InterfaceColor(CUSTOMFILE_PATH);//add 27/01/2012
rResultado = ReflectInit(SKILLS_CHARS_PATH);
rResultado = BlessSoulMix(JEWELS_SUCC_PATH);

return 1;
}

void InitConfigurations()
{
GSCheckSum(CUSTOMFILE_PATH);
PersonalID(CUSTOMFILE_PATH);
}