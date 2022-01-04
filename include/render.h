#ifndef _RENDER_H
#define _RENDER_H

#include "drawing.h"

LPD3DXFONT m_font;
LPD3DXFONT m_font_small;

D3DCOLOR color_LightGrey; // = D3DCOLOR_ARGB(255, 80, 80, 80);
D3DCOLOR color_DarkGrey;  // = D3DCOLOR_ARGB(255, 25, 25, 25);
D3DCOLOR color_White;     // = D3DCOLOR_ARGB(255, 255, 255, 255);
D3DCOLOR color_Black;     // = D3DCOLOR_ARGB(255, 0, 0, 0);
D3DCOLOR color_Green;     // = D3DCOLOR_ARGB(255, 10, 200, 10);
D3DCOLOR color_Blue;      // = D3DCOLOR_ARGB(255, 0, 42, 255);
D3DCOLOR color_Red;       // = D3DCOLOR_ARGB(255, 255, 0, 0);

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
