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

#ifndef __MINGW32__
    void __declspec( naked ) healthDetour(void)
    {
        __asm
        {
            cmp    dword ptr [edi], 0X110E8B50
            je     $ + 0x08
            xor    eax, eax
            mov    eax, eax
            mov    dword ptr [ebx], eax
            mov    ebx, eax
            mov    eax, dword ptr [esp + 0x14]
            pop    esi
            mov    dword ptr [eax], ebx
            pop    ebx
            pop    ecx
            ret    0x8
        }
    }
#else
    void __declspec() healthDetour(void)
    {
        __asm__
        (
            "cmp    dword ptr [edi], 0X110E8B50\n\t"
            "je     $ + 0x08\n\t"
            "xor    eax, eax\n\t"
            "mov    eax, eax\n\t"
            "mov    dword ptr [ebx], eax\n\t"
            "mov    ebx, eax\n\t"
            "mov    eax, dword ptr [esp + 0x14]\n\t"
            "pop    esi\n\t"
            "mov    dword ptr [eax], ebx\n\t"
            "pop    ebx\n\t"
            "pop    ecx\n\t"
            "ret    0x8\n\t"
        );
    }
#endif
