#include "hacks.h"

#include "assembly.h"
#include "offsets.h"
#include "patches.h"
#include "entity.h"
#include "mem.h"

#include <memoryapi.h>

extern uintptr_t g_module_base_addr;

void hack_super_weapons(int bEnabled)
{
    void* const main_ammo_addr    = (void *)(g_module_base_addr + offsets_main_ammo_base);
    void* const shotgun_ammo_addr = (void *)(g_module_base_addr + offsets_shotgun_ammo_base);
    void* const sniper_ammo_addr  = (void *)(g_module_base_addr + offsets_sniper_ammo_base);

    void* const rapid_fire_addr   = (void *)(g_module_base_addr + offsets_rapid_fire_base);

    void* const recoil_addr_0     = (void *)(g_module_base_addr + offsets_recoil_bases[0]);
    void* const recoil_addr_1     = (void *)(g_module_base_addr + offsets_recoil_bases[1]);
    void* const recoil_addr_2     = (void *)(g_module_base_addr + offsets_recoil_bases[2]);
    void* const recoil_addr_3     = (void *)(g_module_base_addr + offsets_recoil_bases[3]);
    void* const recoil_addr_4     = (void *)(g_module_base_addr + offsets_recoil_bases[4]);
    void* const recoil_addr_5     = (void *)(g_module_base_addr + offsets_recoil_bases[5]);

    if (bEnabled)
    {
        memory_nop(main_ammo_addr, sizeof(patch_main_ammo_original));
        memory_patch(sniper_ammo_addr, patch_sniper_ammo_patch, sizeof(patch_sniper_ammo_patch));
        memory_patch(shotgun_ammo_addr, patch_shotgun_ammo_patch, sizeof(patch_shotgun_ammo_patch)); 

        memory_nop(rapid_fire_addr, sizeof(patch_rapid_fire_original));

        memory_patch(recoil_addr_0, patch_recoil_patches[0], sizeof(patch_recoil_patches[0]));
        memory_patch(recoil_addr_1, patch_recoil_patches[1], sizeof(patch_recoil_patches[1]));
        memory_patch(recoil_addr_2, patch_recoil_patches[2], sizeof(patch_recoil_patches[2]));
        memory_patch(recoil_addr_3, patch_recoil_patches[3], sizeof(patch_recoil_patches[3]));
        memory_patch(recoil_addr_4, patch_recoil_patches[4], sizeof(patch_recoil_patches[4]));
        memory_patch(recoil_addr_5, patch_recoil_patches[5], sizeof(patch_recoil_patches[5]));
    }
    else
    {
        memory_patch(main_ammo_addr, patch_main_ammo_original, sizeof(patch_main_ammo_original));
        memory_patch(sniper_ammo_addr, patch_sniper_ammo_original, sizeof(patch_sniper_ammo_original));
        memory_patch(shotgun_ammo_addr, patch_shotgun_ammo_original, sizeof(patch_shotgun_ammo_original));

        memory_patch(rapid_fire_addr, patch_rapid_fire_original, sizeof(patch_rapid_fire_original));

        memory_patch(recoil_addr_0, patch_recoil_originals[0], sizeof(patch_recoil_originals[0]));
        memory_patch(recoil_addr_1, patch_recoil_originals[1], sizeof(patch_recoil_originals[1]));
        memory_patch(recoil_addr_2, patch_recoil_originals[2], sizeof(patch_recoil_originals[2]));
        memory_patch(recoil_addr_3, patch_recoil_originals[3], sizeof(patch_recoil_originals[3]));
        memory_patch(recoil_addr_4, patch_recoil_originals[4], sizeof(patch_recoil_originals[4]));
        memory_patch(recoil_addr_5, patch_recoil_originals[5], sizeof(patch_recoil_originals[5]));
    }

}

unsigned int hack_disable_enemies(int bEnabled)
{
    GameWorld* gameWorld = (GameWorld *)memory_find_dynamic_address(g_module_base_addr + offsets_game_world_base,
                                                                                         offsets_game_world_pointers,
                                                                                         (sizeof(offsets_game_world_pointers)/sizeof(offsets_game_world_pointers[0])));
    if (!gameWorld)
    {
        return 0;
    }

    size_t size = gameWorld->n_entities;

    unsigned int total_entities_changed = 0;
    for (size_t i = 0; i < size; i++)
    {
        Entity* entity = gameWorld->entities[i];
        if (!entity)
        {
            break;
        }

        if (TYPE(entity->lpVtable) == NPC)
        {
            if (bEnabled)
            {
                entity->health = 0;
                ++total_entities_changed;
            }
            else
            {
                entity->health = 150;
                ++total_entities_changed;
            }
        }
    }

    return total_entities_changed;
}

unsigned int hack_unlock_all_doors(void)
{
    GameWorld* gameWorld = (GameWorld *)memory_find_dynamic_address(g_module_base_addr + offsets_game_world_base,
                                                                                         offsets_game_world_pointers,
                                                                                         (sizeof(offsets_game_world_pointers)/sizeof(offsets_game_world_pointers[0])));

    if (!gameWorld)
    {
        return 0;
    }

    size_t size = gameWorld->n_entities;

    unsigned int n_doors_unlocked = 0;
    for (size_t i = 0; i < size; i++)
    {
        Entity* entity = gameWorld->entities[i];
        if (TYPE(entity->lpVtable) == DOOR)
        {
            Door* door = (Door *)entity;
            if (door->access == 0)
            {
                door->access = DOOR_ALL_ACCESS;
                ++n_doors_unlocked;
            }
        }
    }

    return n_doors_unlocked;
}

void hack_test(void)
{
    GameWorld* gameWorld = (GameWorld *)memory_find_dynamic_address(g_module_base_addr + offsets_game_world_base,
                                                                                         offsets_game_world_pointers,
                                                                                         sizeof(offsets_game_world_pointers)/(sizeof(offsets_game_world_pointers[0])));

    if (!gameWorld)
    {
        return;
    }

    size_t size = gameWorld->n_entities;

    Entity* player = NULL;
    for (size_t i = size-1; size > 0; --i)
    {
        Entity* current_entity = gameWorld->entities[i];
        if (TYPE(current_entity->lpVtable) == PLAYER)
        {
            player = current_entity;
            break;
        }
    }

    if (player != NULL)
    {
        // Teleport them all to me
        /*for (size_t i = 0; i < size; ++i)*/
        /*{*/
            /*Entity* current_entity = gameWorld->entities[i];*/
            /*if (TYPE(current_entity->lpVtable) == NPC)*/
            /*{*/
                /*current_entity->x = player->x;*/
                /*current_entity->y = player->y;*/
                /*current_entity->z = player->z;*/
            /*}*/
        /*}*/

        /*player->lpVtable->function_1(player);*/
        /*player->lpVtable->function_2(player);*/
        /*player->lpVtable->function_3(player);*/
        /*player->lpVtable->func_10_1098DD40(player);*/
        /*player->lpVtable->function_5(player);*/
        /*player->lpVtable->function_6(player);*/
        /*player->lpVtable->function_7(player);*/
        /*player->lpVtable->function_8(player);*/
        /*player->lpVtable->function_9(player);*/
        /*player->lpVtable->function_10(player);*/
        /*player->lpVtable->function_11(player);*/
        /*player->lpVtable->function_12(player);*/
    }

}

void hack_no_clip(int bEnabled)
{
    if (bEnabled)
    {
        // Stop xyz movements
        
        // X movement
        // splintercell3.exe+19580D -> fstp dword ptr [edi]
        // splintercell3.exe+19580D -> nop nop
    }
}
