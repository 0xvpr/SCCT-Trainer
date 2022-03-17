#ifndef DRAWING_HEADER
#define DRAWING_HEADER

#include "D3D9Hook.hpp"

namespace drawing {

void draw_border_box(int x, int y, int w, int h, int thickness, D3DCOLOR Colour, LPDIRECT3DDEVICE9 d3dDevice);
void draw_filled_rect(int x, int y, int w, int h, D3DCOLOR color, LPDIRECT3DDEVICE9 d3dDevice);
void draw_text(LPCSTR text, int x, int y, int width, int height, D3DCOLOR color, LPD3DXFONT font);

} // namespace drawing

#endif // DRAWING_HEADER
