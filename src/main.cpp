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

unsigned int total_doors_unlocked = 0;

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

            __displayMenu((bGodMode ? "God Mode activated." : "God Mode deactivated."));
        }

        /* Toggle Unlimited Ammo */
        if (GetAsyncKeyState(VK_NUMPAD2) & 1)
        {
            bGodGun = !bGodGun;
            Hacks::GodGun(bGodGun);

            __displayMenu((bGodGun ? "God Gun activated." : "God Gun deactivated."));
        }

        /*  Disable All Alarms */
        if (GetAsyncKeyState(VK_NUMPAD3) & 1)
        {
            bDisableAlarms = !bDisableAlarms;
            Hacks::DisableAlarms(bDisableAlarms);

            __displayMenu((bDisableAlarms ? "Disabling alarms." : "Re-enabling alarms."));
        }

        /* Toggle PolterGheist */
        if (GetAsyncKeyState(VK_NUMPAD4) & 1)
        {
            bPolterGheist = !bPolterGheist;
            Hacks::PolterGheist(bPolterGheist);

            __displayMenu((bPolterGheist ? "PolterGheist activated." : "PolterGheist deactivated"));
        }

        /* Toggle Afterlife */
        if (GetAsyncKeyState(VK_NUMPAD5) & 1)
        {
            bAfterlife = !bAfterlife;
            unsigned int n_entities_changed = Hacks::Afterlife(bAfterlife);

            char entities_changed_text[64] = {};
            sprintf_s(entities_changed_text, sizeof(entities_changed_text), "%d Enemies %s.", n_entities_changed, bAfterlife ? "Disabled" : "Re-enabled");
            
            __displayMenu(entities_changed_text);
        }

        /* Unlock All Doors */
        if (GetAsyncKeyState(VK_NUMPAD6) & 1)
        {
            unsigned int n_doors_unlocked = Hacks::UnlockAllDoors();

            char unlock_doors_text[64] = {};
            sprintf_s(unlock_doors_text, sizeof(unlock_doors_text), "%d new doors unlocked.", n_doors_unlocked);

            __displayMenu(unlock_doors_text);
        }

    }

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
