/*-------------------------------------------------------*/
/*				Project Evolution Team Season 2          */
/*   Version GS 1.00.18 & GS-CS 1.00.19 Protocol Eng     */
/*             http://evolution-team.eu                  */
/*-------------------------------------------------------*/
/*                    Code By Th3AnG3L                   */
/*             http://evolution-team.eu                  */
/*-------------------------------------------------------*/
#include "Drops.h"
#include "Utilidades.h"
#include "GameServer.h"
#include "Global.h"
#include "Configs.h"
C_DropSystem Drop;

void C_DropSystem::t_LoadSystem()
{
	this->t_num = 0;
	FILE * hFile;
	fopen_s(&hFile, ITEMDROPFILE_PATH, "r");
	char Linha[1024];
	int type,index,lvl,opt,luck,skill,dur,rate,minlvl,maxlvl,exc,ancient;

	if(hFile == 0)
	{
		MessageBox(0, "EItemDropRate.ini - File not found", "Critical Error", MB_OK | MB_ICONSTOP);
		ExitThread(0);
		return;
	}

    while(!feof(hFile))
    {
        fgets(Linha, 1024, hFile);
		if(!strcmp(Linha, "end"))
			break;

		if(Linha[strlen(Linha) - 1] == '\n' || Linha[strlen(Linha) - 1] == '\r')
		{
			if(Linha[0] != '/' || Linha[1] != '/')
			{
				if(t_num > MAX_DROP_NUMBER)
				{
					MessageBoxA(NULL,"Error reading file, Maximum /n\
									 Drops Configuration!","Fatal Error",NULL);
					ExitThread(0);
				}
				sscanf_s(Linha, "%d %d %d %d %d %d %d %d %d %d %d %d", &type, &index, &lvl, &opt, &luck, &skill, &dur, &rate, &minlvl, &maxlvl, &exc, &ancient);
				t_struct[this->t_num].Type		= type;
				t_struct[this->t_num].Index		= index;
				t_struct[this->t_num].Level		= lvl;	
				t_struct[this->t_num].Opt		= opt;	
				t_struct[this->t_num].Luck		= luck;	
				t_struct[this->t_num].Skill		= skill;
				t_struct[this->t_num].Dur		= dur;	
				t_struct[this->t_num].Rate		= rate;	
				t_struct[this->t_num].Minlvl	= minlvl;	
				t_struct[this->t_num].Maxlvl	= maxlvl;
				t_struct[this->t_num].Exc		= exc;
				t_struct[this->t_num].Ancient   = ancient;
				t_num++;
			}
		}
	}
	fclose(hFile);
}
int C_DropSystem::MygEventMonsterItemDrop(BYTE * b_MonsterDataAddr,BYTE * a_gObjAddr)
{
	for(int i = 0; i < t_num; i++)
	{	
		
	WORD wMonsterLv=0;
	WORD wMonsterId=0;
	WORD Player;
	BYTE cMapID,cX,cY;
	PBYTE bDataAddr=0;
	bDataAddr=(PBYTE)b_MonsterDataAddr;

	memcpy(&Player,bDataAddr+0x73,sizeof(WORD));
	memcpy(&wMonsterLv,bDataAddr+0xA0,sizeof(WORD));
	memcpy(&wMonsterId,bDataAddr+0x9C,sizeof(WORD));
	memcpy(&cMapID,bDataAddr+0x10D,sizeof(BYTE));
	memcpy(&cX,bDataAddr+0x108,sizeof(BYTE));
	memcpy(&cY,bDataAddr+0x10A,sizeof(BYTE));
	

	DWORD Item = t_struct[i].Type * 512 + t_struct[i].Index;


	DWORD dwTopHitUser=gObjMonsterTopHitDamageUser(b_MonsterDataAddr);
	DWORD dwRand=rand();
		
	if(this->t_struct[i].Minlvl <= wMonsterLv && this->t_struct[i].Maxlvl >= wMonsterLv)
		{
		    if((rand()%10000) < this->t_struct[i].Rate)

				{
				ItemSerialCreateSend(b_MonsterDataAddr[0],cMapID,cX,cY,Item,t_struct[i].Level,t_struct[i].Dur,t_struct[i].Skill,t_struct[i].Luck,t_struct[i].Opt,dwTopHitUser,t_struct[i].Exc,t_struct[i].Ancient);
				return 1;
				}
		}
	}
	int rValue = gEventMonsterItemDrop(b_MonsterDataAddr, a_gObjAddr);
	return rValue;
}


void MonsterDropCall(BYTE * b_MonsterDataAddr,BYTE * a_gObjAddr)
{
	Drop.MygEventMonsterItemDrop(b_MonsterDataAddr,a_gObjAddr);
}