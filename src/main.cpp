#include "includes.h"

#include <conio.h>
#include <cstdlib>
#include <iostream>


#define DEBUG


bool bNoRecoil = false;
bool bPlayDead = false;
bool bPolterGheist = false;

int previous_health = 0;

uintptr_t modBaseAddr = (uintptr_t)GetModuleHandle(NULL);

void __DisplayMenu(void);

DWORD WINAPI MainThread(LPVOID lpReserved)
{
#ifdef DEBUG
	FILE *fp;
	AllocConsole();
	freopen_s(&fp, "CONOUT$", "w", stdout);
#endif

	/* Main Loop */
    __DisplayMenu();
	while (!GetAsyncKeyState(VK_END))
	{
        /* Toggle PlayDead */
        if (GetAsyncKeyState('G') & 1)
        {
            bPlayDead = !bPlayDead;

            Hacks::PlayDead(bPlayDead, &previous_health);
            __DisplayMenu();

        }

        /* Toggle PolterGheist */
        if (GetAsyncKeyState('I') & 1)
        {
            bPolterGheist = !bPolterGheist;

            Hacks::Invisibilty(bPolterGheist);
            Hacks::Silent(bPolterGheist);
            __DisplayMenu();

        }

        /* Toggle No Recoil */
        if (GetAsyncKeyState('N') & 1)
        {
            bNoRecoil = !bNoRecoil;

            Hacks::NoRecoil(bNoRecoil);
            __DisplayMenu();

        }

        /* Teleport to ADS */
        if (GetAsyncKeyState(VK_LSHIFT) && GetAsyncKeyState('T') & 1)
        {
            Hacks::TeleportToADS();
            __DisplayMenu();
            std:: cout << "Teleporting...\n";
            
        }

        /* KillAll */
        if (GetAsyncKeyState(VK_LSHIFT) && GetAsyncKeyState('K') & 1)
        {
            Hacks::KillAll();
            __DisplayMenu();
            std::cout << "Killing All Enemies.\n";
            
        }
    }

#ifdef DEBUG
	fclose(fp);
	FreeConsole();
#endif

	FreeLibraryAndExitThread((HMODULE)lpReserved, 0);
	PlaySound(TEXT("ErrorSound"), 0, SND_ASYNC);
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

void __DisplayMenu(void)
{
    system("cls"); // slowest but simplest
    std::cout << "Press 'N' to toggle no recoil.\n"
                 "Press 'I' to toggle PolterGheist.\n\n";

    /* Toggle Status */
    std::cout << "PlayDead: " << ( bPlayDead ? "Enabled" : "Disabled") << "\n";
    std::cout << "PolterGheist: " << ( bPolterGheist ? "Enabled" : "Disabled") << "\n";
    std::cout << "NoRecoil: " << ( bNoRecoil ? "Enabled" : "Disabled");
}
