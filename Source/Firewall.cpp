/*-------------------------------------------------------*/
/*				Project Evolution Team Season 2          */
/*   Version GS 1.00.18 & GS-CS 1.00.19 Protocol Eng     */
/*             http://evolution-team.eu                  */
/*-------------------------------------------------------*/
/*                    Code By Th3AnG3L                   */
/*             http://evolution-team.eu                  */
/*-------------------------------------------------------*/
#include "StdAfx.h"

IPBLOCK IPBlockInfo[255];
int IPBlockCount;

void LoadIPBlock()
{
	FILE *fp;
	BOOL bRead = FALSE;
	DWORD dwArgv = 0;
	char sLineTxt[255] = {0};
	IPBlockCount = 1;

	fp = fopen(BANIPFILE_PATH,"r");

	if(!fp)
	{
		MessageBoxA(NULL, "EIPBan.ini not found!!", "Error!", MB_OK);
		::ExitProcess(0);
	}

	rewind(fp);
	
	while(fgets(sLineTxt, 255, fp) != NULL)
	{
		if(sLineTxt[0] == '/')continue;
		if(sLineTxt[0] == ';')continue;

		char IP[16];

		sscanf(sLineTxt, "%s", &IP);
		sprintf(IPBlockInfo[IPBlockCount].IP,"%s",IP);
		IPBlockCount++;
	}

	rewind(fp);
	fclose(fp);
}

bool CheckIP(DWORD aIndex)
{
	char IPAddr[16];
	gObj_GetIP(aIndex,IPAddr);
	for(int x=1;x < IPBlockCount;x++)
	{
		if(!strcmp(IPBlockInfo[x].IP,IPAddr))
		{
			CloseClient(aIndex);
			return false;
		}
	}
	return true;
}
