#ifndef _SQLCLASS_H
#define _SQLCLASS_H
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <SQL.H>
#include <SqlExt.H>
#include "Utilidades.h"
#include "CRecordSet.H"

#define MAXSQLBUFLEN  255

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
extern void DebugInfo(char LogText[], DWORD Type);
class CSQL{

	public:
		bool Connect(char *sDriver, char *sServer, char *sUID, char *sPWD, char *sDatabase);
		bool GetErrorMessage(char *sOutError, const int iErrBufSz, HSTMT hStmt);
		bool ThrowErrorIfSet(HSTMT hStmt);
		bool ThrowError(HSTMT hStmt);
		void Disconnect(void);
		bool ExecuteNonQuery(const char *sSQL);
		bool Execute(const char *sSQL, CRecordSet *lpMyRS);
        bool bConnected;

        CSQL();
        ~CSQL();

		bool bThrowErrors;

    private:
        HENV hSQLEnvironment;
        HDBC hSQLConnection;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#endif
