#include <windows.h>
#include <string.h>

#include "assembly.hpp"
#include "offsets.hpp"
#include "entity.hpp"
#include "hacks.hpp"
#include "memory.hpp"

extern uintptr_t module_base_addr;

extern unsigned int n_entities_changed;
extern unsigned int total_doors_unlocked;

extern bool bDisableEnemies;
extern bool bDisableAlarms;
extern bool bSuperWeapons;
extern bool bMaximizeMenu;
extern bool bGhostMode;
extern bool bShutdown;
extern bool bGodMode;

/*void health_detour(void); // maybe this works?*/

void hack_GodMode(bool bEnabled) {
    const char* health_op = (char *)(module_base_addr + offsets::health_base);
    const char* health_original = "\x2B\xC2"   // sub eax, edx
                                  "\x89\x03"   // mov dword ptr [ebx], eax
                                  "\x8B\xD8";  // mov ebx, eax
    size_t health_op_size = 6;

    if (bEnabled) {
        memory::detour(health_op, (void *)health_detour, health_op_size);

    } else {
        memory::patch(health_op, health_original, health_op_size);
    }

}

void hack_GhostMode(bool bEnabled) {
    const char* visibility_op = (char *)(module_base_addr + offsets::invisibility_base);
    const char* visibility_original = "\x8B\x86\x18\x15\x00\x00";  // mov eax, dword ptr [esi + 0x1518]
    const char* visibility_patch    = "\x90\x90\x90\x90\x90\x90";  // nop
    size_t visibility_size = 6;

    const char* noise_op = (char *)(module_base_addr + offsets::noise_base);
    const char* noise_original = "\x3B\xF8";  // cmp edi, eax
    const char* noise_patch    = "\x39\xC0";  // cmp eax, eax
    size_t noise_size = 2;

    // Add third op for slider

    if (bEnabled) {
        memory::patch(visibility_op, visibility_patch, visibility_size);
        memory::patch(noise_op, noise_patch, noise_size);
    } else {
        memory::patch(visibility_op, visibility_original, visibility_size);
        memory::patch(noise_op, noise_original, noise_size);
    }

}

void hack_SuperWeapons(bool bEnabled) {
    /* Main Weapon Ammo Operation */
    char* main_ammo_op = (char *)(module_base_addr + offsets::main_ammo_base);
    char* main_ammo_original = "\x4B\x4F";  // dec ebx; dec edi
    char* main_ammo_patch    = "\x90\x90";  // nop; nop
    size_t main_ammo_size = 2;


    /* Shotgun Ammo Operations */
    char* shotgun_ammo_op = (char *)(module_base_addr + offsets::shotgun_ammo_base);
    char* shotgun_ammo_original       = "\x49"                      // dec ecx
                                        "\x89\x8F\x1C\x04\x00\x00"  // mov [esi + 0x454], eax
                                        "\x8B\x8F\xFC\x03\x00\x00"  // mov eax, [esi + 0x45C]
                                        "\x48";                     // dec eax

    char* shotgun_ammo_patch          = "\x90"                      // nop
                                        "\x89\x8F\x1C\x04\x00\x00"  // mov [esi + 0x454], eax
                                        "\x8B\x8F\xFC\x03\x00\x00"  // mov eax, [esi + 0x45C]
                                        "\x90";                     // nop
    size_t shotgun_ammo_size = 14;

    /* Sniper Ammo Operations */
    char* sniper_ammo_op = (char *)(module_base_addr + offsets::sniper_ammo_base);
    char* sniper_ammo_original         = "\x48"                      // dec eax
                                         "\x89\x86\x54\x04\x00\x00"  // mov [esi + 0x454], eax
                                         "\x8B\x86\x5C\x04\x00\x00"  // mov eax, [esi + 0x45C]
                                         "\x48";                     // dec eax

    char* sniper_ammo_patch            = "\x90"                      // nop
                                         "\x89\x86\x54\x04\x00\x00"  // mov [esi + 0x454], eax
                                         "\x8B\x86\x5C\x04\x00\x00"  // mov eax, [esi + 0x45C]
                                         "\x90";                     // nop
    size_t sniper_ammo_size = 14;

    /* Recoil & Spread Operations */
    unsigned recoil_op_offsets[6]      = { 0x2F83BE,
                                           0x2F8409,
                                           0x2F845B,
                                           0x2F855E,
                                           0x2F84D5,
                                           0x2F8578 };

    const char* recoil_original[6]     = { "\xD9\x9E\x2C\x05\x00\x00",    // fstp dword ptr [esi + 0x52C]
                                           "\xD9\x9E\x2C\x05\x00\x00",    // fstp dword ptr [esi + 0x52C]
                                           "\xD9\x9E\x2C\x05\x00\x00",    // fstp dword ptr [esi + 0x52C]
                                           "\xD9\x9E\x30\x05\x00\x00",    // fstp dword ptr [esi + 0x530]
                                           "\x89\x96\x30\x05\x00\x00",    // mov  dword ptr [esi + 0x530], edx
                                           "\x89\x8E\x34\x05\x00\x00" };  // mov  dword ptr [esi + 0x534], ecx

    const char* recoil_patches[6]      = { "\x89\x8E\x2C\x05\x00\x00",    // mov dword ptr [esi + 0x52C], ecx
                                           "\x89\x8E\x2C\x05\x00\x00",    // mov dword ptr [esi + 0x52C], ecx
                                           "\x89\x8E\x2C\x05\x00\x00",    // mov dword ptr [esi + 0x52C], ecx
                                           "\x89\x8E\x30\x05\x00\x00",    // mov dword ptr [esi + 0x530], ecx
                                           "\x89\x8E\x30\x05\x00\x00",    // mov dword ptr [esi + 0x530], ecx
                                           "\x89\xBE\x34\x05\x00\x00" };  // mov dword ptr [esi + 0x534], edi
    size_t recoil_op_size = 6;

    /* Rapid Fire Operation */
    char* rapid_fire_op = (char *)(module_base_addr + offsets::rapid_fire_base);
    char* rapid_fire_original = "\x75\x47";  // jne short 0x47
    char* rapid_fire_patch    = "\x90\x90";  // nop
    size_t rapid_fire_size = 2;

    if (bEnabled) {
        (void)memory::patch((BYTE *)main_ammo_op, (BYTE *)main_ammo_patch, main_ammo_size);
        (void)memory::patch((BYTE *)sniper_ammo_op, (BYTE *)sniper_ammo_patch, sniper_ammo_size);
        (void)memory::patch((BYTE *)shotgun_ammo_op, (BYTE *)shotgun_ammo_patch, shotgun_ammo_size); 

        for (size_t i = 0; i < recoil_op_size; i++) {
            const char* recoil_op = (char *)(module_base_addr + recoil_op_offsets[i]);
            (void)memory::patch((BYTE *)recoil_op, (BYTE *)recoil_patches[i], recoil_op_size);
        }

        (void)memory::patch((BYTE *)rapid_fire_op, (BYTE *)rapid_fire_patch, rapid_fire_size);
    } else {
        (void)memory::patch((BYTE *)main_ammo_op, (BYTE *)main_ammo_original, main_ammo_size);
        (void)memory::patch((BYTE *)sniper_ammo_op, (BYTE *)sniper_ammo_original, sniper_ammo_size);
        (void)memory::patch((BYTE *)shotgun_ammo_op, (BYTE *)shotgun_ammo_original, shotgun_ammo_size);

        for (size_t i = 0; i < recoil_op_size; i++) {
            const char* recoil_op = (char *)(module_base_addr + recoil_op_offsets[i]);
            (void)memory::patch((BYTE *)recoil_op, (BYTE *)recoil_original[i], recoil_op_size);
        }

        (void)memory::patch((BYTE *)rapid_fire_op, (BYTE *)rapid_fire_original, rapid_fire_size);
    }

}

