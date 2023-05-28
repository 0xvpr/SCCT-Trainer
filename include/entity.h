#ifndef _ENTITY_H
#define _ENTITY_H

#ifndef TYPE
#define TYPE(x) ((uintptr_t)x)
#endif /* TYPE */

typedef struct PlayerVtable
{
    void (__stdcall  * func_00_10CD6AF0)(int arg1, int arg2, void * unknown);        // To Reverse Engineer
    void (__stdcall  * func_01_10CD6B00)(void);                                      // To Reverse Engineer
    void (__stdcall  * func_02_10CD6B10)(void);                                      // To Reverse Engineer
    void (__thiscall * func_03_10B8C520)(void * this, unsigned char byte);           // To Reverse Engineer
    void (__fastcall * func_04_1098DCC0)(int arg1);                                  // To Reverse Engineer
    void (__fastcall * func_05_10A7E240)(int * arg1);                                // To Reverse Engineer
    void (__stdcall  * func_06_10A799B0)(void);                                      // To Reverse Engineer
    void (__fastcall * func_07_10CD7AC0)(int arg1);                                  // To Reverse Engineer
    void (__fastcall * func_08_10B7E0A0)(int * arg1);                                // To Reverse Engineer
    void (__fastcall * func_09_10993690)(int arg1);                                  // To Reverse Engineer
    void (__thiscall * func_10_1098DD40)(void * this);                               // To Reverse Engineer
    void (__fastcall * func_11_1092B9A0)(int arg1);                                  // To Reverse Engineer
    void (__thiscall * func_12_10CF51B0)(void * this, int arg1, int arg2);           // arg1 == 0x2B2 and arg2 != 0
    void (__thiscall * func_13_10CEE8A0)(void * this, int arg1, int arg2, int arg3); // args are non-zero
    void (__stdcall  * func_14_10A797F0)(void);                                      // To Reverse Engineer
    void (__stdcall  * func_15_10CD6AD0)(void);                                      // To Reverse Engineer
    void (__fastcall * func_16_109957C0)(int arg1);                                  // To Reverse Engineer
    void (__thiscall * func_17_1098FDE0)(void * this, int arg1);                     // if arg2 == _DAT_111f690c
    void (__thiscall * func_18_10CF4890)(void * this, int arg1, int arg2, int arg3); // WHOLE LOTTA GANG SHIT
    void (__thiscall * func_19_10CDB320)(void * this, int arg1, int arg2, int arg3); // WHOLE LOTTA GANG SHIT
    void (__thiscall * func_20_10CDFEB0)(void * this);                               // Maybe not a fastcall????
    int  (__stdcall  * func_21_10CDB910)(void);                                      // To Reverse Engineer
    int  (__stdcall  * func_22_1092AF90)(void);                                      // To Reverse Engineer
    int  (__stdcall  * func_23_1092AFA0)(void);                                      // To Reverse Engineer
    int  (__thiscall * func_24_10A88BD0)(void * this, int arg1, int arg2, int arg3,  // wtf .......................
            int arg4, void * arg5,void * arg6,void * arg7, int arg8, int arg9,       // ...........................
            int  arg10);                                                             // ....................is this
    void (__stdcall  * func_25_1092AFB0)(void);                                      // To Reverse Engineer
    void (__stdcall  * func_26_1092AFC0)(void);                                      // To Reverse Engineer
    void (__stdcall  * func_27_1092AFD0)(void);                                      // To Reverse Engineer
    void (__thiscall * func_28_10B852D0)(void * unknown);                               // No fucking clue but its huge
} PlayerVtable;

typedef struct Entity
{
    PlayerVtable* lpVtable;   // + 0x0000
    char _0xE8[0xE4];
    float x;                  // + 0x00E8
    float y;                  // + 0x00EC
    float z;                  // + 0x00F0
    char _0x420[0x32C];
    int health;               // + 0x0420
} Entity;

typedef struct EntityObject
{
    struct Entity* entity;
} EntityObject;

typedef struct EntityList
{
    struct EntityObject entities[99];
} EntityList;

typedef struct Door
{
    unsigned int door_type;  // + 0x0000
    char _0x4B8[0x4B4];
    int access;              // + 0x04B8
} Door;

typedef struct Weapon
{
    int current_ammo;        // + 0x0000
    int max_clip_size;       // + 0x0004
    int total_ammo;          // + 0x0008
    char _0x51C[0xF0];
    float minimum_reticle;   // + 0x051C
    float bloom_x;           // + 0x0520
    float bloom_y;           // + 0x0524
} Weapon;

#endif
