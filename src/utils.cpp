#include "utils.hpp"

#include <iostream>
#include <cstdlib>

void __displayMenu(void)
{
    system("cls"); // slowest but simplest

    /* Simple Hack Commands */
    std::cout << "Press 'N' to toggle No Recoil.\n"
                 "Press 'U' to unlock all doors.\n"
				 "Press 'I' to toggle PolterGheist.\n"
				 "Press 'Shift' + 'K' to toggle the Afterlife.\n"
				 "Press 'Shift' + 'T' to teleport to crosshair.\n\n";

    /* Current Toggle Statuses */
    std::cout << "PolterGheist: " << (bPolterGheist ? "Enabled" : "Disabled") << "\n";
    std::cout << "Afterlife: "    << (bAfterlife    ? "Enabled" : "Disabled") << "\n";
    std::cout << "NoRecoil: "     << (bNoRecoil     ? "Enabled" : "Disabled") << "\n" << std::endl;
}
