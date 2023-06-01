#ifndef OFFSETS_HEADER
#define OFFSETS_HEADER

#include <stddef.h>
#include <stdint.h>

uint32_t offsets_game_world_base   = 0x00A0DFEC;
uint32_t offsets_weapon_base       = 0x00A0F434;

uint32_t offsets_invisibility_base = 0x0027F12C;
uint32_t offsets_noise_base        = 0x00417E5D;
uint32_t offsets_health_base       = 0x003F07C8;
uint32_t offsets_alarm_base        = 0x0009BC61;

uint32_t offsets_main_ammo_base    = 0x002F9E4A;
uint32_t offsets_shotgun_ammo_base = 0x002FCFF0;
uint32_t offsets_sniper_ammo_base  = 0x002FBC58;
uint32_t offsets_rapid_fire_base   = 0x00178FA2;

uint16_t offsets_game_world_pointers[2] = {
    0x78,
    0x5E4
};

/*uint16_t offsets_weapon_pointers[3] = {*/
    /*0x84,*/
    /*0x6E0,*/
    /*0x434*/
/*};*/

uintptr_t offsets_recoil_bases[6] = {
    0x2F83BE,
    0x2F8409,
    0x2F845B,
    0x2F855E,
    0x2F84D5,
    0x2F8578
};

#endif /* OFFSETS_HEADER */
