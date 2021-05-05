#ifndef _ENTITY_H
#define _ENTITY_H

struct Vec2
{
	float x, y;
};

struct Vec3
{
	float x, y, z;
};

struct Vec4
{
	float x, y, z, w;
};

struct Entity
{
	int entity_type;
	int _0xE8[57];
	float x, y, z;
	int _0x420[203];
	int health;
};

struct EntityObject
{
	struct Entity* entity;
};

struct EntityList
{
	struct EntityObject entities[71];
};

struct Door
{
    int door_type;
    char _0x4B8[0x4B4];
    int access;
};

struct DoorObject
{
    struct Door* door;
};

struct DoorList
{
    struct DoorObject doors[256];
};

struct Weapon
{
	int chamber_ammo, chamber_max_ammo, total_ammo;
	int _0x51C[60];
	float minimum_reticle, bloom_1, bloom_2;
};

#endif
