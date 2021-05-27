#include "offsets.h"
#include "entity.h"
#include "hacks.h"
#include "hook.h"
#include "mem.h"

#define DOOR_ALL_ACCESS 0x00000004

#define PLAYER          0x110E8B50
#define DOOR            0x110FDDD8
#define NPC             0x110F88D8


void hacks_GodMode(bool bGodMode)
{
    const char* health_op = (char *)(module_base_addr + offsets_health_base);
    const char* health_original = "\x2B\xC2"   // sub eax, edx
                                  "\x89\x03"   // mov dword ptr [ebx], eax
                                  "\x8B\xD8";  // mov ebx, eax
    size_t health_op_size = 6;

    if (bGodMode)
    {
        Detour((void *)health_op, (void *)healthDetour, health_op_size);
    }
    else
    {
        Patch((BYTE *)health_op, (BYTE *)health_original, health_op_size);
    }

}

void hacks_GhostMode(bool bGhostMode)
{
    const char* visibility_op = (char *)(module_base_addr + offsets_invisibility_base);
    const char* visibility_original = "\x8B\x86\x18\x15\x00\x00";  // mov eax, dword ptr [esi + 0x1518]
    const char* visibility_patch    = "\x90\x90\x90\x90\x90\x90";  // nop
    size_t visibility_size = 6;

    const char* noise_op = (char *)(module_base_addr + offsets_noise_base);
    const char* noise_original = "\x8B\x43\x30";  // mov eax, dword ptr [ebx + 30]
    const char* noise_patch    = "\x31\xC0\x90";  // xor eax, eax; nop
    size_t noise_size = 3;

    // Add third op for slider

    if (bGhostMode)
    {
        Patch((BYTE *)visibility_op, (BYTE *)visibility_patch, visibility_size);
        Patch((BYTE *)noise_op, (BYTE *)noise_patch, noise_size);
    }
    else
    {
        Patch((BYTE *)visibility_op, (BYTE *)visibility_original, visibility_size);
        Patch((BYTE *)noise_op, (BYTE *)noise_original, noise_size);
    }

}

void hacks_SuperWeapons(bool bSuperWeapons)
{
    /* Main Weapon Ammo Operation */
    const char* main_ammo_op = (char *)(module_base_addr + offsets_main_ammo_base);
    const char* main_ammo_original = "\x4B\x4F";  // dec ebx; dec edi
    const char* main_ammo_patch    = "\x90\x90";  // nop
    size_t main_ammo_size = 2;


    /* Shotgun Ammo Operations */
    const char* shotgun_ammo_op = (char *)(module_base_addr + offsets_shotgun_ammo_base);
    const char* shotgun_ammo_original = "\x49"                      // dec ecx
                                        "\x89\x8F\x1C\x04\x00\x00"  // mov [esi + 0x454], eax
                                        "\x8B\x8F\xFC\x03\x00\x00"  // mov eax, [esi + 0x45C]
                                        "\x48";                     // dec eax

    const char* shotgun_ammo_patch    = "\x90"                      // nop
                                        "\x89\x8F\x1C\x04\x00\x00"  // mov [esi + 0x454], eax
                                        "\x8B\x8F\xFC\x03\x00\x00"  // mov eax, [esi + 0x45C]
                                        "\x90";                     // nop
    size_t shotgun_ammo_size = 14;

    /* Sniper Ammo Operations */
    const char* sniper_ammo_op = (char *)(module_base_addr + offsets_sniper_ammo_base);
    const char* sniper_ammo_original  = "\x48"                      // dec eax
                                        "\x89\x86\x54\x04\x00\x00"  // mov [esi + 0x454], eax
                                        "\x8B\x86\x5C\x04\x00\x00"  // mov eax, [esi + 0x45C]
                                        "\x48";                     // dec eax

    const char* sniper_ammo_patch     = "\x90"                      // nop
                                        "\x89\x86\x54\x04\x00\x00"  // mov [esi + 0x454], eax
                                        "\x8B\x86\x5C\x04\x00\x00"  // mov eax, [esi + 0x45C]
                                        "\x90";                     // nop
    size_t sniper_ammo_size = 14;

    /* Recoil & Spread Operations */
    unsigned recoil_op_offsets[6]  = { 0x2F83BE,
                                       0x2F8409,
                                       0x2F845B,
                                       0x2F855E,
                                       0x2F84D5,
                                       0x2F8578 };

    const char* recoil_original[6] = { "\xD9\x9E\x2C\x05\x00\x00",    // fstp dword ptr [esi + 0x52C]
                                       "\xD9\x9E\x2C\x05\x00\x00",    // fstp dword ptr [esi + 0x52C]
                                       "\xD9\x9E\x2C\x05\x00\x00",    // fstp dword ptr [esi + 0x52C]
                                       "\xD9\x9E\x30\x05\x00\x00",    // fstp dword ptr [esi + 0x530]
                                       "\x89\x96\x30\x05\x00\x00",    // mov  dword ptr [esi + 0x530], edx
                                       "\x89\x8E\x34\x05\x00\x00" };  // mov  dword ptr [esi + 0x534], ecx

    const char* recoil_patch       =   "\x90\x90\x90\x90\x90\x90";    // nop
    size_t recoil_op_size = 6;

    /* Rapid Fire Operation */
    const char* rapid_fire_op = (char *)(module_base_addr + offsets_rapid_fire_base);
    const char* rapid_fire_original = "\x75\x47";  // jne short 0x47
    const char* rapid_fire_patch    = "\x90\x90";  // nop
    size_t rapid_fire_size = 2;

    if (bSuperWeapons)
    {
        Patch((BYTE *)main_ammo_op, (BYTE *)main_ammo_patch, main_ammo_size);
        Patch((BYTE *)sniper_ammo_op, (BYTE *)sniper_ammo_patch, sniper_ammo_size);
        Patch((BYTE *)shotgun_ammo_op, (BYTE *)shotgun_ammo_patch, shotgun_ammo_size);

        for (size_t i = 0; i < recoil_op_size; i++)
        {
            const char* recoil_op = (char *)(module_base_addr + recoil_op_offsets[i]);
            Patch((BYTE *)recoil_op, (BYTE *)recoil_patch, recoil_op_size);
        }

        Patch((BYTE *)rapid_fire_op, (BYTE *)rapid_fire_patch, rapid_fire_size);
    }
    else
    {
        Patch((BYTE *)main_ammo_op, (BYTE *)main_ammo_original, main_ammo_size);
        Patch((BYTE *)sniper_ammo_op, (BYTE *)sniper_ammo_original, sniper_ammo_size);
        Patch((BYTE *)shotgun_ammo_op, (BYTE *)shotgun_ammo_original, shotgun_ammo_size);

        for (size_t i = 0; i < recoil_op_size; i++)
        {
            const char* recoil_op = (char *)(module_base_addr + recoil_op_offsets[i]);
            Patch((BYTE *)recoil_op, (BYTE *)recoil_original[i], recoil_op_size);
        }

        Patch((BYTE *)rapid_fire_op, (BYTE *)rapid_fire_original, rapid_fire_size);
    }

}

