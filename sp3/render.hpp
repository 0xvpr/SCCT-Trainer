#ifndef RENDER_HEADER
#define RENDER_HEADER

#include <d3d9.h>
#include <cstdint>
#include <d3dx9.h>

namespace render {

/**
 * Initializes each menu item
 *
 * @param void
 * @return void
 */
void initialize_menu_items();

/**
 * Draw main UI.
 *
 * @param pDevice
 * @return void
 */
void menu(LPDIRECT3DDEVICE9 pDevice);

struct HackMenu {
    bool         bEnabled;
    char         name[64];
};

struct Resolution {
    std::int32_t x;
    std::int32_t y;
};

struct Coordinates {
    std::int32_t x;
    std::int32_t y;
};

void create_font(LPDIRECT3DDEVICE9);

} // namespace render

#endif /* RENDER_HEADER */
