/*-------------------------------------------------------*/
/*				Project Evolution Team Season 2          */
/*   Version GS 1.00.18 & GS-CS 1.00.19 Protocol Eng     */
/*             http://evolution-team.eu                  */
/*-------------------------------------------------------*/
/*                    Code By Th3AnG3L                   */
/*             http://evolution-team.eu                  */
/*-------------------------------------------------------*/
#include <stdio.h>
void LoadIni();
//=====================================================
//==================ANILLOS DE TRANSFORMACION==========
//=================OGC-SOFT PROGRAMACION 1.0===========
//=====================================================


#define GS_RING1 	(0x004BA5FB+3)
#define GS_RING2 	(0x004BA604+3)
#define GS_RING3 	(0x004BA60D+3)
#define GS_RING4 	(0x004BA616+3)
#define GS_RING5 	(0x004BA61F+3)
#define GS_RING6 	(0x004BA628+3)
#define GS_RING7    (0x004BA62F+3)

//============================================================================
//=============================Orbs De Elf====================================
//============================================================================

#define GS_ORB0		(0x004B9022+1)
#define GS_ORB1		(0x004B9053+1)
#define GS_ORB2		(0x004B9084+1)
#define GS_ORB3		(0x004B90B5+1)
#define GS_ORB4		(0x004B90E6+1)
#define GS_ORB5		(0x004B9117+1)
#define GS_ORB6		(0x004B914B+1)

//==============PRECIOS DE LOS JAWELS============================
#define GS_BLESS_PRICE		(0x00510B13+3)
#define GS_SOUL_PRICE		(0x00510B34+3)
#define GS_CHAOS_PRICE		(0x00510B56+3)
#define GS_LIFE_PRICE		(0x00510B78+3)
#define GS_CREATION_PRICE	(0x00510B99+3)
#define GS_GUARDIAN_PRICE	(0x00510C77+3)

//============================================================
//==========NUMEROS DE PJ PARA EL EVENTO CHAOS CASTLE=========
//============================================================

#define GS_CCPlayer 	(0x005442F0+3)

//===========================================
//=============Elf Soldier===================
//===========================================

#define GS_Elf_Soldier (0x00554DEF+1)
#define GS_BUFFERDEFENSEFORMULA	(0x00554E32+2)
#define GS_BUFFERATTACKFORMULA	(0x00554E50+2)

//==========================================
//==============Guild Alianzas==============
//==========================================

#define GS_GuildAlliance (0x00457DEB+2)


//==========================================
//================PUERTO GS=================
//==========================================

#define GS_UDP_PORT (0x0052112F+1)


//==========================================
//================RATE DE JEWELS============
//==========================================

#define GS_SOUL_RATE  (0x004FEA5B+3)
#define GS_SOUL_LUCK_RATE (0x004FE97C+3)
#define GS_LIFE_RATE  (0x004FF1EA+3)


//==========================================
//==============PREMIO BC===================
//==========================================

#define GS_BC_DROP_ID	(0x0053A1EA+1)
#define GS_BC_DROP_GROUP (0x0053A1EA+1)


//==========================================
//==============LEVEL MAXIMO================
//==========================================

#define GS_MAX_LEVEL1	(0x004C2112+3)
#define GS_MAX_LEVEL2	(0x004DC4B5+2)
#define GS_MAX_LEVEL3	(0x005359AB+1)
#define GS_MAX_LEVEL4	(0x005436DB+1)
#define GS_MAX_LEVEL5	(0x005700CB+1)

// Max Maps
//#define GS_MAX_MAPS (0x00520203+1)


//==========================================
//===============DL PETS====================
//==========================================

#define GS_DARK_HORSE	(0x00499D69+6)
#define GS_DARK_HORSE_PRICE	(0x00499D88+3)
#define GS_DARK_SPIRIT	(0x0049A46A+6)
#define GS_DARK_SPIRIT_PRICE	(0x0049A489+3)


