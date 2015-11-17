/*-------------------------------------------------------*/
/*				Project Evolution Team Season 2          */
/*   Version GS 1.00.18 & GS-CS 1.00.19 Protocol Eng     */
/*             http://evolution-team.eu                  */
/*-------------------------------------------------------*/
/*                    Code By Th3AnG3L                   */
/*             http://evolution-team.eu                  */
/*-------------------------------------------------------*/
#ifndef __FORTUNEWHEEL_H__
#define __FORTUNEWHEEL_H__


// Wheel of Fortune
class CFortune
{
public:

	void Init(char* File);
	void LoadFile(char* File);

	void Reward(int aIndex);
	void Act(int aIndex);

	void Counter();

private:

	int m_Enabled;
	int m_MaxUsage;

	int m_SpinRate;
	int m_RewardAmount;
};

extern CFortune Fortune;

#endif