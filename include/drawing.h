#ifndef _DRAWING_H
#define _DRAWING_H

#include "d3d9hook.h"


void drawing_draw_border_box(int x, int y, int w, int h, int thickness, D3DCOLOR Colour, LPDIRECT3DDEVICE9 d3dDevice);
void drawing_draw_filled_rect(int x, int y, int w, int h, D3DCOLOR color, LPDIRECT3DDEVICE9 d3dDevice);
void drawing_draw_text(LPCSTR text, int x, int y, int width, int height, D3DCOLOR color, LPD3DXFONT font);

#endif /* DRAWING_H */
