#include "d3d9hook.h"

static HWND g_window;

BOOL CALLBACK EnumWindowsCallback(HWND handle, LPARAM lParam)
{
    (void)lParam;

    DWORD wndProcId;
    GetWindowThreadProcessId(handle, &wndProcId);

    if (GetCurrentProcessId() != wndProcId)
    {
        return TRUE; // skip to next g_window
    }

    g_window = handle;
    return FALSE; // g_window found abort search
}

HWND GetProcessWindow()
{
    g_window = NULL;
    EnumWindows(EnumWindowsCallback, (LPARAM)NULL);

    return g_window;
}

BOOL GetD3D9Device(void** pTable, size_t Size)
{
    if (!pTable)
    {
        return FALSE;
    }

    IDirect3D9* pD3D = Direct3DCreate9(D3D_SDK_VERSION);

    if (!pD3D)
    {
        return FALSE;
    }

    IDirect3DDevice9* pDummyDevice = NULL;

    // options to create dummy device
    D3DPRESENT_PARAMETERS d3dpp;
    memset(&d3dpp, 0, sizeof(d3dpp));

    d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
    d3dpp.hDeviceWindow = GetProcessWindow();
    d3dpp.Windowed = TRUE;

    HRESULT dummyDeviceCreated = IDirect3D9_CreateDevice(pD3D, D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, d3dpp.hDeviceWindow, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &pDummyDevice);

    if (dummyDeviceCreated != S_OK)
    {
        // may fail in windowed fullscreen mode, trying again with g_windowed mode
        d3dpp.Windowed = !d3dpp.Windowed;
        dummyDeviceCreated = IDirect3D9_CreateDevice(pD3D, D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, d3dpp.hDeviceWindow, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &pDummyDevice);

        if (dummyDeviceCreated != S_OK)
        {
            IDirect3DDevice9_Release(pD3D);
            return FALSE;
        }
    }
    memcpy(pTable, *(void ***)pDummyDevice, Size);

    IDirect3DDevice9_Release(pDummyDevice);
    IDirect3DDevice9_Release(pD3D);
    return TRUE;
}
