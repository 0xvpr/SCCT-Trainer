#include <windows.h>
#include <string.h>

#include "offsets.h"
#include "entity.h"
#include "hacks.h"
#include "mem.h"

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

void hack_GodMode(bool bGodMode)
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

void hack_GhostMode(bool bGhostMode)
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

void hack_SuperWeapons(bool bSuperWeapons)
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

void hack_DisableAlarms(bool bDisableAlarms)
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

unsigned int hack_DisableEnemies(bool bDisableEnemies)
{
    EntityList* entity_list = *(EntityList **)FindDMAddress(module_base_addr + offsets_entity_list_base,
                                                                               offsets_entity_list_pointers,
                                                                               offsets_entity_list_pointers_size);

    size_t entity_list_size = *((int *)(FindDMAddress(module_base_addr + offsets_entity_list_base,
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

unsigned int hack_UnlockAllDoors(void)
{
    EntityList* _entity_list = *(EntityList **)FindDMAddress(module_base_addr + offsets_entity_list_base,
                                                                                offsets_entity_list_pointers,
                                                                                offsets_entity_list_pointers_size);

    size_t size = *((int *)(FindDMAddress(module_base_addr + offsets_entity_list_base,
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

/*void hack_InitializeMenuItems()*/
/*{*/
    /*strcpy(hackMenu[GOD_MODE].name, "1: God Mode");*/
    /*strcpy(hackMenu[GHOST_MODE].name, "2: Ghost Mode");*/
    /*strcpy(hackMenu[SUPER_WEAPONS].name, "3: Super Weapons");*/
    /*strcpy(hackMenu[DISABLE_ALARMS].name, "4: Disable Alarms");*/
    /*strcpy(hackMenu[DISABLE_ENEMIES].name, "5: Disable Enemies");*/
    /*strcpy(hackMenu[UNLOCK_ALL_DOORS].name, "6: Unlock All Doors");*/
/*}*/

/*void hack_Menu(IDirect3DDevice9* d3dDevice)*/
/*{*/
    /*resolution = *((Resolution *)(0x0009D2A8));*/

    /*float factor = 1.0;*/
    /*if (bMaximizeMenu)*/
    /*{*/
        /*// Title Template*/
        /*draw_DrawFilledRect(coordinates.x, coordinates.y, 140, 100, color_DarkGrey, d3dDevice);*/
        /*draw_DrawBorderBox(coordinates.x, coordinates.y, 140, 100, 4, color_Black, d3dDevice);*/

        /*// Row one*/
        /*int x1 = 20;*/
        /*int y1 = 15;*/
        /*for (int i = 3; i < MAX_MENU_ITEMS; i++)*/
        /*{*/
            /*// If hack is on we display the text colour in green*/
            /*draw_DrawFilledRect(coordinates.x + x1, coordinates.y + y1, 25, 20, hackMenu[i].bEnabled ? color_Green : color_LightGrey, d3dDevice);*/
            /*draw_DrawBorderBox(coordinates.x + x1, coordinates.y + y1, 25, 20, 2, color_Black, d3dDevice);*/

            /*//used to position the next item below*/
            /*x1 += 40;*/
        /*}*/
        /*// Row two*/
        /*int x2 = 20;*/
        /*int y2 = 55;*/
        /*for (int i = 0; i < MAX_MENU_ITEMS - 3; i++)*/
        /*{*/
            /*// If hack is on we display the text colour in green*/
            /*draw_DrawFilledRect(coordinates.x + x2, coordinates.y + y2, 25, 20, hackMenu[i].bEnabled ? color_Green : color_LightGrey, d3dDevice);*/
            /*draw_DrawBorderBox(coordinates.x + x2, coordinates.y + y2, 25, 20, 2, color_Black, d3dDevice);*/

            /*//used to position the next item*/
            /*x2 += 40;*/
        /*}*/
    /*}*/
    /*else*/
    /*{*/
        /*factor = 0.25;*/
        /*// Title Template*/
        /*draw_DrawFilledRect(30, 20, (int)(factor*140), (int)(factor*100), color_DarkGrey, d3dDevice);*/
        /*draw_DrawBorderBox(30, 20, (int)(factor*140), (int)(factor*100), 2, color_Black, d3dDevice);*/

        /*// Row one*/
        /*int x1 = 35;*/
        /*int y1 = 25;*/
        /*for (int i = 3; i < MAX_MENU_ITEMS; i++)*/
        /*{*/
            /*// If hack is on we display the text colour in green*/
            /*draw_DrawFilledRect(x1, y1, (int)(factor*20), (int)(factor*20), hackMenu[i].bEnabled ? color_Green : color_LightGrey, d3dDevice);*/
            /*draw_DrawBorderBox(x1, y1, (int)(factor*20), (int)(factor*20), 1, color_Black, d3dDevice);*/

            /*//used to position the next item below*/
            /*x1 += (int)(factor*40);*/
        /*}*/
        /*// Row two*/
        /*int x2 = 35;*/
        /*int y2 = 35;*/
        /*for (int i = 0; i < MAX_MENU_ITEMS - 3; i++)*/
        /*{*/
            /*// If hack is on we display the text colour in green*/
            /*draw_DrawFilledRect(x2, y2, (int)(factor*20), (int)(factor*20), hackMenu[i].bEnabled ? color_Green : color_LightGrey, d3dDevice);*/
            /*draw_DrawBorderBox(x2, y2, (int)(factor*20), (int)(factor*20), 1, color_Black, d3dDevice);*/

            /*//used to position the next item*/
            /*x2 += (int)(factor*40);*/
        /*}*/
    /*}*/
/*}*/
