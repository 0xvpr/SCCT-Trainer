; --------------------------------------------------------------------------- ;
;                            Exported Functions                               ;
; --------------------------------------------------------------------------- ;

global          _DllMain@12

; --------------------------------------------------------------------------- ;
;                            Imported Functions                               ;
; --------------------------------------------------------------------------- ;

extern          _DisableThreadLibraryCalls@4
extern          _CreateThread@24
extern          _MainThread@4

; --------------------------------------------------------------------------- ;
;                                Definitions                                  ;
; --------------------------------------------------------------------------- ;

TRUE EQU 1
DLL_PROCESS_ATTACH EQU 1

; --------------------------------------------------------------------------- ;
;                             Executable Code                                 ;
; --------------------------------------------------------------------------- ;

section .text
_DllMain@12:
    cmp         dword [esp + 0x8], DLL_PROCESS_ATTACH
    jne         exit
    push        dword [esp + 0x4]
    call        _DisableThreadLibraryCalls@4
    push        0
    push        0
    push        dword [esp + 0x4]
    push        _MainThread@4
    push        0
    push        0
    call        _CreateThread@24
exit:
    mov         eax, TRUE
    ret         12
