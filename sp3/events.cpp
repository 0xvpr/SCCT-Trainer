#include "events.hpp"
#include "render.hpp"
#include "hacks.hpp"

#include <windows.h>

using key_t = enum : std::uint16_t  {
    key_pressed = 0x0001,
    key_held    = 0x8000
};

extern bool menu_is_max;

extern render::Resolution resolution;
extern render::Coordinates coordinates;
extern render::HackMenu hackMenu[MAX_MENU_ITEMS];

std::uint32_t n_entities_changed;
std::uint32_t total_doors_unlocked;

bool bDisableEnemies;
bool bDisableAlarms;
bool bSuperWeapons;
bool bGhostMode;
bool bShutdown;
bool bGodMode;

bool events::handle_keyboard() {

    /* Toggle GodMode */
    if (GetAsyncKeyState(VK_NUMPAD1) & key_t::key_pressed) {
        bGodMode = !bGodMode;
        hackMenu[GOD_MODE].bEnabled = bGodMode;
        hacks::god_mode(bGodMode);
    }

    /* Toggle GhostMode */
    if (GetAsyncKeyState(VK_NUMPAD2) & key_t::key_pressed) {
        bGhostMode = !bGhostMode;
        hackMenu[GHOST_MODE].bEnabled = bGhostMode;
        hacks::ghost_mode(bGhostMode);
    }

    /* Toggle Super Weapons */
    if (GetAsyncKeyState(VK_NUMPAD3) & key_t::key_pressed) {
        bSuperWeapons = !bSuperWeapons;
        hackMenu[SUPER_WEAPONS].bEnabled = bSuperWeapons;
        hacks::super_weapons(bSuperWeapons);
    }

    /*  Disable All Alarms */
    if (GetAsyncKeyState(VK_NUMPAD4) & key_t::key_pressed) {
        bDisableAlarms = !bDisableAlarms;
        hackMenu[DISABLE_ALARMS].bEnabled = bDisableAlarms;
        hacks::disable_alarms(bDisableAlarms);
    }

    /* Toggle DisableEnemies */
    if (GetAsyncKeyState(VK_NUMPAD5) & key_t::key_pressed) {
        bDisableEnemies = !bDisableEnemies;
        hackMenu[DISABLE_ENEMIES].bEnabled = bDisableEnemies;
        n_entities_changed = hacks::disable_enemies(bDisableEnemies);
    }

    /* Unlock All Doors */
    if (GetAsyncKeyState(VK_NUMPAD6) & key_t::key_pressed) {
        hackMenu[UNLOCK_ALL_DOORS].bEnabled = !hackMenu[UNLOCK_ALL_DOORS].bEnabled;
        total_doors_unlocked = hacks::unlock_all_doors();
    }

    // Control Menu Position
    if (menu_is_max) {
        if (GetAsyncKeyState(VK_LEFT) & key_t::key_held) {
            if (coordinates.x > 35) {
                coordinates.x -= 5;
            }
        }

        if (GetAsyncKeyState(VK_RIGHT) & key_t::key_held) {
            if (coordinates.x < resolution.x - 175) {
                coordinates.x += 5;
            }
        }

        if (GetAsyncKeyState(VK_UP) & key_t::key_held) {
            if (coordinates.y > 30) {
                coordinates.y -= 5;
            }
        }

        if (GetAsyncKeyState(VK_DOWN) & key_t::key_held) {
            if (coordinates.y < resolution.y - 120) {
                coordinates.y += 5;
            }
        }

    }

    if (menu_is_max && (GetAsyncKeyState(VK_F3) & key_t::key_pressed) > 0) {
        coordinates.x = 30;
        coordinates.y = 25;
    }

    if (GetAsyncKeyState(VK_F2) & key_t::key_pressed) {
        menu_is_max = !menu_is_max;
    }

    if (GetAsyncKeyState(VK_HOME)) {
        return true;
    }

    return false;
}
