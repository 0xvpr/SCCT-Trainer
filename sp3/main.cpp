/**
 * Created by:      VPR
 * Created:         August 18, 2021
 *
 * Updated by:      VPR
 * Updated:         December 7th, 2022
 * 
 * Brief:           SCCT GUI
 * 
 * Disclaimer:      I claim no liability/responsibility for damages
 *                  associated with however this code is used.
**/

#include "d3d9hook.hpp"
#include "render.hpp"
#include "events.hpp"
#include "memory.hpp"

bool bDisableEnemies = false; // Possible unecessary?
bool bDisableAlarms  = false; // Possible unecessary?
bool bSuperWeapons   = false; // Possible unecessary?
bool bMaximizeMenu   = true;  // Possible unecessary?
bool bGhostMode      = false; // Possible unecessary?
bool bShutdown       = false; // Possible unecessary?
bool bGodMode        = false; // Possible unecessary?
bool bInit           = false; // Possible unecessary? 

unsigned int        total_doors_unlocked    = 0;
unsigned int        n_entities_changed      = 0;

uintptr_t           module_base_addr        = 0;

void*               d3d9Device[119]         = { 0 };
uint8_t             oEndScene_bytes[7]      = { 0 };
tEndScene           oEndScene               = nullptr;
LPDIRECT3DDEVICE9   pD3DDevice              = nullptr;

HRESULT APIENTRY hkEndScene(LPDIRECT3DDEVICE9 pDevice) {
    if (!bInit) {
        /*render_InitializeMenuItems();*/
        /*render_CreateFont(pDevice, 16);*/

        bInit = true;
    }
    render::menu(pDevice);

    return oEndScene(pDevice);
}

DWORD WINAPI MainThread(HINSTANCE hInstance)
{
    module_base_addr = (uintptr_t)GetModuleHandle(nullptr);

    if (GetD3D9Device(d3d9Device, sizeof(d3d9Device))) {
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpedantic"
        memcpy(oEndScene_bytes, d3d9Device[42], sizeof(oEndScene_bytes));
        oEndScene = (tEndScene)memory::tramp_hook((char *)d3d9Device[42], (char *)hkEndScene, 7);
#pragma GCC diagnostic pop
    }

    while (!(bShutdown = events::handle_keyboard())) {
        // Main Loop
    }

    memory::patch(d3d9Device[42], oEndScene_bytes, sizeof(oEndScene_bytes));
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
