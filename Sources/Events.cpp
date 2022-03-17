#include <windows.h>
#include "Events.hpp"
#include "Render.hpp"

using render::Resolution;
using render::Coordinates;
using render::HackMenu;

extern Resolution resolution;
extern Coordinates coordinates;
extern HackMenu hackMenu;

static constexpr uint16_t key_registered = 1 <<  0;
static constexpr uint16_t key_held       = 1 << 15;

bool events::HandleKeyboard()
{
    /* Toggle GodMode */
    if (GetAsyncKeyState(VK_NUMPAD1) & key_registered) {
        hacks::GodMode(hackMenu[GOD_MODE]);
    }

    /* Toggle GhostMode */
    if (GetAsyncKeyState(VK_NUMPAD2) & key_registered) {
        hacks::GhostMode(hackMenu[GHOST_MODE]);
    }

    /* Toggle Super Weapons */
    if (GetAsyncKeyState(VK_NUMPAD3) & key_registered) {
        hacks::SuperWeapons(hackMenu[SUPER_WEAPONS]);
    }

    /*  Disable All Alarms */
    if (GetAsyncKeyState(VK_NUMPAD4) & key_registered) {
        hacks::DisableAlarms(hackMenu[DISABLE_ALARMS]);
    }

    /* Toggle DisableEnemies */
    if (GetAsyncKeyState(VK_NUMPAD5) & key_registered) {
        (void)hacks::DisableEnemies(hackMenu[DISABLE_ENEMIES]);
    }

    /* Unlock All Doors */
    if (GetAsyncKeyState(VK_NUMPAD6) & key_registered) {
        (void)hacks::UnlockAllDoors(hackMenu[UNLOCK_ALL_DOORS]);
    }

    // Control Menu Position
    if (hackMenu.IsMaximized()) // When maximized
    {
        if (GetAsyncKeyState(VK_LEFT) & key_held)
        {
            if (coordinates.x > 35)
            {
                coordinates.x -= 5;
            }
        }

        if (GetAsyncKeyState(VK_RIGHT) & key_held)
        {
            if (coordinates.x < resolution.x - 175)
            {
                coordinates.x += 5;
            }
        }

        if (GetAsyncKeyState(VK_UP) & key_held)
        {
            if (coordinates.y > 30)
            {
                coordinates.y -= 5;
            }
        }

        if (GetAsyncKeyState(VK_DOWN) & key_held)
        {
            if (coordinates.y < resolution.y - 120)
            {
                coordinates.y += 5;
            }
        }

    }

    if (hackMenu.IsMaximized() && (GetAsyncKeyState(VK_F3) & key_registered) > 0)
    {
        coordinates.x = 30;
        coordinates.y = 25;
    }

    if (GetAsyncKeyState(VK_F2) & key_registered)
    {
        hackMenu();
    }

    if (GetAsyncKeyState(VK_END))
    {
        return true;
    }

    return false;
}
