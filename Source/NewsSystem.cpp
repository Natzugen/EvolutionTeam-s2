/*-------------------------------------------------------*/
/*				Project Evolution Team Season 2          */
/*   Version GS 1.00.18 & GS-CS 1.00.19 Protocol Eng     */
/*             http://evolution-team.eu                  */
/*-------------------------------------------------------*/
/*                    Code By Th3AnG3L                   */
/*             http://evolution-team.eu                  */
/*-------------------------------------------------------*/
#include <process.h>
#include "stdafx.h"
#include "Utilidades.h"
#include "NewsSystem.h"


bool NewsON(int ON)
{
	if(ON !=1)
		return 0;
	else
		{
				FILE *fp;
				fp=fopen(NEWSISTEMFILE_PATH,"rb");
				if(!fp)
				{
					MessageBoxA(NULL,"ENews.ini","Error!",MB_OK);
					::ExitProcess(0);
				}
				_beginthread( NewsSystemClass__InsideTrigger, 0, NULL  );
				return 1;
	}

}

void NewsSystemClass__InsideTrigger(void * lpParam)
{
	while(true)
	{
		char MSG01[50];
		char MSG02[50];
		char MSG03[50];
		
		int Sections = GetPrivateProfileIntA("Settings","Evo_Sections",0,NEWSISTEMFILE_PATH);
		long time = GetPrivateProfileIntA("Settings","Evo_Tempo",0,NEWSISTEMFILE_PATH) * 60000;
		if(Sections > 5 || Sections <= 0)
		{
			_endthread();
		}
		Sleep(time);
		GetPrivateProfileStringA("News","Evo_News1","Evolution Team!",MSG01,50,NEWSISTEMFILE_PATH);
		GetPrivateProfileStringA("News","Evo_News2","Evolution Team!",MSG02,50,NEWSISTEMFILE_PATH);
		GetPrivateProfileStringA("News","Evo_News3","Evolution Team!",MSG03,50,NEWSISTEMFILE_PATH);
		StringSendAll(MSG01,0);
		StringSendAll(MSG02,0);
		StringSendAll(MSG03,0);
		if(Sections >= 2)
		{
			Sleep(time);
			GetPrivateProfileStringA("News","Evo_News4","Evolution Team!",MSG01,50,NEWSISTEMFILE_PATH);
			GetPrivateProfileStringA("News","Evo_News5","Evolution Team!",MSG02,50,NEWSISTEMFILE_PATH);
			GetPrivateProfileStringA("News","Evo_News6","Evolution Team!",MSG03,50,NEWSISTEMFILE_PATH);
			StringSendAll(MSG01,0);
			StringSendAll(MSG02,0);
			StringSendAll(MSG03,0);
		}
		if(Sections >= 3)
		{
			Sleep(time);
			GetPrivateProfileStringA("News","Evo_News7","Evolution Team!",MSG01,50,NEWSISTEMFILE_PATH);
			GetPrivateProfileStringA("News","Evo_News8","Evolution Team!",MSG02,50,NEWSISTEMFILE_PATH);
			GetPrivateProfileStringA("News","Evo_News9","Evolution Team!",MSG03,50,NEWSISTEMFILE_PATH);
			StringSendAll(MSG01,0);
			StringSendAll(MSG02,0);
			StringSendAll(MSG03,0);
		}
		if(Sections >= 4)
		{
			Sleep(time);
			GetPrivateProfileStringA("News","Evo_News10","Evolution Team!",MSG01,50,NEWSISTEMFILE_PATH);
			GetPrivateProfileStringA("News","Evo_News11","Evolution Team!",MSG02,50,NEWSISTEMFILE_PATH);
			GetPrivateProfileStringA("News","Evo_News12","Evolution Team!",MSG03,50,NEWSISTEMFILE_PATH);
			StringSendAll(MSG01,0);
			StringSendAll(MSG02,0);
			StringSendAll(MSG03,0);
		}
		if(Sections == 5)
		{
			Sleep(time);
			GetPrivateProfileStringA("News","Evo_News13","Evolution Team!",MSG01,50,NEWSISTEMFILE_PATH);
			GetPrivateProfileStringA("News","Evo_News14","Evolution Team!",MSG02,50,NEWSISTEMFILE_PATH);
			GetPrivateProfileStringA("News","Evo_News15","Evolution Team!",MSG03,50,NEWSISTEMFILE_PATH);
			StringSendAll(MSG01,0);
			StringSendAll(MSG02,0);
			StringSendAll(MSG03,0);
		}
	}
	_endthread();
}
