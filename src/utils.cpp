#include "utils.hpp"

#include <iostream>
#include <cstdlib>

void __displayMenu(const char* text)
{
    system("cls"); // slowest but simplest

    /* Simple Hack Commands */
    std::cout << "Press 'Numpad 1' to toggle GodMode\n";
    std::cout << "Press 'Numpad 2' to toggle GodGun\n";
    std::cout << "Press 'Numpad 3' to toggle Alarms\n";
    std::cout << "Press 'Numpad 4' to toggle PolterGheist\n";
    std::cout << "Press 'Numpad 5' to toggle the Afterlife\n";
    std::cout << "Press 'Numpad 6' to unlock all doors\n";
    std::cout << std::endl;

    /* Current Toggle Statuses */
    std::cout << "1 GodMode:\t\t"      << (bGodMode       ? "Enabled" : "Disabled") << "\n";
    std::cout << "2 GodGun:\t\t"       << (bGodGun        ? "Enabled" : "Disabled") << "\n";
    std::cout << "3 Disable Alarms:\t" << (bDisableAlarms ? "Enabled" : "Disabled") << "\n";
    std::cout << "4 PolterGheist:\t\t" << (bPolterGheist  ? "Enabled" : "Disabled") << "\n";
    std::cout << "5 Afterlife:\t\t"    << (bAfterlife     ? "Enabled" : "Disabled") << "\n";
    std::cout << std::endl;

    std::cout << text << "\n" << std::endl;
}
