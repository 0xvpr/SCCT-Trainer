#include "utils.h"
#include "hacks.h"

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

#define PSEUDO_MODULE_HANDLE -1

#pragma comment(lib, "Winmm.dll")

uintptr_t module_base_addr = 0;

bool bGodMode = false;
bool bGhostMode = false;
bool bSuperWeapons = false;
bool bDisableAlarms = false;
bool bDisableEnemies = false;

unsigned int total_doors_unlocked = 0;
unsigned int n_entities_changed = 0;

DWORD WINAPI MainThread(LPVOID lpReserved)
{
    module_base_addr = (uintptr_t)GetModuleHandle(NULL);

    /* Console */
    FILE* fp;
    AllocConsole();
    freopen_s(&fp, "CONOUT$", "w", stdout);

    /* Main Loop */
    utils_DisplayMenu("Happy hacking!");
    while (!GetAsyncKeyState(VK_END))
    {

        /* Toggle GodMode */
        if (GetAsyncKeyState(VK_NUMPAD1) & 1)
        {
            bGodMode = !bGodMode;
            hacks_GodMode(bGodMode);

            utils_DisplayMenu((bGodMode ? "God Mode activated." : "God Mode Deactivated."));
        }

        /* Toggle GhostMode */
        if (GetAsyncKeyState(VK_NUMPAD2) & 1)
        {
            bGhostMode = !bGhostMode;
            hacks_GhostMode(bGhostMode);

            utils_DisplayMenu((bGhostMode ? "GhostMode activated." : "GhostMode Deactivated"));
        }

        /* Toggle Super Weapons */
        if (GetAsyncKeyState(VK_NUMPAD3) & 1)
        {
            bSuperWeapons = !bSuperWeapons;
            hacks_SuperWeapons(bSuperWeapons);

            utils_DisplayMenu((bSuperWeapons ? "Super Weapons activated." : "Super Weapons Deactivated."));
        }

        /*  Disable All Alarms */
        if (GetAsyncKeyState(VK_NUMPAD4) & 1)
        {
            bDisableAlarms = !bDisableAlarms;
            hacks_DisableAlarms(bDisableAlarms);

            utils_DisplayMenu((bDisableAlarms ? "Disabling alarms." : "Re-enabling alarms."));
        }

        /* Toggle DisableEnemies */
        if (GetAsyncKeyState(VK_NUMPAD5) & 1)
        {
            bDisableEnemies = !bDisableEnemies;
            n_entities_changed = hacks_DisableEnemies(bDisableEnemies);

            char entities_changed_text[64] = { 0 };
            sprintf_s(entities_changed_text, sizeof(entities_changed_text), "%d Enemies %s.", n_entities_changed, bDisableEnemies ? "Disabled" : "Re-enabled");
            
            utils_DisplayMenu(entities_changed_text);
        }

        /* Unlock All Doors */
        if (GetAsyncKeyState(VK_NUMPAD6) & 1)
        {
            unsigned int n_doors_unlocked = hacks_UnlockAllDoors();

            char unlock_doors_text[64] = { 0 };
            sprintf_s(unlock_doors_text, sizeof(unlock_doors_text), "%d new doors unlocked.", n_doors_unlocked);

            utils_DisplayMenu(unlock_doors_text);
        }

    }

    utils_Deactivate();
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