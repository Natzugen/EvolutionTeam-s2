/*-------------------------------------------------------*/
/*				Project Evolution Team Season 2          */
/*   Version GS 1.00.18 & GS-CS 1.00.19 Protocol Eng     */
/*             http://evolution-team.eu                  */
/*-------------------------------------------------------*/
/*                    Code By Th3AnG3L                   */
/*             http://evolution-team.eu                  */
/*-------------------------------------------------------*/
#include "StdAfx.h"

// SQL Connection
CQuery SQL;

CQuery::CQuery()
{
	AffectCount = -1;
	ret = SQL_SUCCESS;
	SQLAllocHandle(SQL_HANDLE_ENV,SQL_NULL_HANDLE,&hEnv);
	SQLSetEnvAttr(hEnv,SQL_ATTR_ODBC_VERSION,(SQLPOINTER)SQL_OV_ODBC3,SQL_IS_INTEGER);
}

CQuery::~CQuery()
{
	if(hStmt) SQLFreeHandle(SQL_HANDLE_STMT,hStmt);
	if(hDbc) SQLDisconnect(hDbc);
	if(hDbc) SQLFreeHandle(SQL_HANDLE_DBC,hDbc);
	if(hEnv) SQLFreeHandle(SQL_HANDLE_ENV,hEnv);
}

BOOL CQuery::Connect(int Type,char *ConStr,char *UID,char *PWD)
{
	SQLCHAR InCon[255];
	SQLCHAR OutCon[255];
    SQLSMALLINT cbOutCon;

	int ii = 1;
	SQLRETURN Ret;
	SQLINTEGER NativeError;
	SQLCHAR SqlState[6],Msg[255];
	SQLSMALLINT MsgLen;
	char str[256];

	m_Type = Type;
	strcpy(m_szConnect,ConStr);
	strcpy(m_Id,UID);
	strcpy(m_Pass,PWD);

	SQLAllocHandle(SQL_HANDLE_DBC,hEnv,&hDbc);
	switch (Type)
	{
	case 1:
		sprintf((char*)InCon,"DRIVER=%s; SERVER=%s; UID=%s; PWD=%s; DATABASE=%s;",szDriver,szServer2,User,Password,DataBase);

		//wsprintf((char *)InCon,"DRIVER={Microsoft Access Driver (*.mdb)};DBQ=%s;",ConStr);
		ret = SQLDriverConnect(hDbc,NULL,(SQLCHAR *)InCon,sizeof(InCon),OutCon,sizeof(OutCon),&cbOutCon,SQL_DRIVER_NOPROMPT);
		break;
	case 2:
		wsprintf((char *)InCon,"FileDsn=%s",ConStr);
		ret = SQLDriverConnect(hDbc,NULL,(SQLCHAR *)InCon,sizeof(InCon),OutCon,sizeof(OutCon),&cbOutCon,SQL_DRIVER_NOPROMPT);
		break;
	case 3:
		ret = SQLConnect(hDbc,(SQLCHAR *)ConStr,SQL_NTS,(SQLCHAR *)UID,SQL_NTS,(SQLCHAR *)PWD,SQL_NTS);
		break;
	}

	if((ret != SQL_SUCCESS) && (ret != SQL_SUCCESS_WITH_INFO))
	{
		while(Ret = SQLGetDiagRec(SQL_HANDLE_DBC,hDbc,ii,SqlState,&NativeError,Msg,sizeof(Msg),&MsgLen) != SQL_NO_DATA)
		{
			wsprintf(str,"SQLSTATE:%s,Diagnosis:%s",(LPCTSTR)SqlState,(LPCTSTR)Msg);
			MessageBoxA(0,"Unable to connect to SQL Server.\nPlease configure the connection.","Error",MB_OK | MB_ICONSTOP);
			ExitProcess(0);
			++ii;
		}
		return FALSE;
	}

	ret = SQLAllocHandle(SQL_HANDLE_STMT,hDbc,&hStmt);
	if((ret != SQL_SUCCESS) && (ret != SQL_SUCCESS_WITH_INFO))
	{
		hStmt = 0;
		return FALSE;
	}
	return TRUE;
}

BOOL CQuery::ReConnect()
{
	return Connect(m_Type,m_szConnect,m_Id,m_Pass);
}

