#include <cstdint>

#include "offsets.hpp"
#include "entity.hpp"
#include "hacks.hpp"
#include "mem.hpp"

#define GUERRILLA   0x110F88D8
#define PLAYER      0x110E8B50
#define ever ;;


void Hacks::KillAll(void)
{
/*
 *    uintptr_t module_base_addr = (uintptr_t)GetModuleHandle(NULL);
 *    EntityList* _entity_list = *(EntityList**)Memory::FindDMAddress(module_base_addr + 0xA0DFEC,
 *                                                                      offsets::entity_list_offsets,
 *                                                                      offsets::entity_list_offsets_size);
 *
 *    int current_entity = 0;
 *    for (ever)
 *    {
 *        Entity* entity= _entity_list->entities[current_entity].entity;
 *        if (entity->entity_type == PLAYER)
 *            break;
 *    
 *        if (entity->entity_type == GUERRILLA)
 *            entity->health = 0;
 *
 *        current_entity++;
 *    }
 */
}

// NEEDS UPDATE
void Hacks::PlayDead(bool bPlayDead, int* previous_health)
{
/*
 *    uintptr_t module_base_addr = (uintptr_t)GetModuleHandle(NULL);
 *    Entity* player = *(Entity**)Memory::FindDMAddress(module_base_addr + 0xA0F424,
 *                                                        offsets::player_hp_offsets,
 *                                                        offsets::player_hp_offsets_size);
 *
 *    if (bPlayDead)
 *    {
 *        *previous_health = player->health;
 *        player->health = 0;
 *    }
 *    else
 *    {
 *        player->health = *previous_health;
 *    }
 */
}

// NEEDS UPDATE
void Hacks::TeleportToADS(void)
{
/*
 *    uintptr_t module_base_addr = (uintptr_t)GetModuleHandle(NULL);
 *    EntityList* _entity_list = *(EntityList**)FindDMAAddress_attached(module_base_addr + 0xA0DFEC,
 *                                                                      offsets::entity_list_offsets,
 *                                                                      offsets::entity_list_offsets_size);
 *    Vec3* _ads_cam = (Vec3*)FindDMAAddress_attached(module_base_addr + 0x8FA4E8,
 *                                                    offsets::cam_offsets,
 *                                                    offsets::cam_offsets_size);
 *
 *    int entity_type;
 *    int current_entity = 0;
 *    for (ever)
 *    {
 *        entity_type = _entity_list->entities[current_entity].entity->entity_type;
 *        if (entity_type == PLAYER)
 *        {
 *            _entity_list->entities[current_entity].entity->x = _ads_cam->x + 40;
 *            _entity_list->entities[current_entity].entity->y = _ads_cam->y + 10;
 *            _entity_list->entities[current_entity].entity->z = _ads_cam->z + 100;
 *
 *            break;
 *        }
 *
 *        current_entity++;
 *    }
 */
}

void Hacks::Invisibilty(bool bPolterGheist)
{
    uintptr_t module_base_addr = (uintptr_t)GetModuleHandle(NULL);
    const char* visibility_op = (char *)(module_base_addr + 0x27F12C);

    const char* original = "\x8B\x86\x18\x15\x00\x00";
    const char* patch    = "\xB8\xAC\xC5\x27\x37\x90";
    size_t size = 6;

    if (bPolterGheist)
    {
        Memory::Patch((BYTE *)visibility_op, (BYTE *)patch, size);
    }
    else
    {
        Memory::Patch((BYTE *)visibility_op, (BYTE *)original, size);
    }

}

void Hacks::Silent(bool bPolterGheist)
{
    uintptr_t module_base_addr = (uintptr_t)GetModuleHandle(NULL);
    const char* noise_op = (char *)(module_base_addr + 0x417E4F);

    const char* original = "\xD9\x9E\x3C\x04\x00\x00";
    const char* patch    = "\x90\x90\x90\x90\x90\x90";
    size_t size = 6;

    if (bPolterGheist)
    {
        Memory::Patch((BYTE *)noise_op, (BYTE *)patch, size);
    }
    else
    {
        Memory::Patch((BYTE *)noise_op, (BYTE *)original, size);
    }

}

// NEEDS UPDATE
void Hacks::NoRecoil(bool bNoRecoil)
{
    uintptr_t module_base_addr = (uintptr_t)GetModuleHandle(NULL);
    Weapon* weapon = (Weapon*)Memory::FindDMAddress(module_base_addr + 0xA0F434,
                                                      offsets::weapon_offsets,
                                                      offsets::weapon_offsets_size);

    uintptr_t addresses[6] = { 
                  0x2F83BE,
                  0x2F8409,
                  0x2F845B,
                  0x2F855E,
                  0x2F84D5,
                  0x2F8578
    };

    const char* original[6] = {    
                  "\xD9\x9E\x2C\x05\x00\x00",
                  "\xD9\x9E\x2C\x05\x00\x00",
                  "\xD9\x9E\x2C\x05\x00\x00",
                  "\xD9\x9E\x30\x05\x00\x00",
                  "\x89\x96\x30\x05\x00\x00",
                  "\x89\x8E\x34\x05\x00\x00"
    };

    const char* patch = "\x90\x90\x90\x90\x90\x90";
    size_t size = 6;

    if (bNoRecoil)
    {
        for (int i = 0; i < 6; i++)
        {
            char* op = (char *)(module_base_addr + addresses[i]);
            Memory::Patch((BYTE *)op, (BYTE *)patch, size);
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
            char* op = (char *)(module_base_addr + addresses[i]);
            Memory::Patch((BYTE *)op, (BYTE *)original[i], size);
        }

    }

}

// NEEDS UPDATE
bool Hacks::KillEnt(void* pThis, int arg1)
{
    return true;
}
