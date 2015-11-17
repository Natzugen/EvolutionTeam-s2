/*#ifndef __PKGUARD_H__
#define __PKGUARD_H__

// PK Guard
class CPKGuard
{
public:

	void Init(char* File);
	void LoadFile(char* File);

	void Act(int aIndex);

	void Npc(int aIndex,int Monster);

private:

	int m_Enabled;

	int m_ClearType;
	int c_Price;
	int m_Price;
};

extern CPKGuard PKGuard;

#endif */