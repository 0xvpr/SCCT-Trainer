#ifndef _OFFSETS_HPP
#define _OFFSETS_HPP

namespace offsets
{
    // Static Offsets
    unsigned weapon_base             = 0x00A0F434;
    unsigned entity_list_base        = 0x00A0DFEC;

    unsigned invisibility_base       = 0x0027F12C;
    unsigned noise_base              = 0x00417E59;
    unsigned health_base             = 0x003F07C8;
    unsigned alarm_base              = 0x0009BC61;

    unsigned main_ammo_base          = 0x002F9E4A;
    unsigned shotgun_ammo_base       = 0x002FCFF0;
    unsigned sniper_ammo_base        = 0x002FBC58;
    unsigned rapid_fire_base         = 0x00178FA2;

    // Multi Level Pointers
    unsigned weapon_offsets[3]       = { 0x84, 0x6E0, 0x434 };
    unsigned entity_list_offsets[2]  = { 0x78, 0x5E4 };

    // Length of Multi-level Pointers
    size_t weapon_offsets_size		 = sizeof(weapon_offsets) / sizeof(int);
    size_t entity_list_offsets_size	 = sizeof(entity_list_offsets) / sizeof(int);
}


#endif
