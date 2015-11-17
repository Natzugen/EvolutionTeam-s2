/*-------------------------------------------------------*/
/*				Project Evolution Team Season 2          */
/*   Version GS 1.00.18 & GS-CS 1.00.19 Protocol Eng     */
/*             http://evolution-team.eu                  */
/*-------------------------------------------------------*/
/*                    Code By Th3AnG3L                   */
/*             http://evolution-team.eu                  */
/*-------------------------------------------------------*/
#ifndef __RESETGUARD_H__
#define __RESETGUARD_H__

// Reset Guard
struct RESET_INFO
{
	int m_Class;
	int m_KeepStat;
	int m_AddStat;
	int m_ExtraStat;
	int m_ResetLevel;
	int m_NewLevel;
	int m_ReqPrice;
	int m_Price;
	int m_ResetCounter;

	int m_ReqItem;
	int m_ItemType;
	int m_ItemIndex;
};

class CResetGuard
{
public:

	void Init(char* File);
	void LoadFile(char* File);

	void ResetStats(int aIndex,int Class);
	void UpdateStats(int aIndex);
	int CheckItem(int aIndex);

	void Act(int aIndex);

	void Npc(int aIndex,int Monster);

private:

	int m_Enabled;

	int m_Info;
	int m_ReqInfo;
	RESET_INFO m_ResetInfo[255];
	
};

extern CResetGuard ResetGuard;

#endif