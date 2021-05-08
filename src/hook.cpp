#include "hook.h"

#include <windows.h>

bool Detour(void* hookedFunc, void* myFunc, int length)
{
    if (length < 5)
        return false;

    DWORD oldProtect;
    VirtualProtect(hookedFunc, length, PAGE_EXECUTE_READWRITE, &oldProtect);

    memset(hookedFunc, 0x90, length);
    DWORD relAddr = ((DWORD)myFunc - (DWORD)hookedFunc) - 5;

    *(BYTE *)hookedFunc = 0xE9;
    *(DWORD *)((DWORD)hookedFunc + 1) = relAddr;
    VirtualProtect(hookedFunc, length, oldProtect, &oldProtect);

    return true;
}

void __declspec( naked ) healthDetour(void)
{
    __asm
    {
		cmp    DWORD PTR [edi],0x110e8b50
		je     $+0x08
		xor    eax,eax
		mov    eax,eax
		mov    DWORD PTR [ebx],eax
		mov    ebx,eax
		mov    eax,DWORD PTR [esp+0x14]
		pop    esi
		mov    DWORD PTR [eax],ebx
		pop    ebx
		pop    ecx
		ret    0x8
    }
}
