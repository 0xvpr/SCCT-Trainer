#include "mem.h"

uintptr_t FindDMAddress(uintptr_t ptr, unsigned offsets[], size_t size)
{
    uintptr_t addr = ptr;

    for (size_t i = 0; i < size; i++)
    {
        addr = *(uintptr_t*)addr;
        addr += offsets[i];
    }

    return addr;
}

void Patch(BYTE* dst, BYTE* src, size_t size)
{
    DWORD oldprotect;

    VirtualProtect(dst, size, PAGE_EXECUTE_WRITECOPY, &oldprotect);
    memcpy(dst, src, size); 
    VirtualProtect(dst, size, oldprotect, &oldprotect);
}

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

bool Hook(char* src, char* dst, int len)
{
    if (len < 5)
        return false;

    DWORD curProtection;

    VirtualProtect(src, len, PAGE_EXECUTE_READWRITE, &curProtection);
    memset(src, 0x90, len);

    uintptr_t relativeAddress = (uintptr_t)(dst - src - 5);
    *src = (char)0xE9;
    *(uintptr_t*)(src + 1) = (uintptr_t)relativeAddress;

    DWORD temp;
    VirtualProtect(src, len, curProtection, &temp);

    return true;
}

char* TrampHook(char* src, char* dst, unsigned int len)
{
    if (len < 5)
        return 0;

    char* gateway = (char*)VirtualAlloc(0, len + 5, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
    memcpy(gateway, src, len);

    uintptr_t gateJmpAddy = (uintptr_t)(src - gateway - 5);
    *(gateway + len) = (char)0xE9;
    *(uintptr_t*)(gateway + len + 1) = gateJmpAddy;

    if (Hook(src, dst, len))
    {
        return gateway;
    }

    else return NULL;
}

#ifndef __MINGW32__
    void __declspec( naked ) healthDetour(void)
    {
        __asm
        {
            cmp    dword ptr [edi], 0x110E8B50
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
