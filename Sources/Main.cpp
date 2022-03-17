/**
 * Author    Malik Booker
 * Created:  August 18, 2021
 * Modified: March 17, 2022
 * 
 * Brief:
 *     SCCT GUI
 * 
 * Disclaimer:
 *     I claim no liability/responsibility
 *     for damage associated with however this code is used.
**/

#include "D3D9Hook.hpp"
#include "Render.hpp"
#include "Events.hpp"
#include "Memory.hpp"

unsigned int total_doors_unlocked = 0;
unsigned int n_entities_changed   = 0;

uintptr_t module_base_addr = 0;

bool bShutdown = false;
bool bInit = false;

void* d3d9Device[119] = { 0 };
unsigned char oEndScene_bytes[7] = { 0 };
tEndScene oEndScene = NULL;
LPDIRECT3DDEVICE9 pD3DDevice = NULL;

HRESULT APIENTRY hkEndScene(LPDIRECT3DDEVICE9 pDevice) {

    if (!bInit) {
        /*render_InitializeMenuItems();*/
        /*render_CreateFont(pDevice, 16);*/

        bInit = true;
    }
    render::Menu(pDevice);

    return oEndScene(pDevice);
}

DWORD WINAPI MainThread(LPVOID lpReserved) {

    (void)lpReserved;
    module_base_addr = (uintptr_t)GetModuleHandle(NULL);

    if (GetD3D9Device(d3d9Device, sizeof(d3d9Device))) {
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpedantic"
        memcpy(oEndScene_bytes, d3d9Device[42], sizeof(oEndScene_bytes));
        oEndScene = (tEndScene)memory::tramp_hook((char *)d3d9Device[42], (char *)hkEndScene, 7);
#pragma GCC diagnostic pop
    }

    while (!(bShutdown = events::HandleKeyboard())) {
        // Main Loop
    }

    (void)memory::patch(d3d9Device[42], oEndScene_bytes, sizeof(oEndScene_bytes));
    FreeLibraryAndExitThread((HMODULE)lpReserved, 0);
    return TRUE;
}

BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved) {

    (void)lpReserved;
    switch (dwReason)
    {
        case DLL_PROCESS_ATTACH:
        {
            DisableThreadLibraryCalls(hInstance);
            CreateThread(0, 0, MainThread, hInstance, 0, 0);
            break;
        }
        case DLL_PROCESS_DETACH:
            break;
        default:
            break;
    }

    return TRUE;
}
