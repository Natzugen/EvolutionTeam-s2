#ifndef __HATCHERYEVENT_H__
#define __HATCHERYEVENT_H__

// Hatchery Event
#define MIN_RESET 1
#define MIN_PLAYERCOUNT	2
#define MAX_PLAYERCOUNT	10

enum EVENT_STATE
{
	STATE_CLOSED,
	STATE_OPEN,
	STATE_PREPARE,
	STATE_BATTLE,
	STATE_BATTLE2,
	STATE_BATTLE3,
	STATE_BATTLE4,
	STATE_END
};

typedef struct 
{
	int	m_EventState;
	int	m_RemainTime;
	int	m_UserCount;
	int m_UserIndex[50];
	int	m_SpawnedMonsters;
	int	m_MonsterIndex[50];

	// HARD
	int m_UserLevel[50];
	int m_UserDefense[50];
	int m_UserDamageMin[50];
	int m_UserDamageMax[50];
	int m_UserMagicDamageMin[50];
	int m_UserMagicDamageMax[50];

} EVENT_DATA, *LPEVENT_DATA;

struct MONSTER_INFO
{
	int m_MonsterState;
	int m_MonsterID;
	int m_MonsterX;
	int m_MonsterY;
	int m_MonsterLife;

	int m_MonsterLevel;
	int m_MonsterDefense;
	int m_MonsterDamageMin;
	int m_MonsterDamageMax;
};

class CHatcheryEvent
{
public:

	void Init(char* File);
	void LoadFile(char* File);
	int CheckTicket(int aIndex);
	void Npc(int aIndex,int Monster);
	void SetState(int iState);
	void Calculate(int Count);
	void SetMonsters(int iState);
	bool MonsterKillManager(OBJECTSTRUCT *lpObj, OBJECTSTRUCT *lpTargetObj);
	void Start();

	int m_StageCount;
	int m_MonsterCount;
	int m_TotalRewards;

	int m_OpenTime;
	int m_PrepareTime;
	int m_BattleTime;
	int	m_SleepTime;

	EVENT_DATA m_HatcheryEvent;

private:

	int m_Enabled;
	MONSTER_INFO m_MonsterInfo[255];
};

void EventStart(void * lpParam);

extern CHatcheryEvent HatcheryEvent;

#endif