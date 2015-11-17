/*-------------------------------------------------------*/
/*				Project Evolution Team Season 2          */
/*   Version GS 1.00.18 & GS-CS 1.00.19 Protocol Eng     */
/*             http://evolution-team.eu                  */
/*-------------------------------------------------------*/
/*                    Code By Th3AnG3L                   */
/*             http://evolution-team.eu                  */
/*-------------------------------------------------------*/
#include "StdAfx.h"

// Database Functions
CMuOnline MuDB;

int CMuOnline::CheckVip(char Account[11])
{


	char Query[150];
	int Vip;

	wsprintf(Query,"SELECT vip FROM MEMB_INFO WHERE memb___id = '%s'",Account);
	SQL.Exec(Query);
	SQL.Fetch();

	Vip = SQL.GetInt("vip");

	SQL.Clear();

	return Vip;
}

void CMuOnline::UpdateResets(char Name[11])
{


	char Query[150];

	wsprintf(Query,"UPDATE Character SET Resets = Resets+1 WHERE Name = '%s'",Name);
	SQL.Exec(Query);
}

int CMuOnline::ResetMagiass(char Name[11])
{
	//char Query[150];
	char cSelectStr[0xFF] ={0x00} ;
	wsprintf(cSelectStr,"UPDATE Character SET MagicList = NULL WHERE Name = '%s'",Name);
	SQL.Exec(cSelectStr);
	return 1;
}

int CMuOnline::CheckMute(char Name[11])
{


	char Query[150];
	int Mute;

	wsprintf(Query,"SELECT MutePost FROM Character WHERE Name = '%s'",Name);
	SQL.Exec(Query);
	SQL.Fetch();

	Mute = SQL.GetInt("MutePost");

	SQL.Clear();

	return Mute;
}

int CMuOnline::GetMutePost(char Name[11])
{


	char Query[150];
	int Mute;

	wsprintf(Query,"SELECT MutePost FROM Character WHERE Name = '%s'",Name);
	SQL.Exec(Query);
	SQL.Fetch();

	Mute = SQL.GetInt("MutePost");

	SQL.Clear();

	return Mute;
}

void CMuOnline::UpdateMutePostOn(char Name[11])
{


	char Query[150];

	wsprintf(Query,"UPDATE Character SET MutePost = 1 WHERE Name = '%s'",Name);
	SQL.Exec(Query);
}

void CMuOnline::UpdateMutePostOff(char Name[11])
{

	char Query[150];

	wsprintf(Query,"UPDATE Character SET MutePost = 0 WHERE Name = '%s'",Name);
	SQL.Exec(Query);
}

int CMuOnline::GetCtlCode(char Name[11])
{


	char Query[150];
	int CtlCode;

	wsprintf(Query,"SELECT CtlCode FROM Character WHERE Name = '%s'",Name);
	SQL.Exec(Query);
	SQL.Fetch();

	CtlCode = SQL.GetInt("CtlCode");

	SQL.Clear();

	return CtlCode;
}

int CMuOnline::GetClase(char Name[11])
{


	char Query[150];
	int CtlCode1;

	wsprintf(Query,"SELECT Class FROM Character WHERE Name = '%s'",Name);
	SQL.Exec(Query);
	SQL.Fetch();

	CtlCode1 = SQL.GetInt("Class");

	SQL.Clear();

	return CtlCode1;
}

int CMuOnline::GetResets(char Name[11])
{


	char Query[150];
	int CtlCode2;

	wsprintf(Query,"SELECT Resets FROM Character WHERE Name = '%s'",Name);
	SQL.Exec(Query);
	SQL.Fetch();

	CtlCode2 = SQL.GetInt("Resets");

	SQL.Clear();

	return CtlCode2;
}




void CMuOnline::UpdateBanOn(char Name[11])
{


	char Query[150];

	wsprintf(Query,"UPDATE Character SET CtlCode = 1 WHERE Name = '%s'",Name);
	SQL.Exec(Query);
}

void CMuOnline::UpdateBanOff(char Name[11])
{


	char Query[150];

	wsprintf(Query,"UPDATE Character SET CtlCode = 0 WHERE Name = '%s'",Name);
	SQL.Exec(Query);
}

void CMuOnline::UpdateFortuneInfo(char Account[11])
{


	char Query[150];

	wsprintf(Query,"UPDATE MEMB_INFO SET fortuneusage = fortuneusage+1 WHERE memb___id = '%s'",Account);
	SQL.Exec(Query);
}

