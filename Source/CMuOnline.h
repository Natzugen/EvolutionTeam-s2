/*-------------------------------------------------------*/
/*				Project Evolution Team Season 2          */
/*   Version GS 1.00.18 & GS-CS 1.00.19 Protocol Eng     */
/*             http://evolution-team.eu                  */
/*-------------------------------------------------------*/
/*                    Code By Th3AnG3L                   */
/*             http://evolution-team.eu                  */
/*-------------------------------------------------------*/
#ifndef __CMUONLINE_H__
#define __CMUONLINE_H__

// Database Functions
class CMuOnline
{
public:

	int CheckVip(char Account[11]);
	void UpdateResets(char Name[11]);
	int CheckMute(char Name[11]);
	int GetMutePost(char Name[11]);
	void UpdateMutePostOn(char Name[11]);
	void UpdateMutePostOff(char Name[11]);
	int GetCtlCode(char Name[11]);
	int GetClase(char Name[11]);
	int GetWHInUse(char Name[11]);
	int GetResets(char Name[11]);
	int GetAccuent(char Name[11]);
	int ResetMagiass(char Name[11]);
	void UpdateBanOn(char Name[11]);
	void UpdateBanOff(char Name[11]);
	void UpdateFortuneInfo(char Account[11]);
	void ResetFortuneInfo(char Account[11]);
	void DarCashShop(char Account[11],int Cantidad);
	int GetFortuneInfo(char Account[11]);
	void UpdateFortuneDay(char Account[11]);
	int GetFortuneDay(char Account[11]);
	void UpdateFortuneWin(char Name[11]);
	void ResetFortune();
	int GetFortuneWin();
	int GetFortuneWinDay();
	int GetBanAccount(char Name[11]);
	void UpdateBanAccount(char Name[11]);
};

extern CMuOnline MuDB;

#endif