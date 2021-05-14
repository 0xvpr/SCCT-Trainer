#ifndef _OFFSETS_HPP
#define _OFFSETS_HPP

namespace offsets
{
    // Static Offsets
    unsigned int entity_list_base       = 0x00A0DFEC;
    unsigned int weapon_base            = 0x00A0F434;

    unsigned int invisibility_base      = 0x0027F12C;
    unsigned int noise_base             = 0x00417E59;
    unsigned int health_base            = 0x003F07C8;
    unsigned int alarm_base             = 0x0009BC61;

    unsigned int main_ammo_base         = 0x002F9E4A;
    unsigned int shotgun_ammo_base      = 0x002FCFF0;
    unsigned int sniper_ammo_base       = 0x002FBC58;
    unsigned int rapid_fire_base        = 0x00178FA2;

    // Multi Level Pointers
    unsigned int entity_list_offsets[2] = { 0x78, 0x5E4 };
    unsigned int weapon_offsets[3]      = { 0x84, 0x6E0, 0x434 };

    // Length of Multi-level Pointers
    size_t entity_list_offsets_size	    = sizeof(entity_list_offsets) / sizeof(int);
    size_t weapon_offsets_size		    = sizeof(weapon_offsets) / sizeof(int);
}


#endif
