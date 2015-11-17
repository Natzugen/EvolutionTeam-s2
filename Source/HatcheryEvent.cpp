#include "StdAfx.h"
#include "Log.h"
#include "Structures.h"
#include "Utilidades.h"
#include "EventItemBag.h"

// Hatchery Event
CHatcheryEvent HatcheryEvent;

void CHatcheryEvent::Init(char* File)
{
	this->m_Enabled = GetPrivateProfileInt("GameServerInfo","EnableHatcheryEvent",1,CUSTOMFILE_PATH);
	this->m_MonsterCount = 0;
	this->m_HatcheryEvent.m_UserCount = 0;
	this->m_HatcheryEvent.m_EventState = STATE_CLOSED;

	if(this->m_Enabled == 1)
	{
		this->LoadFile(File);
		Log.Info("[HatcheryEvent]: Init -> Enabled");
	}
}

void CHatcheryEvent::LoadFile(char* File)
{
	SMDFile = fopen(File,"r");

	if(SMDFile == 0)
	{
		MessageBoxA(0,"Unable to load HatcheryEvent.dat - File not found.","Error",MB_OK);
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

					this->m_OpenTime = TokenNumber;

					iToken = GetToken();
					this->m_PrepareTime = TokenNumber;

					iToken = GetToken();
					this->m_BattleTime = TokenNumber;

					iToken = GetToken();
					this->m_SleepTime = TokenNumber * 1000;
				}
			}

			if(SubClass == 1)
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

					this->m_MonsterInfo[m_MonsterCount].m_MonsterState = TokenNumber;

					iToken = GetToken();
					this->m_MonsterInfo[m_MonsterCount].m_MonsterID = TokenNumber;

					iToken = GetToken();
					this->m_MonsterInfo[m_MonsterCount].m_MonsterX = TokenNumber;

					iToken = GetToken();
					this->m_MonsterInfo[m_MonsterCount].m_MonsterY = TokenNumber;

					iToken = GetToken();
					this->m_MonsterInfo[m_MonsterCount].m_MonsterLife = TokenNumber;

					this->m_MonsterCount++;
				}
			}
		}
	}

	fclose(SMDFile);
}

int CHatcheryEvent::CheckTicket(int aIndex)
{
	int iType = ITEMGET(14,47);

	for(int i = 12; i < 76; i++)
	{
		if(gObj[aIndex].pInventory[i].m_Type == iType && gObj[aIndex].pInventory[i].m_Level == 0)
		{
			gObjInventoryDeleteItem(aIndex,i);
			GCInventoryItemDeleteSend(aIndex,i,1);
			return true;
		}
	}

	return false;
}

