/*-------------------------------------------------------*/
/*				Project Evolution Team Season 2          */
/*   Version GS 1.00.18 & GS-CS 1.00.19 Protocol Eng     */
/*             http://evolution-team.eu                  */
/*-------------------------------------------------------*/
/*                    Code By Th3AnG3L                   */
/*             http://evolution-team.eu                  */
/*-------------------------------------------------------*/
#include "StdAfx.h"
#include <stdio.h>
#include <direct.h>
#include <time.h>
#include <math.h>
#include <windows.h>
#include <commctrl.h>
#include <string.h>


GMSYSTEM GMSystemInfo[255];
int GMSystemCount;

void LoadGMSystem()
{
	FILE *fp;
	BOOL bRead = FALSE;
	DWORD dwArgv = 0;
	char sLineTxt[255] = {0};
	GMSystemCount = 1;

	fp = fopen(GMSISTEMFILE_PATH,"r");

	if(!fp)
	{
		MessageBoxA(NULL, "EGMSystem.ini not found!!", "Error!", MB_OK);
		::ExitProcess(0);
	}

	rewind(fp);
	
	while(fgets(sLineTxt, 255, fp) != NULL)
	{
		if(sLineTxt[0] == '/')continue;
		if(sLineTxt[0] == ';')continue;

		int n[18];
		char GetGMName[11];

		sscanf(sLineTxt, "%s %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d", &GetGMName, &n[0], &n[1], &n[2], &n[3], &n[4], &n[5], &n[6], &n[7], &n[8], &n[9], &n[10], &n[11], &n[12], &n[13], &n[14], &n[15], &n[16], &n[17]);
		sprintf(GMSystemInfo[GMSystemCount].Name,"%s",GetGMName);
		GMSystemInfo[GMSystemCount].Drop	= n[0];
		GMSystemInfo[GMSystemCount].Gg		= n[1];
		GMSystemInfo[GMSystemCount].Zen 	= n[2];
		GMSystemInfo[GMSystemCount].Re		= n[3];
		GMSystemInfo[GMSystemCount].Cre		= n[4];
		GMSystemInfo[GMSystemCount].Skin	= n[5];
		GMSystemInfo[GMSystemCount].On		= n[6];
		GMSystemInfo[GMSystemCount].SetPk	= n[7];
		GMSystemInfo[GMSystemCount].SetZen  = n[8];
		GMSystemInfo[GMSystemCount].SetLevel  = n[9];
		GMSystemInfo[GMSystemCount].MutePost  = n[10];
		GMSystemInfo[GMSystemCount].Unmute  = n[11];
		GMSystemInfo[GMSystemCount].BanChar  = n[12];
		GMSystemInfo[GMSystemCount].UnBanChar  = n[13];
		GMSystemInfo[GMSystemCount].Move  = n[14];
		GMSystemInfo[GMSystemCount].Gmove = n[15];
		GMSystemInfo[GMSystemCount].Cash = n[16];
		GMSystemInfo[GMSystemCount].BanAccount = n[17];
		GMSystemCount++;
	}

	rewind(fp);
	fclose(fp);
}
