#include "utils.hpp"
#include "hacks.hpp"

#include <iostream>
#include <cstdlib>

void __displayMenu(const char* text)
{
    system("cls"); // slowest but simplest

    /* Simple Hack Commands */
    std::cout << "Press 'Numpad 1' to toggle God Mode.\n";
    std::cout << "Press 'Numpad 2' to toggle GhostMode.\n";
    std::cout << "Press 'Numpad 3' to toggle Super Weapons.\n";
    std::cout << "Press 'Numpad 4' to toggle Alarms.\n";
    std::cout << "Press 'Numpad 5' to toggle Enemies.\n";
    std::cout << "Press 'Numpad 6' to unlock all doors.\n";
    std::cout << std::endl;

    /* Current Toggle Statuses */
    std::cout << "1 -- God Mode:\t\t"      << (bGodMode        ? "Enabled" : "Disabled") << "\n";
    std::cout << "2 -- Ghost Mode:\t"      << (bSuperWeapons   ? "Enabled" : "Disabled") << "\n";
    std::cout << "3 -- Super Weapons:\t"   << (bDisableAlarms  ? "Enabled" : "Disabled") << "\n";
    std::cout << "4 -- Disable Alarms:\t"  << (bGhostMode      ? "Enabled" : "Disabled") << "\n";
    std::cout << "5 -- Disable Enemies:\t" << (bDisableEnemies ? "Enabled" : "Disabled") << "\n";
    std::cout << "6 -- Doors Unlocked:\t"  << total_doors_unlocked << "\n";
    std::cout << std::endl;

    std::cout << text << std::endl;
}

void __deactivate(void)
{
    system("cls");

    std::cout << "Deactivating all cheats\n" << std::endl;

    Hacks::GodMode(false);
    Hacks::GhostMode(false);
    Hacks::SuperWeapons(false);
    Hacks::DisableAlarms(false);
    Hacks::DisableEnemies(false);
}
