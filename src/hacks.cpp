#include "offsets.hpp"
#include "entity.hpp"
#include "hacks.hpp"
#include "mem.hpp"

#define GUERRILLA       0x110F88D8
#define PLAYER          0x110E8B50
#define DOOR            0x110FDDD8

#define DOOR_ALL_ACCESS 0x00000004


void Hacks::Afterlife(bool bAfterlife)
{
    EntityList* entity_list = *(EntityList **)Memory::FindDMAddress(module_base_addr + offsets::entity_list_base,
                                                                    offsets::entity_list_offsets,
                                                                    offsets::entity_list_offsets_size);

    size_t size = *((int *)(Memory::FindDMAddress(module_base_addr + offsets::entity_list_base,
                                                  offsets::entity_list_offsets,
                                                  offsets::entity_list_offsets_size)) + 1);

    for (size_t i = 0; i < size; i++)
    {
        Entity* entity = entity_list->entities[i].entity;
        if (entity->entity_type == GUERRILLA)
        {
            if (bAfterlife == true)
                entity->health = 0;
            else
                entity->health = 150;
        }
    }

}

void Hacks::UnlimitedHealth(bool bUnlimitedHealth)
{
    /* Unlimited Health Prototype */

    // Detour sub health if entity type is PLAYER
}

void Hacks::UnlimitedAmmo(bool bUnlimitedAmmo)
{
    /* Main Weapon Ammo Operation */
    const char* main_ammo_op = (char*)(module_base_addr + offsets::main_ammo_base);
    const char* main_ammo_original = "\x4B\x4F";  // dec ebx; dec edi
    const char* main_ammo_patch    = "\x90\x90";  // nop
    size_t main_ammo_size = 2;


    /* Shotgun Ammo Operations */
    const char* shotgun_ammo_op = (char *)(module_base_addr + offsets::shotgun_ammo_base);
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
    const char* sniper_ammo_op = (char *)(module_base_addr + offsets::sniper_ammo_base);
    const char* sniper_ammo_original = "\x48"                      // dec eax
                                       "\x89\x86\x54\x04\x00\x00"  // mov [esi + 0x454], eax
                                       "\x8B\x86\x5C\x04\x00\x00"  // mov eax, [esi + 0x45C]
                                       "\x48";                     // dec eax

    const char* sniper_ammo_patch    = "\x90"                      // nop
                                       "\x89\x86\x54\x04\x00\x00"  // mov [esi + 0x454], eax
                                       "\x8B\x86\x5C\x04\x00\x00"  // mov eax, [esi + 0x45C]
                                       "\x90";                     // nop
    size_t sniper_ammo_size = 14;

    if (bUnlimitedAmmo)
    {
        Memory::Patch((BYTE *)main_ammo_op, (BYTE *)main_ammo_patch, main_ammo_size);
        Memory::Patch((BYTE *)sniper_ammo_op, (BYTE *)sniper_ammo_patch, sniper_ammo_size);
        Memory::Patch((BYTE *)shotgun_ammo_op, (BYTE *)shotgun_ammo_patch, shotgun_ammo_size);
    }
    else
    {
        Memory::Patch((BYTE *)main_ammo_op, (BYTE *)main_ammo_original, main_ammo_size);
        Memory::Patch((BYTE *)sniper_ammo_op, (BYTE *)sniper_ammo_original, sniper_ammo_size);
        Memory::Patch((BYTE *)shotgun_ammo_op, (BYTE *)shotgun_ammo_original, shotgun_ammo_size);
    }

}

void Hacks::Invisibilty(bool bPolterGheist)
{
    const char* visibility_op = (char *)(module_base_addr + offsets::invisibility_base);
    const char* original = "\x8B\x86\x18\x15\x00\x00";  // mov eax, dword ptr [esi + 0x1518]
    const char* patch    = "\x90\x90\x90\x90\x90\x90";  // nop
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
    const char* noise_op = (char *)(module_base_addr + offsets::noise_base);
    const char* original = "\x8B\x43\x30";  // mov eax, dword ptr [ebx + 30]
    const char* patch    = "\x31\xC0\x90";  // xor eax, eax; nop
    size_t size = 3;

    if (bPolterGheist)
    {
        Memory::Patch((BYTE *)noise_op, (BYTE *)patch, size);
    }
    else
    {
        Memory::Patch((BYTE *)noise_op, (BYTE *)original, size);
    }

}

void Hacks::NoRecoil(bool bNoRecoil)
{
    Weapon* weapon = (Weapon *)Memory::FindDMAddress(module_base_addr + offsets::weapon_base,
                                                     offsets::weapon_offsets,
                                                     offsets::weapon_offsets_size);

    uintptr_t op_offsets[6] = { 0x2F83BE,
                                0x2F8409,
                                0x2F845B,
                                0x2F855E,
                                0x2F84D5,
                                0x2F8578 };

    const char* original[6] = { "\xD9\x9E\x2C\x05\x00\x00",    // fstp dword ptr [esi + 0x52C]
                                "\xD9\x9E\x2C\x05\x00\x00",    // fstp dword ptr [esi + 0x52C]
                                "\xD9\x9E\x2C\x05\x00\x00",    // fstp dword ptr [esi + 0x52C]
                                "\xD9\x9E\x30\x05\x00\x00",    // fstp dword ptr [esi + 0x530]
                                "\x89\x96\x30\x05\x00\x00",    // mov  dword ptr [esi + 0x530], edx
                                "\x89\x8E\x34\x05\x00\x00" };  // mov  dword ptr [esi + 0x534], ecx

    const char* patch =         "\x90\x90\x90\x90\x90\x90";    // nop
    size_t size = 6;

    if (bNoRecoil)
    {
        for (size_t i = 0; i < size; i++)
        {
            const char* op = (char *)(module_base_addr + op_offsets[i]);
            Memory::Patch((BYTE *)op, (BYTE *)patch, size);
        }
    }
    else
    {
        for (size_t i = 0; i < size; i++)
        {
            const char* op = (char *)(module_base_addr + op_offsets[i]);
            Memory::Patch((BYTE *)op, (BYTE *)original[i], size);
        }
    }

}

void Hacks::UnlockAllDoors(void)
{
    EntityList* _entity_list = *(EntityList **)Memory::FindDMAddress(module_base_addr + offsets::entity_list_base,
                                                                     offsets::entity_list_offsets,
                                                                     offsets::entity_list_offsets_size);

    size_t size = *((int *)(Memory::FindDMAddress(module_base_addr + offsets::entity_list_base,
                                                  offsets::entity_list_offsets,
                                                  offsets::entity_list_offsets_size)) + 1);

    for (size_t i = 0; i < size; i++)
    {
        Entity* entity= _entity_list->entities[i].entity;
        if (entity->entity_type == DOOR)
        {
            Door* door = (Door *)entity;
            if (door->access == 0)
                door->access = DOOR_ALL_ACCESS;
        }
    }

}
