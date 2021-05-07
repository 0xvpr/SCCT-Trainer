#ifndef _OFFSETS_HPP
#define _OFFSETS_HPP

namespace offsets
{
    // Static Offsets
    unsigned weapon_base             = 0xA0F434;
    unsigned entity_list_base        = 0xA0DFEC;

    unsigned invisibility_base       = 0x27F12C;
    unsigned noise_base              = 0x417E59;

    unsigned main_ammo_base          = 0x2F9E4A;
    unsigned shotgun_ammo_base       = 0x2FCFF0;
    unsigned sniper_ammo_base        = 0x2FBC58;

    // Multi Level Pointers
    unsigned weapon_offsets[3]       = { 0x84, 0x6E0, 0x434 };
    unsigned entity_list_offsets[2]  = { 0x78, 0x5E4 };

    // Length of Multi-level Pointers
    size_t weapon_offsets_size		 = sizeof(weapon_offsets) / sizeof(int);
    size_t entity_list_offsets_size	 = sizeof(entity_list_offsets) / sizeof(int);
}

#endif