//============================================
//==========DROP ITEMS========================
//============================================

#define GS_EXC_DROP_RATE	(0x0041B0F8+1)
#define GS_EXC_SKILL_RATE	(0x0041B44C+6) //(0x0041B44C+6)
#define GS_EXC_LUCK_RATE	(0x0041B456+6) //(0x0041B456+6)
#define GS_SKILL_RATE		(0x0041B4A5+6) //(0x0041B4A5+6)
#define GS_LUCK_RATE		(0x0041B4AF+6) //(0x0041B4AF+6)

//============================================
//=============PUNTOS POR LEVEL===============
//============================================

#define GS_LVL_UP_DL	(0x004DC58C+2) //Original 7
#define GS_LVL_UP_MG	(0x004DC5B4+2) //Original 7
#define GS_LVL_UP_NORMAL (0x004DC5CB+2) //Original 5



//============================================
//===============ZEN MAXIMO===================
//============================================

#define GS_MAX_ZEN	(0x005050A5+3) //MAX INVENTARIO
#define GS_MAX_ZEN1	(0x00447986+3) //MAX Baul 0
#define GS_MAX_ZEN2	(0x00447A7C+3) //MAX BAUL 1
#define GS_MAX_ZEN3	(0x004479B2+2) //MAx BAUL 2

#define GS_MAX_INVENTORY		(0x005050A5+3)
#define GS_MAX_VAULT1			(0x00447986+3)
#define GS_MAX_VAULT2			(0x004479B2+2)
#define GS_MAX_VAULT3			(0x00447A7C+3)

//=============================================
//==================LEVEL maximo Exp===========
//=============================================

#define GS_MaxLevel2	(0x00521262)

//==================HASTA ACA==================

//PARTY ZEN FIX
//=========================================
// Party Zen Bug Fix
//=========================================
#define GS_PARTY_ZEN_FIX (0x004E3437)

//==========================================
//Mana Shield
//==========================================
#define GS_18_ADDR_DwSoulBarrierA				( 0x004B9DEB+1 )  // default 50 0x32
#define GS_18_ADDR_DwSoulBarrierB				( 0x004B9E0B+1 )  // difault 200 0xC8
#define GS_18_ADDR_DwSoulBarrierC				( 0x004B9E36+1 )  // difault 40 dword  segun mi busqueda es 004B9E36 //original es 004B9E40
#define GS_18_ADDR_DwSoulBarrierMax1			( 0x004B9DEB+1 )  // default 50 byte 0-100 x segun mi busqueda es 004B9DEB+1 //original es 004B9E19+2
#define GS_18_ADDR_DwSoulBarrierMax2			( 0x004B9D0B+1 )  // dword x segun mi busqueda es 004B9D0B+1 //original es 004B9E1E+1


//==========================================
//INERT DEL BK
//==========================================
#define GS_18_ADDR_DkAddLifeSkillA				( 0x004B99DF+1 )  //Divisor
#define GS_18_ADDR_DkAddLifeSkillB				( 0x004B9A53+1 )  //Divisor
#define GS_18_ADDR_DkAddLifeSkillC				( 0x004B9B68+1 )  //Divisor
#define GS_18_ADDR_DkAddLifeSkillD				( 0x004B99FF+1 )  //Divisor
#define DkGreaterFortitudeInit_Offset_01		004B9A2Eh
#define DkGreaterFortitudeInit_Offset_02		004B9A2Fh
#define S3ItemRepair_Offset_01	 0x0043DD6B

/*
#define GS_18_ADDR_DkAddLifeSkillA				( 0x004CB7CF+1 )  //Divisor
#define GS_18_ADDR_DkAddLifeSkillB				( 0x004CB843+1 )  //Divisor
#define GS_18_ADDR_DkAddLifeSkillC				( 0x004CB958+1 )  //Divisor
#define GS_18_ADDR_DkAddLifeSkillD				( 0x004CB7EF+1 )  //Divisor
#define DkGreaterFortitudeInit_Offset_01		004CB81Eh
#define DkGreaterFortitudeInit_Offset_02		004CB81Fh
*/

