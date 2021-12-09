/**
 * @Author    Malik Booker
 * @Created:  August 18, 2021
 * @Modified: September 6, 2021
 * 
 * @Brief:
 * SCCT GUI
 * 
 * @Disclaimer:
 * I claim no liability/responsibility
 * for damage associated with however this code is used.
**/

#include "d3d9hook.h"
#include "render.h"
#include "events.h"
#include "mem.h"

bool bDisableEnemies = false; // Possible unecessary?
bool bDisableAlarms  = false; // Possible unecessary?
bool bSuperWeapons   = false; // Possible unecessary?
bool bMaximizeMenu   = true;  // Possible unecessary?
bool bGhostMode      = false; // Possible unecessary?
bool bShutdown       = false; // Possible unecessary?
bool bGodMode        = false; // Possible unecessary?
bool bInit           = false; // Possible unecessary? 

unsigned int total_doors_unlocked = 0;
unsigned int n_entities_changed   = 0;

uintptr_t module_base_addr = 0;

void* d3d9Device[119] = { 0 };
tEndScene oEndScene = NULL;
LPDIRECT3DDEVICE9 pD3DDevice = NULL;

HRESULT APIENTRY hkEndScene(LPDIRECT3DDEVICE9 pDevice)
{
    if (bInit == false)
    {
        render_InitializeMenuItems();
        bInit = true;
    }

    render_Menu(pDevice);
    events_HandleKeyboard();

    return oEndScene(pDevice);
}

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
DWORD WINAPI MainThread(LPVOID lpReserved)
{
    module_base_addr = (uintptr_t)GetModuleHandle(NULL);

    if (GetD3D9Device(d3d9Device, sizeof(d3d9Device)))
    {
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpedantic"
        oEndScene = (tEndScene)TrampHook((char *)d3d9Device[42], (char *)hkEndScene, 7);
#pragma GCC diagnostic pop
    }

    return TRUE;
}
#pragma GCC diagnostic pop

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
    switch (dwReason)
    {
        case DLL_PROCESS_ATTACH:
            DisableThreadLibraryCalls(hInstance);
            CreateThread(0, 0, MainThread, hInstance, 0, 0);
            break;
        case DLL_PROCESS_DETACH:
            break;
        default:
            break;
    }

    return TRUE;
}
#pragma GCC diagnostic pop
