#include "drawing.h"

void draw_DrawBorderBox(int x, int y, int w, int h, int thickness, D3DCOLOR color, IDirect3DDevice9* d3dDevice)
{
    draw_DrawFilledRect(x, y, w, thickness, color, d3dDevice);                 // Top horizontal line
    draw_DrawFilledRect(x, y, thickness, h, color, d3dDevice);                 // Left vertical line
    draw_DrawFilledRect((x + w), y, thickness, h, color, d3dDevice);           // Right vertical line
    draw_DrawFilledRect(x, y + h, w + thickness, thickness, color, d3dDevice); // Bottom horizontal line
}

void draw_DrawFilledRect(int x, int y, int w, int h, D3DCOLOR color, IDirect3DDevice9* d3dDevice)
{
    D3DRECT BarRect = { x, y, x + w, y + h };
    IDirect3DDevice9_Clear(d3dDevice, 1, &BarRect, D3DCLEAR_TARGET | D3DCLEAR_TARGET, color, 0, 0);
}

void draw_DrawText(LPCSTR TextToDraw, int x, int y, D3DCOLOR color, LPD3DXFONT m_font)
{
    RECT rct = { x - 120, y, x + 120, y + 15 };

    // Possible in theory to draw text but this game won't allow it
    m_font->lpVtbl->DrawTextA(m_font, NULL, TextToDraw, -1, &rct, DT_NOCLIP, color);
}