void CHatcheryEvent::Npc(int aIndex,int Monster)
{
	if(!(this->m_HatcheryEvent.m_EventState == STATE_OPEN))
	{			
		if(this->m_HatcheryEvent.m_EventState == STATE_CLOSED) 
		{
			ChatTargetSend(&gObj[Monster], "Hatchery is closed now, try again later.", aIndex);
		} 
		else 
		{	
			ChatTargetSend(&gObj[Monster], "Hatchery is running now, try again later.", aIndex);
		}
	}
	else
	{	
		for (int i = 0; i < this->m_HatcheryEvent.m_UserCount; i++)
		{
			if(this->m_HatcheryEvent.m_UserIndex[i] == aIndex)
			{
				gObjTeleport(aIndex,5,160,25);
				return;
			}
		}

		if(this->m_HatcheryEvent.m_UserCount >= MAX_PLAYERCOUNT)
		{
			ChatTargetSend(&gObj[Monster], "Hatchery is already full!", aIndex);
			return;
		}

		if(AddTab[aIndex].m_Resets < MIN_RESET)
		{
			ChatTargetSend(&gObj[Monster], "You need minimum 1 reset to join!", aIndex);
			return;
		}

		if(this->CheckTicket(aIndex) == 0)
		{
			ChatTargetSend(&gObj[Monster],"You don't have Hatchery Key.",aIndex);
			return;
		}

		this->m_HatcheryEvent.m_UserIndex[this->m_HatcheryEvent.m_UserCount] = aIndex;
		this->m_HatcheryEvent.m_UserLevel[this->m_HatcheryEvent.m_UserCount] = gObj[aIndex].Level;
		this->m_HatcheryEvent.m_UserDefense[this->m_HatcheryEvent.m_UserCount] = gObj[aIndex].m_Defense;
		this->m_HatcheryEvent.m_UserDamageMin[this->m_HatcheryEvent.m_UserCount] = (gObj[aIndex].Dexterity + gObj[aIndex].Strength + gObj[aIndex].Vitality + gObj[aIndex].Energy) / 25; // NEW
		this->m_HatcheryEvent.m_UserDamageMax[this->m_HatcheryEvent.m_UserCount] = (gObj[aIndex].Dexterity + gObj[aIndex].Strength + gObj[aIndex].Vitality + gObj[aIndex].Energy) / 20; // NEW
		this->m_HatcheryEvent.m_UserCount++;

		gObjTeleport(aIndex,5,160,25);
		gObj[aIndex].MapNumber = 3;
		Log.Info("[HatcheryEvent] (%s)(%s) Registred User", gObj[aIndex].AccountID, gObj[aIndex].Name);
	}
}

void CHatcheryEvent::SetState(int iState)
{
	this->m_HatcheryEvent.m_EventState = iState;

	switch(iState)
	{
		case STATE_CLOSED:
			ServerMsgSendAll("The Hatchery Event Closed!");
			Log.Info("[HatcheryEvent] SetState -> CLOSED");
			break;

		case STATE_OPEN:
			this->m_HatcheryEvent.m_RemainTime = m_OpenTime * 60;
			Log.Info("[HatcheryEvent] SetState -> OPEN");
			break;

		case STATE_PREPARE:
			this->m_HatcheryEvent.m_RemainTime = m_PrepareTime * 60;
			this->Calculate(this->m_HatcheryEvent.m_UserCount);
			Log.Info("[HatcheryEvent] SetState -> PREPARE");
			break;

		case STATE_BATTLE:
			this->m_HatcheryEvent.m_RemainTime = m_BattleTime * 60;

			this->SetMonsters(1);
			Log.Info("[HatcheryEvent] SetState -> BATTLE");
			break;

		case STATE_BATTLE2:
			this->SetMonsters(2);
			Log.Info("[HatcheryEvent] SetState -> BATTLE 2");
			break;

		case STATE_BATTLE3:
			this->SetMonsters(3);
			Log.Info("[HatcheryEvent] SetState -> BATTLE 3");
			break;

		case STATE_BATTLE4:
			this->SetMonsters(4);
			Log.Info("[HatcheryEvent] SetState -> BATTLE 4");
			break;

		case STATE_END:
			for (int i = 0; i < this->m_HatcheryEvent.m_UserCount; i++)
			{
				if (this->m_HatcheryEvent.m_UserIndex[i] != 0)
				{
					if (OnlineStatus(gObj[this->m_HatcheryEvent.m_UserIndex[i]].m_Index) == true)
					{
						if (gObj[this->m_HatcheryEvent.m_UserIndex[i]].MapNumber == 5)
						{
							gObjTeleport(this->m_HatcheryEvent.m_UserIndex[i],3,20,243);
						}
					}
				}

				this->m_HatcheryEvent.m_UserIndex[i] = 0;
			}

			for (int i = 0; i < this->m_MonsterCount; i++)
			{
				if (this->m_HatcheryEvent.m_MonsterIndex[i] != -1)
				{
					gObjDel(this->m_HatcheryEvent.m_MonsterIndex[i]);
					this->m_HatcheryEvent.m_MonsterIndex[i] = -1;
				}	
			}

			this->m_HatcheryEvent.m_RemainTime = 0;
			this->m_HatcheryEvent.m_UserCount = 0;
			this->m_HatcheryEvent.m_SpawnedMonsters = 0;
			this->m_HatcheryEvent.m_EventState = STATE_CLOSED;
			Log.Info("[HatcheryEvent] SetState -> END");

			this->SetState(STATE_CLOSED);
			break;
	}
}

