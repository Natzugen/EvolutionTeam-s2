#include "USER.h"
#include "StdAfx.h"
#include "Protocolos.h"

void GCDamageSend(int aIndex, int TargetIndex, int AttackDamage, int MSBFlag, int MSBDamage, int iShieldDamage)
{
	PMSG_ATTACKRESULT pResult;
	
	PHeadSetB((LPBYTE)&pResult, 0xDC, sizeof(pResult));
	pResult.NumberH = SET_NUMBERH(TargetIndex);
	pResult.NumberL = SET_NUMBERL(TargetIndex);
	pResult.DamageH = SET_NUMBERH(AttackDamage);
	pResult.DamageL = SET_NUMBERL(AttackDamage);
	pResult.btShieldDamageH = SET_NUMBERH(iShieldDamage);
	pResult.btShieldDamageL = SET_NUMBERL(iShieldDamage);
	
	if ( MSBFlag != FALSE )
	{
		pResult.NumberH &= 0x7F;
		pResult.NumberH |= 0x80;
	}
	
	pResult.DamageType = MSBDamage;

	OBJECTSTRUCT * gObj = (OBJECTSTRUCT*)OBJECT_POINTER(aIndex);
	OBJECTSTRUCT * gTarg = (OBJECTSTRUCT*)OBJECT_POINTER(TargetIndex);
	
	pResult.Life = gTarg->Life;
	pResult.MaxLife = gTarg->MaxLife + gTarg->AddLife; //fix for inner strenght
	
	if(gTarg->Type == OBJECT_USER)
	{
		DataSend(TargetIndex, (LPBYTE)&pResult, pResult.h.size);
	}
	
	if(gObj->Type == OBJECT_USER)
	{
		DataSend(aIndex, (LPBYTE)&pResult, pResult.h.size);
	}
}