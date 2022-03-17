#include "Render.hpp"
#include "Drawing.hpp"
#include "Hacks.hpp"

using render::HackMenu;
using render::Resolution;
using render::Coordinates;

LPD3DXFONT m_font;
LPD3DXFONT m_font_small;

HackMenu hackMenu;
Resolution resolution{0, 0};
Coordinates coordinates{30, 25};

static constexpr uint32_t d3d9_resolution_address  = 0x0009D2A8;

static constexpr D3DCOLOR color_LightGrey          = D3DCOLOR_ARGB(255,  80,  80,  80);
static constexpr D3DCOLOR color_DarkGrey           = D3DCOLOR_ARGB(255,  25,  25,  25);
static constexpr D3DCOLOR color_White              = D3DCOLOR_ARGB(255, 255, 255, 255);
static constexpr D3DCOLOR color_Black              = D3DCOLOR_ARGB(255,   0,   0,   0);
static constexpr D3DCOLOR color_Green              = D3DCOLOR_ARGB(255,  10, 200,  10);
static constexpr D3DCOLOR color_Blue               = D3DCOLOR_ARGB(255,   0,  42, 255);
static constexpr D3DCOLOR color_Red                = D3DCOLOR_ARGB(255, 255,   0,   0);

void render::Menu(IDirect3DDevice9* d3dDevice) {

    resolution = *((Resolution *)(d3d9_resolution_address));

    float factor = 1.0;
    if (hackMenu.IsMaximized())
    {
        // Title Template
        drawing::draw_filled_rect(coordinates.x, coordinates.y, 140, 100, color_DarkGrey, d3dDevice);
        drawing::draw_border_box(coordinates.x, coordinates.y, 140, 100, 4, color_Black, d3dDevice);

        // Row one
        int x1 = 20;
        int y1 = 15;
        for (unsigned i = 3; i < MAX_MENU_ITEMS; i++)
        {
            // If hack is on we display the text colour in green
            drawing::draw_filled_rect(coordinates.x + x1, coordinates.y + y1, 25, 20, hackMenu[i].IsEnabled() ? color_Green : color_LightGrey, d3dDevice);
            drawing::draw_border_box(coordinates.x + x1, coordinates.y + y1, 25, 20, 2, color_Black, d3dDevice);

            //used to position the next item below
            x1 += 40;
        }
        // Row two
        int x2 = 20;
        int y2 = 55;
        for (unsigned i = 0; i < MAX_MENU_ITEMS - 3; i++)
        {
            // If hack is on we display the text colour in green
            drawing::draw_filled_rect(coordinates.x + x2, coordinates.y + y2, 25, 20, hackMenu[i].IsEnabled() ? color_Green : color_LightGrey, d3dDevice);
            drawing::draw_border_box(coordinates.x + x2, coordinates.y + y2, 25, 20, 2, color_Black, d3dDevice);

            //used to position the next item
            x2 += 40;
        }
    }
    else
    {
        factor = 0.25;
        // Title Template
        drawing::draw_filled_rect(30, 20, (int)(factor*140), (int)(factor*100), color_DarkGrey, d3dDevice);
        drawing::draw_border_box(30, 20, (int)(factor*140), (int)(factor*100), 2, color_Black, d3dDevice);

        // Row one
        int x1 = 35;
        int y1 = 25;
        for (unsigned i = 3; i < MAX_MENU_ITEMS; i++)
        {
            // If hack is on we display the text colour in green
            drawing::draw_filled_rect(x1, y1, (int)(factor*20), (int)(factor*20), hackMenu[i].IsEnabled() ? color_Green : color_LightGrey, d3dDevice);
            drawing::draw_border_box(x1, y1, (int)(factor*20), (int)(factor*20), 1, color_Black, d3dDevice);

            //used to position the next item below
            x1 += (int)(factor*40);
        }
        // Row two
        int x2 = 35;
        int y2 = 35;
        for (unsigned i = 0; i < MAX_MENU_ITEMS - 3; i++)
        {
            // If hack is on we display the text colour in green
            drawing::draw_filled_rect(x2, y2, (int)(factor*20), (int)(factor*20), hackMenu[i].IsEnabled() ? color_Green : color_LightGrey, d3dDevice);
            drawing::draw_border_box(x2, y2, (int)(factor*20), (int)(factor*20), 1, color_Black, d3dDevice);

            //used to position the next item
            x2 += (int)(factor*40);
        }
    }
}

void render::CreateFont(LPDIRECT3DDEVICE9 pDevice, int size) {

    // Draw font
    D3DXCreateFont(
        pDevice,            // LPDIRECT3DDEVICE9 pDevice
        size,               // Height
        0,                  // Width
        FW_BOLD,            // Weight
        0,                  // MIP Levels
        false,              // Italic
        DEFAULT_CHARSET,    // Charset
        OUT_DEFAULT_PRECIS, // Precision
        DEFAULT_QUALITY,    // Quality
        DEFAULT_PITCH | FF_DONTCARE, // Pitch and Family
        "Arial",            // Font name
        &m_font             // LPD3DXFONT
    );
            
}
