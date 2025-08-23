/**
 * Created by:      VPR
 * Created:         August 18, 2021
 *
 * Updated by:      VPR
 * Updated:         August 8th, 2025
 * 
 * Brief:           dookie code, don't replicate.
 * 
 * Disclaimer:      I claim no liability/responsibility for damages
 *                  associated with however this code is used.
**/

#include "d3d9hook.hpp"
#include "render.hpp"
#include "events.hpp"
#include "memory.hpp"

static bool bInit = false;

std::uint32_t      total_doors_unlocked       = 0;
std::uint32_t      n_entities_changed         = 0;

uintptr_t          module_base_addr           = 0;

void*              d3d9_device[119]           = { 0 };
uint8_t            original_endscene_bytes[7] = { 0 };

d3d9::endscene_t   original_endscene          = nullptr;
LPDIRECT3DDEVICE9  pD3DDevice                 = nullptr;

HRESULT APIENTRY endscene_hook(LPDIRECT3DDEVICE9 pDevice) {
    if (!bInit) {
        //render::initialize_menu_items();
        //render::create_font(pDevice, 16);

        bInit = true;
    }
    
    render::menu(pDevice);
    return original_endscene(pDevice);
}

DWORD WINAPI MainThread(HINSTANCE hInstance) {
    module_base_addr = (uintptr_t)GetModuleHandle(nullptr);

    if (d3d9::get_device(d3d9_device, sizeof(d3d9_device))) {
        memcpy(original_endscene_bytes, d3d9_device[42], sizeof(original_endscene_bytes));
        original_endscene = reinterpret_cast<d3d9::endscene_t>(
            memory::trampoline_hook<sizeof original_endscene_bytes>(
                reinterpret_cast<char *>(d3d9_device[d3d9::render_function_index]),
                reinterpret_cast<char *>(endscene_hook)
            )
        );
    }

    while (!events::handle_keyboard()) {
        // Main Loop
    }

    memory::patch(d3d9_device[42], original_endscene_bytes);
    FreeLibraryAndExitThread(hInstance, 0);
    return TRUE;
}

BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved) {
    UNREFERENCED_PARAMETER(lpReserved);

    switch (dwReason) {
        case DLL_PROCESS_ATTACH:
        {
            DisableThreadLibraryCalls(hInstance);
            CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)MainThread, hInstance, 0, nullptr);
            break;
        }
        default: { break; }
    }

    return TRUE;
}
