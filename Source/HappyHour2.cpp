/*#include <stdio.h>
#include <Time.h>
#include "stdafx.h"
#include "HappyHour2.h"
//#include "Offsets.h"
//#include "../Headers/GsFunc.h"
//#include "../Headers/Extra.h"
//#include "../Headers/Commands.h"


GOBJHAPPYHOURCOMMON gObjHappyHourEvent;

bool HappyON(int ON)
{
	if(ON !=1)
		return 0;
	else
		{
				FILE *fp;
				fp=fopen(NEWSISTEMFILE_PATH,"rb");
				if(!fp)
				{
					MessageBoxA(NULL,"OGC-HappyHour.ini","Error!",MB_OK);
					::ExitProcess(0);
				}
				_beginthread( HappyHour__InsideTrigger, 0, NULL  );
				return 1;
	}

}

void HappyHour__AddExtraExp(int ExtraExp)
{
	float * EXPERIENCE = (float *)(gAddExperience); 
	(*EXPERIENCE)+=ExtraExp;
}

void HappyHour__AddExtraDrop(int ExtraDrop)
{
	SetDrop(GetDrop()+ExtraDrop);
}

void HappyHour__InsideTrigger(void * lpParam)
{
	char sBuf[255] = {0};
	char sBuf2[255] = {0};
	long time = GetPrivateProfileIntA("General","OGC_Tiempo",0,NEWSISTEMFILE_PATH) * 60000;
	if(gObjHappyHourEvent.Start==1) 
	{	
		Sleep(time);
		wsprintf(sBuf, "HappyHour Event has started.",gObjHappyHourEvent.ExtraExp,gObjHappyHourEvent.ExtraDrop); //Started
		wsprintf(sBuf2, "[Server: %s] %s",GS_NAME,sBuf);
		//DebugInfo(sBuf2,3);
		//SendNoticeToAllGS(sBuf2);
		StringSendAll(sBuf2,0);

		HappyHour__AddExtraExp(gObjHappyHourEvent.ExtraExp);
		HappyHour__AddExtraDrop(gObjHappyHourEvent.ExtraDrop);

		wsprintf(sBuf, "Experience changed to: %d, Drop changed to: %d",GetExp(),GetDrop());
		//DebugInfo(sBuf,3);
		//SendNoticeToAll(sBuf,0x00);
		StringSendAll(sBuf,0);
		

		Sleep(gObjHappyHourEvent.Minutes);

		gObjHappyHourEvent.Start=0;
		wsprintf(sBuf, "HappyHour Event has finished."); //Finished
		wsprintf(sBuf2, "[Server: %s] %s",GS_NAME,sBuf);
		//DebugInfo(sBuf2,3);
		//SendNoticeToAllGS(sBuf2);
		StringSendAll(sBuf2,0);
		//
		HappyHour__AddExtraExp(-gObjHappyHourEvent.ExtraExp);
		HappyHour__AddExtraDrop(-gObjHappyHourEvent.ExtraDrop);

		_endthread();
		return;
	}
}

void HappyHour__Start()
{
	if((gObjHappyHourEvent.Enabled == 1) && (gObjHappyHourEvent.Start == 0))
	{
		gObjHappyHourEvent.Start=1;
		_beginthread( HappyHour__InsideTrigger, 0, NULL  );
	}
}

bool HappyHour__ReadFile(char * FilePath)
{
	int Temp									= 0;
	gObjHappyHourEvent.Start					= 0;
	gObjHappyHourEvent.Enabled					= GetPrivateProfileInt("General", "OGC_HappyHourEnabled",1, HappyFILE_PATH) ;
	Temp										= GetPrivateProfileInt("General", "OGC_HappyHourMinutes",5, HappyFILE_PATH) ;
	gObjHappyHourEvent.Minutes					= (Temp * 60)*1000;

	gObjHappyHourEvent.ExtraExp					= GetPrivateProfileInt("HappyHour", "OGC_HappyHourExtraExperience",0, HappyFILE_PATH) ;
	gObjHappyHourEvent.ExtraDrop				= GetPrivateProfileInt("HappyHour", "OGC_HappyHourExtraItemDropPer",0, HappyFILE_PATH) ;

	return 1;
}*/