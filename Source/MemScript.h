/*-------------------------------------------------------*/
/*				Project Evolution Team Season 2          */
/*   Version GS 1.00.18 & GS-CS 1.00.19 Protocol Eng     */
/*             http://evolution-team.eu                  */
/*-------------------------------------------------------*/
/*                    Code By Th3AnG3L                   */
/*             http://evolution-team.eu                  */
/*-------------------------------------------------------*/
#ifndef WZMEMSCRIPT
#define WZMEMSCRIPT

#if _MSC_VER > 1000
#pragma once
#endif

#include "ReadScript.h"

class CWzMemScript
{
public:

	CWzMemScript();
	virtual ~CWzMemScript();

	int SetBuffer( char* buffer, int buffersize);
	void SetScriptParsingBuffer(char* buffer, int size);
	enum SMDToken GetToken();
	//enum SMDToken __thiscall TokenType();
	int GetNumber();
	char* GetString();
	int GetC();
	void UnGetC(int ch);

private:

	char* m_pBuffer;	// 4
	int m_iBufferSize;	// 8
	int m_iBufferCount;	// C
	HANDLE m_hFile;	// 10
	char * m_Token;	// 14
	float TokenNumber;	// 18
	char TokenString[100];	// 1C
	enum SMDToken CurrentToken;	// 80
};

#endif
