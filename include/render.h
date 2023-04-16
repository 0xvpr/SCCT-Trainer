#ifndef _RENDER_H
#define _RENDER_H

#include "d3d9hook.h"
#ifndef __cplusplus
#include <stdbool.h>
#endif // __cplusplus

/**
 * Initializes each menu item
 *
 * @param void
 * @return void
 */
void render_InitializeMenuItems(void);

/**
 * Draw main UI.
 *
 * @param pDevice
 * @return void
 */
void render_Menu(IDirect3DDevice9* pDevice);

/**
 * TODO
**/
void render_CreateFont(LPDIRECT3DDEVICE9 pDevice, int size);

typedef struct _HackMenu
{
    bool bEnabled;
    char name[64];
} HackMenu;

typedef struct _Resolution
{
    int x;
    int y;
} Resolution;

typedef struct _Coordinates
{
    int x;
    int y;
} Coordinates;

#endif /* _RENDER_H */
