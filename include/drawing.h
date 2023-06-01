#ifndef DRAWING_HEADER
#define DRAWING_HEADER

#include "d3d9hook.h"

void drawing_draw_border_box(int x, int y, int w, int h, int thickness, D3DCOLOR color, LPDIRECT3DDEVICE9 d3dDevice);
void drawing_draw_filled_rect(int x, int y, int w, int h, D3DCOLOR color, LPDIRECT3DDEVICE9 d3dDevice);

#endif /* DRAWING_HEADER */
