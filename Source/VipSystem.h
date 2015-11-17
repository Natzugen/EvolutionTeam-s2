/*-------------------------------------------------------*/
/*				Project Evolution Team Season 2          */
/*   Version GS 1.00.18 & GS-CS 1.00.19 Protocol Eng     */
/*             http://evolution-team.eu                  */
/*-------------------------------------------------------*/
/*                    Code By Th3AnG3L                   */
/*             http://evolution-team.eu                  */
/*-------------------------------------------------------*/
#include "user.h"
#ifndef __VIPSYSTEM_H__
#define __VIPSYSTEM_H__

// Vip System
class CVipSystem
{
public:

	void Init();
	void Load(int aIndex);

	void ApplyVip(int aIndex);

	int Vip[OBJECT_MAX - OBJECT_MIN];

	int m_Enabled;
	float m_Exp;
	float m_BronzeExp;
	int m_BronzeDrop;
	float m_PlatinumExp;
	int m_PlatinumDrop;
	float m_GoldExp;
	int m_GoldDrop;
};

long ExpCalculator(OBJECTSTRUCT* pObj,int Experience);

__declspec() void MonsterExpSingleEx();
__declspec() void MonsterExpPartyEx();

extern CVipSystem VipSystem;
#endif