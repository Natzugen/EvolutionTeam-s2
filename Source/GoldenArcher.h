/*-------------------------------------------------------*/
/*				Project Evolution Team Season 2          */
/*   Version GS 1.00.18 & GS-CS 1.00.19 Protocol Eng     */
/*             http://evolution-team.eu                  */
/*-------------------------------------------------------*/
/*                    Code By Th3AnG3L                   */
/*             http://evolution-team.eu                  */
/*-------------------------------------------------------*/
#ifndef __GOLDENARCHER_H__
#define __GOLDENARCHER_H__

// Golden Archer
struct ARCHER_REWARD_INFO
{
	int m_DropType;
	int m_DropIndex;
	int m_DropLevel;
	int m_DropOption;
	int m_DropLuck;
	int m_DropSkill;
	float m_DropDurability;
	int m_DropExcellent;
	int m_DropRate;
};

class CGoldenArcher
{
public:

	void Init(char* File);
	void LoadFile(char* File);

	int CheckRena(int aIndex);
	int RandomizeDrop(int aIndex);

	void Act(int aIndex);
	
	void Npc(int aIndex,int Monster);

private:

	int m_Enabled;

	int m_TotalDrops;
	int m_RenaCount;
	ARCHER_REWARD_INFO m_RewardInfo[255];
};

extern CGoldenArcher GoldenArcher;

#endif