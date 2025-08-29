#ifndef OFFSETS_HEADER
#define OFFSETS_HEADER

#include <cstdint>
#include <array>

namespace offsets {

constexpr std::uint32_t game_world_base   = 0xA0DFEC;
constexpr std::uint32_t weapon_base       = 0xA0F434;

constexpr std::uint32_t invisibility_base = 0x27F12C;
constexpr std::uint32_t noise_base        = 0x417E5D;
constexpr std::uint32_t health_base       = 0x3F07C8;
constexpr std::uint32_t alarm_base        = 0x09BC61;

constexpr std::uint32_t main_ammo_base    = 0x2F9E4A;
constexpr std::uint32_t shotgun_ammo_base = 0x2FCFF0;
constexpr std::uint32_t sniper_ammo_base  = 0x2FBC58;
constexpr std::uint32_t rapid_fire_base   = 0x178FA2;

constexpr std::array<std::uint16_t,  2> game_world_pointers = {
    0x78, 0x5E4
};
constexpr std::array<std::uint16_t,  3> weapon_pointers = {
    0x84, 0x6E0, 0x434
};
constexpr std::array<std::uintptr_t, 6> recoil_op_offsets = {
    0x2F83BE,
    0x2F8409,
    0x2F845B,
    0x2F855E,
    0x2F84D5,
    0x2F8578
};

} // namespace offsets;

#endif // OFFSETS_HEADER
