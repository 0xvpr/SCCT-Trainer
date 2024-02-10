extern          _oEndScene
extern          _render_menu@4

section         .text
global          _hook_end_scene

_hook_end_scene:
    push        dword [ esp + 0x4 ]
    call        _render_menu@4
    jmp         [_oEndScene]
    ;push   ebx
    ;sub    esp,0x18
    ;mov    ebx, dword [esp+0x20]
    ;mov    dword [esp],ebx
    ;call   _render_menu@4
    ;sub    esp,0x4
    ;mov    dword [esp+0x20],ebx
    ;add    esp,0x18
    ;pop    ebx
    ;jmp    dword [_oEndScene]
    ;xchg   esi,esi
    ;xchg   esi,esi
    ;nop
    ;nop
