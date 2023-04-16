#include "render.h"
#include "drawing.h"
#include "hacks.h"

extern bool bMaximizeMenu;

extern LPD3DXFONT m_font;
extern LPD3DXFONT m_font_small;

static const D3DCOLOR color_LightGrey = D3DCOLOR_ARGB( 255,  80,  80,  80 );
static const D3DCOLOR color_DarkGrey  = D3DCOLOR_ARGB( 255,  25,  25,  25 );
//static const D3DCOLOR color_White   = D3DCOLOR_ARGB( 255, 255, 255, 255 );
static const D3DCOLOR color_Black     = D3DCOLOR_ARGB( 255,   0,   0,   0 );
static const D3DCOLOR color_Green     = D3DCOLOR_ARGB( 255,  10, 200,  10 );
//static const D3DCOLOR color_Blue    = D3DCOLOR_ARGB( 255,   0,  42, 255 );
//static const D3DCOLOR color_Red     = D3DCOLOR_ARGB( 255, 255,   0,   0 );

Resolution resolution = { 0, 0 };
Coordinates coordinates = { 30, 25 };
HackMenu hackMenu[MAX_MENU_ITEMS] = { 0 };

void render_InitializeMenuItems()
{
    strcpy(hackMenu[GOD_MODE].name, "1: God Mode");
    strcpy(hackMenu[GHOST_MODE].name, "2: Ghost Mode");
    strcpy(hackMenu[SUPER_WEAPONS].name, "3: Super Weapons");
    strcpy(hackMenu[DISABLE_ALARMS].name, "4: Disable Alarms");
    strcpy(hackMenu[DISABLE_ENEMIES].name, "5: Disable Enemies");
    strcpy(hackMenu[UNLOCK_ALL_DOORS].name, "6: Unlock All Doors");
}

void render_Menu(IDirect3DDevice9* d3dDevice)
{
    resolution = *((Resolution *)(0x0009D2A8));

    float factor = 1.0;
    if (bMaximizeMenu)
    {
        // Title Template
        drawing_draw_filled_rect(coordinates.x, coordinates.y, 140, 100, color_DarkGrey, d3dDevice);
        drawing_draw_border_box(coordinates.x, coordinates.y, 140, 100, 4, color_Black, d3dDevice);

        // TODO: Testing Text
        /*if (m_font != NULL)*/
        /*{*/
            /*drawing_DrawText("Testing", 140, 20, color_White, m_font);*/
        /*}*/

        // Row one
        int x1 = 20;
        int y1 = 15;
        for (int i = 3; i < MAX_MENU_ITEMS; i++)
        {
            // If hack is on we display the text colour in green
            drawing_draw_filled_rect(coordinates.x + x1, coordinates.y + y1, 25, 20, hackMenu[i].bEnabled ? color_Green : color_LightGrey, d3dDevice);
            drawing_draw_border_box(coordinates.x + x1, coordinates.y + y1, 25, 20, 2, color_Black, d3dDevice);

            //used to position the next item below
            x1 += 40;
        }
        // Row two
        int x2 = 20;
        int y2 = 55;
        for (int i = 0; i < MAX_MENU_ITEMS - 3; i++)
        {
            // If hack is on we display the text colour in green
            drawing_draw_filled_rect(coordinates.x + x2, coordinates.y + y2, 25, 20, hackMenu[i].bEnabled ? color_Green : color_LightGrey, d3dDevice);
            drawing_draw_border_box(coordinates.x + x2, coordinates.y + y2, 25, 20, 2, color_Black, d3dDevice);

            //used to position the next item
            x2 += 40;
        }
    }
    else
    {
        factor = 0.25;
        // Title Template
        drawing_draw_filled_rect(30, 20, (int)(factor*140), (int)(factor*100), color_DarkGrey, d3dDevice);
        drawing_draw_border_box(30, 20, (int)(factor*140), (int)(factor*100), 2, color_Black, d3dDevice);

        // Row one
        int x1 = 35;
        int y1 = 25;
        for (int i = 3; i < MAX_MENU_ITEMS; i++)
        {
            // If hack is on we display the text colour in green
            drawing_draw_filled_rect(x1, y1, (int)(factor*20), (int)(factor*20), hackMenu[i].bEnabled ? color_Green : color_LightGrey, d3dDevice);
            drawing_draw_border_box(x1, y1, (int)(factor*20), (int)(factor*20), 1, color_Black, d3dDevice);

            //used to position the next item below
            x1 += (int)(factor*40);
        }
        // Row two
        int x2 = 35;
        int y2 = 35;
        for (int i = 0; i < MAX_MENU_ITEMS - 3; i++)
        {
            // If hack is on we display the text colour in green
            drawing_draw_filled_rect(x2, y2, (int)(factor*20), (int)(factor*20), hackMenu[i].bEnabled ? color_Green : color_LightGrey, d3dDevice);
            drawing_draw_border_box(x2, y2, (int)(factor*20), (int)(factor*20), 1, color_Black, d3dDevice);

            //used to position the next item
            x2 += (int)(factor*40);
        }
    }
}

void render_CreateFont(LPDIRECT3DDEVICE9 pDevice, int size) {

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
