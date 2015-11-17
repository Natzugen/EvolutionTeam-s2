/*-------------------------------------------------------*/
/*				Project Evolution Team Season 2          */
/*   Version GS 1.00.18 & GS-CS 1.00.19 Protocol Eng     */
/*             http://evolution-team.eu                  */
/*-------------------------------------------------------*/
/*                    Code By Th3AnG3L                   */
/*             http://evolution-team.eu                  */
/*-------------------------------------------------------*/
#ifndef __CQUERY_H__
#define __CQUERY_H__

// SQL Connection
class CQuery
{
public:
	
	enum
	{
		MAXCOL = 100,
		BLOBBATCH = 10000,
		CQUERYNULL = -100,
		CQUERYEOF = -101,
		CQUERYNOCOL = -102,
		CQUERYERROR = -103
	};

private:

	SQLHENV hEnv;
	SQLHDBC hDbc;
	SQLRETURN ret;
	char Col[MAXCOL][255];
	bool m_bConnected;
	HENV m_SQLEnvironment;
	HDBC m_SQLConnection;
	HSTMT m_STMT;
	long m_RowCount;
	long m_ColCount;
	
	
	int	m_Type;
	char m_szConnect[128];
	char m_Id[20];
	char m_Pass[20];

	int FindCol(char *name);
	BOOL ReConnect();

	char*szDriver;
	char DataBase[255];
	char szServer[50];
	char szServer2[50];
	char User[255];
	char Password[255];

public:

	SQLINTEGER AffectCount;
	SQLHSTMT hStmt;
	SQLSMALLINT nCol;
	SQLCHAR ColName[MAXCOL][50];
	SQLINTEGER lCol[MAXCOL];

	void PrintDiag();
	CQuery();
	~CQuery();
	BOOL Connect(int Type,char *ConStr,char *UID = NULL,char *PWD = NULL);
	BOOL Exec(LPCTSTR szSQL);
	int ExecGetInt(LPCTSTR szSQL);
	BOOL ExecGetStr(LPCTSTR szSQL,char *buf);
	SQLRETURN Fetch();
	void Clear();
	int GetInt(int nCol);
	int GetInt(char *sCol);
	float GetFloat(int nCol);
	float GetFloat(char *sCol);
	void GetStr(int nCol,char *buf);
	void GetStr(char *sCol,char *buf);
	int ReadBlob(LPCTSTR szSQL,void *buf);
	void WriteBlob(LPCTSTR szSQL,void *buf,int size);
	void InitConnection();
	bool Execute(char* szQuery,...);
	int GetInt2();
};

extern CQuery SQL;
#endif