BOOL CQuery::Exec(LPCTSTR szSQL)
{
	int c;

	ret = SQLExecDirect(hStmt,(SQLCHAR *)szSQL,SQL_NTS);
	if((ret != SQL_SUCCESS) && (ret != SQL_SUCCESS_WITH_INFO) && (ret != SQL_NO_DATA))
	{
		PrintDiag();
		return FALSE;
	}

	SQLRowCount(hStmt,&AffectCount);

	SQLNumResultCols(hStmt,&nCol);
	if(nCol > MAXCOL)
	{

		return FALSE;
	}

	if(nCol == 0)
	{
		Clear();
		return TRUE;
	}

	for(c = 0; c < nCol; c++)
	{
		SQLBindCol(hStmt,c+1,SQL_C_CHAR,Col[c],255,&lCol[c]);
		SQLDescribeCol(hStmt,c+1,ColName[c],30,NULL,NULL,NULL,NULL,NULL);
	}
	return TRUE;
}

int CQuery::ExecGetInt(LPCTSTR szSQL)
{
	int i;

	if(Exec(szSQL) == FALSE) 
	{
		return CQUERYERROR;
	}

	if(Fetch() == SQL_NO_DATA)
	{
		Clear();
		return CQUERYEOF;
	}

	i = GetInt(1);

	Clear();

	return i;
}

BOOL CQuery::ExecGetStr(LPCTSTR szSQL,char *buf)
{
	if(Exec(szSQL) == FALSE)
	{
		buf[0] = '\0';
		return FALSE;
	}

	if(Fetch()==SQL_NO_DATA)
	{
		Clear();
		buf[0] = '\0';
		return FALSE;
	}
	GetStr(1,buf);
	Clear();
	return TRUE;
}

SQLRETURN CQuery::Fetch()
{
	ret = SQLFetch(hStmt);
	return ret;
}

void CQuery::Clear()
{
	SQLCloseCursor(hStmt);
	SQLFreeStmt(hStmt,SQL_UNBIND);
}

int CQuery::FindCol(char *name)
{
	int i;

	for(i = 0; i < nCol; ++i)
	{
		if(stricmp(name,(LPCTSTR)ColName[i]) == 0)
		{
			return i+1;
		}
	}
	return -1;
}

int CQuery::GetInt(int nCol)
{
	if(nCol > this->nCol)
	{
		return CQUERYNOCOL;
	}

	if(lCol[nCol-1] == SQL_NULL_DATA)
	{
		return CQUERYNULL;
	}
	else
	{
		return atoi(Col[nCol-1]);
	}
}

int CQuery::GetInt(char *sCol)
{
	int n;

	n = FindCol(sCol);

	if(n == -1)
	{
		return CQUERYNOCOL;
	}
	else
	{
		return GetInt(n);
	}
}

float CQuery::GetFloat(int nCol)
{
	if(nCol > this->nCol)
	{
		return CQUERYNOCOL;
	}

	if(lCol[nCol-1] == SQL_NULL_DATA)
	{
		return CQUERYNULL;
	}
	else
	{
		return (float)atof(Col[nCol-1]);
	}
}

int CQuery::GetInt2()
{
    long lSize,lResult=0;

    while(true)
	{
	    if(SQL_SUCCEEDED(SQLFetch(this->m_STMT)) == 0)
		    break;
		
		if(SQL_SUCCEEDED(SQLGetData(this->m_STMT,1,SQL_C_LONG,&lResult,sizeof(long),&lSize)) == 0)
		    break;
		
		return lResult;
	}

	return 0;
}
bool CQuery::Execute(char* szQuery,...)
{
	if(this->m_bConnected == 0)
	{
        return false;
	}

    if(SQL_SUCCEEDED(SQLAllocHandle(SQL_HANDLE_STMT,this->m_SQLConnection,&this->m_STMT)) == 0)
    {
	    return false;
	}

	char szTemp[1024];

	va_list pArguments;

	va_start(pArguments,szQuery);
	vsprintf(szTemp,szQuery,pArguments);
	va_end(pArguments);

    if(SQL_SUCCEEDED(SQLPrepare(this->m_STMT,(unsigned char*)szTemp,strlen(szTemp))) == 0)
    {
	    return false;
	}
			
	SQLRETURN Execute = SQLExecute(this->m_STMT);

    if(Execute == SQL_SUCCESS || Execute == SQL_SUCCESS_WITH_INFO || Execute == SQL_NO_DATA)
    {
	    if(SQLRowCount(this->m_STMT,&this->m_RowCount) != SQL_SUCCESS)
		{
		    this->m_RowCount = 0;
		}

		if(SQLNumResultCols(this->m_STMT,(SQLSMALLINT*)&this->m_ColCount) != SQL_SUCCESS)
		{
		    this->m_ColCount = 0;
		}

		return true;
	}

	return false;
}

float CQuery::GetFloat(char *sCol)
{
	int n;
	
	n = FindCol(sCol);
	
	if(n == -1)
	{
		return CQUERYNOCOL;
	}
	else
	{
		return GetFloat(n);
	}
}

