#include "hacks.h"

#include "offsets.h"
#include "entity.h"
#include "mem.h"

extern uintptr_t g_module_base_addr;

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
