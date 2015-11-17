#ifndef __STRUCTURES_H__
#define __STRUCTURES_H__

#pragma once

// Custom Structures
struct COMMANDS_INFO
{
	int postenabled;
	int postlevel;
	int postcostzen;
	int postpricezen;
	int postsave;

	int addenabled;
	int addlevel;
	int addcost;
	int addprice;
};

struct CUSTOM_INFO
{
	// Mana Shield
	int msmax;
};

struct CUSTOM_GS_STRUCT
{
	COMMANDS_INFO commands;
	CUSTOM_INFO customs;
};

extern CUSTOM_GS_STRUCT conf;

typedef	struct ADDITIONAL_STRUCT 
{			
	// QuestSystem
	int m_QuestIndex;
	int m_QuestState;
	int m_MonsterCount;

	// PostSystem
	int m_PostDelay;

	// VipSystem
	int m_Vip;

	// Other
	int m_Resets;

} ADDITIONAL_STRUCT;

extern ADDITIONAL_STRUCT AddTab[OBJECT_MAX];


#endif