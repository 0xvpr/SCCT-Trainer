#include <stdio.h>

#include "includes.h"


// #define DEBUG


bool bKillAll = false;
bool bNoRecoil = false;
bool bPlayDead = false;
bool bPolterGheist = false;

uint64_t previous_health = 0;


DWORD WINAPI MainThread(LPVOID lpReserved)
{
	uintptr_t module_base_addr = (uintptr_t)GetModuleHandle(NULL);
#ifdef DEBUG
	FILE *f;
	AllocConsole();
	freopen_s(&f, "CONOUT$", "w", stdout);
#endif

	// Main Loop
	while (!GetAsyncKeyState(VK_END))
	{
		
		// Toggle PlayDead
		if (GetAsyncKeyState('G') & 1)
		{
			bPlayDead = !bPlayDead;

			PlayDead(bPlayDead, &previous_health);
			printf("PlayDead: %s.\n", bPlayDead ? "Enabled" : "Disabled");

		}

		// Toggle PolterGheist
		if (GetAsyncKeyState('I') & 1)
		{
			bPolterGheist = !bPolterGheist;

			Invisibilty(bPolterGheist);
			Silent(bPolterGheist);
			printf("PolterGheist: %s.\n", bPolterGheist ? "Enabled" : "Disabled");

		}

		// Toggle No Recoil
		if (GetAsyncKeyState('N') & 1)
		{
			bNoRecoil = !bNoRecoil;

			NoRecoil(bNoRecoil);
			printf("NoRecoil: %s.\n", bNoRecoil ? "Enabled" : "Disabled");	

		}

		// Teleport to ADS
		if (GetAsyncKeyState(VK_LSHIFT) && GetAsyncKeyState('T') & 1)
		{
			TeleportToADS();
			printf("Teleporting...\n");
			
		}
		
		// KillAll
		if (GetAsyncKeyState(VK_LSHIFT) && GetAsyncKeyState('K') & 1)
		{
			bKillAll = !bKillAll;

			KillAll(bKillAll);
			printf("All Enemies %s.\n", bKillAll ? "Enabled" : "Disabled");
			
		}
		
	}

#ifdef f
	fclose(f);
	FreeConsole();
#endif

	FreeLibraryAndExitThread((HMODULE)lpReserved, 0);
	PlaySound(TEXT("ErrorSound"), 0, SND_ASYNC);
	return TRUE;
}

BOOL WINAPI DllMain(HINSTANCE hModule, DWORD dwReason, LPVOID lpReserved)
{
	switch (dwReason)
	{
		case DLL_PROCESS_ATTACH:
			DisableThreadLibraryCalls(hModule);
			CreateThread(NULL, 0, MainThread, hModule, 0, NULL);
			break;
		case DLL_PROCESS_DETACH:
			break;
	}

	return TRUE;
}