void hack_DisableAlarms(bool bEnabled) {
    const char* alarm_op = (char *)(module_base_addr + offsets::alarm_base);
    const char* alarm_original = "\x0F\x85\x35\x03\x00\x00"; // jne splintercell3.exe + 0x9BF9C
    const char* alarm_patch    = "\xE9\x36\x03\x00\x00\x90"; // jmp splintercell3.exe + 0x9BF9C
    size_t alarm_size = 6;

    if (bEnabled) {
        memory::patch((BYTE *)alarm_op, (BYTE *)alarm_patch, alarm_size);
    } else {
        memory::patch((BYTE *)alarm_op, (BYTE *)alarm_original, alarm_size);
    }
}

unsigned int hack_DisableEnemies(bool bEnabled) {
    EntityList* entity_list = *(EntityList **)memory::find_dynamic_address(module_base_addr + offsets::entity_list_base,
                                                                                              offsets::entity_list_pointers,
                                                                                              offsets::entity_list_pointers_size);

    size_t entity_list_size = *((size_t *)(memory::find_dynamic_address(module_base_addr + offsets::entity_list_base,
                                                                                           offsets::entity_list_pointers,
                                                                                           offsets::entity_list_pointers_size)) + 1);

    unsigned int total_entities_changed = 0;
    for (size_t i = 0; i < entity_list_size; i++)
    {
        Entity* entity = entity_list->entities[i].entity;
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

unsigned int hack_UnlockAllDoors(void) {
    EntityList* _entity_list = *(EntityList **)memory::find_dynamic_address(module_base_addr + offsets::entity_list_base,
                                                                                               offsets::entity_list_pointers,
                                                                                               offsets::entity_list_pointers_size);

    size_t size = *((size_t *)(memory::find_dynamic_address(module_base_addr + offsets::entity_list_base,
                                                                               offsets::entity_list_pointers,
                                                                               offsets::entity_list_pointers_size)) + 1);

    unsigned int local_total = 0;
    unsigned int n_doors_unlocked = 0;
    for (size_t i = 0; i < size; i++) {
        Entity* entity = _entity_list->entities[i].entity;
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
