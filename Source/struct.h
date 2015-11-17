/*-------------------------------------------------------*/
/*				Project Evolution Team Season 2          */
/*   Version GS 1.00.18 & GS-CS 1.00.19 Protocol Eng     */
/*             http://evolution-team.eu                  */
/*-------------------------------------------------------*/
/*                    Code By Th3AnG3L                   */
/*             http://evolution-team.eu                  */
/*-------------------------------------------------------*/
#include "StdAfx.h"
#ifndef STRUCT_H
#define STRUCT_H


struct COMANDO_POST
{
int switchpost;
};

struct COMANDO_DROP
{
int Active;
};


struct QUEST_ITEM_DROP
{
int Active;
int MapID1; //Death Flame Map ID
int MapID2; //Hell Horn Map ID
int MapID3; //Feather of Phoenix Map ID
int MinZen1; //Zen Quest Part1
int MinZen2; //Zen Quest Part2
int MinZen3; //Zen Quest Part3
int MinLevel1; //Level Quest Part1
int MinLevel2; //Level Quest Part2
int MinLevel3; //level quest part3
int DropRate1; //Death Flame Drop Rate
int DropRate2; //Hell Horn Drop Rate
int DropRate3; //Feather of Phoenix drop rate
};

struct MOVE_POINT
{
char CityName[30];
unsigned char MapNum;
short cX;
short cY;
int MinZen;
short MinLevel;
};

struct CONMEMBER_RELOAD
{
int active;
int time;
int pasttime;
};

struct COMANDO_SKIN
{
int active;
int onlyforgm;
int level;
int zen;
};

struct COMANDO_ZEN
{
int active;
int onlyforgm;
};


struct EvoServers
{
COMANDO_POST cmdpost;
COMANDO_DROP cmddrop;
QUEST_ITEM_DROP s3quest;
MOVE_POINT moves;
CONMEMBER_RELOAD cmember;
COMANDO_SKIN cmdskin;
COMANDO_ZEN cmdzen;
};

extern EvoServers configs;

#endif

typedef struct EventTimes
{
	UINT Type;
	UINT Hour;
	UINT Minute;

	UINT Month;
	UINT Day;
	UINT DayOfWeek;
}EVENTTIMES;

extern EVENTTIMES EventTimesConfig[255]; 
extern int EventTimeCount;