void CHatcheryEvent::Calculate(int Count)
{
	int Level = 0;
	int Defense = 0;
	int DamageMin = 0;
	int DamageMax = 0;

	for(int i = 0; i < Count; i++)
	{
		Level += this->m_HatcheryEvent.m_UserLevel[i];
		Defense += this->m_HatcheryEvent.m_UserDefense[i];
		DamageMin += this->m_HatcheryEvent.m_UserDamageMin[i];
		DamageMax += this->m_HatcheryEvent.m_UserDamageMax[i];
	}

	for (int i = 0; i < this->m_MonsterCount; i++)
	{
		this->m_MonsterInfo[i].m_MonsterLevel = Level / Count;
		this->m_MonsterInfo[i].m_MonsterDefense = Defense / Count;
		this->m_MonsterInfo[i].m_MonsterDamageMin = DamageMin / Count;
		this->m_MonsterInfo[i].m_MonsterDamageMax = DamageMax / Count;
	}
}

void CHatcheryEvent::SetMonsters(int iState)
{
	for (int i = 0; i < this->m_MonsterCount; i++)
	{
		if (this->m_MonsterInfo[i].m_MonsterState == iState)
		{
			int Result = gObjAddMonster(5);

			if (Result >= 0)
			{
				gObj[Result].X = this->m_MonsterInfo[i].m_MonsterX;
				gObj[Result].Y = this->m_MonsterInfo[i].m_MonsterY;
				gObj[Result].MapNumber = 5;
				gObj[Result].TX = gObj[Result].X;
				gObj[Result].TY = gObj[Result].Y;
				gObj[Result].m_OldX = gObj[Result].X;
				gObj[Result].m_OldY = gObj[Result].Y;
				gObj[Result].StartX = (BYTE)gObj[Result].X;
				gObj[Result].StartY = (BYTE)gObj[Result].Y;
				gObjSetMonster(Result, this->m_MonsterInfo[i].m_MonsterID);
				gObj[Result].Dir = rand() % 8;

				gObj[Result].Level = (1.2 * (this->m_MonsterInfo[i].m_MonsterLevel / 4)) + (this->m_MonsterInfo[i].m_MonsterState * 2);
				gObj[Result].Life = this->m_MonsterInfo[i].m_MonsterLife * (this->m_MonsterInfo[i].m_MonsterState + this->m_HatcheryEvent.m_UserCount);
				gObj[Result].m_Defense = this->m_MonsterInfo[i].m_MonsterDefense * (this->m_MonsterInfo[i].m_MonsterState + 1);
				gObj[Result].m_AttackDamageMin = this->m_MonsterInfo[i].m_MonsterDamageMin * (this->m_MonsterInfo[i].m_MonsterState);
				gObj[Result].m_AttackDamageMax = this->m_MonsterInfo[i].m_MonsterDamageMax * (this->m_MonsterInfo[i].m_MonsterState * 2);

				this->m_HatcheryEvent.m_SpawnedMonsters++;
				this->m_HatcheryEvent.m_MonsterIndex[this->m_HatcheryEvent.m_SpawnedMonsters] = Result;

				Log.Info("[HatcheryEvent] Mob Add: Level: %d, Defense: %d, DmgMin: %d, DmgMax: %d", gObj[Result].Level, gObj[Result].m_Defense, gObj[Result].m_AttackDamageMin, gObj[Result].m_AttackDamageMax);
			}
		}
	}
}

