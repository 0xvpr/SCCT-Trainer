#include "hacks.hpp"

#include "offsets.hpp"
#include "patches.hpp"

#include "assembly.hpp"
#include "engine.hpp"
#include "memory.hpp"

#include <ranges>

#include <windows.h>

extern uintptr_t module_base_addr;
extern std::uint32_t total_doors_unlocked;

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
        memory::nop_sled<6>(visibility_op);
        memory::patch(noise_op, patches::noise_patch);
    } else {
        memory::patch(visibility_op, patches::visibility_original);
        memory::patch(noise_op, patches::noise_original);
    }
}

void hacks::super_weapons(bool state) {
    const auto main_ammo_op    = module_base_addr + offsets::main_ammo_base;
    const auto shotgun_ammo_op = module_base_addr + offsets::shotgun_ammo_base;
    const auto sniper_ammo_op  = module_base_addr + offsets::sniper_ammo_base;
    const auto rapid_fire_op   = module_base_addr + offsets::rapid_fire_base;

    if (state) {
        memory::nop_sled<2>(main_ammo_op);
        memory::patch(sniper_ammo_op, patches::sniper_ammo_patch);
        memory::patch(shotgun_ammo_op, patches::shotgun_ammo_patch);

        for (const auto [offset, patch] : std::views::zip(offsets::recoil_op_offsets, patches::recoil_patches) ) {
            const auto recoil_op = module_base_addr + offset;
            memory::patch(recoil_op, patch);
        }

        memory::nop_sled<2>(rapid_fire_op);
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

std::uint32_t hacks::disable_enemies(bool state) {
    const auto game_world = reinterpret_cast<engine::game_world_t *>(memory::find_dynamic_address(module_base_addr + offsets::game_world_base,
                                                                                                                     offsets::game_world_pointers));
    if (!game_world) {
        return 0;
    }

    auto entity_list = game_world->entity_list_ptr;
    auto entity_list_size = game_world->entity_list_size;

    if (entity_list == nullptr || !entity_list_size) {
        return 0;
    }

    std::uint32_t total_entities_changed = 0;
    for (std::size_t i = 0; i < entity_list_size; ++i) {
        auto& entity = *entity_list[i];

        if (engine::tag_if_aligned(entity.object_tag) == engine::object_tag::npc) {
            engine::enemy_t& enemy = reinterpret_cast<engine::enemy_t &>(entity);

            if (state) {
                enemy.health = 0;
            } else {
                enemy.health = 150;
            }

            ++total_entities_changed;
        }
    }

    return total_entities_changed;
}

std::uint32_t hacks::unlock_all_doors() {
    const auto game_world = reinterpret_cast<engine::game_world_t *>(memory::find_dynamic_address(module_base_addr + offsets::game_world_base,
                                                                                                                     offsets::game_world_pointers));
    if (!game_world) {
        return 0;
    }

    auto entity_list = game_world->entity_list_ptr;
    auto entity_list_size = game_world->entity_list_size;

    if (entity_list == nullptr || !entity_list_size) {
        return 0;
    }

    std::uint32_t local_total = 0;
    std::uint32_t n_doors_unlocked = 0;
    for (std::size_t i = 0; i < entity_list_size; ++i) {
        auto& entity = *entity_list[i];

        if (engine::tag_if_aligned(entity.object_tag) == engine::object_tag::door) {
            engine::door_t& door = reinterpret_cast<engine::door_t &>(entity);

            if (door.access == 0) {
                door.access = DOOR_ALL_ACCESS;
                ++n_doors_unlocked;
            }

            if (door.access == DOOR_ALL_ACCESS) {
                ++local_total;
            }

        }
    }
    total_doors_unlocked = local_total;

    return n_doors_unlocked;
}
