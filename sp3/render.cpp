#include "render.hpp"
#include "drawing.hpp"
#include "hacks.hpp"

LPD3DXFONT g_font;
bool menu_is_max;

namespace color {
static constexpr D3DCOLOR LightGrey = D3DCOLOR_ARGB(255, 80, 80, 80);
static constexpr D3DCOLOR DarkGrey  = D3DCOLOR_ARGB(255, 25, 25, 25);
//static constexpr D3DCOLOR White     = D3DCOLOR_ARGB(255, 255, 255, 255);
static constexpr D3DCOLOR Black     = D3DCOLOR_ARGB(255, 0, 0, 0);
static constexpr D3DCOLOR Green     = D3DCOLOR_ARGB(255, 10, 200, 10);
//static constexpr D3DCOLOR color::Blue    = D3DCOLOR_ARGB(255, 0, 42, 255);
//static constexpr D3DCOLOR color::Red     = D3DCOLOR_ARGB(255, 255, 0, 0);
} // namespace color

render::Resolution resolution = { 0, 0 };
render::Coordinates coordinates = { 30, 25 };
render::HackMenu hackMenu[MAX_MENU_ITEMS] = {  };

void render::initialize_menu_items() {
    strcpy(hackMenu[GOD_MODE].name,         "1: God Mode");
    strcpy(hackMenu[GHOST_MODE].name,       "2: Ghost Mode");
    strcpy(hackMenu[SUPER_WEAPONS].name,    "3: Super Weapons");
    strcpy(hackMenu[DISABLE_ALARMS].name,   "4: Disable Alarms");
    strcpy(hackMenu[DISABLE_ENEMIES].name,  "5: Disable Enemies");
    strcpy(hackMenu[UNLOCK_ALL_DOORS].name, "6: Unlock All Doors");
}

void render::menu(IDirect3DDevice9* d3dDevice) {
    resolution = *((render::Resolution *)(0x0009D2A8));

    float factor = 1.0;
    if (menu_is_max) {
        // Title Template
        draw::draw_filled_rect(coordinates.x, coordinates.y, 140, 100, color::DarkGrey, d3dDevice);
        draw::draw_border_box(coordinates.x, coordinates.y, 140, 100, 4, color::Black, d3dDevice);

        //TODO: Testing Text
        //if (g_font != NULL) {
            //draw::draw_text("Testing", 140, 20, 10, 10, color::White, g_font);
        //}

        // Row one
        int x1 = 20;
        int y1 = 15;
        for (std::uint32_t i = 3; i < MAX_MENU_ITEMS; ++i) {
            // If hack is on we display the text colour in green
            draw::draw_filled_rect(coordinates.x + x1, coordinates.y + y1, 25, 20, hackMenu[i].bEnabled ? color::Green : color::LightGrey, d3dDevice);
            draw::draw_border_box(coordinates.x + x1, coordinates.y + y1, 25, 20, 2, color::Black, d3dDevice);

            //used to position the next item below
            x1 += 40;
        }
        // Row two
        int x2 = 20;
        int y2 = 55;
        for (std::uint32_t i = 0; i < MAX_MENU_ITEMS - 3; ++i) {
            // If hack is on we display the text colour in green
            draw::draw_filled_rect(coordinates.x + x2, coordinates.y + y2, 25, 20, hackMenu[i].bEnabled ? color::Green : color::LightGrey, d3dDevice);
            draw::draw_border_box(coordinates.x + x2, coordinates.y + y2, 25, 20, 2, color::Black, d3dDevice);

            //used to position the next item
            x2 += 40;
        }
    } else {
        factor = 0.25;
        // Title Template
        draw::draw_filled_rect(30, 20, (int)(factor*140), (int)(factor*100), color::DarkGrey, d3dDevice);
        draw::draw_border_box(30, 20, (int)(factor*140), (int)(factor*100), 2, color::Black, d3dDevice);

        // Row one
        int x1 = 35;
        int y1 = 25;
        for (std::uint32_t i = 3; i < MAX_MENU_ITEMS; ++i)
        {
            // If hack is on we display the text colour in green
            draw::draw_filled_rect(x1, y1, (int)(factor*20), (int)(factor*20), hackMenu[i].bEnabled ? color::Green : color::LightGrey, d3dDevice);
            draw::draw_border_box(x1, y1, (int)(factor*20), (int)(factor*20), 1, color::Black, d3dDevice);

            //used to position the next item below
            x1 += (int)(factor*40);
        }
        // Row two
        int x2 = 35;
        int y2 = 35;
        for (std::uint32_t i = 0; i < MAX_MENU_ITEMS - 3; ++i) {
            // If hack is on we display the text colour in green
            draw::draw_filled_rect(x2, y2, (int)(factor*20), (int)(factor*20), hackMenu[i].bEnabled ? color::Green : color::LightGrey, d3dDevice);
            draw::draw_border_box(x2, y2, (int)(factor*20), (int)(factor*20), 1, color::Black, d3dDevice);

            //used to position the next item
            x2 += (int)(factor*40);
        }
    }
}

void render::create_font(LPDIRECT3DDEVICE9 pDevice, int size) {

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
        &g_font             // LPD3DXFONT
    );
}
