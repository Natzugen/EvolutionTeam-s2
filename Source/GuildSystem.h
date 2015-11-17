#include "USER.h"
#include "StdAfx.h"

#ifndef __GUILDSEVENT_H__
#define __GUILDSEVENT_H__

typedef void (*pCGGuildMasterInfoSave) (int, PMSG_GUILDINFOSAVE*);
extern pCGGuildMasterInfoSave CGGuildMasterInfoSave;

// Guild System
class CGuildSystem
{
public:

	void Init();
	void Check(int aIndex, PMSG_GUILDINFOSAVE *lpMsg);

private:

	int m_Enabled;
	int m_Price;
	int m_MaxGuilds;
};

extern CGuildSystem GuildSystem;

#endif