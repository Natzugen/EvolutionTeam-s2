// SQLManager.cpp: implementation of the CQuery class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MSSQL.h"
#include "USER.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CQueryX SQLX;

CQueryX::CQueryX()
{
	this->m_SQLRowCount = -1;
	this->m_SQLResult = SQL_SUCCESS;

	SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &this->m_SQLEnvHandle);
	SQLSetEnvAttr(this->m_SQLEnvHandle, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)3, 250);
}

CQueryX::~CQueryX()
{
	if ( this->m_SQLSTMTHandle )
		SQLFreeHandle(SQL_HANDLE_STMT, this->m_SQLSTMTHandle);

	if ( this->m_SQLDBConnectionHandle )
		SQLDisconnect(this->m_SQLDBConnectionHandle);

	if ( this->m_SQLDBConnectionHandle )
		SQLFreeHandle(SQL_HANDLE_DBC, this->m_SQLDBConnectionHandle);

	if ( this->m_SQLEnvHandle )
		SQLFreeHandle(SQL_HANDLE_STMT, this->m_SQLEnvHandle);
}






bool CQueryX::Connect(int iDBType, SQLCHAR * lpszDNS, SQLCHAR * lpszID, SQLCHAR * lpszPass)
{
	int iRecCount = 1;

	this->m_iDBType = iDBType;
	strcpy((char*)this->m_DNS, (char*)lpszDNS);
	strcpy((char*)this->m_ID, (char*)lpszID);
	strcpy((char*)this->m_Pass, (char*)lpszPass);

	SQLAllocHandle(SQL_HANDLE_DBC, this->m_SQLEnvHandle, &this->m_SQLDBConnectionHandle);


	switch ( this->m_iDBType )
	{
	case 3:
		{
			this->m_SQLResult = SQLConnect(this->m_SQLDBConnectionHandle, lpszDNS, -3, lpszID, -3, lpszPass, -3 );
		}
	}

	if ( this->m_SQLResult != SQL_SUCCESS && this->m_SQLResult != SQL_SUCCESS_WITH_INFO )
	{
		SQLCHAR SQLState[256];
		SQLINTEGER SQLNativeError;
		SQLCHAR SQLMessageText[256];
		SQLSMALLINT SQLTextLen;

		while ( true )
		{
			SQLRETURN ret = SQLGetDiagRec(SQL_HANDLE_DBC, this->m_SQLDBConnectionHandle, iRecCount,
				SQLState,  &SQLNativeError, SQLMessageText, 255, &SQLTextLen);

			if ( ret == SQL_NO_DATA )
				break;

			iRecCount++;
		}

		return false;
	}

	this->m_SQLResult = SQLAllocHandle(SQL_HANDLE_STMT, this->m_SQLDBConnectionHandle, &this->m_SQLSTMTHandle);

	if ( this->m_SQLResult != SQL_SUCCESS && this->m_SQLResult != SQL_SUCCESS_WITH_INFO )
	{
		this->m_SQLSTMTHandle = NULL;
		return false;
	}

	return true;
}


bool CQueryX::ReConnect()
{
	return this->Connect(this->m_iDBType, this->m_DNS, this->m_ID, this->m_Pass);
}





bool CQueryX::Execute(LPSTR lpszStatement)
{

	SQLAllocHandle(SQL_HANDLE_STMT, this->m_SQLDBConnectionHandle, &this->m_SQLSTMTHandle);

	this->m_SQLResult = SQLExecDirect(this->m_SQLSTMTHandle, (SQLCHAR *)lpszStatement, -3);

	if ( this->m_SQLResult != SQL_SUCCESS && this->m_SQLResult != SQL_SUCCESS_WITH_INFO && this->m_SQLResult != SQL_NO_DATA )
	{
		this->LogError();
		return false;
	}

	SQLRowCount(this->m_SQLSTMTHandle, &this->m_SQLRowCount);
	SQLNumResultCols(this->m_SQLSTMTHandle, &this->m_SQLColCount);

	if ( this->m_SQLColCount > MAX_SQL_COL )
	{
		return false;
	}

	if ( this->m_SQLColCount == 0 )
	{
		this->Close();
		return true;
	}

	for ( int i=0;i<this->m_SQLColCount ; i++)
	{
		SQLBindCol(this->m_SQLSTMTHandle,i+1, SQL_CHAR, this->m_SQLReturnChar[i], MAX_SQLCHAR_RETURN_SIZE, &this->m_SQLReturnCharSize[i]);
		SQLDescribeCol(this->m_SQLSTMTHandle, i+1, this->m_SQLColName[i], 31, NULL, NULL, NULL, NULL, NULL);
	}

	return true;
}



