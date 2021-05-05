#include <iostream>
#include <windows.h>

DWORD WINAPI MainThread(LPVOID lpReserved)
{
    while (true)
    {
        // Do nothing
    }

    FreeLibraryAndExitThread((HMODULE)lpReserved, 0);
    return TRUE;
}