//===========================
// MANA 2
//===========================
#define GS_MANA_SHIELD_1			(0x004B9DEB+1)
#define GS_MANA_SHIELD_2			(0x004B9E0B+1)
#define GS_MANA_SHIELD_3			(0x004B9E36+1)
//===========================================
//MAQUINA DE CHAOS RATES OFFSETS
//===========================================
// +10+11+12+13
#define GS_18_ADDR_CBmix10						( 0x00496626+6 )  //50 DW
#define GS_18_ADDR_CBmix11						( 0x00496651+6 )  //45 DW
#define GS_18_ADDR_CBmix12						( 0x0049667C+6 )  //45 DW
#define GS_18_ADDR_CBmix13						( 0x004966A7+6 )  //45 DW
#define GS_18_ADDR_CBmixMaxRate1				( 0x004966E5+6 )  //75 B 
#define GS_18_ADDR_CBmixMaxRate2				( 0x004966F1+6 )  //75 DW


#define AGInit_FIX_Z28_01						0x004294B8
#define AGInit_FIX_Z28_02						0x004D2E85
#define AGInit_FIX_Z28_03						0x00514EA4
#define AGInit_FIX_Z28_04						0x004FF1E7
#define AGInit_FIX_Z28_05						0x004D2E48

#define AGInit_FIX_PK_01						0x004B638A
#define AGInit_FIX_PK_02						0x004B665C
#define AGInit_FIX_PK_03						0x004B6687
#define AGInit_FIX_PK_DROP						0x004DECD0
#define AGInit_FIX_QUEST	                    0x00435A3B
#define AGInit_FIX_MONSTER_DIE	                0x00414FA3
#define AGInit_FIX_380_OPTION	                0x006C4B39
#define FIRESCREAM_HACK_DC_FIX	                0x0044BED3

#define CommonSkills_TwistingSlash_01			0043015Bh
#define CommonSkills_TwistingSlash_02			00430157h
#define CommonSkills_TwistingSlash_03			0x004FD024

#define GS_18_ADDR_ItemsinTheFloor1				( 0x00493A42+1 )
#define GS_18_ADDR_ItemsinTheFloor2				( 0x00493BF3+1 )

//Party Exp

#define Party2Exp								0x004E30BA
#define Party3Exp								0x004E30C9
#define Party4Exp								0x004E30D8
#define Party5Exp								0x004E30E7
#define SetParty3Exp							0x004E3084
#define SetParty4Exp							0x004E3093
#define SetParty5Exp							0x004E30A2


//Blood Castle Reward
#define GS_18_ADDR_BCRewardID	 ( 0x0053A1E8+1 )
#define GS_18_ADDR_BCRewardType	 ( 0x0053A1EA+1 )
#define GS_18_ADDR_BCRewardOpt1	 ( 0x0053A1FF+1 )
#define GS_18_ADDR_BCRewardOpt2	 ( 0x0053A201+1 )
#define GS_18_ADDR_BCRewardOpt3	 ( 0x0053A203+1 )
#define GS_18_ADDR_BCRewardOpt4	 ( 0x0053A205+1 )
#define GS_18_ADDR_BCRewardOpt5	 ( 0x0053A207+1 )

