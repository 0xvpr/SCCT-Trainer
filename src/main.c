#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <windows.h>
#include <tlhelp32.h>

#include "includes.h"


#define DEBUG 1


bool bKillAll = false;
bool bNoRecoil = false;
bool bPlayDead = false;
bool bPolterGheist = false;

uint64_t previous_health = 0;


DWORD WINAPI MainThread(LPVOID lpReserved)
{
	uintptr_t module_base_addr = (uintptr_t)GetModuleHandle(NULL);
	FILE *f;
	
	// Debug Console
	if (DEBUG)
	{
		AllocConsole();
		freopen_s(&f, "CONOUT$", "w", stdout);
	}

	// Main Loop
	while (!GetAsyncKeyState(VK_END))
	{
		
		// Toggle PlayDead
		if (GetAsyncKeyState('G') & 1)
		{
			bPlayDead = !bPlayDead;

			PlayDead(bPlayDead, &previous_health);
			if (DEBUG)
			{
				printf("PlayDead: %s.\n", bPlayDead ? "Enabled" : "Disabled");
			}

		}

		// Toggle PolterGheist
		if (GetAsyncKeyState('I') & 1)
		{
			bPolterGheist = !bPolterGheist;

			Invisibilty(bPolterGheist);
			Silent(bPolterGheist);
			if (DEBUG)
			{
				printf("PolterGheist: %s.\n", bPolterGheist ? "Enabled" : "Disabled");
			}

		}

		// Toggle No Recoil
		if (GetAsyncKeyState('N') & 1)
		{
			bNoRecoil = !bNoRecoil;

			NoRecoil(bNoRecoil);
			if (DEBUG)
			{
				printf("NoRecoil: %s.\n", bNoRecoil ? "Enabled" : "Disabled");	
			}

		}

		// Teleport to ADS
		if (GetAsyncKeyState(VK_LSHIFT) && GetAsyncKeyState('T') & 1)
		{
			TeleportToADS();
			if (DEBUG)
			{
				printf("Teleporting...\n");
			}
			
		}
		
		// KillAll
		if (GetAsyncKeyState(VK_LSHIFT) && GetAsyncKeyState('K') & 1)
		{
			bKillAll = !bKillAll;

			KillAll(bKillAll);
			if (DEBUG)
			{
				printf("All Enemies %s.\n", bKillAll ? "Enabled" : "Disabled");
			}
			
		}
		
	}

	if (DEBUG)
	{
		fclose(f);
		FreeConsole();
	}

	FreeLibraryAndExitThread((HMODULE)lpReserved, 0);
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
