/*-------------------------------------------------------*/
/*				Project Evolution Team Season 2          */
/*   Version GS 1.00.18 & GS-CS 1.00.19 Protocol Eng     */
/*             http://evolution-team.eu                  */
/*-------------------------------------------------------*/
/*                    Code By Th3AnG3L                   */
/*             http://evolution-team.eu                  */
/*-------------------------------------------------------*/
#include "Move.h"
#include "Struct.h"
#include "User.h"
#include "GameServer.h"
#include "Utilidades.h"

C_Teleport Move;

void C_Teleport::t_LoadTeleports()
{
	this->t_num = 0;
	FILE* mFile;
	fopen_s(&mFile, "..\\EData\\EMoveReq.ini","r");
	char Linha[1024];
	int map,x1,x2,y1,y2,xp,zen,lvl;

	if(mFile == 0)
	{
		MessageBox(0, "EMoveReq.ini - File Not Found", "Critical Error", MB_OK | MB_ICONSTOP);
		ExitThread(0);
		return;
	}

    while(!feof(mFile))
    {
        fgets(Linha, 1024, mFile);
		if(!strcmp(Linha, "end"))
			break;

        if(Linha[strlen(Linha) - 1] == '\n' || Linha[strlen(Linha) - 1] == '\r')
        {
            if(Linha[0] != '/' || Linha[1] != '/')
            {
				if(t_num > MAX_TELEPORT_NUMBER)
				{
					MessageBoxA(NULL,"Error reading teleport file, max /n\
									 number of moves overflowed!","Fatal Error",NULL);
					ExitThread(0);
				}
				char *rest;
				strcpy_s(t_struct[this->t_num].t_Name, 30, strtok_s(Linha,	"	        ", &rest));
				sscanf_s(rest, "%d %d %d %d %d %d %d",&map,&x1,&y1,&x2,&y2,&lvl,&zen);
				t_struct[this->t_num].map = map;
				t_struct[this->t_num].x1 = x1;
				t_struct[this->t_num].x2 = x2;
				t_struct[this->t_num].y1 = y1;
				t_struct[this->t_num].y2 = y2;
				t_struct[this->t_num].Money = zen;
				t_struct[this->t_num].MinLevel = lvl;
				t_num++;
            }
        }
    }
    fclose(mFile);
}
void C_Teleport::t_PlayerTeleport(DWORD aIndex, char *cmd)
{
	for(int i = 0; i < t_num; i++)
	{
		char Message[200];
		if(!_strcmpi(cmd,t_struct[i].t_Name))
		{
			OBJECTSTRUCT * gObj = (OBJECTSTRUCT*)OBJECT_POINTER(aIndex);

			unsigned char WarpMoney = t_struct[i].Money;
			unsigned short RequireLevel = t_struct[i].MinLevel;

			if( gObj->Level < RequireLevel )
			{
				LogAddFunc1(2,"Move -> [%s][%s] Not enough level to teleport",gObj->AccountID,gObj->Name);
				return;
			}

			else if(gObj->Money < WarpMoney)
			{
				LogAddFunc1(2,"Move -> [%s][%s] Not enough zen to teleport",gObj->AccountID,gObj->Name);
				return;
			}

			else if(gObj->m_PK_Level == 6)
			{
				LogAddFunc1(2,"Move -> [%s][%s] PK Try teleporting",gObj->AccountID,gObj->Name);
				return;
			}
			else if(t_struct[i].map == 10 && gObj->pInventory[WINGS].m_Type == SLOT_EMPTY && gObj->pInventory[GUARDIAN].m_Type != 0x1a25)
			{
				LogAddFunc1(2,"Move -> [%s][%s] Try Teleporting Icarus without Wings",gObj->AccountID,gObj->Name);
				return;
			}
			else if(t_struct[i].map == 7 && gObj->pInventory[GUARDIAN].m_Type == 0x1A02 || t_struct[i].map == 7 && gObj->pInventory[GUARDIAN].m_Type == 0x1A03)
			{
				LogAddFunc1(2,"Move -> [%s][%s] Try teleporting Altans with Uni or Dino",gObj->AccountID,gObj->Name);
				return;
			}
			else
			{
				int FinalX;
				int FinalY;

				if((t_struct[i].x2 - t_struct[i].x1) > 0)
				{
					FinalX = min(t_struct[i].x1, t_struct[i].x2) + rand()% (max(t_struct[i].x1, t_struct[i].x2) - min(t_struct[i].x1, t_struct[i].x2));
				}
				else
				{
					FinalX = t_struct[i].x1;
				}

				if((t_struct[i].y2 - t_struct[i].y1) > 0)
				{
					FinalY = min(t_struct[i].y1, t_struct[i].y2) + rand()% (max(t_struct[i].y1, t_struct[i].y2) - min(t_struct[i].y1, t_struct[i].y2));
				}
				else 
				{
					FinalY =  t_struct[i].y1;
				}
				


				gObj->X = FinalX;
				gObj->Y = FinalY;

				gObj->Money -= t_struct[i].Money;
				GCMoneySend(aIndex,gObj->Money);

				gObjTeleport(aIndex, t_struct[i].map, gObj->X, gObj->Y);
				LogAddFunc1(2,"Move -> [%s][%s] Teleport OK - New Position = [%s]",gObj->AccountID,gObj->Name,t_struct[i].t_Name);
			}
		}
	}
}