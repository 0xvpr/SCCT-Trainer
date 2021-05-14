#include "utils.h"
#include "hacks.h"

#include <stdio.h>
#include <stdlib.h>

void utils_DisplayMenu(const char* text)
{
    system("cls"); // slowest but simplest

    /* Simple display */
    printf("Press 'Numpad 1' to toggle God Mode.\n");
    printf("Press 'Numpad 2' to toggle GhostMode.\n");
    printf("Press 'Numpad 3' to toggle Super Weapons.\n");
    printf("Press 'Numpad 4' to toggle Alarms.\n");
    printf("Press 'Numpad 5' to toggle Enemies.\n");
    printf("Press 'Numpad 6' to unlock all doors.\n");
    printf("\n");

    /* Current toggle statuses */
    printf("1 -- God Mode:\t\t%s\n",      (bGodMode        ? "Enabled" : "Disabled"));
    printf("2 -- Ghost Mode:\t%s\n",      (bGhostMode      ? "Enabled" : "Disabled"));
    printf("3 -- Super Weapons:\t%s\n",   (bSuperWeapons   ? "Enabled" : "Disabled"));
    printf("4 -- Disable Alarms:\t%s\n",  (bDisableAlarms  ? "Enabled" : "Disabled"));
    printf("5 -- Disable Enemies:\t%s\n", (bDisableEnemies ? "Enabled" : "Disabled"));
    printf("6 -- Doors Unlocked:\t%d\n",  total_doors_unlocked);
    printf("\n");

    printf("%s\n", text);
}

void utils_Deactivate(void)
{
    system("cls");

    printf("Deactivating all cheats\n\n");

    hacks_GodMode(false);
    hacks_GhostMode(false);
    hacks_SuperWeapons(false);
    hacks_DisableAlarms(false);
    hacks_DisableEnemies(false);
}
