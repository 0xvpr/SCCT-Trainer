#include "utils.hpp"

#include <iostream>
#include <cstdlib>

void __displayMenu(const char* text)
{
    system("cls"); // slowest but simplest

    /* Simple Hack Commands */
    std::cout << "Press 'Numpad 1' to toggle Unlimited Health\n";
    std::cout << "Press 'Numpad 2' to toggle Unlimited Ammo\n";
    std::cout << "Press 'Numpad 3' to toggle No Recoil\n";
    std::cout << "Press 'Numpad 4' to toggle PolterGheist\n";
    std::cout << "Press 'Numpad 5' to toggle the Afterlife\n";
    std::cout << "Press 'Numpad 6' to unlock all doors\n";
    std::cout << std::endl;

    /* Current Toggle Statuses */
    std::cout << "Unlimited Health: " << (bUnlimitedHealth ? "Enabled" : "Disabled") << "\n";
    std::cout << "Unlimited Ammo: "   << (bUnlimitedAmmo   ? "Enabled" : "Disabled") << "\n";
    std::cout << "No Recoil: "        << (bNoRecoil        ? "Enabled" : "Disabled") << "\n";
    std::cout << "PolterGheist: "     << (bPolterGheist    ? "Enabled" : "Disabled") << "\n";
    std::cout << "Afterlife: "        << (bAfterlife       ? "Enabled" : "Disabled") << "\n";
    std::cout << std::endl;

    std::cout << text;
}
