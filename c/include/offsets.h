#ifndef _OFFSETS_H
#define _OFFSETS_H

#include <stddef.h>

// Static Offsets
unsigned int offsets_entity_list_base        = 0x00A0DFEC;
unsigned int offsets_weapon_base             = 0x00A0F434;

unsigned int offsets_invisibility_base       = 0x0027F12C;
unsigned int offsets_noise_base              = 0x00417E59;
unsigned int offsets_health_base             = 0x003F07C8;
unsigned int offsets_alarm_base              = 0x0009BC61;

unsigned int offsets_main_ammo_base          = 0x002F9E4A;
unsigned int offsets_shotgun_ammo_base       = 0x002FCFF0;
unsigned int offsets_sniper_ammo_base        = 0x002FBC58;
unsigned int offsets_rapid_fire_base         = 0x00178FA2;

// Multi Level Pointers
unsigned int offsets_entity_list_pointers[2] = { 0x78, 0x5E4 };
unsigned int offsets_weapon_pointers[3]      = { 0x84, 0x6E0, 0x434 };

// Length of Multi-level Pointers
size_t offsets_entity_list_pointers_size = sizeof(offsets_entity_list_pointers) / sizeof(int);
size_t offsets_weapon_pointers_size	     = sizeof(offsets_weapon_pointers) / sizeof(int);


#endif
