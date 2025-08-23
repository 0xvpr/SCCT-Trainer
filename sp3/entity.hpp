#ifndef ENTITY_HEADER
#define ENTITY_HEADER

#include <cstddef>

struct PlayerVtable {
    void (* function_1)(void); // TODO 
};

struct Entity {
    void* lpVtable;           // + 0x0000
    char  _0xE8[0xE4];
    float x;                  // + 0x00E8
    float y;                  // + 0x00EC
    float z;                  // + 0x00F0
    char  _0x420[0x32C];
    int   health;             // + 0x0420
};

struct EntityObject {
    Entity* entity;
};

struct EntityList {
    EntityObject* entities;
};

struct GameWorld {
    EntityList* entity_list_ptr;
    std::size_t entity_list_size;
};

struct Door {
    unsigned int door_type;     // + 0x0000
    char         _0x4B8[0x4B4];
    int          access;        // + 0x04B8
};

struct Weapon {
    int   current_ammo;      // + 0x0000
    int   max_clip_size;     // + 0x0004
    int   total_ammo;        // + 0x0008
    char  _0x51C[0xF0];
    float minimum_reticle;   // + 0x051C
    float bloom_x;           // + 0x0520
    float bloom_y;           // + 0x0524
};

#endif // ENTITY_HEADER
