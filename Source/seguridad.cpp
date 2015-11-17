/*-------------------------------------------------------*/
/*				Project Evolution Team Season 2          */
/*   Version GS 1.00.18 & GS-CS 1.00.19 Protocol Eng     */
/*             http://evolution-team.eu                  */
/*-------------------------------------------------------*/
/*                    Code By Th3AnG3L                   */
/*             http://evolution-team.eu                  */
/*-------------------------------------------------------*/
#include "seguridad.h"
#include "stdafx.h"
#define MacCount 13

bool CheckingMAC(LPCSTR MacID)
{
	//ACA PONER LOS MAC DE LOS CLIENTES, SI LA MAC NO ESTA ACA ENTONCES EL SERVER NO LE VA A FUNCIONAR.
	char ClientsMacs[MacCount][18] =
	{
		"B8-88-E3-45-2E-CA", //ME
	};

	for(int x=0; x<MacCount; x++)
	{
		if(!strcmp(MacID,ClientsMacs[x]))
		{
			return true;
		}
	}
	return false;
}

bool CheckMAC()
{
	unsigned char MACData[6];

	UUID uuid;
    UuidCreateSequential( &uuid );

    for (int i=2; i<8; i++)
	{
		MACData[i - 2] = uuid.Data4[i];
	}

	char MACADDR[18];
	sprintf(MACADDR, "%02X-%02X-%02X-%02X-%02X-%02X", MACData[0], MACData[1], MACData[2], MACData[3], MACData[4], MACData[5]);

	if(CheckingMAC(MACADDR))
	{
		return true;
	}

	else
	{	
		char Nose[255];
		sprintf(Nose, "You do not have license to use these files, send this serial: %02X-%02X-%02X-%02X-%02X-%02X  to support@evolution-team.eu", MACData[0], MACData[1], MACData[2], MACData[3], MACData[4], MACData[5]);
		MessageBoxA(NULL, Nose, "License Error By Evolution Team",MB_OK);
		::ExitProcess(0);
	}
	return false;
}