SQLRETURN CQueryX::Fetch()
{
	this->m_SQLResult = SQLFetch(this->m_SQLSTMTHandle);
	return this->m_SQLResult;
}



void CQueryX::Close()
{
	SQLCloseCursor(this->m_SQLSTMTHandle);
	SQLFreeStmt(this->m_SQLSTMTHandle, SQL_UNBIND);
}



int CQueryX::GetColIndex(SQLCHAR * lpszCol)
{
	for ( int i=0;i<this->m_SQLColCount;i++)
	{
		if ( !strcmp((char*)lpszCol, (char*)this->m_SQLColName[i]))
		{
			return i;
		}
	}

	return -1;
}

#define GET_INFO_ERROR	-102



int CQueryX::ConvertToInteger(int iColIndex)
{
	if ( iColIndex > this->m_SQLColCount )
		return GET_INFO_ERROR;

	return atoi((char*)this->m_SQLReturnChar[iColIndex]);
}


int CQueryX::GetAsInteger(LPSTR lpszCol)
{
	int iColIndex = this->GetColIndex((SQLCHAR *)lpszCol);

	if ( iColIndex == -1 )
		return GET_INFO_ERROR;

	return this->ConvertToInteger(iColIndex);
}



float CQueryX::ConvertToFloat(int iColIndex)
{
	if ( iColIndex > this->m_SQLColCount )
		return GET_INFO_ERROR;

	return (float)atof((char*)this->m_SQLReturnChar[iColIndex]);
}


float CQueryX::GetAsFloat(LPSTR lpszCol)
{
	int iColIndex = this->GetColIndex((SQLCHAR *)lpszCol);

	if ( iColIndex == -1 )
		return GET_INFO_ERROR;

	return this->ConvertToFloat(iColIndex);
}

void CQueryX::ConvertToString(const int iColIndex, LPSTR OUT lpszReturnBuffer)
{
	if ( iColIndex > this->m_SQLColCount )
	{
		lpszReturnBuffer[0] = '\0';
		return;
	}

	lstrcpy(lpszReturnBuffer, (char*)this->m_SQLReturnChar[iColIndex]);
}




void CQueryX::GetAsString(LPSTR lpszCol, LPSTR OUT lpszReturnBuffer)
{
	int iColIndex = this->GetColIndex((SQLCHAR *)lpszCol);

	if ( iColIndex == -1 )
	{
		lpszReturnBuffer[0] = '\0';
		return;
	}

	this->ConvertToString(iColIndex, lpszReturnBuffer);
}



void CQueryX::LogError()
{
	int iRecord = 1;
	SQLCHAR SQLState[256];
	SQLINTEGER SQLNativeError;
	SQLCHAR SQLMessageText[256];
	SQLSMALLINT SQLTextLen;

	while ( true )
	{
		int ret = SQLGetDiagRec(SQL_HANDLE_STMT, this->m_SQLSTMTHandle, iRecord, 
			SQLState, &SQLNativeError, SQLMessageText, 253, &SQLTextLen);

		if ( ret == SQL_NO_DATA )
			break;

		iRecord++;

		if ( iRecord > 3 )
			break;
	}

	if ( !strcmp((char*)SQLState, "08S01"))	// Communication Link Failure
		this->ReConnect();
}






