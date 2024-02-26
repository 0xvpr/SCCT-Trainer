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
