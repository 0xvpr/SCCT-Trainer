#include "render.hpp"
#include "drawing.hpp"
#include "hacks.hpp"

bool menu_is_max = true;

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

void render::menu(IDirect3DDevice9* d3d9_device) {
    resolution = *((render::Resolution *)(0x0009D2A8));

    float factor = 1.0;
    if (menu_is_max) {
        // Title Template
        draw::draw_filled_rect(coordinates.x, coordinates.y, 140, 100, color::DarkGrey, d3d9_device);
        draw::draw_border_box(coordinates.x, coordinates.y, 140, 100, 4, color::Black, d3d9_device);

        //TODO: Testing Text
        //if (g_font != NULL) {
            //draw::draw_text("Testing", 140, 20, 10, 10, color::White, g_font);
        //}

        // Row one
        std::int32_t x1 = 20;
        std::int32_t y1 = 15;
        for (std::uint32_t i = 3; i < MAX_MENU_ITEMS; ++i) {
            // If hack is on we display the text colour in green
            draw::draw_filled_rect(coordinates.x + x1, coordinates.y + y1, 25, 20, hackMenu[i].bEnabled ? color::Green : color::LightGrey, d3d9_device);
            draw::draw_border_box(coordinates.x + x1, coordinates.y + y1, 25, 20, 2, color::Black, d3d9_device);

            //used to position the next item below
            x1 += 40;
        }
        // Row two
        std::int32_t x2 = 20;
        std::int32_t y2 = 55;
        for (std::uint32_t i = 0; i < MAX_MENU_ITEMS - 3; ++i) {
            // If hack is on we display the text colour in green
            draw::draw_filled_rect(coordinates.x + x2, coordinates.y + y2, 25, 20, hackMenu[i].bEnabled ? color::Green : color::LightGrey, d3d9_device);
            draw::draw_border_box(coordinates.x + x2, coordinates.y + y2, 25, 20, 2, color::Black, d3d9_device);

            //used to position the next item
            x2 += 40;
        }
    } else {
        factor = 0.25;
        // Title Template
        draw::draw_filled_rect(30, 20, (std::int32_t)(factor*140), (std::int32_t)(factor*100), color::DarkGrey, d3d9_device);
        draw::draw_border_box(30, 20, (std::int32_t)(factor*140), (std::int32_t)(factor*100), 2, color::Black, d3d9_device);

        // Row one
        std::int32_t x1 = 35;
        std::int32_t y1 = 25;
        for (std::uint32_t i = 3; i < MAX_MENU_ITEMS; ++i)
        {
            // If hack is on we display the text colour in green
            draw::draw_filled_rect(x1, y1, (std::int32_t)(factor*20), (std::int32_t)(factor*20), hackMenu[i].bEnabled ? color::Green : color::LightGrey, d3d9_device);
            draw::draw_border_box(x1, y1, (std::int32_t)(factor*20), (std::int32_t)(factor*20), 1, color::Black, d3d9_device);

            //used to position the next item below
            x1 += (std::int32_t)(factor*40);
        }
        // Row two
        std::int32_t x2 = 35;
        std::int32_t y2 = 35;
        for (std::uint32_t i = 0; i < MAX_MENU_ITEMS - 3; ++i) {
            // If hack is on we display the text colour in green
            draw::draw_filled_rect(x2, y2, (std::int32_t)(factor*20), (std::int32_t)(factor*20), hackMenu[i].bEnabled ? color::Green : color::LightGrey, d3d9_device);
            draw::draw_border_box(x2, y2, (std::int32_t)(factor*20), (std::int32_t)(factor*20), 1, color::Black, d3d9_device);

            //used to position the next item
            x2 += (std::int32_t)(factor*40);
        }
    }
}
