/*-------------------------------------------------------*/
/*				Project Evolution Team Season 2          */
/*   Version GS 1.00.18 & GS-CS 1.00.19 Protocol Eng     */
/*             http://evolution-team.eu                  */
/*-------------------------------------------------------*/
/*                    Code By Th3AnG3L                   */
/*             http://evolution-team.eu                  */
/*-------------------------------------------------------*/
#include "GameServer.h"
#include "Utilidades.h"

#define MAX_DROP_NUMBER 1000 // Max Number of Drops in the ItemDropRate file

struct S_DropSystem
{
	unsigned char Type;
	unsigned int Index;
	unsigned char Level;
	unsigned char Opt;
	unsigned int Luck;
	unsigned char Skill;
	unsigned char Dur;
	unsigned int Rate;
	unsigned int Minlvl;
	unsigned int Maxlvl;
	unsigned char DropMap;
	unsigned char Exc;
	unsigned char Ancient;
};
class C_DropSystem
{
public:
	S_DropSystem t_struct[MAX_DROP_NUMBER];
	unsigned short t_num;
	void t_LoadSystem();
	int MygEventMonsterItemDrop(BYTE * b_MonsterDataAddr,BYTE * a_gObjAddr);
private:
	S_DropSystem		Item[120];
	unsigned char		ItemCount;
};
void MonsterDropCall(BYTE * b_MonsterDataAddr,BYTE * a_gObjAddr);
extern C_DropSystem Drop;