#define GS_CCREWARD1			(0x00547404+3)
#define GS_CCREWARD2			(0x00547441+3)
#define GS_CCREWARD3			(0x005474B7+3)
#define GS_CCREWARD4			(0x005474F5+3)
#define GS_BCREWARDTYPE			(0x0053A1EB)
#define GS_BCREWARDITEMID		(0x0053A1E9)
#define GS_REDDRAGONREWARDID1	(0x0041AB03+1)
#define GS_REDDRAGONREWARDTYPE1	(0x0041AB05+1)
#define GS_REDDRAGONREWARDID2	(0x0041AB71+1)
#define GS_REDDRAGONREWARDTYPE2	(0x0041AB73+1)
#define GS_WHITEWIZREWARDID		(0x0046D1C7+1)
#define GS_WHITEWIZREWARDTYPE	(0x0046D1C9+1)
#define GS_CHAOSMIX_10			(0x0049662C)
#define GS_CHAOSMIX_11			(0x00496657)
#define GS_CHAOSMIX_12			(0x00496682)
#define GS_CHAOSMIX_13			(0x004966AD)
#define GS_CHAOSMIX_MAXRATE1	(0x004966EB)
#define GS_CHAOSMIX_MAXRATE2	(0x004966F7)
#define GS_CHAOSMIX_LUCKADD		(0x004966D8)
#define GS_CAPEMIXRATE1			(0x00497DF0+6)
#define GS_CAPEMIXRATE2			(0x00497DFC+6)
#define GS_WINGLVL1MIXRATE1		(0x00498499+6)
#define GS_WINGLVL1MIXRATE2		(0x004984A5+6)
#define GS_WINGLVL2MIXRATE1		(0x00497E11+6)
#define GS_WINGLVL2MIXRATE2		(0x00497E1D+6)
#define GS_MANASHIELDA			(0x004B9DEC)//0x004B9DEC
#define GS_MANASHIELDB			(0x004B9E0C)//0x004B9E0C
#define GS_MANASHIELDC			(0x004B9E37)//0x004B9E37
#define GS_FORTITUDEA			(0x004B99E0)
#define GS_FORTITUDED			(0x004B9A00)
#define GS_ANCIENTEXC			(0x0050E556)
#define GS_ANCIENTJOH			(0x005735DB)
#define GS_HP_RECOVERY1			(0x0044D5D2)
#define GS_HP_RECOVERY2			(0x0044D5DB)
#define GS_HP_RECOVERY3			(0x0044D5E4)
#define GS_HP_RECOVERY4			(0x0044D5ED)
#define GS_MP_RECOVERY1			(0x0044D90D)
#define GS_MP_RECOVERY2			(0x0044D945)
#define GS_MP_RECOVERY3			(0x0044D97D)
#define GS_PARTYBONUS1			(0x004E30BA)
#define GS_PARTYBONUS2			(0x004E30C9)
#define GS_PARTYBONUS3			(0x004E30D8)
#define GS_PARTYBONUS4			(0x004E30E7)
#define GS_PARTYBONUS5			(0x004E3084)
#define GS_PARTYBONUS6			(0x004E3093)
#define GS_PARTYBONUS7			(0x004E30A2)
#define GS_PARTYBONUS8			(0x00465CF9)
#define GS_PARTYBONUS9			(0x00465D08)
#define GS_PARTYBONUS10			(0x00465D17)
#define GS_PARTYBONUS11			(0x00465D26)
#define GS_PARTYBONUS12			(0x00465CC3)
#define GS_PARTYBONUS13			(0x00465CD2)
#define GS_PARTYBONUS14			(0x00465CE1)
#define GS_GENPOINTS1			(0x004DC5CB+2)
#define GS_GENPOINTS2			(0x00535AF3+2)
#define GS_GENPOINTS3			(0x00543823+2)
#define GS_GENPOINTS4			(0x00570213+2)
#define GS_MGPOINTS1			(0x004DC5B4+2)
#define GS_MGPOINTS2			(0x00535AD0+2)
#define GS_MGPOINTS3			(0x00543800+2)
#define GS_MGPOINTS4			(0x005701F0+2)
#define GS_DLPOINTS1			(0x004DC58C+2)
#define GS_DLPOINTS2			(0x00535AD0+2)
#define GS_DLPOINTS3			(0x00543800+2)
#define GS_DLPOINTS4			(0x005701F0+2)
#define GS_MARLONPOINTS1		(0x004DC5EF+2)
#define GS_MARLONPOINTS2		(0x00535B29+2)
#define GS_MARLONPOINTS3		(0x00543859+2)
#define GS_MARLONPOINTS4		(0x00570249+2)
#define GS_TWISTINGSLASHLVLREQ	(0x00483640+7)
#define GS_RAGEFULBLOWLVLREQ	(0x00483659+7)
#define GS_DEATHSTABLVLREQ		(0x00483672+7)
#define GS_FORTITUDELVLREQ		(0x004836A4+7)
#define GS_PENETRATIONLVLREQ	(0x004836BD+7)
#define GS_DARKRAVENDURABILITY	(0x004C9694+2)