int CQueryX::GetAsBinary(LPSTR lpszStatement, LPBYTE OUT lpszReturnBuffer)
{
	SQLCHAR * pSQLBuf;
	SQLINTEGER BufLen;
	SQLCHAR SQLBinary[10000];
	SQLINTEGER lOfs = 0;
	SQLINTEGER SQLLen;


	this->m_SQLResult = SQLExecDirect(this->m_SQLSTMTHandle, (SQLCHAR *)lpszStatement, 253);

	if ( this->m_SQLResult != SQL_SUCCESS )
	{
		this->LogError();
		return -1;
	}

	while ( true )
	{
		this->m_SQLResult = SQLFetch(this->m_SQLSTMTHandle);

		if ( this->m_SQLResult == SQL_NO_DATA )
			break;

		pSQLBuf = lpszReturnBuffer;

		while ( true )
		{

			this->m_SQLResult = SQLGetData(this->m_SQLSTMTHandle,
				1, SQL_C_BINARY, SQLBinary, 10000, &SQLLen);

			if ( this->m_SQLResult == SQL_NO_DATA )
				break;

			if ( SQLLen == -1 )
			{
				this->Close();
				return 0;
			}

			if ( this->m_SQLResult == SQL_SUCCESS )
			{
				BufLen = SQLLen;
			}
			else
			{
				BufLen = 10000;
			}

			lOfs += BufLen;
			memcpy(pSQLBuf, SQLBinary, BufLen);
			pSQLBuf = &pSQLBuf[lOfs];
		}
	}

	this->Close();
	return BufLen;
}


void CQueryX::Disconnect()
{
	if ( this->m_SQLSTMTHandle )
		SQLFreeHandle(SQL_HANDLE_STMT, this->m_SQLSTMTHandle);

	if ( this->m_SQLDBConnectionHandle )
		SQLDisconnect(this->m_SQLDBConnectionHandle);

	if ( this->m_SQLDBConnectionHandle )
		SQLFreeHandle(SQL_HANDLE_DBC, this->m_SQLDBConnectionHandle);

	this->m_SQLSTMTHandle = NULL;
	this->m_SQLDBConnectionHandle = NULL;
}

int CQueryX::GetUserResetNumber(int aIndex)
{

	char szTemp[256];
	OBJECTSTRUCT *gObj = (OBJECTSTRUCT*)OBJECT_POINTER(aIndex);
	wsprintf(szTemp, "SELECT * FROM Character WHERE Name = '%s'", gObj->Name);

	this->Execute(szTemp);
	SQLFetch(this->m_SQLSTMTHandle);

	int ResetCount = this->GetAsInteger("Resets");
	SQLFreeHandle(SQL_HANDLE_STMT, this->m_SQLSTMTHandle);

	return ResetCount;
}
int CQueryX::GetResetCharacter(char Name[11])
{	
	char SQLJob[0xFF];
	char MSG2[200];
	GetPrivateProfileString("MoveStadium","ResetColumn","Resets",MSG2,200,".\\Custom.ini");
	// ---
	wsprintf(SQLJob, "SELECT %s FROM Character WHERE Name = '%s'",MSG2, Name);
	this->Execute(SQLJob);
	SQLFetch(this->m_SQLSTMTHandle);
	this->ResetS = this->GetAsInteger("Resets");
	SQLFreeHandle(SQL_HANDLE_STMT, this->m_SQLSTMTHandle);
	// ---
	return ResetS;
}

