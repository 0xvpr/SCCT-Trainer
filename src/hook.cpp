#include "hook.hpp"
#include "detours.h"

#include <cstring>

LPD3DXFONT font;
endScene pEndScene;

HRESULT __stdcall DxHook::HookedEndScene(IDirect3DDevice9* pDevice)
{
    HRESULT result;
    int padding = 2;

    D3DRECT d3dRect = { 0 };
    memset(&d3dRect, 0, sizeof(d3dRect));

    d3dRect.x1 = 100;    // top
    d3dRect.x2 = 300;    // bottom
    d3dRect.y1 = 50;     // left
    d3dRect.y2 = 100;    // right

    pDevice->Clear(1, &d3dRect, D3DCLEAR_TARGET, D3DCOLOR_ARGB(255, 0, 0, 0), 0.0f, 0);
    if (!font)
    {
        D3DXCreateFont(pDevice,                     // IDirect3D9* pDevice
                       16,                          // Height
                       0,                           // Width
                       FW_BOLD,                     // Weight
                       1,                           // Mip Levels
                       0,                           // Italic
                       DEFAULT_CHARSET,             // Character set
                       OUT_DEFAULT_PRECIS,          // Precision
                       DEFAULT_QUALITY,             // Quality
                       DEFAULT_PITCH | FF_DONTCARE, // Pitch and Family
                       "Arial",                     // const char* name
                       &font);                      // LPD3DXFONT font
    }

    RECT textRect;
    SetRect(&textRect,
            d3dRect.x1 + padding,     // top
            d3dRect.y1 + padding,     // left
            d3dRect.x2 - padding,     // bottom
            d3dRect.y2 - padding);    // right

    font->DrawText(NULL,
                   "Hacks Activated: ",
                   -1,
                   &textRect,
                   DT_NOCLIP | DT_LEFT,
                   D3DCOLOR_ARGB(255, 153, 255, 153));

    result = pEndScene(pDevice);
    return result;
}

void DxHook::HookEndScene(void)
{
    IDirect3D9* pD3D = Direct3DCreate9(D3D_SDK_VERSION);
    if (!pD3D)
        return;

    D3DPRESENT_PARAMETERS d3dParams = { 0 };
    memset(&d3dParams, 0, sizeof(d3dParams));

    d3dParams.SwapEffect = D3DSWAPEFFECT_DISCARD;
    d3dParams.hDeviceWindow = GetForegroundWindow();
    d3dParams.Windowed = false;

    IDirect3DDevice9* pDevice = nullptr;

    HRESULT result = pD3D->CreateDevice(D3DADAPTER_DEFAULT,
                                        D3DDEVTYPE_HAL,
                                        d3dParams.hDeviceWindow,
                                        D3DCREATE_SOFTWARE_VERTEXPROCESSING,
                                        &d3dParams,
                                        &pDevice);

    if (FAILED(result) || pDevice == nullptr)
    {
        d3dParams.Windowed = true;
        HRESULT result = pD3D->CreateDevice(D3DADAPTER_DEFAULT,
                                            D3DDEVTYPE_HAL,
                                            d3dParams.hDeviceWindow,
                                            D3DCREATE_SOFTWARE_VERTEXPROCESSING,
                                            &d3dParams,
                                            &pDevice);

        if (FAILED(result) || pDevice == nullptr)
        {
            pD3D->Release();
            return;
        }
    }

    void** vTable = *reinterpret_cast<void***>(pDevice);
    pEndScene = (endScene)DetourFunction((BYTE *)vTable[42],
                                         (BYTE *)DxHook::HookedEndScene);

    pDevice->Release();
    pD3D->Release();
}
