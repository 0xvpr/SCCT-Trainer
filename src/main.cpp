#include "utils.hpp"
#include "hacks.hpp"

#include <iostream>

#pragma comment(lib, "Winmm.lib")

uintptr_t module_base_addr = (uintptr_t)GetModuleHandle(NULL);

bool bGodGun = false;
bool bGodMode = false;
bool bAfterlife = false;
bool bPolterGheist = false;
bool bDisableAlarms = false;

DWORD WINAPI MainThread(LPVOID lpReserved)
{
    /* Console */
    FILE* fp;
    AllocConsole();
    freopen_s(&fp, "CONOUT$", "w", stdout);

    /* Main Loop */
    __displayMenu("Happy hacking!");
    while (!GetAsyncKeyState(VK_END))
    {

        /* Toggle GodMode */
        if (GetAsyncKeyState(VK_NUMPAD1) & 1)
        {
            bGodMode = !bGodMode;
            Hacks::GodMode(bGodMode);

            __displayMenu((bGodMode ? "GodMode Activated." : "GodMode Deactivated"));
        }

        /* Toggle Unlimited Ammo */
        if (GetAsyncKeyState(VK_NUMPAD2) & 1)
        {
            bGodGun = !bGodGun;
            Hacks::GodGun(bGodGun);

            __displayMenu((bGodGun ? "GodGun Activated." : "GodGun Deactivated"));
        }

        /*  Disable All Alarms */
        if (GetAsyncKeyState(VK_NUMPAD3) & 1)
        {
            bDisableAlarms = !bDisableAlarms;
            Hacks::DisableAlarms(bDisableAlarms);

            __displayMenu((bDisableAlarms == true ? "Disabling alarms." : "Reenabling alarms."));
        }

        /* Toggle PolterGheist */
        if (GetAsyncKeyState(VK_NUMPAD4) & 1)
        {
            bPolterGheist = !bPolterGheist;
            Hacks::PolterGheist(bPolterGheist);

            __displayMenu((bPolterGheist ? "PolterGheist Activated." : "PolterGheist Deactivated"));
        }

        /* Toggle Afterlife */
        if (GetAsyncKeyState(VK_NUMPAD5) & 1)
        {
            bAfterlife = !bAfterlife;
            Hacks::Afterlife(bAfterlife);
            
            __displayMenu((bAfterlife == true ? "Disabling all enemies." : "Restoring all enemies."));
        }

        /* Unlock All Doors */
        if (GetAsyncKeyState(VK_NUMPAD6) & 1)
        {
            Hacks::UnlockAllDoors();

            __displayMenu("Doors Unlocked.");
        }

    }
    /* Deactivate all cheats */
    std::cout << "Deactivating all cheats\n" << std::endl;

    Hacks::GodGun(false);
    Hacks::GodMode(false);
    Hacks::Afterlife(false);
    Hacks::PolterGheist(false);
    Hacks::DisableAlarms(false);

    PlaySound(TEXT("Exit Success"), 0, SND_SYNC);

    fclose(fp);
    FreeConsole();
    FreeLibraryAndExitThread((HMODULE)lpReserved, 0);

    return TRUE;
}

BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
    switch (dwReason)
    {
        case DLL_PROCESS_ATTACH:
            DisableThreadLibraryCalls(hInstance);
            CreateThread(0, 0, MainThread, hInstance, 0, 0);
            break;
        case DLL_PROCESS_DETACH:
            break;
        default:
            break;
    }

    return TRUE;
}
