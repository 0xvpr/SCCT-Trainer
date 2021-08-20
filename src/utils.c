#include "utils.h"
#include "hacks.h"

void DeactivateMenu(void)
{
    hack_GodMode(false);
    hack_GhostMode(false);
    hack_SuperWeapons(false);
    hack_DisableAlarms(false);
    hack_DisableEnemies(false);
}
