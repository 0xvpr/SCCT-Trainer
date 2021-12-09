#ifndef _D3D9HOOK_H
#define _D3D9HOOK_H

#include <windows.h>
#include <stdbool.h>
#include <d3d9.h>
#include <d3dx9.h>

typedef HRESULT(APIENTRY* tEndScene)(LPDIRECT3DDEVICE9 pDevice);

bool GetD3D9Device(void** pTable, size_t size);

BOOL CALLBACK EnumWindowsCallback(HWND handle, LPARAM lParam);

HWND GetProcessWindow();

#endif /* _D3D9HOOK_H */
