#ifndef __EVENTMANAGEMENT_H__
#define __EVENTMANAGEMENT_H__

// Event Management
enum
{
	EVENT_ID_HATCHERY = 0,
	EVENT_ID_BALI = 1,
};

struct EVENT_ID_SETTINGS
{
	int m_EventKind;
	int m_DayWeek;
	int m_Hour;
	int m_Minute;
};

class CEventManagement
{
public:

	void Init(char* File);
	void LoadFile(char* File);

	void Run();
	void StartEvent(int EventKind);

private:

	int m_Enabled;
	int m_EventsCount;
	EVENT_ID_SETTINGS m_EventInfo[255];
};

extern CEventManagement EventManagement;

#endif