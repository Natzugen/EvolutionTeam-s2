#include "stdafx.h"
#include "windows.h"
#include "winbase.h"
#include "COMMCTRL.h"
#include "time.h"
#include "windef.h"
#include <direct.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <cstdlib>
#include <cstdio>
#include <cstdarg>

//SQL Server
#define CFG_ARQUIVO	".\\OGC_Connect.ini"
#include "cSQL.H"
#include "cRecordSet.H"
#include "SQL.H"
//#include "../Headers/SCFDBPackets.h"
#pragma warning(disable:4172)

CSQL MsSQL;
CRecordSet MyRS;
TCHAR sql_server[64];
TCHAR sql_user[64];
TCHAR sql_pass[64];
TCHAR sql_databasemu[64];
TCHAR sql_databaseme[64];
//TCHAR sql_databasescfmt[64]="OGC-Servers";
TCHAR sql_resets[64];
TCHAR sql_vip[64];
TCHAR sql_zscountcol[64];
TCHAR sql_zscountcolname[64];

/*
Para prevenir Errores en Bases de datos NO mixeadas como la mia hay q usar:
Por Ejemplo: 

SELECT Resets FROM MuOnline.dbo.Character WHERE Name = '%s'
UPDATE Me_Muonline.dbo.MEMB_INFO SET bloc_code = 0 WHERE memb___id = '%s'

Es algo que te permite usar MSSQL 2005 SIN problemas.
Mira abajo si no la petie, creo que con por ejemplo deberia funcionar:

sprintf(sSQL, "SELECT %s FROM %s WHERE Name = '%s'",sql_resets, sql_character, Jogador);

*/
void SQL_Load()
{
	MsSQL.bThrowErrors = true;

	// -- SQL Server
	GetPrivateProfileString("SQL","OGC_Host","localhost",sql_server,64,CFG_ARQUIVO);
	GetPrivateProfileString("SQL","OGC_Username","sa",sql_user,64,CFG_ARQUIVO);
	GetPrivateProfileString("SQL","OGC_Password","654321",sql_pass,64,CFG_ARQUIVO);
	GetPrivateProfileString("SQL","OGC_DatabaseMU","MuOnline1",sql_databasemu,64,CFG_ARQUIVO);
	GetPrivateProfileString("SQL","OGC_DatabaseME","Me_Muonline",sql_databaseme,64,CFG_ARQUIVO);
	//GetPrivateProfileString("SQL","SCFDatabaseSCFMT","SCFMT",sql_databasescfmt,64,CFG_ARQUIVO);
	GetPrivateProfileString("SQL","OGC_ColumnResets","Resets",sql_resets,64,CFG_ARQUIVO);
	GetPrivateProfileString("SQL","OGC_ColumnVip","Vip",sql_vip,64,CFG_ARQUIVO);
	GetPrivateProfileString("SQL","OGC_CountCol","zs_count",sql_zscountcol,64,CFG_ARQUIVO);
	GetPrivateProfileString("SQL","OGC_CharNameCol","Name",sql_zscountcolname,64,CFG_ARQUIVO);
	//SQL_Conectar();
//	MsSQL.Disconnect();
}

bool SQL_Conectar()
{
		if(!MsSQL.Connect("{SQL Server}", sql_server, sql_user, sql_pass, sql_databasemu))
		{
		//	DebugInfo("SQL Server connect error",99);
			//MsgBox("SQL: No fue posible conectar al servidor.\n");
			MessageBox(NULL,"SQL: No fue posible conectar al servidor","OGC-Servers",MB_OK);
				::ExitProcess(0);
		//	return false;
		}
		return true;
}

int SQL_DelChar(char* PlayerName)
{
	char sSQL[1024] = {0};
	wsprintf(sSQL,"SELECT %s FROM [%s].[dbo].[Character] where %s='%s'", sql_zscountcol,sql_databasemu,sql_zscountcolname,PlayerName);
	
	if(!MsSQL.Execute(sSQL, &MyRS))	{
		DebugInfo("Failed to execute the SQL statement",99);
		//MsgBox("Failed to execute the SQL statement.\n");
		MessageBox(NULL,"Failed to execute the SQL statement","OGC-Servers",MB_OK);
			::ExitProcess(0);
		return false;
	}

	char sBuf[1024] = {0};
	int iBufSz = 0;

	while(MyRS.Fetch()) {
		MyRS.sColumnEx(1,sBuf, sizeof(sBuf), &iBufSz);
	}
	
	int DelChar = atoi(sBuf);
	MyRS.Close();
	return DelChar;
}