void hacks_DisableAlarms(bool bDisableAlarms)
{
    const char* alarm_op = (char *)(module_base_addr + offsets_alarm_base);
    const char* alarm_original = "\x0F\x85\x35\x03\x00\x00"; // jne splintercell3.exe + 0x9BF9C
    const char* alarm_patch    = "\xE9\x36\x03\x00\x00\x90"; // jmp splintercell3.exe + 0x9BF9C
    size_t alarm_size = 6;

    if (bDisableAlarms)
    {
        Patch((BYTE *)alarm_op, (BYTE *)alarm_patch, alarm_size);
    }
    else
    {
        Patch((BYTE *)alarm_op, (BYTE *)alarm_original, alarm_size);
    }
}

unsigned int hacks_DisableEnemies(bool bDisableEnemies)
{
    EntityList* entity_list = *(EntityList **)FindDMAddress_attached(module_base_addr + offsets_entity_list_base,
                                                                                        offsets_entity_list_pointers,
                                                                                        offsets_entity_list_pointers_size);

    size_t entity_list_size = *((int *)(FindDMAddress_attached(module_base_addr + offsets_entity_list_base,
                                                                                  offsets_entity_list_pointers,
                                                                                  offsets_entity_list_pointers_size)) + 1);

    unsigned int n_entities_changed = 0;
    for (size_t i = 0; i < entity_list_size; i++)
    {
        Entity* entity = entity_list->entities[i].entity;
        if (entity->entity_type == NPC)
        {
            if (bDisableEnemies == true)
            {
                entity->health = 0;
                ++n_entities_changed;
            }
            else
            {
                entity->health = 150;
                ++n_entities_changed;
            }
        }
    }

    return n_entities_changed;
}

unsigned int hacks_UnlockAllDoors(void)
{
    EntityList* _entity_list = *(EntityList **)FindDMAddress_attached(module_base_addr + offsets_entity_list_base,
                                                                                         offsets_entity_list_pointers,
                                                                                         offsets_entity_list_pointers_size);

    size_t size = *((int *)(FindDMAddress_attached(module_base_addr + offsets_entity_list_base,
                                                                      offsets_entity_list_pointers,
                                                                      offsets_entity_list_pointers_size)) + 1);

    unsigned int local_total = 0;
    unsigned int n_doors_unlocked = 0;
    for (size_t i = 0; i < size; i++)
    {
        Entity* entity = _entity_list->entities[i].entity;
        if (entity->entity_type == DOOR)
        {
            Door* door = (Door *)entity;
            if (door->access == 0)
            {
                door->access = DOOR_ALL_ACCESS;
                ++n_doors_unlocked;
            }

            if (door->access == DOOR_ALL_ACCESS)
            {
                ++local_total;
            }

        }
    }
    total_doors_unlocked = local_total;

    return n_doors_unlocked;
}
