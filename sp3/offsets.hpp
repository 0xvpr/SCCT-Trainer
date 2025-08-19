#ifndef OFFSETS_HEADER
#define OFFSETS_HEADER

#include <cstdint>

namespace offsets {

constexpr uint32_t entity_list_base  = 0x00A0DFEC;
constexpr uint32_t weapon_base       = 0x00A0F434;

constexpr uint32_t invisibility_base = 0x0027F12C;
constexpr uint32_t noise_base        = 0x00417E5D;
constexpr uint32_t health_base       = 0x003F07C8;
constexpr uint32_t alarm_base        = 0x0009BC61;

constexpr uint32_t main_ammo_base    = 0x002F9E4A;
constexpr uint32_t shotgun_ammo_base = 0x002FCFF0;
constexpr uint32_t sniper_ammo_base  = 0x002FBC58;
constexpr uint32_t rapid_fire_base   = 0x00178FA2;

constexpr uint16_t entity_list_pointers[2] = { 0x78, 0x5E4 };
constexpr uint16_t weapon_pointers[3]      = { 0x84, 0x6E0, 0x434 };

constexpr size_t   entity_list_pointers_size   = sizeof(entity_list_pointers)/sizeof(entity_list_pointers[0]);
constexpr size_t   weapon_pointers_size = sizeof(weapon_pointers)/sizeof(weapon_pointers[0]);

} // namespace offsets;

#endif
