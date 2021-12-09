#include <windows.h>
#include "events.h"
#include "render.h"


extern uintptr_t module_base_addr;

extern unsigned int n_entities_changed;
extern unsigned int total_doors_unlocked;

extern bool bDisableEnemies;
extern bool bDisableAlarms;
extern bool bSuperWeapons;
extern bool bMaximizeMenu;
extern bool bGhostMode;
extern bool bShutdown;
extern bool bGodMode;

extern Resolution resolution;
extern Coordinates coordinates;
extern HackMenu hackMenu[MAX_MENU_ITEMS];

bool events_HandleKeyboard(void)
{
    /* Toggle GodMode */
    if (GetAsyncKeyState(VK_NUMPAD1) & 1)
    {
        bGodMode = !bGodMode;
        hackMenu[GOD_MODE].bEnabled = bGodMode;
        hack_GodMode(bGodMode);
    }

    /* Toggle GhostMode */
    if (GetAsyncKeyState(VK_NUMPAD2) & 1)
    {
        bGhostMode = !bGhostMode;
        hackMenu[GHOST_MODE].bEnabled = bGhostMode;
        hack_GhostMode(bGhostMode);
    }

    /* Toggle Super Weapons */
    if (GetAsyncKeyState(VK_NUMPAD3) & 1)
    {
        bSuperWeapons = !bSuperWeapons;
        hackMenu[SUPER_WEAPONS].bEnabled = bSuperWeapons;
        hack_SuperWeapons(bSuperWeapons);
    }

    /*  Disable All Alarms */
    if (GetAsyncKeyState(VK_NUMPAD4) & 1)
    {
        bDisableAlarms = !bDisableAlarms;
        hackMenu[DISABLE_ALARMS].bEnabled = bDisableAlarms;
        hack_DisableAlarms(bDisableAlarms);
    }

    /* Toggle DisableEnemies */
    if (GetAsyncKeyState(VK_NUMPAD5) & 1)
    {
        bDisableEnemies = !bDisableEnemies;
        hackMenu[DISABLE_ENEMIES].bEnabled = bDisableEnemies;
        n_entities_changed = hack_DisableEnemies(bDisableEnemies);
    }

    /* Unlock All Doors */
    if (GetAsyncKeyState(VK_NUMPAD6) & 1)
    {
        hackMenu[UNLOCK_ALL_DOORS].bEnabled = !hackMenu[UNLOCK_ALL_DOORS].bEnabled;
        total_doors_unlocked = hack_UnlockAllDoors();
    }

    // Control Menu Position
    if (bMaximizeMenu) // When maximized
    {
        if (GetAsyncKeyState(VK_LEFT) & 0x8000)
        {
            if (coordinates.x > 35)
            {
                coordinates.x -= 5;
            }
        }

        if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
        {
            if (coordinates.x < resolution.x - 175)
            {
                coordinates.x += 5;
            }
        }

        if (GetAsyncKeyState(VK_UP) & 0x8000)
        {
            if (coordinates.y > 30)
            {
                coordinates.y -= 5;
            }
        }

        if (GetAsyncKeyState(VK_DOWN) & 0x8000)
        {
            if (coordinates.y < resolution.y - 120)
            {
                coordinates.y += 5;
            }
        }

    }

    if(bMaximizeMenu && (GetAsyncKeyState(VK_F3) & 1) > 0)
    {
        coordinates.x = 30;
        coordinates.y = 25;
    }

    if(GetAsyncKeyState(VK_F2) & 1)
    {
        bMaximizeMenu = !bMaximizeMenu;
    }

    return false;
}
