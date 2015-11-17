/*#ifndef __COMMONSCFEVENTS_H__
#define __COMMONSCFEVENTS_H__

typedef struct gObjHappyHourCommonCFG
{
	int Enabled;
	int Start;
	int Minutes;

	int ExtraExp;
	int ExtraDrop;

}GOBJHAPPYHOURCOMMON;

extern GOBJHAPPYHOURCOMMON gObjHappyHourEvent;
#endif __COMMONSCFEVENTS_H__

void HappyHour__InsideTrigger(void * lpParam);
bool HappyON(int ON);*/