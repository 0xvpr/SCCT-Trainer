/**
 * Created by:      VPR
 * Created:         August 18, 2021
 *
 * Updated by:      VPR
 * Updated:         May 31th, 2023
 * 
 * Brief:           SCCT GUI
 * 
 * Disclaimer:      I claim no liability/responsibility for damages
 *                  associated with however this code is used.
**/

#include "d3d9hook.h"
#include "render.h"
#include "events.h"
#include "mem.h"
#include "assembly.h"

uintptr_t g_module_base_addr = 0;

tEndScene oEndScene = NULL;

HRESULT APIENTRY hook_end_scene(LPDIRECT3DDEVICE9 pDevice)
{
    render_menu(pDevice);

    return oEndScene(pDevice);
}

DWORD
WINAPI
MainThread(HINSTANCE hInstance)
{
    g_module_base_addr = (uintptr_t)GetModuleHandle(NULL);
    void* gateway = NULL;
    uint8_t oEndScene_bytes[7] = { 0 };
    void* d3d9Device[119] = { 0 };

    if (GetD3D9Device(d3d9Device, sizeof(d3d9Device)))
    {
        memcpy(oEndScene_bytes, d3d9Device[42], sizeof(oEndScene_bytes));
        gateway = memory_tramp_hook(d3d9Device[42], (PVOID)hook_end_scene, sizeof(oEndScene_bytes));
        oEndScene = (tEndScene)gateway;
    }

    while (!events_handle_keyboard())
    {
        // Main Loop
    }

    VirtualFree(gateway, sizeof(oEndScene_bytes)+sizeof(char)+sizeof(void *), MEM_RELEASE);
    memory_patch(d3d9Device[42], oEndScene_bytes, sizeof(oEndScene_bytes));
    FreeLibraryAndExitThread(hInstance, 0);
}