void CMuOnline::ResetFortuneInfo(char Account[11])
{


	char Query[150];

	wsprintf(Query,"UPDATE MEMB_INFO SET fortuneusage = 0 WHERE memb___id = '%s'",Account);
	SQL.Exec(Query);
}

int CMuOnline::GetFortuneInfo(char Account[11])
{


	char Query[150];
	int Usage;

	wsprintf(Query,"SELECT fortuneusage FROM MEMB_INFO WHERE memb___id = '%s'",Account);
	SQL.Exec(Query);
	SQL.Fetch();

	Usage = SQL.GetInt("fortuneusage");

	SQL.Clear();

	return Usage;
}

void CMuOnline::UpdateFortuneDay(char Account[11])
{
	SYSTEMTIME LocalTime;
	GetLocalTime(&LocalTime);



	char Query[150];

	wsprintf(Query,"UPDATE MEMB_INFO SET fortuneday = '%d' WHERE memb___id = '%s'",LocalTime.wDay,Account);
	SQL.Exec(Query);
}

int CMuOnline::GetFortuneDay(char Account[11])
{


	char Query[150];
	int Day;

	wsprintf(Query,"SELECT fortuneday FROM MEMB_INFO WHERE memb___id = '%s'",Account);
	SQL.Exec(Query);
	SQL.Fetch();

	Day = SQL.GetInt("fortuneday");

	SQL.Clear();

	return Day;
}

void CMuOnline::UpdateFortuneWin(char Name[11])
{
	SYSTEMTIME LocalTime;
	GetLocalTime(&LocalTime);


	char Query[150];

	wsprintf(Query,"UPDATE T_Fortune_Info SET PotCollected = 1, PotCollectDay = '%d', PotCollector = '%s'",LocalTime.wDay,Name);
	SQL.Exec(Query);
}

void CMuOnline::ResetFortune()
{
	SYSTEMTIME LocalTime;
	GetLocalTime(&LocalTime);



	char Query[150];

	wsprintf(Query,"UPDATE T_Fortune_Info SET PotCollected = 0, PotCollector = ''");
	SQL.Exec(Query);
}

int CMuOnline::GetFortuneWin()
{


	char Query[150];
	int Collected;

	wsprintf(Query,"SELECT PotCollected FROM T_Fortune_Info");
	SQL.Exec(Query);
	SQL.Fetch();

	Collected = SQL.GetInt("PotCollected");

	SQL.Clear();

	return Collected;
}

int CMuOnline::GetFortuneWinDay()
{


	char Query[150];
	int CollectDay;

	wsprintf(Query,"SELECT PotCollectDay FROM T_Fortune_Info");
	SQL.Exec(Query);
	SQL.Fetch();

	CollectDay = SQL.GetInt("PotCollectDay");

	SQL.Clear();

	return CollectDay;
}

int CMuOnline::GetWHInUse(char Name[11])
{


	char Query[150];
	int CtlCodes;

	wsprintf(Query,"SELECT WHInUse FROM warehouse WHERE AccountID = '%s'",Name);
	SQL.Exec(Query);
	SQL.Fetch();

	CtlCodes = SQL.GetInt("WHInUse");

	SQL.Clear();

	return CtlCodes;
}

void CMuOnline::DarCashShop(char Account[11],int Cantidad)
{


	char Query[150];

	wsprintf(Query,"UPDATE MEMB_INFO SET cspoints = '%d' WHERE memb___id = '%s'",Cantidad,Account);
	SQL.Exec(Query);
}

int CMuOnline::GetAccuent(char Name[11])
{


	char Query[150];
	int CtlCode4;

	wsprintf(Query,"SELECT AccountID FROM Character WHERE Name = '%s'",Name);
	SQL.Exec(Query);
	SQL.Fetch();

	CtlCode4 = SQL.GetInt("AccountID");

	SQL.Clear();

	return CtlCode4;
}

int CMuOnline::GetBanAccount(char Name[11])
{


	char Query[150];
	int CtlCode;

	wsprintf(Query,"SELECT bloc_code FROM MEMB_INFO WHERE memb___id = '%s'",Name);
	SQL.Exec(Query);
	SQL.Fetch();

	CtlCode = SQL.GetInt("bloc_code");

	SQL.Clear();

	return CtlCode;
}

void CMuOnline::UpdateBanAccount(char Name[11])
{


	char Query[150];

	wsprintf(Query,"UPDATE MEMB_INFO SET bloc_code = 1 WHERE memb___id = '%s'",Name);
	SQL.Exec(Query);
}