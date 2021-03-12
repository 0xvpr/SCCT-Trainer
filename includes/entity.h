#ifndef ENTITY_H_
#define ENTITY_H_

#include <stdint.h>

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
	uint32_t entity_type;
	int _0xE8[57];
	float x, y, z;
	int _0x420[203];
	uint64_t health;
};

struct EntityObject
{
	struct Entity* entity;
};

struct EntityList
{
	struct EntityObject entities[71];
};

struct Weapon
{
	int chamber_ammo, chamber_max_ammo, total_ammo;
	int _0x51C[60];
	float minimum_reticle, bloom_1, bloom_2;
};

#endif
