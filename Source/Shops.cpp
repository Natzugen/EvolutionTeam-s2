/*-------------------------------------------------------*/
/*				Project Evolution Team Season 2          */
/*   Version GS 1.00.18 & GS-CS 1.00.19 Protocol Eng     */
/*             http://evolution-team.eu                  */
/*-------------------------------------------------------*/
/*                    Code By Th3AnG3L                   */
/*             http://evolution-team.eu                  */
/*-------------------------------------------------------*/
/*#include "stdafx.h"
#include "Shops.h"
#include "MemScript.h"
#include <process.h>

DWORD Exc;

// CODIGO TOTALMENTE LEECHADO DA SCFMT

__declspec(naked) void ExcShop()
{
	Exc=0;

	_asm
	{
		MOV EDI,CWzMemScript::GetNumber
		CALL EDI
		MOV DWORD PTR SS:[EBP-0xBC],EAX
		LEA ECX,DWORD PTR SS:[EBP-0x9C]
		MOV EDI,CWzMemScript::GetToken
		CALL EDI
		MOV DWORD PTR SS:[EBP-0xA0],EAX
		LEA ECX,DWORD PTR SS:[EBP-0x9C]
		MOV EDI,CWzMemScript::GetNumber
		CALL EDI
		MOV Exc,EAX
		MOV EDI,ShopExcellentMod_Exit1 
		JMP EDI
	}
}

__declspec(naked) void ExcShopAdd()
{
	_asm
	{
		PUSH Exc
		MOV AL,BYTE PTR SS:[EBP+0x20]
		MOV EDI,ShopExcellentMod_Exit2
		JMP EDI
	}
}

void AssemblyExcShops()
{
	*(DWORD*)((ShopExcellentMod_Hook1+ 1)) = (DWORD)&ExcShop - (ShopExcellentMod_Hook1+ 5); 
	*(BYTE*)(ShopExcellentMod_Hook1) = 0xE9;
		
	*(DWORD*)((ShopExcellentMod_Hook2+ 1)) = (DWORD)&ExcShopAdd - (ShopExcellentMod_Hook2+ 5); 
	*(BYTE*)(ShopExcellentMod_Hook2) = 0xE9;
}
*/