bool CHatcheryEvent::MonsterKillManager(OBJECTSTRUCT *lpObj, OBJECTSTRUCT *lpTargetObj)
{
	if ((this->m_HatcheryEvent.m_EventState != STATE_CLOSED) && (lpObj->MapNumber == 5))
	{
		for (int i = 0; i < this->m_MonsterCount; i++)
		{
			if (this->m_HatcheryEvent.m_MonsterIndex[i] == lpObj->m_Index)
			{
				gObjDel(this->m_HatcheryEvent.m_MonsterIndex[i]);
				this->m_HatcheryEvent.m_SpawnedMonsters--;
				this->m_HatcheryEvent.m_MonsterIndex[i] = -1;

				switch (lpObj->Class)
				{
				case 337:
					ServerMsgSendMap(5,0,"Congratulations! You have defeated the Hatchery!");

					for(int i = 0; i < this->m_HatcheryEvent.m_UserCount; i++)
					{
						if (OnlineStatus(gObj[this->m_HatcheryEvent.m_UserIndex[i]].m_Index) == true)
						{
							if((rand() % 1000) < 700)
							{
								HatcheryDrop->DropItem(this->m_HatcheryEvent.m_UserIndex[i]);
							}
						}
					}
				}

				return true;
			}
		}
	}

	return false;
}

void CHatcheryEvent::Start()
{
	if (this->m_Enabled == 0)
	{
		return;
	}

	if(this->m_HatcheryEvent.m_EventState == STATE_CLOSED)
	{
		char Message[200];
		sprintf(Message, "%d minute(s) left before entry into Hatchery.", this->m_OpenTime);
		ServerMsgSendAll(Message);
		this->SetState(STATE_OPEN);
		_beginthread(EventStart,0,NULL);
	}
}

