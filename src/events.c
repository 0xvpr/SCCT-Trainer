#include "events.h"

#include "hacks.h"
#include "render.h"

#include <windows.h>

extern uintptr_t module_base_addr;

extern int g_maximized;

extern Resolution g_resolution;
extern Coordinates g_coordinates;
extern HackMenu g_hack_menu[MAX_MENU_ITEMS];

int events_handle_keyboard(void)
{
    /*[> Toggle GodMode <]*/
    if (GetAsyncKeyState(VK_NUMPAD1) & 1)
    {
        g_hack_menu[GOD_MODE].bEnabled = !g_hack_menu[GOD_MODE].bEnabled;
        hack_god_mode(g_hack_menu[GOD_MODE].bEnabled);
    }

    /*[> Toggle GhostMode <]*/
    if (GetAsyncKeyState(VK_NUMPAD2) & 1)
    {
        g_hack_menu[GHOST_MODE].bEnabled = !g_hack_menu[GHOST_MODE].bEnabled;
        hack_ghost_mode(g_hack_menu[GHOST_MODE].bEnabled);
    }

    /*[> Toggle Super Weapons <]*/
    if (GetAsyncKeyState(VK_NUMPAD3) & 1)
    {
        g_hack_menu[SUPER_WEAPONS].bEnabled = !g_hack_menu[SUPER_WEAPONS].bEnabled;
        hack_super_weapons(g_hack_menu[SUPER_WEAPONS].bEnabled);
    }

    /*[>  Disable All Alarms <]*/
    if (GetAsyncKeyState(VK_NUMPAD4) & 1)
    {
        g_hack_menu[DISABLE_ALARMS].bEnabled = !g_hack_menu[DISABLE_ALARMS].bEnabled;
        hack_disable_alarms(g_hack_menu[DISABLE_ALARMS].bEnabled);
    }

    /*[> Toggle DisableEnemies <]*/
    if (GetAsyncKeyState(VK_NUMPAD5) & 1)
    {
        g_hack_menu[DISABLE_ENEMIES].bEnabled = !g_hack_menu[DISABLE_ENEMIES].bEnabled;
        /*[>n_entities_changed = <]*/
        hack_disable_enemies(g_hack_menu[DISABLE_ENEMIES].bEnabled);
    }

    /*[> Unlock All Doors <]*/
    if (GetAsyncKeyState(VK_NUMPAD6) & 1)
    {
        //g_hack_menu[UNLOCK_ALL_DOORS].bEnabled = !g_hack_menu[UNLOCK_ALL_DOORS].bEnabled;
        /*[>total_doors_unlocked = <]*/
        hack_unlock_all_doors();
    }

    /*[> Unlock All Doors <]*/
    if (GetAsyncKeyState(VK_NUMPAD7) & 1)
    {
        hack_test();
    }

    // Control Menu Position
    if (g_maximized) // When maximized
    {
        if ((GetAsyncKeyState(VK_LEFT) & 1) > 0)
        {
            if (g_coordinates.x > 35)
            {
                g_coordinates.x -= 5;
            }
        }

        if ((GetAsyncKeyState(VK_RIGHT) & 1) > 0)
        {
            if (g_coordinates.x < g_resolution.x - 175)
            {
                g_coordinates.x += 5;
            }
        }

        if ((GetAsyncKeyState(VK_UP) & 1) > 0)
        {
            if (g_coordinates.y > 30)
            {
                g_coordinates.y -= 5;
            }
        }

        if ((GetAsyncKeyState(VK_DOWN) & 1) > 0)
        {
            if (g_coordinates.y < g_resolution.y - 120)
            {
                g_coordinates.y += 5;
            }
        }

    }

    if (g_maximized && (GetAsyncKeyState(VK_F3) & 1) > 0)
    {
        g_coordinates.x = 30;
        g_coordinates.y = 25;
    }

    if (GetAsyncKeyState(VK_F2) & 1)
    {
        g_maximized = !g_maximized;
    }

    if (GetAsyncKeyState(VK_HOME))
    {
        hack_god_mode(0);
        hack_ghost_mode(0);
        hack_super_weapons(0);
        hack_disable_alarms(0);
        hack_disable_enemies(0);

        return 1;
    }

    return 0;
}
