#ifndef RENDER_HEADER
#define RENDER_HEADER

#include "Drawing.hpp"

namespace render {

/**
 * Initializes each menu item
 *
 * @param void
 * @return void
 */
void InitializeMenuItems(void);

/**
 * Draw main UI.
 *
 * @param pDevice
 * @return void
 */
void Menu(IDirect3DDevice9* pDevice);

/**
 * TODO
**/
void CreateFont(LPDIRECT3DDEVICE9 pDevice, int size);

struct HackItem {
private: // Variables
    const char* title;
    bool        bEnabled;
public: // Constructors/Destructors
    HackItem(const char* _title)
        : title(_title)
        , bEnabled(false)
    {
    }
    ~HackItem()
    {
    }
public: // Member functions
    const char* Title() const {
        return title;
    }
    bool IsEnabled() const {
        return bEnabled;
    }
public: // Overloaded functions/operators
    bool operator () (void) {
        bEnabled = !bEnabled;
        return bEnabled;
    }
};

struct HackMenu {
private: // Variables
    HackItem*   items;
    unsigned    n_items;
    bool        bMaximized;
public: // Constructors/Destructors
    HackMenu()
        : items()
        , n_items(6)
        , bMaximized(true)
    {
        items = (HackItem *)calloc(n_items, sizeof(HackItem));
        items[0] = HackItem("1: God Mode");
        items[1] = HackItem("2: Ghost Mode");
        items[2] = HackItem("3: Super Weapons");
        items[3] = HackItem("4: Disable Alarms");
        items[4] = HackItem("5: Disable Enemies");
        items[5] = HackItem("6: Unlock All Doors");
    }
    ~HackMenu() {
        free(items);
    }
public: // Overloaded functions
    HackItem& operator [] (unsigned index) {
        return items[index];
    }

    bool operator () (void) {
        bMaximized = !bMaximized;
        return bMaximized;
    }

    bool IsMaximized() const {
        return bMaximized;
    }

};

typedef struct _Resolution {
    int x;
    int y;
} Resolution;

typedef struct _Coordinates {
    int x;
    int y;
} Coordinates;

} // namespace render

#endif // RENDER_HEADER