/*

int SQL_Reset(char* Jogador)
{
	char sSQL[1024] = {0};
	wsprintf(sSQL,"SELECT %s FROM %s.dbo.Character WHERE Name = '%s'", sql_resets , sql_databasemu ,Jogador);
	if(!MsSQL.Execute(sSQL, &MyRS))	{
		DebugInfo("Failed to execute the SQL statement",99);
		//MsgBox("Failed to execute the SQL statement.\n");
		return false;
	}

	char sBuf[1024] = {0};
	int iBufSz = 0;

	while(MyRS.Fetch()) {
		MyRS.sColumnEx(1,sBuf, sizeof(sBuf), &iBufSz);
	}
	
	int Resets = atoi(sBuf);
	MyRS.Close();
	return Resets;
}

int SQL_IsVip(char* PlayerName)
{
	char sSQL[1024] = {0};
	wsprintf(sSQL,"SELECT SCFIsVip FROM %s.dbo.MEMB_INFO WHERE memb___id = '%s'",  sql_databaseme ,PlayerName);
	if(!MsSQL.Execute(sSQL, &MyRS))	{
		DebugInfo("Failed to execute the SQL statement",99);
		//MsgBox("Failed to execute the SQL statement.\n");
		return false;
	}

	char sBuf[1024] = {0};
	int iBufSz = 0;

	while(MyRS.Fetch()) {
		MyRS.sColumnEx(1,sBuf, sizeof(sBuf), &iBufSz);
	}
	
	int Vip = atoi(sBuf);
	MyRS.Close();
	return Vip;
}

int SQL_VipDays(char* PlayerName)
{
	char sSQL[1024] = {0};
	wsprintf(sSQL,"SELECT SCFVipDays FROM %s.dbo.MEMB_INFO WHERE memb___id = '%s'",  sql_databaseme ,PlayerName);
	if(!MsSQL.Execute(sSQL, &MyRS))	{
		DebugInfo("Failed to execute the SQL statement",99);
		//MsgBox("Failed to execute the SQL statement.\n");
		return false;
	}

	char sBuf[1024] = {0};
	int iBufSz = 0;

	while(MyRS.Fetch()) {
		MyRS.sColumnEx(1,sBuf, sizeof(sBuf), &iBufSz);
	}
	
	int Vip = atoi(sBuf);
	MyRS.Close();
	return Vip;
}

int SQL_Get_ExtCKNum(char* PlayerName)
{
	char sSQL[1024] = {0};
	wsprintf(sSQL,"SELECT ExtCKNum FROM [%s].[dbo].[Warehouse] where AccountID='%s'", sql_databasemu,PlayerName);
	if(!MsSQL.Execute(sSQL, &MyRS))	{
		DebugInfo("Failed to execute the SQL statement",99);
		//MsgBox("Failed to execute the SQL statement.\n");
		return false;
	}

	char sBuf[1024] = {0};
	int iBufSz = 0;

	while(MyRS.Fetch()) {
		MyRS.sColumnEx(1,sBuf, sizeof(sBuf), &iBufSz);
	}
	
	int ExtCKNum = atoi(sBuf);
	MyRS.Close();
	return ExtCKNum;
}

int SQL_VipMoney(char* PlayerName)
{
	char sSQL[1024] = {0};
	wsprintf(sSQL,"SELECT SCFVipMoney FROM %s.dbo.MEMB_INFO WHERE memb___id = '%s'",  sql_databaseme ,PlayerName);
	if(!MsSQL.Execute(sSQL, &MyRS))	{
		DebugInfo("Failed to execute the SQL statement",99);
		//MsgBox("Failed to execute the SQL statement.\n");
		return false;
	}

	char sBuf[1024] = {0};
	int iBufSz = 0;

	while(MyRS.Fetch()) {
		MyRS.sColumnEx(1,sBuf, sizeof(sBuf), &iBufSz);
	}
	
	int Vip = atoi(sBuf);
	MyRS.Close();
	return Vip;
}
*/