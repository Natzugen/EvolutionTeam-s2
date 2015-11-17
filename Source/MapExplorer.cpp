/*#include "StdAfx.h"

// Explorer Expansion
void _declspec(naked) ExplorerExtension()
{
	_asm
	{
		MOV EDI,0x0052E091;
		CMP EDX,0x801F;
		JG 0x0052E091;

		CMP EDX,50;
		JE Lorencia;

		CMP EDX,51;
		JE Dungeon;

		CMP EDX,52;
		JE Devias;

		CMP EDX,53;
		JE Noria;

		CMP EDX,54;
		JE LostTower;

		CMP EDX,56;
		JE Stadium;

		CMP EDX,57;
		JE Atlans;

		CMP EDX,58;
		JE Tarkan;

		CMP EDX,59;
		JE DevilSquare;

		CMP EDX,60;
		JE DevilSquare2;

		CMP EDX,61;
		JE Icarus;

		CMP EDX,62;
		JE BloodCastle1;

		CMP EDX,63;
		JE BloodCastle2;

		CMP EDX,64;
		JE BloodCastle3;

		CMP EDX,65;
		JE BloodCastle4;

		CMP EDX,66;
		JE BloodCastle5;

		CMP EDX,67;
		JE BloodCastle6;

		CMP EDX,68;
		JE BloodCastle7;

		CMP EDX,69;
		JE ChaosCastle1;

		CMP EDX,70;
		JE ChaosCastle2;

		CMP EDX,71;
		JE ChaosCastle3;

		CMP EDX,72;
		JE ChaosCastle4;

		CMP EDX,73;
		JE ChaosCastle5;

		CMP EDX,74;
		JE ChaosCastle6;

		CMP EDX,75;
		JE Kalima1;

		CMP EDX,76;
		JE Kalima2;

		CMP EDX,77;
		JE Kalima3;

		CMP EDX,78;
		JE Kalima4;

		CMP EDX,79;
		JE Kalima5;

		CMP EDX,80;
		JE Kalima6;

		CMP EDX,81;
		JE Kalima7;

		CMP EDX,82;
		JE Aida;

		CMP EDX,83;
		JE Kanturu1n2;

		CMP EDX,84;
		JE Kanturu3;

		CMP EDX,85;
		JE RefineryTower;

		MOV DWORD PTR DS:[0xB8A9E44],0;
		MOV EDI,0x0052DF7A;
		JMP EDI;

		Lorencia:
		MOV DWORD PTR DS:[0xB8A9E40],0;
		MOV DWORD PTR DS:[0xB8A9E44],1;
		JMP Fix;

		Dungeon:
		MOV DWORD PTR DS:[0xB8A9E40],1;
		MOV DWORD PTR DS:[0xB8A9E44],1;
		JMP Fix;

		Devias:
		MOV DWORD PTR DS:[0xB8A9E40],2;
		MOV DWORD PTR DS:[0xB8A9E44],1;
		JMP Fix;

		Noria:
		MOV DWORD PTR DS:[0xB8A9E40],3;
		MOV DWORD PTR DS:[0xB8A9E44],1;
		JMP Fix;

		LostTower:
		MOV DWORD PTR DS:[0xB8A9E40],4;
		MOV DWORD PTR DS:[0xB8A9E44],1;
		JMP Fix;

		Stadium:
		MOV DWORD PTR DS:[0xB8A9E40],6;
		MOV DWORD PTR DS:[0xB8A9E44],1;
		JMP Fix;

		Atlans:
		MOV DWORD PTR DS:[0xB8A9E40],7;
		MOV DWORD PTR DS:[0xB8A9E44],1;
		JMP Fix;

		Tarkan:
		MOV DWORD PTR DS:[0xB8A9E40],8;
		MOV DWORD PTR DS:[0xB8A9E44],1;
		JMP Fix;

		DevilSquare:
		MOV DWORD PTR DS:[0xB8A9E40],9;
		MOV DWORD PTR DS:[0xB8A9E44],1;
		JMP Fix;

		DevilSquare2:
		MOV DWORD PTR DS:[0xB8A9E40],32;
		MOV DWORD PTR DS:[0xB8A9E44],1;
		JMP Fix;

		Icarus:
		MOV DWORD PTR DS:[0xB8A9E40],10;
		MOV DWORD PTR DS:[0xB8A9E44],1;
		JMP Fix;

		BloodCastle1:
		MOV DWORD PTR DS:[0xB8A9E40],11;
		MOV DWORD PTR DS:[0xB8A9E44],1;
		JMP Fix;

		BloodCastle2:
		MOV DWORD PTR DS:[0xB8A9E40],12;
		MOV DWORD PTR DS:[0xB8A9E44],1;
		JMP Fix;

		BloodCastle3:
		MOV DWORD PTR DS:[0xB8A9E40],13;
		MOV DWORD PTR DS:[0xB8A9E44],1;
		JMP Fix;

		BloodCastle4:
		MOV DWORD PTR DS:[0xB8A9E40],14;
		MOV DWORD PTR DS:[0xB8A9E44],1;
		JMP Fix;

		BloodCastle5:
		MOV DWORD PTR DS:[0xB8A9E40],15;
		MOV DWORD PTR DS:[0xB8A9E44],1;
		JMP Fix;

		BloodCastle6:
		MOV DWORD PTR DS:[0xB8A9E40],16;
		MOV DWORD PTR DS:[0xB8A9E44],1;
		JMP Fix;

		BloodCastle7:
		MOV DWORD PTR DS:[0xB8A9E40],17;
		MOV DWORD PTR DS:[0xB8A9E44],1;
		JMP Fix;

		ChaosCastle1:
		MOV DWORD PTR DS:[0xB8A9E40],18;
		MOV DWORD PTR DS:[0xB8A9E44],1;
		JMP Fix;

		ChaosCastle2:
		MOV DWORD PTR DS:[0xB8A9E40],19;
		MOV DWORD PTR DS:[0xB8A9E44],1;
		JMP Fix;

		ChaosCastle3:
		MOV DWORD PTR DS:[0xB8A9E40],20;
		MOV DWORD PTR DS:[0xB8A9E44],1;
		JMP Fix;

		ChaosCastle4:
		MOV DWORD PTR DS:[0xB8A9E40],21;
		MOV DWORD PTR DS:[0xB8A9E44],1;
		JMP Fix;

		ChaosCastle5:
		MOV DWORD PTR DS:[0xB8A9E40],22;
		MOV DWORD PTR DS:[0xB8A9E44],1;
		JMP Fix;

		ChaosCastle6:
		MOV DWORD PTR DS:[0xB8A9E40],23;
		MOV DWORD PTR DS:[0xB8A9E44],1;
		JMP Fix;

		Kalima1:
		MOV DWORD PTR DS:[0xB8A9E40],24;
		MOV DWORD PTR DS:[0xB8A9E44],1;
		JMP Fix;

		Kalima2:
		MOV DWORD PTR DS:[0xB8A9E40],25;
		MOV DWORD PTR DS:[0xB8A9E44],1;
		JMP Fix;

		Kalima3:
		MOV DWORD PTR DS:[0xB8A9E40],26;
		MOV DWORD PTR DS:[0xB8A9E44],1;
		JMP Fix;

		Kalima4:
		MOV DWORD PTR DS:[0xB8A9E40],27;
		MOV DWORD PTR DS:[0xB8A9E44],1;
		JMP Fix;

		Kalima5:
		MOV DWORD PTR DS:[0xB8A9E40],28;
		MOV DWORD PTR DS:[0xB8A9E44],1;
		JMP Fix;

		Kalima6:
		MOV DWORD PTR DS:[0xB8A9E40],29;
		MOV DWORD PTR DS:[0xB8A9E44],1;
		JMP Fix;

		Kalima7:
		MOV DWORD PTR DS:[0xB8A9E40],36;
		MOV DWORD PTR DS:[0xB8A9E44],1;
		JMP Fix;

		Aida:
		MOV DWORD PTR DS:[0xB8A9E40],33;
		MOV DWORD PTR DS:[0xB8A9E44],1;
		JMP Fix;

		Kanturu1n2:
		MOV DWORD PTR DS:[0xB8A9E40],37;
		MOV DWORD PTR DS:[0xB8A9E44],1;
		JMP Fix;

		Kanturu3:
		MOV DWORD PTR DS:[0xB8A9E40],38;
		MOV DWORD PTR DS:[0xB8A9E44],1;
		JMP Fix;

		RefineryTower:
		MOV DWORD PTR DS:[0xB8A9E40],39;
		MOV DWORD PTR DS:[0xB8A9E44],1;
		JMP Fix;

		Fix:
		MOV EDI,0x0052E4DC;
		JMP EDI;
		};
}

// Map Explorer Intializer
void InitMapExplorer()
{
	memset((PBYTE)0x0052DF6A,0xE9,1);
	FunctionHook((DWORD)&ExplorerExtension,0x0052DF6A);
	SetNop(0x0052DF6F,11);
} */