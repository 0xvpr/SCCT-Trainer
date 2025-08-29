#include "drawing.hpp"

void draw::draw_border_box(std::int32_t x, std::int32_t y, std::int32_t w, std::int32_t h, std::int32_t thickness, D3DCOLOR color, LPDIRECT3DDEVICE9 d3dDevice) {
     draw::draw_filled_rect(x, y, w, thickness, color, d3dDevice);                 // Top horizontal line
     draw::draw_filled_rect(x, y, thickness, h, color, d3dDevice);                 // Left vertical line
     draw::draw_filled_rect((x + w), y, thickness, h, color, d3dDevice);           // Right vertical line
     draw::draw_filled_rect(x, y + h, w + thickness, thickness, color, d3dDevice); // Bottom horizontal line
}

void draw::draw_filled_rect(std::int32_t x, std::int32_t y, std::int32_t w, std::int32_t h, D3DCOLOR color, LPDIRECT3DDEVICE9 d3dDevice) {
    D3DRECT BarRect = { x, y, x + w, y + h };

    IDirect3DDevice9_Clear(d3dDevice, 1, &BarRect, D3DCLEAR_TARGET | D3DCLEAR_TARGET, color, 0, 0);
}

void draw::draw_text(LPCSTR text, std::int32_t x, std::int32_t y, std::int32_t width, std::int32_t height, D3DCOLOR color, LPD3DXFONT font) {
    RECT rct = { x, y, x + width, y + height };

    font->DrawTextA(nullptr, text, -1, &rct, DT_NOCLIP, color);
}
