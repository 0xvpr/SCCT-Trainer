#include "mem.h"

#include <memoryapi.h>

uintptr_t memory_find_dynamic_address(uintptr_t ptr, uint16_t* offsets, size_t size)
{ 
    uintptr_t addr = ptr;

    for (size_t i = 0; i < size; i++)
    {
        addr = *(uintptr_t *)addr;
        addr += offsets[i];

        if (*(uintptr_t *)addr == 0)
        {
            return 0;
        }
    }

    return addr;
}

void memory_nop(void* dst, size_t size)
{
    DWORD oldprotect;

    VirtualProtect(dst, size, PAGE_EXECUTE_WRITECOPY, &oldprotect);
    memset(dst, 0x90, size); 
    VirtualProtect(dst, size, oldprotect, &oldprotect);
}

void memory_patch(void* dst, const void* src, size_t size)
{
    DWORD oldprotect;

    VirtualProtect(dst, size, PAGE_EXECUTE_WRITECOPY, &oldprotect);
    memcpy(dst, src, size); 
    VirtualProtect(dst, size, oldprotect, &oldprotect);
}

int memory_detour(void* targetFunc, void(* myFunc)(), size_t size)
{
    if (size < 5)
    {
        return FALSE;
    }

    DWORD dwProtect;
    VirtualProtect(targetFunc, size, PAGE_EXECUTE_READWRITE, &dwProtect);

    memset(targetFunc, 0x90, size); // memset nop
    uintptr_t relative_addr = ((uintptr_t)myFunc - (uintptr_t)targetFunc) - 5;

    *(unsigned char *)targetFunc = 0xE9; // replace with jmp
    *(uintptr_t *)((uintptr_t)targetFunc + 1) = relative_addr;
    VirtualProtect(targetFunc, size, dwProtect, &dwProtect);

    return TRUE;
}

char* memory_tramp_hook(char* src, char* dst, size_t size)
{
    if (size < 5)
    {
        return 0;
    }

    char* gateway = (char *)VirtualAlloc(0, size + 5, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
    memcpy(gateway, src, size);

    uintptr_t gateJmpAddress = (uintptr_t)(src - gateway - 5);
    *(gateway + size) = (char)0xE9;
    *(uintptr_t *)(gateway + size + 1) = gateJmpAddress;

    if (memory_detour(src, (void(*)())dst, size))
    {
        return gateway;
    }
    else
    {
        VirtualFree(gateway, size+5, MEM_RELEASE);
        return NULL;
    }
}