void EventStart(void * lpParam)
{
	while (HatcheryEvent.m_HatcheryEvent.m_EventState != STATE_CLOSED)
	{
		// STATE_OPEN
		if(HatcheryEvent.m_HatcheryEvent.m_EventState == STATE_OPEN)
		{
			if (HatcheryEvent.m_HatcheryEvent.m_RemainTime <= 0)
			{
				if (HatcheryEvent.m_HatcheryEvent.m_UserCount >= MIN_PLAYERCOUNT)
				{
					char Preapare[200];
					sprintf(Preapare, "%d  minute(s) left before battle starts.", HatcheryEvent.m_PrepareTime / 60);
					ServerMsgSendMap(5, 0, Preapare);
					HatcheryEvent.SetState(STATE_PREPARE);
				}
				else
				{
					HatcheryEvent.SetState(STATE_END);
					Log.Info("[HatcheryEvent] Event Closed - Min Users Not Reached");
				}
			}
			else
			{
				HatcheryEvent.m_HatcheryEvent.m_RemainTime--;

				char Message[200];
				sprintf(Message, "%d  minute(s) left before entry into Hatchery.", HatcheryEvent.m_HatcheryEvent.m_RemainTime / 60);

				if (HatcheryEvent.m_HatcheryEvent.m_RemainTime == 240)
				{
					ServerMsgSendAll(Message);
				}
				else if (HatcheryEvent.m_HatcheryEvent.m_RemainTime == 180)
				{
					ServerMsgSendAll(Message);
				}
				else if (HatcheryEvent.m_HatcheryEvent.m_RemainTime == 120)
				{
					ServerMsgSendAll(Message);
				}
				else if (HatcheryEvent.m_HatcheryEvent.m_RemainTime == 60)
				{
					ServerMsgSendAll(Message);
				}
			}
		}

		// STATE_PREPARE
		else if(HatcheryEvent.m_HatcheryEvent.m_EventState == STATE_PREPARE)
		{
			if (HatcheryEvent.m_HatcheryEvent.m_RemainTime <= 0)
			{
				ServerMsgSendAll("The Hatchery Event has started!");
				HatcheryEvent.SetState(STATE_BATTLE);
			}
			else
			{
				HatcheryEvent.m_HatcheryEvent.m_RemainTime--;
			}
		}

		// BATTLE TIMER
		else if(HatcheryEvent.m_HatcheryEvent.m_EventState >= STATE_BATTLE && HatcheryEvent.m_HatcheryEvent.m_EventState <= STATE_BATTLE4)
		{
			if (HatcheryEvent.m_HatcheryEvent.m_RemainTime != 0)
			{
				char Battle[200];
				sprintf(Battle, "Next battle will start in %d second(s).", HatcheryEvent.m_SleepTime / 1000);

				// BATTLE1
				if(HatcheryEvent.m_HatcheryEvent.m_EventState == STATE_BATTLE)
				{
					if (HatcheryEvent.m_HatcheryEvent.m_SpawnedMonsters <= 0)
					{
						ServerMsgSendMap(5,0,Battle);
						Sleep(HatcheryEvent.m_SleepTime);
						HatcheryEvent.SetState(STATE_BATTLE2);
					}
				}

				// BATTLE 2
				else if(HatcheryEvent.m_HatcheryEvent.m_EventState == STATE_BATTLE2)
				{
					if (HatcheryEvent.m_HatcheryEvent.m_SpawnedMonsters <= 0)
					{
						ServerMsgSendMap(5,0,Battle);
						Sleep(HatcheryEvent.m_SleepTime);
						HatcheryEvent.SetState(STATE_BATTLE3);
					}
				}

				// BATTLE 3
				else if(HatcheryEvent.m_HatcheryEvent.m_EventState == STATE_BATTLE3)
				{
					if (HatcheryEvent.m_HatcheryEvent.m_SpawnedMonsters <= 0)
					{
						ServerMsgSendMap(5,0,Battle);
						Sleep(HatcheryEvent.m_SleepTime);
						HatcheryEvent.SetState(STATE_BATTLE4);
					}
				}

				// BATTLE 4
				else if(HatcheryEvent.m_HatcheryEvent.m_EventState == STATE_BATTLE4)
				{
					if (HatcheryEvent.m_HatcheryEvent.m_SpawnedMonsters <= 0)
					{
						ServerMsgSendMap(5, 0, "30 second(s) left for leave Hatchery.");
						Sleep(30000);
						HatcheryEvent.SetState(STATE_END);
					}
				}
			}
			else
			{
				ServerMsgSendMap(5, 0, "Event failed! Must kill all mobs before time is up!");
				HatcheryEvent.SetState(STATE_END);
			}

			HatcheryEvent.m_HatcheryEvent.m_RemainTime--;

			char Message[200];
			sprintf(Message, "The Hatchery will be closed in %d minute(s).", HatcheryEvent.m_HatcheryEvent.m_RemainTime / 60);

			if (HatcheryEvent.m_HatcheryEvent.m_RemainTime == 900)
			{
				ServerMsgSendAll(Message);
			}
			else if (HatcheryEvent.m_HatcheryEvent.m_RemainTime == 600)
			{
				ServerMsgSendAll(Message);
			}
			else if (HatcheryEvent.m_HatcheryEvent.m_RemainTime == 300)
			{
				ServerMsgSendAll(Message);
			}
			else if (HatcheryEvent.m_HatcheryEvent.m_RemainTime == 240)
			{
				ServerMsgSendAll(Message);
			}
			else if (HatcheryEvent.m_HatcheryEvent.m_RemainTime == 180)
			{
				ServerMsgSendAll(Message);
			}
			else if (HatcheryEvent.m_HatcheryEvent.m_RemainTime == 120)
			{
				ServerMsgSendAll(Message);
			}
			else if (HatcheryEvent.m_HatcheryEvent.m_RemainTime == 60)
			{
				ServerMsgSendAll(Message);
			}
		}

		Sleep(1000);
	}

	_endthread();
}