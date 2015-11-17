/*-------------------------------------------------------*/
/*				Project Evolution Team Season 2          */
/*   Version GS 1.00.18 & GS-CS 1.00.19 Protocol Eng     */
/*             http://evolution-team.eu                  */
/*-------------------------------------------------------*/
/*                    Code By Th3AnG3L                   */
/*             http://evolution-team.eu                  */
/*-------------------------------------------------------*/

typedef struct GMSystem
{
	char Name[11];
	int Drop;
	int Gg;
	int Zen;
	int Re;
	int Cre;
	int Skin;
	int On;
	int SetPk;
	int SetZen;
	int SetLevel;
	int MutePost;
	int Unmute;
	int BanChar;
	int UnBanChar;
	int Move;
	int Gmove;
	int Cash;
	int BanAccount;

}GMSYSTEM;

//Structures
extern GMSYSTEM GMSystemInfo[255];
extern int GMSystemCount;

void LoadGMSystem();
