// SQLManager.h: interface for the CSQLManager class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SQLMANAGER_H__B5C8DBF6_FA05_4C98_A934_EEFB96226E03__INCLUDED_)
#define AFX_SQLMANAGER_H__B5C8DBF6_FA05_4C98_A934_EEFB96226E03__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "StdAfx.h"


#define MAX_SQL_COL	100
#define MAX_SQLCHAR_RETURN_SIZE	255


class CQueryX  
{
public:

	CQueryX();
	~CQueryX();

	bool Connect(int iDBType, SQLCHAR * lpszDNS, SQLCHAR * lpszID, SQLCHAR * lpszPass);	// Connect With DB
	void Disconnect();	// Disconnect
	bool Execute(LPSTR lpszStatement); // Execute an Statement
	void Close();


	// Get Values Obtained from Execute
	int GetAsInteger(LPSTR lpszCol);
	__int64 GetAsLongLong(LPSTR lpszCol);
	float GetAsFloat(LPSTR lpszCol);
	void GetAsString(LPSTR lpszCol, LPSTR OUT lpszReturnBuffer);
	int GetAsBinary(LPSTR lpszStatement, LPBYTE OUT lpszReturnBuffer);
	int SelectVIP(int aIndex);
	int GetaIndexPlayer(char Name[11]);
	int SelectNameV(char Name[11]);
	int GetResetCharacter(char Name[11]);
	int GetUserResetNumber(int aIndex);
	int GetCoinsPlayer(char Account[11]);
	int GetCreditsPlayer(char Account[11]);
	void UpdateUserResetNumber(int aIndex);
	int SynFloodProtect1(char IP[15]);
	void SynFloodProtect2(char IP[15]);
	int GetFieldInt(char* Table, char* Field, const char* Optional, ...);
	int GetBlockPCharacter(char Name[11]);
	void UpdatePostBCharacter(char Name[11],int PostBlockC);
	void UpdatePostBCharacter2(char Name[11],int PostBlockD);
	void UpdateaIndexBCharacter(char Name[11],int aIndexS);
	void UpdateResetSystem(char Name[11],int Resets);
	void UpdateCashOffExpSystemPlus(char Account[11],int gems);
	void UpdateCashOffExpSystemMinus(char Account[11],int gems);
	void UpdateCashOffExpSystemPlusCredit(char Account[11],int gems);
	void UpdateCashOffExpSystemMinusCredit(char Account[11],int gems);
	void UpdateZenPlayer(char Name[11],int zen);
	void ReloadMobSystem(char Name[11]);
	__int64 GetFieldLongLong(char* Table, char* Field, const char* Optional, ...);
	std::string GetFieldChar(char* Table, char* Field, const char* Optional, ...);
	std::string GetFieldBinary(char* Table, char* Field, const char* Optional, ...);
	int ResetCount;
	int ResetS;
	int BlockPost;
	int CountIp;
	int aIndexP;
	int CoinsP;
	int CreditsP;

private:

	bool ReConnect();	// Reconnect in case of Link Failure
	void LogError();	// Log in Case of Error
	SQLRETURN Fetch();
	int GetColIndex(SQLCHAR * lpszCol);
	__int64 GetColIndexLong(SQLCHAR * lpszCol);
	int ConvertToInteger(int iColIndex);
	__int64 ConvertToLongLong(int iColIndex);
	float ConvertToFloat(int iColIndex);
	void ConvertToString(const int iColIndex, LPSTR OUT lpszReturnBuffer);


public:

	SQLHANDLE m_SQLEnvHandle;	// Environ Handle 
	SQLHANDLE m_SQLDBConnectionHandle;	// Connection Handle
	SQLRETURN m_SQLResult;	// LAs Result of any Operation
	SQLCHAR	m_SQLReturnChar[MAX_SQL_COL][MAX_SQLCHAR_RETURN_SIZE];	// Buufer with Results of a Statement
	int m_iDBType;	// DBType 1 : Acces 3 : SQL
	SQLCHAR m_DNS[128];	// DNS
	SQLCHAR m_ID[20];	// Id
	SQLCHAR m_Pass[20];	// Password
	SQLINTEGER m_SQLRowCount;	// Row Count
	SQLHANDLE m_SQLSTMTHandle;	// Statement Handle
	SQLSMALLINT m_SQLColCount;	// Collumns Count
	SQLCHAR m_SQLColName[MAX_SQL_COL][50];	// Collumn Name
	SQLINTEGER m_SQLReturnCharSize[MAX_SQL_COL];	// Collumn Size

};

extern CQueryX SQLX;
#endif // !defined(AFX_SQLMANAGER_H__B5C8DBF6_FA05_4C98_A934_EEFB96226E03__INCLUDED_)
