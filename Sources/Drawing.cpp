#include "Drawing.hpp"

extern LPD3DXFONT m_font;
extern LPD3DXFONT m_font_small;

void drawing::draw_border_box(int x, int y, int w, int h, int thickness, D3DCOLOR color, LPDIRECT3DDEVICE9 d3dDevice) { 

    drawing::draw_filled_rect(x, y, w, thickness, color, d3dDevice);                 // Top horizontal line
    drawing::draw_filled_rect(x, y, thickness, h, color, d3dDevice);                 // Left vertical line
    drawing::draw_filled_rect((x + w), y, thickness, h, color, d3dDevice);           // Right vertical line
    drawing::draw_filled_rect(x, y + h, w + thickness, thickness, color, d3dDevice); // Bottom horizontal line
}

void drawing::draw_filled_rect(int x, int y, int w, int h, D3DCOLOR color, LPDIRECT3DDEVICE9 d3dDevice) {

    D3DRECT BarRect = { x, y, x + w, y + h };
    d3dDevice->Clear(1, &BarRect, D3DCLEAR_STENCIL | D3DCLEAR_ZBUFFER | D3DCLEAR_TARGET, color, 0, 0);
}

void drawing::draw_text(LPCSTR text, int x, int y, int width, int height, D3DCOLOR color, LPD3DXFONT font) {

    RECT rct = { x, y, x + width, y + height };
    font->DrawTextA(NULL, text, -1, &rct, DT_NOCLIP, color);
}
