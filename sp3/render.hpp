#ifndef RENDER_HEADER
#define RENDER_HEADER

#include <d3d9.h>

namespace render {

/**
 * Initializes each menu item
 *
 * @param void
 * @return void
 */
void initializemenuitems(void);

/**
 * Draw main UI.
 *
 * @param pDevice
 * @return void
 */
void menu(IDirect3DDevice9* pDevice);

/**
 * TODO
**/
void create_font(LPDIRECT3DDEVICE9 pDevice, int size);

struct HackMenu {
    bool bEnabled;
    char name[64];
};

struct Resolution {
    int x;
    int y;
};

struct Coordinates {
    int x;
    int y;
};

} // namespace render

#endif /* RENDER_HEADER */