void CQuery::GetStr(int nCol,char *buf)
{
	if(nCol > this->nCol)
	{
		buf[0] = '\0';
		return;
	}

	if(lCol[nCol-1] == SQL_NULL_DATA) 
	{
		buf[0] = '\0';
	}
	else
	{
		lstrcpy(buf,Col[nCol-1]);
	}
}

void CQuery::GetStr(char *sCol,char *buf)
{
	int n;
	
	n = FindCol(sCol);
	
	if(n == -1)
	{
		buf[0] = '\0';
	}
	else
	{
		GetStr(n,buf);
	}
}

void CQuery::PrintDiag()
{
	int ii;
	SQLRETURN Ret;
	SQLINTEGER NativeError;
	SQLCHAR SqlState[6],Msg[255];
	SQLSMALLINT MsgLen;
	char str[256];

	ii = 1;
	
	while(Ret = SQLGetDiagRec(SQL_HANDLE_STMT,hStmt,ii,SqlState,&NativeError,Msg,sizeof(Msg),&MsgLen) != SQL_NO_DATA)
	{
		wsprintf(str,"SQLSTATE:%s,Diagnosis:%s",(LPCTSTR)SqlState,(LPCTSTR)Msg);
		++ii;
	}

	if(strcmp((LPCTSTR)SqlState,"08S01") == 0)
	{
		ReConnect();
	}
}

int CQuery::ReadBlob(LPCTSTR szSQL,void *buf)
{
	SQLCHAR BinaryPtr[BLOBBATCH];
	SQLINTEGER LenBin;
	char *p;
	int nGet;
	int TotalGet = 0;

	ret = SQLExecDirect(hStmt,(SQLCHAR *)szSQL,SQL_NTS);
	
	if(ret != SQL_SUCCESS)
	{
		PrintDiag();
		return -1;
	}

	while((ret = SQLFetch(hStmt)) != SQL_NO_DATA)
	{
		p = (char*)buf;
		while((ret = SQLGetData(hStmt,1,SQL_C_BINARY,BinaryPtr,sizeof(BinaryPtr),&LenBin)) != SQL_NO_DATA)
		{
			if(LenBin == SQL_NULL_DATA)
			{
				Clear();
				return 0;
			}

			if(ret == SQL_SUCCESS)
			{
				nGet = LenBin;
			}
			else
			{
				nGet = BLOBBATCH;
			}

			TotalGet += nGet;
			memcpy(p,BinaryPtr,nGet);
			p += nGet;
		}
	}

	Clear();

	return TotalGet;
}

void CQuery::WriteBlob(LPCTSTR szSQL,void *buf,int size)
{
	SQLINTEGER cbBlob;
	char tmp[BLOBBATCH],*p;
	SQLPOINTER pToken;
	int nPut;

	cbBlob = SQL_LEN_DATA_AT_EXEC(size);
	SQLBindParameter(hStmt,1,SQL_PARAM_INPUT,SQL_C_BINARY,SQL_LONGVARBINARY,size,0,(SQLPOINTER)1,0,&cbBlob);
	SQLExecDirect(hStmt,(SQLCHAR *)szSQL,SQL_NTS);
	ret = SQLParamData(hStmt,&pToken);

	while(ret == SQL_NEED_DATA)
	{
		if(ret == SQL_NEED_DATA)
		{
			if((int)pToken == 1)
			{
				for(p = (char *)buf; p < (char *)buf + size; p += BLOBBATCH)
				{
					nPut = min(BLOBBATCH,(char *)buf + size - p);
					memcpy(tmp,p,nPut);
					SQLPutData(hStmt,(PTR)tmp,nPut);
				}
			}
		}
		ret = SQLParamData(hStmt,&pToken);
	}
	Clear();
}

void CQuery::InitConnection()
{
	szDriver="{SQL Server}";
	GetPrivateProfileString("SQLServer","Host","127.0.0.1",szServer,sizeof(szServer),SQLFILE_PATH);
	GetPrivateProfileString("SQLServer","Host","127.0.0.1",szServer2,sizeof(szServer2),SQLFILE_PATH);
	GetPrivateProfileString("SQLServer","Database","MuOnline",DataBase,sizeof(DataBase),SQLFILE_PATH);
	GetPrivateProfileString("SQLServer","User","sa",User,sizeof(User),SQLFILE_PATH);
	GetPrivateProfileString("SQLServer","Password","1234",Password,sizeof(Password),SQLFILE_PATH);
	
	this->Connect(3,DataBase,User,Password);
}