#define GS_18_ADDR_BlessWaterPrice	 (0x00510CAF+2)	// 祝福药水价格 90W
#define GS_18_ADDR_SoulWaterPrice	 (0x00510CD5+2)	// 灵魂药水价格 45W
#define GS_18_ADDR_BlessMixPrice	 (0x00510BC5+2)	// (+0/+1/+2)祝福组合价格=祝福价格X10
#define GS_18_ADDR_SoulMixPrice	 (0x00510BF3+2)	// (+0/+1/+2)灵魂组合价格=灵魂价格X10

//AttackSpeed-Defense-Etc
#define GS_18_ADDR_AttackDamageMin_Bow_StrDexDiv_Elf1	 0x004C2BD3
#define GS_18_ADDR_AttackDamageMin_Bow_StrDexDiv_Elf2	 0x004C2C02

#define GS_18_ADDR_AttackDamageMax_Bow_StrDexDiv_Elf1	 0x004C2BEA
#define GS_18_ADDR_AttackDamageMax_Bow_StrDexDiv_Elf2	 0x004C2C19

#define GS_18_ADDR_AttackDamageMin_NoBow_DexDiv_Elf1	 0x004C2C33
#define GS_18_ADDR_AttackDamageMin_NoBow_DexDiv_Elf2	 0x004C2C7B

#define GS_18_ADDR_AttackDamageMin_NoBow_StrDiv_Elf1	 0x004C2C40
#define GS_18_ADDR_AttackDamageMin_NoBow_StrDiv_Elf2	 0x004C2C88

#define GS_18_ADDR_AttackDamageMax_NoBow_Elf1	 0x004C2C56
#define GS_18_ADDR_AttackDamageMax_NoBow_Elf2	 0x004C2C9E

#define GS_18_ADDR_AttackDamageMin_DexStrDiv_Elf1	 0x004C2CC8
#define GS_18_ADDR_AttackDamageMin_DexStrDiv_Elf2	 0x004C2CF7

#define GS_18_ADDR_AttackDamageMax_DexStrDiv_Elf1	 0x004C2D0E
#define GS_18_ADDR_AttackDamageMax_DexStrDiv_Elf2	 0x004C2CDF

#define GS_18_ADDR_AttackDamageMin_StrDiv_DK1	 0x004C2D39
#define GS_18_ADDR_AttackDamageMin_StrDiv_DK2	 0x004C2D62

#define GS_18_ADDR_AttackDamageMax_StrDiv_DK1	 0x004C2D4D
#define GS_18_ADDR_AttackDamageMax_StrDiv_DK2	 0x004C2D76

#define GS_18_ADDR_AttackDamageMin_StrDiv_MG1	 0x004C2DA5
#define GS_18_ADDR_AttackDamageMin_StrDiv_MG2	 0x004C2DED

#define GS_18_ADDR_AttackDamageMin_EneDiv_MG1	 0x004C2DB2
#define GS_18_ADDR_AttackDamageMin_EneDiv_MG2	 0x004C2DFA

#define GS_18_ADDR_AttackDamageMax_StrDiv_MG1	 0x004C2DC8
#define GS_18_ADDR_AttackDamageMax_StrDiv_MG2	 0x004C2E10

#define GS_18_ADDR_AttackDamageMin_StrDiv_DL1	 0x004C2E95
#define GS_18_ADDR_AttackDamageMin_StrDiv_DL2	 0x004C2E4F

