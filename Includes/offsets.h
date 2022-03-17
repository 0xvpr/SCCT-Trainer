#ifndef _OFFSETS_H
#define _OFFSETS_H

#include <stddef.h>
#include <stdint.h>

uint32_t offsets_entity_list_base  = 0x00A0DFEC;
uint32_t offsets_weapon_base       = 0x00A0F434;

uint32_t offsets_invisibility_base = 0x0027F12C;
uint32_t offsets_noise_base        = 0x00417E5D;
uint32_t offsets_health_base       = 0x003F07C8;
uint32_t offsets_alarm_base        = 0x0009BC61;

uint32_t offsets_main_ammo_base    = 0x002F9E4A;
uint32_t offsets_shotgun_ammo_base = 0x002FCFF0;
uint32_t offsets_sniper_ammo_base  = 0x002FBC58;
uint32_t offsets_rapid_fire_base   = 0x00178FA2;

uint16_t offsets_entity_list_pointers[2] = { 0x78, 0x5E4 };
uint16_t offsets_weapon_pointers[3]      = { 0x84, 0x6E0, 0x434 };

size_t offsets_entity_list_pointers_size = 2;
size_t offset_weapon_pointers_size = 3;

#endif
