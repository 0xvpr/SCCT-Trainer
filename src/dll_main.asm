extern      _DisableThreadLibraryCalls@4
extern      _MainThread@4
extern      _CreateThread@24

section     .text
global      _DllMain@12

%define     DLL_PROCESS_ATTACH 1

_DllMain@12:
    cmp     byte [ esp + 0x8 ], DLL_PROCESS_ATTACH
    jne     exit
    push    dword [ esp + 0x4 ]
    call    _DisableThreadLibraryCalls@4
    push    0
    push    0
    push    dword [ esp + 0x4 ]
    push    _MainThread@4
    push    0
    push    0
    call    _CreateThread@24
exit:
    mov     eax, 1
    ret     12