int CQueryX::GetBlockPCharacter(char Name[11])
{	
	char SQLJob[0xFF];
	char MSG2[200];
	//GetPrivateProfileString("MoveStadium","ResetColumn","Resets",MSG2,200,".\\Custom.ini");
	// ---
	wsprintf(SQLJob, "SELECT PostBlock FROM Character WHERE Name = '%s'", Name);
	this->Execute(SQLJob);
	SQLFetch(this->m_SQLSTMTHandle);
	this->BlockPost = this->GetAsInteger("PostBlock");
	SQLFreeHandle(SQL_HANDLE_STMT, this->m_SQLSTMTHandle);
	// ---
	return BlockPost;
}
void CQueryX::UpdatePostBCharacter(char Name[11],int PostBlockC)
{
	char SQLJob[0xFF];
	wsprintf(SQLJob,"UPDATE Character SET PostBlock='%d' WHERE Name='%s'",PostBlockC,Name);
	this->Execute(SQLJob);
}
int CQueryX::GetaIndexPlayer(char Name[11])
{	
	char SQLJob[0xFF];
	char MSG2[200];
	// ---
	wsprintf(SQLJob, "SELECT aIndex FROM Character WHERE Name = '%s'", Name);
	this->Execute(SQLJob);
	SQLFetch(this->m_SQLSTMTHandle);
	this->aIndexP = this->GetAsInteger("aIndex");
	SQLFreeHandle(SQL_HANDLE_STMT, this->m_SQLSTMTHandle);
	// ---
	return aIndexP;
}
void CQueryX::UpdateaIndexBCharacter(char Name[11],int aIndexS)
{
	char SQLJob[0xFF];
	wsprintf(SQLJob,"UPDATE Character SET aIndex ='%d' WHERE Name='%s'",aIndexS,Name);
	this->Execute(SQLJob);
}
void CQueryX::UpdatePostBCharacter2(char Name[11],int PostBlockD)
{
	char SQLJob[0xFF];
	wsprintf(SQLJob,"UPDATE Character SET PostBlock='%d'-1 WHERE Name='%s'",BlockPost,Name);
	this->Execute(SQLJob);
}
void CQueryX::UpdateUserResetNumber(int aIndex)
{
	char szTemp[256];
	OBJECTSTRUCT *gObj = (OBJECTSTRUCT*)OBJECT_POINTER(aIndex);
	wsprintf(szTemp, "SELECT * FROM Character WHERE Name = '%s'", gObj->Name);

	this->Execute(szTemp);
	SQLFetch(this->m_SQLSTMTHandle);

	int ResetCount = this->GetAsInteger("Resets");
	SQLFreeHandle(SQL_HANDLE_STMT, this->m_SQLSTMTHandle);

	char szTemp2[256];
	wsprintf(szTemp2, "UPDATE Character SET Resets = %d+1 WHERE Name = '%s'", ResetCount, gObj->Name);

	this->Execute(szTemp2);
	SQLFetch(this->m_SQLSTMTHandle);
	SQLFreeHandle(SQL_HANDLE_STMT, this->m_SQLSTMTHandle);
}
void CQueryX::UpdateResetSystem(char Name[11],int Resets)
{
	char SQLJob[0xFF];
	wsprintf(SQLJob,"UPDATE Character SET Resets='%d' WHERE Name='%s'",Resets+1,Name);
	this->Execute(SQLJob);
}

void CQueryX::UpdateCashOffExpSystemPlus(char Account[11],int gems)
{
	char SQLJob[0xFF];
	wsprintf(SQLJob,"UPDATE MEMB_INFO SET CSPoints = CSPoints + %d WHERE memb_guid = (SELECT memb_guid FROM MEMB_INFO WHERE memb___id = '%s')", gems, Account); 
	this->Execute(SQLJob);

}

void CQueryX::UpdateCashOffExpSystemMinus(char Account[11],int gems)
{
	char SQLJob[0xFF];
	wsprintf(SQLJob,"UPDATE MEMB_INFO SET CSPoints = CSPoints - %d WHERE memb_guid = (SELECT memb_guid FROM MEMB_INFO WHERE memb___id = '%s')", gems, Account); 
	this->Execute(SQLJob);

}
void CQueryX::UpdateCashOffExpSystemPlusCredit(char Account[11],int gems)
{
	char SQLJob[0xFF];
	wsprintf(SQLJob,"UPDATE MEMB_CREDITS SET credits = credits + %d WHERE memb___id = '%s' ", gems, Account); 
	this->Execute(SQLJob);

}