#define GS_18_ADDR_AttackDamageMin_EneDiv_DL1	 0x004C2E5C
#define GS_18_ADDR_AttackDamageMin_EneDiv_DL2	 0x004C2EA2

#define GS_18_ADDR_AttackDamageMax_StrDiv_DL1	 0x004C2E72
#define GS_18_ADDR_AttackDamageMax_StrDiv_DL2	 0x004C2EB8

#define GS_18_ADDR_AttackDamageMax_EneDiv_DL1	 0x004C2E7F
#define GS_18_ADDR_AttackDamageMax_EneDiv_DL2	 0x004C2EC5

#define GS_18_ADDR_AttackDamageMin_StrDiv_DWSU1	 0x004C2EDD
#define GS_18_ADDR_AttackDamageMin_StrDiv_DWSU2	 0x004C2F07

#define GS_18_ADDR_AttackDamageMax_StrDiv_DWSU1	 0x004C2EF2
#define GS_18_ADDR_AttackDamageMax_StrDiv_DWSU2	 0x004C2F1C

#define GS_18_ADDR_AttackSpeed_Elf1	 ( 0x004C3436+1 ) //32
#define GS_18_ADDR_AttackSpeed_Elf2	 ( 0x004C344A+1 ) //32
#define GS_18_ADDR_AttackSpeed_DK_MG1	 ( 0x004C3485+1 ) //0F 
#define GS_18_ADDR_AttackSpeed_DK_MG2	 ( 0x004C3499+1 ) //14 
#define GS_18_ADDR_AttackSpeed_DL1	 ( 0x004C34C0+1 ) //0A
#define GS_18_ADDR_AttackSpeed_DL2	 ( 0x004C34D4+1 ) //0A
#define GS_18_ADDR_AttackSpeed_DS1	 ( 0x004C34EA+1 ) //14 
#define GS_18_ADDR_AttackSpeed_DS2	 ( 0x004C34FE+1 ) //0A 

#define GS_18_ADDR_SuccessfulBlocking_Elf	 ( 0x004C3A5C+1 ) //default /4 
#define GS_18_ADDR_SuccessfulBlocking_DS_DK_MG	( 0x004C3A84+1 ) // /3
#define GS_18_ADDR_SuccessfulBlocking_DL	 ( 0x004C3A9A+1 ) // /7

#define GS_18_ADDR_Defense_Elf	 ( 0x004C3EB5+1 ) // /0A
#define GS_18_ADDR_Defense_DK	 ( 0x004C3EDC+1 ) // /3
#define GS_18_ADDR_Defense_DL	 ( 0x004C3F03+1 ) // /7
#define GS_18_ADDR_Defense_DS_MG	 ( 0x004C3F19+1 ) // /4

#define BlessPotionMix				(0x0049AA0E)//add 27/01/2012
#define SoulPotionMix				(0x0049AE1E)//add 27/01/2012
#define BlessPotionPrice			 0x0051132B//add 27/01/2012
#define SoulPotionPrice				 0x00510CD7//add 27/01/2012
#define SetItemRate1				(0x00499378+6)//add 27/01/2012
#define SetItemRate2				(0x00499384+6)//add 27/01/2012
#define DinorantMix					(0x004970A8)//add 27/01/2012
#define LifeStoneMix				(0x0049B2B1)//add 27/01/2012
#define MenuColorNormal					(0x004A9747+1) //Green Default add 27/01/2012
#define MenuColorDSDisconnected			(0x004A9758+1) //Pink Default add 27/01/2012
#define MenuTextColor					(0x004A9D17+1) //White Default add 27/01/2012

#define GS_DAMAGEREF_DIV1			0x0040F354 //add 28/01/2012
#define GS_DAMAGEREF_DIV2			0x0040F36C //add 28/01/2012


#define LogAdd ((void(*)(BYTE,char*,...)) 0x00403C01)
bool IniciaIni();
void InitConfigurations();

