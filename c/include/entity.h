#ifndef _ENTITY_H
#define _ENTITY_H

typedef struct Entity
{
    unsigned int entity_type; // 0x00
    char _0xE8[0xE4];
    float x;                  // 0xE8
    float y;                  // 0xEC
    float z;                  // 0xF0
    char _0x420[0x326];
    int health;               // 0x420
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
    unsigned int door_type;  // 0x00
    char _0x4B8[0x4B4];
    int access;              // 0x4B8
} Door;

typedef struct Weapon
{
    int current_ammo;        // 0x434
    int max_clip_size;       // 0x438
    int total_ammo;          // 0x43C
    char _0x51C[0xE8];
    float minimum_reticle;   // 0x51C
    float bloom_x;           // 0x520
    float bloom_y;           // 0x524
} Weapon;


#endif
