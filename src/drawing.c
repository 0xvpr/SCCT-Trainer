#include "drawing.h"

LPD3DXFONT m_font = NULL;
LPD3DXFONT m_font_small = NULL;

const D3DCOLOR colorLightGrey = D3DCOLOR_ARGB(255, 80, 80, 80);
const D3DCOLOR colorDarkGrey  = D3DCOLOR_ARGB(255, 25, 25, 25);
const D3DCOLOR colorWhite     = D3DCOLOR_ARGB(255, 255, 255, 255);
const D3DCOLOR colorBlack     = D3DCOLOR_ARGB(255, 0, 0, 0);
const D3DCOLOR colorGreen     = D3DCOLOR_ARGB(255, 10, 200, 10);
const D3DCOLOR colorBlue      = D3DCOLOR_ARGB(255, 0, 42, 255);
const D3DCOLOR colorRed       = D3DCOLOR_ARGB(255, 255, 0, 0);

void drawing_draw_border_box(int x, int y, int w, int h, int thickness, D3DCOLOR color, LPDIRECT3DDEVICE9 d3dDevice)
{ 
    drawing_draw_filled_rect(x, y, w, thickness, color, d3dDevice);                 // Top horizontal line
    drawing_draw_filled_rect(x, y, thickness, h, color, d3dDevice);                 // Left vertical line
    drawing_draw_filled_rect((x + w), y, thickness, h, color, d3dDevice);           // Right vertical line
    drawing_draw_filled_rect(x, y + h, w + thickness, thickness, color, d3dDevice); // Bottom horizontal line
}

void drawing_draw_filled_rect(int x, int y, int w, int h, D3DCOLOR color, LPDIRECT3DDEVICE9 d3dDevice)
{
    D3DRECT BarRect = { x, y, x + w, y + h };
    IDirect3DDevice9_Clear(d3dDevice, 1, &BarRect, D3DCLEAR_STENCIL | D3DCLEAR_ZBUFFER | D3DCLEAR_TARGET, color, 0, 0);
}

void drawing_draw_text(LPCSTR text, int x, int y, int width, int height, D3DCOLOR color, LPD3DXFONT font)
{
    RECT rct = { x, y, x + width, y + height };
    font->lpVtbl->DrawTextA(font, NULL, text, -1, &rct, DT_NOCLIP, color);
}
