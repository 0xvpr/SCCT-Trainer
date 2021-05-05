#include "hacks.hpp"

#include <iostream>

#pragma comment(lib, "Winmm.lib")


bool bNoRecoil = false;
bool bPlayDead = false;
bool bAfterlife = false;
bool bPolterGheist = false;

int previous_health = 0;

void __DisplayMenu(void);

DWORD WINAPI MainThread(LPVOID lpReserved)
{
    /* Console */
	FILE *fp;
	AllocConsole();
	freopen_s(&fp, "CONOUT$", "w", stdout);

	/* Main Loop */
    __DisplayMenu();
	while (!GetAsyncKeyState(VK_END))
	{

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

        /* Unlock All Doors */
        if (GetAsyncKeyState('U') & 1)
        {
            Hacks::UnlockAllDoors();
            __DisplayMenu();
            std:: cout << "Doors Unlocked.\n";

        }

        /* Toggle Afterlife */
        if (GetAsyncKeyState(VK_LSHIFT) && GetAsyncKeyState('K') & 1)
        {
            bAfterlife = !bAfterlife;

            Hacks::Afterlife(bAfterlife);
            __DisplayMenu();
            std::cout << (bAfterlife == true ? "Disabling" : "Restoring" ) << "all enemies.\n";
            
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

void __DisplayMenu(void)
{
    system("cls"); // slowest but simplest
    std::cout << "Press 'N' to toggle no recoil.\n"
                 "Press 'I' to toggle PolterGheist.\n"
                 "Press 'U' to unlock all doors.\n\n";

    /* Toggle Status */
    std::cout << "PlayDead: " << ( bPlayDead ? "Enabled" : "Disabled") << "\n";
    std::cout << "PolterGheist: " << ( bPolterGheist ? "Enabled" : "Disabled") << "\n";
    std::cout << "NoRecoil: " << ( bNoRecoil ? "Enabled" : "Disabled\n\n");
}
