#ifndef ENGINE_HEADER
#define ENGINE_HEADER

#include <cstddef>
#include <cstdint>
#include <cmath>

namespace engine {

struct PlayerVtable {
    void (* function_1)(void); // TODO 
};

struct enemy_t {
    PlayerVtable  vtable;               // + 0x0000
    std::uint8_t  padding_0xE4[0xE4];   // + 0x00E4
    std::float_t  x;                    // + 0x00E8
    std::float_t  y;                    // + 0x00EC
    std::float_t  z;                    // + 0x00F0
    std::uint8_t  padding_0x420[0x32C]; // + 0x041C
    std::int32_t  health;               // + 0x0420
};

struct entity_t {
    std::uintptr_t type;                // + 0x0000
};

struct game_world_t {
    entity_t**    entity_list_ptr;      // + 0x0000
    std::size_t   entity_list_size;     // + 0x0004
};

struct door_t {
    std::uint32_t door_type;            // + 0x0000
    std::uint8_t  padding_0x4B4[0x4B4]; // + 0x04B4
    std::int32_t  access;               // + 0x04B8
};

struct weapon_t {
    std::int32_t  current_ammo;         // + 0x0000
    std::int32_t  max_clip_size;        // + 0x0004
    std::int32_t  total_ammo;           // + 0x0008
//  std::uint8_t  padding_0x51C[0xF0];
    std::uint8_t  padding_0xF0[0xF0];   // + 0x00F0
    std::float_t  minimum_reticle;      // + 0x00FC
    std::float_t  bloom_x;              // + 0x00F0
    std::float_t  bloom_y;              // + 0x00F4
};

} // namespace engine

#endif // ENGINE_HEADER
