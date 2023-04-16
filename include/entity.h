#ifndef _ENTITY_H
#define _ENTITY_H

#ifndef TYPE
#define TYPE(x) ((uintptr_t)x)
#endif /* TYPE */

typedef struct PlayerVtable
{
    void (* function_1)(void); // To Reverse Engineer
    void (* function_2)(void); // To Reverse Engineer
    void (* function_3)(void); // To Reverse Engineer
    void (* function_4)(void); // To Reverse Engineer
    void (* function_5)(void); // To Reverse Engineer
    void (* function_6)(void); // To Reverse Engineer
    void (* function_7)(void); // To Reverse Engineer
    void (* function_8)(void); // To Reverse Engineer
    void (* function_9)(void); // To Reverse Engineer
    void (* function_10)(void); // To Reverse Engineer
    void (* function_11)(void); // To Reverse Engineer
    void (* function_12)(void); // To Reverse Engineer
    void (__thiscall * function_13)(void *, int, int); // To Reverse Engineer
} PlayerVtable;

typedef struct Entity
{
    PlayerVtable* lpVtable;   // + 0x0000
    char _0xE8[0xE4];
    float x;                  // + 0x00E8
    float y;                  // + 0x00EC
    float z;                  // + 0x00F0
    char _0x420[0x32C];
    int health;               // + 0x0420
} Entity;

typedef struct EntityObject
{
    struct Entity* entity;
} EntityObject;

typedef struct EntityList
{
    struct EntityObject entities[99];
} EntityList;

typedef struct Door
{
    unsigned int door_type;  // + 0x0000
    char _0x4B8[0x4B4];
    int access;              // + 0x04B8
} Door;

typedef struct Weapon
{
    int current_ammo;        // + 0x0000
    int max_clip_size;       // + 0x0004
    int total_ammo;          // + 0x0008
    char _0x51C[0xF0];
    float minimum_reticle;   // + 0x051C
    float bloom_x;           // + 0x0520
    float bloom_y;           // + 0x0524
} Weapon;

#endif
