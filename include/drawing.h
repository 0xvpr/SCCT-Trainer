#ifndef _DRAWING_H
#define _DRAWING_H

#include "d3d9hook.h"

void draw_DrawBorderBox(int x, int y, int w, int h, int thickness, D3DCOLOR Colour, IDirect3DDevice9* d3dDevice);

void draw_DrawFilledRect(int x, int y, int w, int h, D3DCOLOR color, IDirect3DDevice9* d3dDevice);

void draw_DrawText(LPCSTR TextToDraw, int x, int y, D3DCOLOR Colour, LPD3DXFONT m_font);

#endif /* _DRAWING_H */
