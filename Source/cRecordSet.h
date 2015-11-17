#ifndef _CRECORDSET_H
#define _CRECORDSET_H
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <SQL.H>
#include <SQLExt.H>

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class CRecordSet{
	
	public:
		bool Close(void);
		bool Fetch(void);
		bool FetchEx(long *lErrCode);
		bool GetData(const SQLUSMALLINT iCol, SQLSMALLINT iType, SQLPOINTER pvBuf, SQLINTEGER iBufSz, SQLINTEGER *piOutBufSz);
		bool GetColInfo(const int iCol, char *sOutName, int iSzOfOutName, int *iOutColNameLen, int *ioutDataType, int *iOutColSize, int *iNumOfDeciPlaces, int *iColNullable);
		bool sColumnEx(const int iCol, char *sBuf, const int iBufSz, int *iOutLen);
		bool lColumnEx(const int iCol, long *plOutVal);
		long lColumn(const int iCol);
		bool dColumnEx(const int iCol, double *pdOutVal);
		bool bColumnEx(const int iCol, WORD * plOutVal);
		double dColumn(const int iCol);
		bool fColumnEx(const int iCol, float *pfOutVal);
		float fColumn(const int iCol);
		bool GetErrorMessage(char *sOutError, const int iErrBufSz);
		bool ThrowErrorIfSet(void);
		bool ThrowError(void);

		int RTrim(char *sData, int iDataSz);
		void ReplaceSingleQuotes(char *sData, int iDataSz);

		HSTMT hSTMT;
		long RowCount;
		long ColCount;

		bool bTrimCharData;
		bool bReplaceSingleQuotes;
		bool bThrowErrors;

        CRecordSet();
        ~CRecordSet();
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#endif
