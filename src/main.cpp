#include "utils.hpp"
#include "hacks.hpp"

#include <iostream>

#pragma comment(lib, "Winmm.lib")

uintptr_t module_base_addr = (uintptr_t)GetModuleHandle(NULL);

bool bNoRecoil = false;
bool bAfterlife = false;
bool bPolterGheist = false;
bool bUnlimitedAmmo = false;
bool bUnlimitedHealth = false;

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

        /* Toggle Unlimited Health*/
        if (GetAsyncKeyState(VK_NUMPAD1) & 1)
        {
            bUnlimitedHealth = !bUnlimitedHealth;

            Hacks::UnlimitedHealth(bUnlimitedHealth);

            __displayMenu("Unlimited Health Activated.");
        }

        /* Toggle Unlimited Ammo */
        if (GetAsyncKeyState(VK_NUMPAD2) & 1)
        {
            bUnlimitedAmmo = !bUnlimitedAmmo;

            Hacks::UnlimitedAmmo(bUnlimitedAmmo);

            __displayMenu("Unlimited Ammo Activated.");
        }

        /* Toggle No Recoil */
        if (GetAsyncKeyState(VK_NUMPAD3) & 1)
        {
            bNoRecoil = !bNoRecoil;

            Hacks::NoRecoil(bNoRecoil);

            __displayMenu("");
        }

        /* Toggle PolterGheist */
        if (GetAsyncKeyState(VK_NUMPAD4) & 1)
        {
            bPolterGheist = !bPolterGheist;

            Hacks::Invisibilty(bPolterGheist);
            Hacks::Silent(bPolterGheist);

            __displayMenu("");

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
    PlaySound(TEXT("ErrorSound"), 0, SND_SYNC);

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
