#ifndef _HOOK_HPP
#define _HOOK_HPP

#include <d3d9.h>
#include <d3dx9.h>
#include <windows.h>

extern LPD3DXFONT font;

typedef HRESULT(__stdcall* endScene)(IDirect3DDevice9* pDevice);
extern endScene pEndScene;

class DxHook
{
    public:
        /*
         * HookEndScene
         *
         * @param: void
         * @rtype: void
         */
        static void HookEndScene(void);
        
        /*
         * TODO
         */
        static HRESULT __stdcall HookedEndScene(IDirect3DDevice9* pDevice);
};

#endif
