/*-------------------------------------------------------*/
/*				Project Evolution Team Season 2          */
/*   Version GS 1.00.18 & GS-CS 1.00.19 Protocol Eng     */
/*             http://evolution-team.eu                  */
/*-------------------------------------------------------*/
/*                    Code By Th3AnG3L                   */
/*             http://evolution-team.eu                  */
/*-------------------------------------------------------*/
#include "User.h"
#include "GameServer.h"
#include "Utilidades.h"

#define MAX_TELEPORT_NUMBER 50	// Max Number of "maps" in the teleport file
#define MAX_MAPS_NUMBER 50

struct S_Teleport
{
	char t_Name[30];
	unsigned short MinLevel;
	unsigned int Money;
	unsigned short x1;
	unsigned short y1;
	unsigned short x2;
	unsigned short y2;
	unsigned short map;
};

class C_Teleport
{
public:
	S_Teleport t_struct[MAX_TELEPORT_NUMBER];
	unsigned short t_num;
	void t_LoadTeleports();
	void t_PlayerTeleport(DWORD aIndex,char * map);
};
extern C_Teleport Move;