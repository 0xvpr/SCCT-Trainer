#ifndef ENGINE_HEADER
#define ENGINE_HEADER


#include <cstddef>
#include <cstdint>
#include <cmath>


namespace engine {

namespace object_tag {

constexpr std::uintptr_t player = 0x110E8B50;
constexpr std::uintptr_t door   = 0x110FDDD8;
constexpr std::uintptr_t npc    = 0x110F88D8;

} // namespace tag

struct player_vtable {
    virtual void function_1(); // TODO 
};

struct enemy_vtable {
    virtual void function_1(); // TODO 
};

struct door_vtable {
    virtual void function_1(); // TODO
};

struct enemy_t : public enemy_vtable {
//  player_vtable vtable;               // + 0x0000
    std::uint8_t  padding_0xE4[0xE4];   // + 0x00E4
    std::float_t  x;                    // + 0x00E8
    std::float_t  y;                    // + 0x00EC
    std::float_t  z;                    // + 0x00F0
    std::uint8_t  padding_0x420[0x32C]; // + 0x041C
    std::int32_t  health;               // + 0x0420
};

struct object_t {
    std::uintptr_t object_tag;          // + 0x0000
};

struct game_world_t {
    object_t**    entity_list_ptr;      // + 0x0000
    std::size_t   entity_list_size;     // + 0x0004
};

struct door_t : door_vtable {
//  door_vtable door_type;              // + 0x0000
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

template <std::size_t alignment = std::alignment_of<void (*)()>::value>
inline std::uintptr_t tag_if_aligned(uintptr_t addr) noexcept {
    return addr & (-( !(addr & (alignment-1)) ));
}

} // namespace engine

#endif // ENGINE_HEADER
