#ifndef __NPC_H__
#define __NPC_H__

// NPC Manager
class CNPC
{
public:

	void Init();
	void Talk(int aIndex,int Monster);

private:

	int Archer_Enabled;
	int PKGuard_Enabled;
	int ResetGuard_Enabled;
	int m_Enabled;
	int m_Count;
};

int gObjSetMonsterEx(int aIndex,int Monster);

extern CNPC NPC;

#endif