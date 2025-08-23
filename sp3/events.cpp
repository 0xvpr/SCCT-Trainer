#include "events.hpp"
#include "render.hpp"
#include "hacks.hpp"

#include <windows.h>

extern bool menu_is_max;

extern render::Resolution resolution;
extern render::Coordinates coordinates;
extern render::HackMenu hackMenu[MAX_MENU_ITEMS];

unsigned int n_entities_changed;
unsigned int total_doors_unlocked;

bool bDisableEnemies;
bool bDisableAlarms;
bool bSuperWeapons;
bool bGhostMode;
bool bShutdown;
bool bGodMode;

bool events::handle_keyboard() {
    /* Toggle GodMode */
    if (GetAsyncKeyState(VK_NUMPAD1) & 1) {
        bGodMode = !bGodMode;
        hackMenu[GOD_MODE].bEnabled = bGodMode;
        hacks::god_mode(bGodMode);
    }

    /* Toggle GhostMode */
    if (GetAsyncKeyState(VK_NUMPAD2) & 1) {
        bGhostMode = !bGhostMode;
        hackMenu[GHOST_MODE].bEnabled = bGhostMode;
        hacks::ghost_mode(bGhostMode);
    }

    /* Toggle Super Weapons */
    if (GetAsyncKeyState(VK_NUMPAD3) & 1) {
        bSuperWeapons = !bSuperWeapons;
        hackMenu[SUPER_WEAPONS].bEnabled = bSuperWeapons;
        hacks::super_weapons(bSuperWeapons);
    }

    /*  Disable All Alarms */
    if (GetAsyncKeyState(VK_NUMPAD4) & 1) {
        bDisableAlarms = !bDisableAlarms;
        hackMenu[DISABLE_ALARMS].bEnabled = bDisableAlarms;
        hacks::disable_alarms(bDisableAlarms);
    }

    /* Toggle DisableEnemies */
    if (GetAsyncKeyState(VK_NUMPAD5) & 1) {
        bDisableEnemies = !bDisableEnemies;
        hackMenu[DISABLE_ENEMIES].bEnabled = bDisableEnemies;
        n_entities_changed = hacks::disable_enemies(bDisableEnemies);
    }

    /* Unlock All Doors */
    if (GetAsyncKeyState(VK_NUMPAD6) & 1) {
        hackMenu[UNLOCK_ALL_DOORS].bEnabled = !hackMenu[UNLOCK_ALL_DOORS].bEnabled;
        total_doors_unlocked = hacks::unlock_all_doors();
    }

    // Control Menu Position
    if (menu_is_max) {
        if (GetAsyncKeyState(VK_LEFT) & 0x8000) {
            if (coordinates.x > 35) {
                coordinates.x -= 5;
            }
        }

        if (GetAsyncKeyState(VK_RIGHT) & 0x8000) {
            if (coordinates.x < resolution.x - 175) {
                coordinates.x += 5;
            }
        }

        if (GetAsyncKeyState(VK_UP) & 0x8000) {
            if (coordinates.y > 30) {
                coordinates.y -= 5;
            }
        }

        if (GetAsyncKeyState(VK_DOWN) & 0x8000) {
            if (coordinates.y < resolution.y - 120) {
                coordinates.y += 5;
            }
        }

    }

    if (menu_is_max && (GetAsyncKeyState(VK_F3) & 1) > 0) {
        coordinates.x = 30;
        coordinates.y = 25;
    }

    if (GetAsyncKeyState(VK_F2) & 1) {
        menu_is_max = !menu_is_max;
    }

    if (GetAsyncKeyState(VK_HOME)) {
        return true;
    }

    return false;
}
