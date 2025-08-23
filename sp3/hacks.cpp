#include "hacks.hpp"

#include "patches.hpp"
#include "offsets.hpp"

#include "assembly.hpp"
#include "entity.hpp"
#include "memory.hpp"

#include <ranges>

#include <windows.h>

extern uintptr_t module_base_addr;
extern unsigned int total_doors_unlocked;

void hacks::god_mode(bool state) {
    const auto health_op = module_base_addr + offsets::health_base;

    if (state) {
        constexpr auto patch_size = patches::health_original.size();
        memory::detour<patch_size>(health_op, health_detour);
    } else {
        memory::patch(health_op, patches::health_original);
    }

}

void hacks::ghost_mode(bool state) {
    const auto visibility_op = module_base_addr + offsets::invisibility_base;
    const auto noise_op      = module_base_addr + offsets::noise_base;

    if (state) {
        memory::patch(visibility_op, patches::visibility_ins.patch);
        memory::patch(noise_op, patches::noise_ins.patch);
    } else {
        memory::patch(visibility_op, patches::visibility_ins.original);
        memory::patch(noise_op, patches::noise_ins.original);
    }
}

void hacks::super_weapons(bool state) {
    const auto main_ammo_op    = module_base_addr + offsets::main_ammo_base;
    const auto shotgun_ammo_op = module_base_addr + offsets::shotgun_ammo_base;
    const auto sniper_ammo_op  = module_base_addr + offsets::sniper_ammo_base;
    const auto rapid_fire_op   = module_base_addr + offsets::rapid_fire_base;

    if (state) {
        memory::patch(main_ammo_op, patches::main_ammo_patch);
        memory::patch(sniper_ammo_op, patches::sniper_ammo_patch);
        memory::patch(shotgun_ammo_op, patches::shotgun_ammo_patch);

        for (const auto [offset, patch] : std::views::zip(offsets::recoil_op_offsets, patches::recoil_patches) ) {
            const auto recoil_op = module_base_addr + offset;
            memory::patch(recoil_op, patch);
        }

        memory::patch(rapid_fire_op, patches::rapid_fire_patch); 
    } else {
        memory::patch(main_ammo_op, patches::main_ammo_original);
        memory::patch(sniper_ammo_op, patches::sniper_ammo_original);
        memory::patch(shotgun_ammo_op, patches::shotgun_ammo_original);

        for (const auto [offset, patch] : std::views::zip(offsets::recoil_op_offsets, patches::recoil_originals) ) {
            const auto recoil_op = module_base_addr + offset;
            memory::patch(recoil_op, patch);
        }

        memory::patch(rapid_fire_op, patches::rapid_fire_original);
    }

}

void hacks::disable_alarms(bool state) {
    const auto alarm_op = module_base_addr + offsets::alarm_base;

    auto patch = (state ? patches::alarm_patch : patches::alarm_original);
    memory::patch(alarm_op, patch);
}

unsigned int hacks::disable_enemies(bool state) {
    const EntityList* entity_list = *(EntityList **)(memory::find_dynamic_address(module_base_addr + offsets::entity_list_base,
                                                                                                     offsets::entity_list_pointers));

    const size_t entity_list_size = *((std::size_t *)(memory::find_dynamic_address(module_base_addr + offsets::entity_list_base,
                                                                                                      offsets::entity_list_pointers) + 1));

    unsigned int total_entities_changed = 0;
    for (std::size_t i = 0; i < entity_list_size; ++i) {
        Entity* entity = entity_list->entities[i].entity;
        if (TYPE(entity->lpVtable) == NPC) {
            if (state) {
                entity->health = 0;
                ++total_entities_changed;
            } else {
                entity->health = 150;
                ++total_entities_changed;
            }
        }
    }

    return total_entities_changed;
}

unsigned int hacks::unlock_all_doors() {
    const EntityList* _entity_list = *(EntityList **)(memory::find_dynamic_address(module_base_addr + offsets::entity_list_base,
                                                                                                      offsets::entity_list_pointers));

    const std::size_t size = *((std::size_t *)(memory::find_dynamic_address(module_base_addr + offsets::entity_list_base,
                                                                                               offsets::entity_list_pointers) + 1));

    unsigned int local_total = 0;
    unsigned int n_doors_unlocked = 0;
    for (std::size_t i = 0; i < size; ++i) {
        const Entity* entity = _entity_list->entities[i].entity;
        if (TYPE(entity->lpVtable) == DOOR) {
            Door* door = (Door *)entity;
            if (door->access == 0) {
                door->access = DOOR_ALL_ACCESS;
                ++n_doors_unlocked;
            }

            if (door->access == DOOR_ALL_ACCESS) {
                ++local_total;
            }

        }
    }
    total_doors_unlocked = local_total;

    return n_doors_unlocked;
}
