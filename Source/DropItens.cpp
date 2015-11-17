/*-------------------------------------------------------*/
/*				Project Evolution Team Season 2          */
/*   Version GS 1.00.18 & GS-CS 1.00.19 Protocol Eng     */
/*             http://evolution-team.eu                  */
/*-------------------------------------------------------*/
/*                    Code By Th3AnG3L                   */
/*             http://evolution-team.eu                  */
/*-------------------------------------------------------*/
#include "GameServer.h"
#include "Global.h"
#include "DropItens.h"

int MygEventMonsterItemDrop (BYTE * b_MonsterDataAddr,BYTE * a_gObjAddr)
{
WORD wMonsterLv =0;
WORD wMonsterId =0;
WORD Player;
BYTE cMapID, cX, cY;
PBYTE bDataAddr =0;
bDataAddr = (PBYTE)b_MonsterDataAddr;


memcpy(&Player,bDataAddr+0x73,sizeof(WORD));
memcpy(&wMonsterLv, bDataAddr+0xA0, sizeof(WORD));
memcpy(&wMonsterId, bDataAddr+0x9C, sizeof(WORD));
memcpy(&cMapID, bDataAddr+0x10D, sizeof(BYTE));
memcpy(&cX, bDataAddr+0x108, sizeof(BYTE));
memcpy(&cY, bDataAddr+0x10A, sizeof(BYTE));


DWORD dwPena = ItemGetNumberMake(13,14); //pluma
//(13,14) = pluma xD
DWORD dwPena2 = ItemGetNumberMake(12,31); //jewels soul
DWORD dwTopHitUser = gObjMonsterTopHitDamageUser( b_MonsterDataAddr );

DWORD dwRand = rand();


WORD gMonsterID = 0x4D ; //monster Lvl 77 Metal Balrog 
if (wMonsterId<=gMonsterID)
{
if ( dwRand % 10000 >= (10000 - 60)) //60% es para probar
{
ItemSerialCreateSend(b_MonsterDataAddr[0], cMapID,cX,cY,dwPena ,0,255,0,0,0 ,dwTopHitUser,0,0);
return 1;
}
}
//WORD 
	gMonsterID = 0x34 ; //monster level 52  Ice Queen
if (wMonsterId>=gMonsterID) //Mayor a monsters lvl 72 dropearan soul
{
if ( dwRand % 10000 >= (10000 - 90)) //90% es para probar
{
ItemSerialCreateSend(b_MonsterDataAddr[0], cMapID,cX,cY,dwPena2 ,0,255,0,0,0 ,dwTopHitUser,0,0);
return 1;
}
}
int rValue = gEventMonsterItemDrop(b_MonsterDataAddr, a_gObjAddr);
return rValue;
}