#include "render.h"
#include "hacks.h"

extern bool bMaximizeMenu;

D3DCOLOR color_LightGrey = D3DCOLOR_ARGB(255, 80, 80, 80);
D3DCOLOR color_DarkGrey  = D3DCOLOR_ARGB(255, 25, 25, 25);
D3DCOLOR color_White     = D3DCOLOR_ARGB(255, 255, 255, 255);
D3DCOLOR color_Black     = D3DCOLOR_ARGB(255, 0, 0, 0);
D3DCOLOR color_Green     = D3DCOLOR_ARGB(255, 10, 200, 10);
D3DCOLOR color_Blue      = D3DCOLOR_ARGB(255, 0, 42, 255);
D3DCOLOR color_Red       = D3DCOLOR_ARGB(255, 255, 0, 0);

Resolution resolution = { 0, 0 };          // TODO: move to 
Coordinates coordinates = { 30, 25 };      // TODO: move to render.c
HackMenu hackMenu[MAX_MENU_ITEMS] = { 0 }; // TODO: move to render.c

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
        draw_DrawFilledRect(coordinates.x, coordinates.y, 140, 100, color_DarkGrey, d3dDevice);
        draw_DrawBorderBox(coordinates.x, coordinates.y, 140, 100, 4, color_Black, d3dDevice);

        // Row one
        int x1 = 20;
        int y1 = 15;
        for (int i = 3; i < MAX_MENU_ITEMS; i++)
        {
            // If hack is on we display the text colour in green
            draw_DrawFilledRect(coordinates.x + x1, coordinates.y + y1, 25, 20, hackMenu[i].bEnabled ? color_Green : color_LightGrey, d3dDevice);
            draw_DrawBorderBox(coordinates.x + x1, coordinates.y + y1, 25, 20, 2, color_Black, d3dDevice);

            //used to position the next item below
            x1 += 40;
        }
        // Row two
        int x2 = 20;
        int y2 = 55;
        for (int i = 0; i < MAX_MENU_ITEMS - 3; i++)
        {
            // If hack is on we display the text colour in green
            draw_DrawFilledRect(coordinates.x + x2, coordinates.y + y2, 25, 20, hackMenu[i].bEnabled ? color_Green : color_LightGrey, d3dDevice);
            draw_DrawBorderBox(coordinates.x + x2, coordinates.y + y2, 25, 20, 2, color_Black, d3dDevice);

            //used to position the next item
            x2 += 40;
        }
    }
    else
    {
        factor = 0.25;
        // Title Template
        draw_DrawFilledRect(30, 20, (int)(factor*140), (int)(factor*100), color_DarkGrey, d3dDevice);
        draw_DrawBorderBox(30, 20, (int)(factor*140), (int)(factor*100), 2, color_Black, d3dDevice);

        // Row one
        int x1 = 35;
        int y1 = 25;
        for (int i = 3; i < MAX_MENU_ITEMS; i++)
        {
            // If hack is on we display the text colour in green
            draw_DrawFilledRect(x1, y1, (int)(factor*20), (int)(factor*20), hackMenu[i].bEnabled ? color_Green : color_LightGrey, d3dDevice);
            draw_DrawBorderBox(x1, y1, (int)(factor*20), (int)(factor*20), 1, color_Black, d3dDevice);

            //used to position the next item below
            x1 += (int)(factor*40);
        }
        // Row two
        int x2 = 35;
        int y2 = 35;
        for (int i = 0; i < MAX_MENU_ITEMS - 3; i++)
        {
            // If hack is on we display the text colour in green
            draw_DrawFilledRect(x2, y2, (int)(factor*20), (int)(factor*20), hackMenu[i].bEnabled ? color_Green : color_LightGrey, d3dDevice);
            draw_DrawBorderBox(x2, y2, (int)(factor*20), (int)(factor*20), 1, color_Black, d3dDevice);

            //used to position the next item
            x2 += (int)(factor*40);
        }
    }
}
