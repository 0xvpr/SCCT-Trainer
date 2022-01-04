#ifndef _DRAWING_H
#define _DRAWING_H

#include "d3d9hook.h"

void drawing_draw_border_box(int x, int y, int w, int h, int thickness, D3DCOLOR Colour, LPDIRECT3DDEVICE9 d3dDevice);
void drawing_draw_filled_rect(int x, int y, int w, int h, D3DCOLOR color, LPDIRECT3DDEVICE9 d3dDevice);
void drawing_draw_text(LPCSTR text, int x, int y, int width, int height, D3DCOLOR color, LPD3DXFONT font);

const D3DCOLOR colorLightGrey; // = D3DCOLOR_ARGB(255, 80, 80, 80);
const D3DCOLOR colorDarkGrey; // = D3DCOLOR_ARGB(255, 25, 25, 25);
const D3DCOLOR colorWhite;     // = D3DCOLOR_ARGB(255, 255, 255, 255);
const D3DCOLOR colorBlack;     // = D3DCOLOR_ARGB(255, 0, 0, 0);
const D3DCOLOR colorGreen;     // = D3DCOLOR_ARGB(255, 10, 200, 10);
const D3DCOLOR colorBlue;      // = D3DCOLOR_ARGB(255, 0, 42, 255);
const D3DCOLOR colorRed;       // = D3DCOLOR_ARGB(255, 255, 0, 0);

#endif /* DRAWING_H */