void CQueryX::UpdateCashOffExpSystemMinusCredit(char Account[11],int gems)
{
	char SQLJob[0xFF];
	wsprintf(SQLJob,"UPDATE MEMB_CREDITS SET credits = credits - %d WHERE memb___id = '%s'", gems, Account); 
	this->Execute(SQLJob);


}
int CQueryX::GetCoinsPlayer(char Account[11])
{	
	char SQLJob[0xFF];
	char MSG2[200];
	// ---  UPDATE MuCashShop_DATA SET CashPoint = CashPoint + %d WHERE memb_guid = (SELECT memb_guid FROM MEMB_INFO WHERE memb___id = '%s')
	wsprintf(SQLJob, "SELECT CSPoints FROM MEMB_INFO WHERE memb_guid = (SELECT memb_guid FROM MEMB_INFO WHERE memb___id = '%s')", Account);
	this->Execute(SQLJob);
	SQLFetch(this->m_SQLSTMTHandle);
	this->CoinsP = this->GetAsInteger("CSPoints");
	SQLFreeHandle(SQL_HANDLE_STMT, this->m_SQLSTMTHandle);
	// ---
	return CoinsP;
}
void CQueryX::UpdateZenPlayer(char Name[11],int zen)
{
	char SQLJob[0xFF];
	wsprintf(SQLJob,"UPDATE Character SET Money = %d WHERE Name='%s'", zen, Name); 
	this->Execute(SQLJob);

}

int CQueryX::GetCreditsPlayer(char Account[11])
{	
	char SQLJob[0xFF];
	char MSG2[200];
	// ---  UPDATE MuCashShop_DATA SET CashPoint = CashPoint + %d WHERE memb_guid = (SELECT memb_guid FROM MEMB_INFO WHERE memb___id = '%s')
	wsprintf(SQLJob, "SELECT Credits FROM MEMB_CREDITS WHERE memb___id = '%s'", Account);
	this->Execute(SQLJob);
	SQLFetch(this->m_SQLSTMTHandle);
	this->CreditsP = this->GetAsInteger("Credits");
	SQLFreeHandle(SQL_HANDLE_STMT, this->m_SQLSTMTHandle);
	// ---
	return CreditsP;
}
int  CQueryX::SelectVIP(int aIndex)
{   
	char szTemp[256];
	OBJECTSTRUCT *gObj = (OBJECTSTRUCT*)OBJECT_POINTER(aIndex);
	//BOOL bRet = ASql.ExecQuery("SELECT Type FROM T_PVPGens WHERE Name='%s';",Name);
	BOOL bRet =  wsprintf(szTemp,"SELECT VIP FROM Character WHERE Name='%s';",gObj->Name);
	int SelectVIP = 0;		
	

	if ( Fetch() == SQL_NO_DATA || bRet == FALSE )
	{	
		SelectVIP  = -1;
		Close();
	}
	else
	{
		SelectVIP = GetAsInteger("VIP");
		Close();
	}

	return SelectVIP;


}
int CQueryX::SelectNameV(char Name[11])
{   
	char szTemp[256];
	//BOOL bRet = ASql.ExecQuery("SELECT Type FROM T_PVPGens WHERE Name='%s';",Name);
	BOOL bRet =  wsprintf(szTemp,"SELECT Name FROM Character WHERE VIP='1'");
	int SelectNameV = 0;		
	

	if ( Fetch() == SQL_NO_DATA || bRet == FALSE )
	{	
		SelectNameV  = -1;
		Close();
	}
	else
	{
		SelectNameV = GetAsInteger("VIP");
		Close();
	}

	return SelectNameV;


}
int CQueryX::GetFieldInt( char* Table, char* Field, const char* Optional, ... )
{
	char Buffer[512];
	char buf[512]={0};
	va_list pArguments;
	va_start(pArguments, Optional);
	vsprintf_s(Buffer, Optional, pArguments);
	va_end(pArguments);
	if (Optional)
	{
		sprintf_s(buf,"SELECT * FROM %s %s", Table, Buffer);
	}
	else
		sprintf_s(buf,"SELECT * FROM %s",  Table);

	this->Execute(buf);
	SQLFetch(this->m_SQLSTMTHandle);
	int ReturnInt = this->GetAsInteger(Field);
	SQLFreeHandle(SQL_HANDLE_STMT, this->m_SQLSTMTHandle);

	return ReturnInt;
}

