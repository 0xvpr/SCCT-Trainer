#ifndef RENDER_HEADER
#define RENDER_HEADER

#include "d3d9hook.h"
#include <stdint.h>

/**
 * Draw main UI.
 *
 * @param pDevice
 * @return void
 */
void WINAPI render_menu(IDirect3DDevice9* pDevice);


typedef struct _HackMenu
{
    int bEnabled;
    char name[64];
} HackMenu;

typedef struct _Resolution
{
    uint16_t x;
    uint16_t y;
} Resolution;

typedef struct _Coordinates
{
    uint16_t x;
    uint16_t y;
} Coordinates;

#endif /* RENDER_HEADER */
