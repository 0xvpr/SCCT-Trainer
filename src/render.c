#include "render.h"
#include "drawing.h"
#include "hacks.h"

int g_maximized = 1;
Resolution g_resolution = { 0, 0 };
Coordinates g_coordinates = { 30, 25 };
HackMenu g_hack_menu[MAX_MENU_ITEMS] = { 0 };

static const D3DCOLOR c_light_grey = D3DCOLOR_ARGB( 255,  80,  80,  80 );
static const D3DCOLOR c_dark_grey  = D3DCOLOR_ARGB( 255,  25,  25,  25 );
static const D3DCOLOR c_black      = D3DCOLOR_ARGB( 255,   0,   0,   0 );
static const D3DCOLOR c_neon_green = D3DCOLOR_ARGB( 255,  10, 200,  10 );

void
WINAPI
render_menu(IDirect3DDevice9* d3dDevice)
{
    g_resolution = *((Resolution *)(0x0009D2A8));

    float factor = 1.0;
    if (g_maximized)
    {
        // Title Template
        drawing_draw_filled_rect(g_coordinates.x, g_coordinates.y, 140, 100, c_dark_grey, d3dDevice);
        drawing_draw_border_box(g_coordinates.x, g_coordinates.y, 140, 100, 4, c_black, d3dDevice);

        // Row one
        int x1 = 20;
        int y1 = 15;
        for (int i = 3; i < MAX_MENU_ITEMS; i++)
        {
            // If hack is on we display the text colour in green
            drawing_draw_filled_rect(g_coordinates.x + x1, g_coordinates.y + y1, 25, 20, g_hack_menu[i].bEnabled ? c_neon_green : c_light_grey, d3dDevice);
            drawing_draw_border_box(g_coordinates.x + x1, g_coordinates.y + y1, 25, 20, 2, c_black, d3dDevice);

            //used to position the next item below
            x1 += 40;
        }
        // Row two
        int x2 = 20;
        int y2 = 55;
        for (int i = 0; i < MAX_MENU_ITEMS - 3; i++)
        {
            // If hack is on we display the text colour in green
            drawing_draw_filled_rect(g_coordinates.x + x2, g_coordinates.y + y2, 25, 20, g_hack_menu[i].bEnabled ? c_neon_green : c_light_grey, d3dDevice);
            drawing_draw_border_box(g_coordinates.x + x2, g_coordinates.y + y2, 25, 20, 2, c_black, d3dDevice);

            //used to position the next item
            x2 += 40;
        }
    }
    else
    {
        factor = 0.25;
        // Title Template
        drawing_draw_filled_rect(30, 20, (int)(factor*140), (int)(factor*100), c_dark_grey, d3dDevice);
        drawing_draw_border_box(30, 20, (int)(factor*140), (int)(factor*100), 2, c_black, d3dDevice);

        // Row one
        int x1 = 35;
        int y1 = 25;
        for (int i = 3; i < MAX_MENU_ITEMS; i++)
        {
            // If hack is on we display the text colour in green
            drawing_draw_filled_rect(x1, y1, (int)(factor*20), (int)(factor*20), g_hack_menu[i].bEnabled ? c_neon_green : c_light_grey, d3dDevice);
            drawing_draw_border_box(x1, y1, (int)(factor*20), (int)(factor*20), 1, c_black, d3dDevice);

            //used to position the next item below
            x1 += (int)(factor*40);
        }
        // Row two
        int x2 = 35;
        int y2 = 35;
        for (int i = 0; i < MAX_MENU_ITEMS - 3; i++)
        {
            // If hack is on we display the text colour in green
            drawing_draw_filled_rect(x2, y2, (int)(factor*20), (int)(factor*20), g_hack_menu[i].bEnabled ? c_neon_green : c_light_grey, d3dDevice);
            drawing_draw_border_box(x2, y2, (int)(factor*20), (int)(factor*20), 1, c_black, d3dDevice);

            //used to position the next item
            x2 += (int)(factor*40);
        }
    }
}