std::string	CQueryX::GetFieldChar( char* Table, char* Field, const char* Optional, ... )
{
	char Buffer[512];
	char buf[512]={0};
	va_list pArguments;
	va_start(pArguments, Optional);
	vsprintf_s(Buffer, Optional, pArguments);
	va_end(pArguments);
	if (Optional)
	{
		sprintf_s(buf,"SELECT * FROM %s %s", Table, Buffer);
	}
	else
		sprintf_s(buf,"SELECT * FROM %s",  Table);

	this->Execute(buf);
	SQLFetch(this->m_SQLSTMTHandle);
	this->GetAsString(Field,Buffer);
	SQLFreeHandle(SQL_HANDLE_STMT, this->m_SQLSTMTHandle);

	return Buffer;
}

std::string CQueryX::GetFieldBinary( char* Table, char* Field, const char* Optional, ... )
{
	char Buffer[512];
	char buf[512]={0};
	BYTE buf2[2000]={0};
	va_list pArguments;
	va_start(pArguments, Optional);
	vsprintf_s(Buffer, Optional, pArguments);
	va_end(pArguments);
	if (Optional)
	{
		sprintf_s(buf,"SELECT * FROM %s %s", Table, Buffer);
	}
	else
		sprintf_s(buf,"SELECT * FROM %s",  Table);

	this->Execute(buf);
	SQLFetch(this->m_SQLSTMTHandle);
	this->GetAsBinary(Field,buf2);
	SQLFreeHandle(SQL_HANDLE_STMT, this->m_SQLSTMTHandle);

	return (char*)buf2;
}

// --------------------------------------------------------------------------
__int64 CQueryX::ConvertToLongLong(int iColIndex)
{
	if ( iColIndex > this->m_SQLColCount )
		return GET_INFO_ERROR;

	return _atoi64((char*)this->m_SQLReturnChar[iColIndex]);
}
// -------=====
__int64 CQueryX::GetColIndexLong(SQLCHAR * lpszCol)
{
	for ( int i=0;i<this->m_SQLColCount;i++)
	{
		if ( !strcmp((char*)lpszCol, (char*)this->m_SQLColName[i]))
		{
			return i;
		}
	}

	return -1;
}
// -------=====
__int64 CQueryX::GetAsLongLong(LPSTR lpszCol)
{
	int iColIndex = this->GetColIndex((SQLCHAR *)lpszCol);

	if ( iColIndex == -1 )
		return GET_INFO_ERROR;

	return this->ConvertToLongLong(iColIndex);
}


__int64 CQueryX::GetFieldLongLong( char* Table, char* Field, const char* Optional, ... )
{
	char Buffer[512];
	char buf[512]={0};
	va_list pArguments;
	va_start(pArguments, Optional);
	vsprintf_s(Buffer, Optional, pArguments);
	va_end(pArguments);
	if (Optional)
	{
		sprintf_s(buf,"SELECT * FROM %s %s", Table, Buffer);
	}
	else
		sprintf_s(buf,"SELECT * FROM %s",  Table);

	this->Execute(buf);
	SQLFetch(this->m_SQLSTMTHandle);
	__int64 ReturnInt = this->GetAsLongLong(Field);
	SQLFreeHandle(SQL_HANDLE_STMT, this->m_SQLSTMTHandle);

	return ReturnInt;
}


int CQueryX::SynFloodProtect1(char IP[15])
{	
	char SQLJob[0xFF];
	char MSG2[200];
	//GetPrivateProfileString("MoveStadium","ResetColumn","Resets",MSG2,200,".\\Custom.ini");
	// --- 
	wsprintf(SQLJob, "SELECT  COUNT(IP) FROM SynFlood where IP='%s' ",IP);
	this->Execute(SQLJob);
	SQLFetch(this->m_SQLSTMTHandle);
	this->CountIp = this->GetAsInteger("CountIp");
	SQLFreeHandle(SQL_HANDLE_STMT, this->m_SQLSTMTHandle);
	// ---
	return CountIp;
}
void CQueryX::SynFloodProtect2(char IP[15])
{
	char SQLJob[0xFF];
	wsprintf(SQLJob,"INSERT INTO SynFlood  VALUES('%s')",IP);
	this->Execute(SQLJob);
}

void CQueryX::ReloadMobSystem(char Name[11])
{
	char SQLJob[0xFF];
	wsprintf(SQLJob,"DELETE FROM T_SummonPet_Info WHERE memb__char='%s'",Name);
	this->Execute(SQLJob);
}