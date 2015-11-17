#include "StdAfx.h"
#include "Log.h"

// Event Management
CEventManagement EventManagement;

void CEventManagement::Init(char* File)
{
	this->m_Enabled = GetPrivateProfileInt("GameServerInfo","EnableEventManager",1,CUSTOMFILE_PATH);
	this->m_EventsCount = 0;

	if(this->m_Enabled == 1)
	{
		this->LoadFile(File);
		Log.Add("%s file load!",File);
	}
}

void CEventManagement::LoadFile(char* File)
{
	SMDFile = fopen(File,"r");

	if(SMDFile == 0)
	{
		MessageBoxA(0,"Unable to load EventManagement.dat - File not found.","Error",MB_OK);
		this->m_Enabled = 0;
		return;
	}

	int iToken = 0;

	while(true)
	{
		iToken = GetToken();

		if(iToken == 2)
		{
			break;
		}

		if(iToken == 1)
		{
			int SubClass = TokenNumber;

			if(SubClass == 0)
			{
				while (true)
				{
					iToken = GetToken();

					if(iToken == 0)
					{
						if(strcmp("end",TokenString) == 0)
						{
							break;
						}
					}

					this->m_EventInfo[m_EventsCount].m_EventKind = TokenNumber;

					iToken = GetToken();
					this->m_EventInfo[m_EventsCount].m_DayWeek = TokenNumber;

					iToken = GetToken();
					this->m_EventInfo[m_EventsCount].m_Hour = TokenNumber;

					iToken = GetToken();
					this->m_EventInfo[m_EventsCount].m_Minute = TokenNumber;

					this->m_EventsCount++;
				}
			}
		}
	}

	fclose(SMDFile);
}

void CEventManagement::Run()
{
	SYSTEMTIME t;
	GetLocalTime(&t);

	for (int i=0;i<this->m_EventsCount;i++)
	{
		// Day of Week Check
		if (m_EventInfo[i].m_DayWeek != -1)
		{
			if (m_EventInfo[i].m_DayWeek < 0 || m_EventInfo[i].m_DayWeek > 6)
			{
				continue;
			}

			if (m_EventInfo[i].m_DayWeek != t.wDayOfWeek)
			{
				continue;
			}
		}

		// Hour Check
		if (m_EventInfo[i].m_Hour == 24)
		{
			m_EventInfo[i].m_Hour = 0;
		}

		if (m_EventInfo[i].m_Hour < 0 || m_EventInfo[i].m_Hour > 23)
		{
			continue;
		}

		if (m_EventInfo[i].m_Hour != t.wHour)
		{
			continue;
		}

		// Minute Check
		if (m_EventInfo[i].m_Minute == 60)
		{
			m_EventInfo[i].m_Minute = 0;
		}

		if (m_EventInfo[i].m_Minute < 0 || m_EventInfo[i].m_Minute > 59)
		{
			continue;
		}

		if (m_EventInfo[i].m_Minute != t.wMinute)
		{
			continue;
		}

		// Event Run
		StartEvent(m_EventInfo[i].m_EventKind);
	}
}

void CEventManagement::StartEvent(int EventKind)
{
	switch (EventKind)
	{
		case EVENT_ID_HATCHERY:
			HatcheryEvent.Start();
		break;

		//case EVENT_ID_BALI:
		//	BaliEvent.Start();
		//break;
	}
}