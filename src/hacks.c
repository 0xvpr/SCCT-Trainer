#include <stdint.h>

#include "offsets.h"
#include "entity.h"
#include "hacks.h"
#include "mem.h"

#define GUERRILLA	0x110F88D8
#define PLAYER		0x110E8B50
#define ever ;;


/**
 * Reduces the All enemies' health to zero without killing them.
 * Enemies will neither sound alarms nor actively try to kill the 
 * player.
 *
 * WARNING: this WILL break the game's state triggering mechanics
 * and prevent the player from completing the mission.
 * 
 * @param bool
 * @return void
 */
void KillAll(bool bKillAll)
{
	uintptr_t module_base_addr = (uintptr_t)GetModuleHandle(NULL);
	struct EntityList* _entity_list = *(struct EntityList**)FindDMAAddress_attached(module_base_addr + 0xA0DFEC, entity_list_offsets, entity_list_offsets_size);

	uint32_t entity_type;
	int current_entity = 0;
	for (ever)
	{
		struct Entity* entity= _entity_list->entities[current_entity].entity;
		if (entity->entity_type == PLAYER)
		{
			break;
		}
		if (entity->entity_type == GUERRILLA)
		{
			if (bKillAll)
			{
				entity->health = 0;
			}
			else
			{
				entity->health = 150;
			}
		}

		current_entity++;
	}

}

/**
 * Reduces the player's health to zero without killing the player.
 * Enemies will neither sound alarms nor actively try to kill 
 * the player.
 * 
 * @param bool, int64_t*
 * @return void
 */
void PlayDead(bool bPlayDead, uint64_t* previous_health)
{
	uintptr_t module_base_addr = (uintptr_t)GetModuleHandle(NULL);
	struct Entity* player = *(struct Entity**)FindDMAAddress_attached(module_base_addr + 0xA0F424, player_hp_offsets, player_hp_offsets_size);

	if (bPlayDead)
	{
		*previous_health = player->health;
		player->health = 0;
	}
	else
	{
		player->health = *previous_health;
	}
}

/**
 * Teleports player to coordinates that the weapon
 * crosshair was last pointing to.
 * 
 * @param none
 * @return void
 */
void TeleportToADS(void)
{
	uintptr_t module_base_addr = (uintptr_t)GetModuleHandle(NULL);

	struct EntityList* _entity_list = *(struct EntityList**)FindDMAAddress_attached(module_base_addr + 0xA0DFEC, entity_list_offsets, entity_list_offsets_size);
	struct Vec3* _ads_cam = (struct Vec3*)FindDMAAddress_attached(module_base_addr + 0x8FA4E8, cam_offsets, cam_offsets_size);

	uint32_t entity_type;
	int current_entity = 0;
	for (ever)
	{
		entity_type = _entity_list->entities[current_entity].entity->entity_type;
		if (entity_type == PLAYER)
		{
			_entity_list->entities[current_entity].entity->x = _ads_cam->x + 40;
			_entity_list->entities[current_entity].entity->y = _ads_cam->y + 10;
			_entity_list->entities[current_entity].entity->z = _ads_cam->z + 100;

			break;
		}

		current_entity++;
	}
}

/**
 * Makes the player's visibility meter never rise above 1.
 * What it does not do is make the player invisible to lasers,
 * cameras, motion sensors, and the like.
 * 
 * @param bool
 * @return void
 */
void Invisibilty(bool bPolterGheist)
{
	uintptr_t module_base_addr = (uintptr_t)GetModuleHandle(NULL);
	char* visibility_op = (LPVOID)(module_base_addr + 0x27F12C);

	char* original = "\x8B\x86\x18\x15\x00\x00";
	char* patch	   = "\xB8\xAC\xC5\x27\x37\x90";
	size_t size    = 6;

	if (bPolterGheist)
	{
		Patch(visibility_op, patch, size);
	}
	else
	{
		Patch(visibility_op, original, size);
	}

}

/**
 * Makes the player's sound meter never rise above 1.
 * 
 * WARNING: if the player moves in zero threshold
 * environments, enemies WILL still be able to hear
 * the player and trace their location.
 * 
 * @param bool
 * @return void
 */
void Silent(bool bPolterGheist)
{
	uintptr_t module_base_addr = (uintptr_t)GetModuleHandle(NULL);
	char* noise_op = (LPVOID)(module_base_addr + 0x417E4F);

	char* original = "\xD9\x9E\x3C\x04\x00\x00";
	char* patch	   = "\x90\x90\x90\x90\x90\x90";
	size_t size    = 6;

	if (bPolterGheist)
	{
		Patch(noise_op, patch, size);
	}
	else
	{
		Patch(noise_op, original, size);
	}

}

/**
 * Zero's the weapon's aiming reticle and disables spread
 * 
 * @param bool
 * @return void
 */
void NoRecoil(bool bNoRecoil)
{
	uintptr_t module_base_addr = (uintptr_t)GetModuleHandle(NULL);
	struct Weapon* weapon = (LPVOID)FindDMAAddress_attached(module_base_addr + 0xA0F434, weapon_offsets, weapon_offsets_size);

	uintptr_t addresses[6] = { 
				  0x2F83BE,
				  0x2F8409,
				  0x2F845B,
				  0x2F855E,
			      0x2F84D5,
				  0x2F8578
	};

	char* original[6] = {	
                  "\xD9\x9E\x2C\x05\x00\x00",
                  "\xD9\x9E\x2C\x05\x00\x00",
				  "\xD9\x9E\x2C\x05\x00\x00",
				  "\xD9\x9E\x30\x05\x00\x00",
				  "\x89\x96\x30\x05\x00\x00",
				  "\x89\x8E\x34\x05\x00\x00"
	};

	char* patch = "\x90\x90\x90\x90\x90\x90";
	size_t size = 6;

	if (bNoRecoil)
	{
		for (int i = 0; i < 6; i++)
		{
			char* op = (LPVOID)(module_base_addr + addresses[i]);
			Patch(op, patch, size);
		}

		if (weapon != NULL)
		{
			weapon->minimum_reticle = 0;
			weapon->bloom_1         = 0;
			weapon->bloom_2         = 0;
		}
	}
	else
	{
		for (int i = 0; i < 6; i++)
		{
			char* op = (LPVOID)(module_base_addr + addresses[i]);
			Patch(op, original[i], size);
		}

	}

}
