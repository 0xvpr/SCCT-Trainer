#ifndef _OFFSETS_H
#define _OFFSETS_H

#include <stddef.h>

unsigned offsets_entity_list_base  = 0x00A0DFEC;
unsigned offsets_weapon_base       = 0x00A0F434;

unsigned offsets_invisibility_base = 0x0027F12C;
unsigned offsets_noise_base        = 0x00417E59;
unsigned offsets_health_base       = 0x003F07C8;
unsigned offsets_alarm_base        = 0x0009BC61;

unsigned offsets_main_ammo_base    = 0x002F9E4A;
unsigned offsets_shotgun_ammo_base = 0x002FCFF0;
unsigned offsets_sniper_ammo_base  = 0x002FBC58;
unsigned offsets_rapid_fire_base   = 0x00178FA2;

unsigned offsets_entity_list_pointers[2] = { 0x78, 0x5E4 };
unsigned offsets_weapon_pointers[3]      = { 0x84, 0x6E0, 0x434 };

size_t offsets_entity_list_pointers_size = 2;
size_t offset_weapon_pointers_size = 3;

#endif
