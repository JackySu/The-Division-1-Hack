#ifndef GLOBAL_H
#define GLOBAL_H

#include <Windows.h>

extern "C" LPVOID lpRemain;
extern "C" void hkFunction();
extern "C" void aimbotFunc();

/*
 * detours.h do not contain these structs so we need to redifine it here.
 * You can find the original definition in detours.cpp in the library source code.
 */
struct DETOUR_ALIGN
{
	BYTE    obTarget : 3;
	BYTE    obTrampoline : 5;
};

struct DETOUR_INFO
{
	// An X64 instuction can be 15 bytes long.
	// In practice 11 seems to be the limit.
	BYTE            rbCode[30];     // target code + jmp to pbRemain.
	BYTE            cbCode;         // size of moved target code.
	BYTE            cbCodeBreak;    // padding to make debugging easier.
	BYTE            rbRestore[30];  // original target code.
	BYTE            cbRestore;      // size of original target code.
	BYTE            cbRestoreBreak; // padding to make debugging easier.
	DETOUR_ALIGN    rAlign[8];      // instruction alignment array.
	PBYTE           pbRemain;       // first instruction after moved code. [free list]
	PBYTE           pbDetour;       // first instruction of detour function.
	BYTE            rbCodeIn[8];    // jmp [pbDetour]
};

using lpGetValueFnc = INT64(*)();

BYTE fakeLookAtFunc[128] = {
	// this func is injected at targetAddr
	0x90, 0x90, 0x90, 0x90, 0x90, // hook aimbot func here
	0xE9, 0x90, 0x90, 0x90, 0x90, // jmp TheDivision.exe+1057080
	0x90, 0x90, // padding
	// FullAutoWrapper -> TheDivision.exe+19C7850
	// targetAddr + 0xC
	0x48, 0x89, 0x5C, 0x24, 0x10,
	0x56,
	0x48, 0x83, 0xEC, 0x20,
	0x48, 0x8B, 0xDA,
	0x48, 0x8B, 0xF1,
	0xE8, 0xDF, 0xFF, 0xFF, 0xFF, // call targetAddr
	0xE9, 0x90, 0x90, 0x90, 0x90, // jmp TheDivision.exe+19C7865
	0x90
};

#endif