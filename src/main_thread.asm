section     .data
global      _oEndScene
global      _g_module_base_addr

_g_module_base_addr:
    dd      0
_oEndScene:
    dd      0

section     .text
extern      _FreeLibraryAndExitThread@8
extern      _VirtualFree@12
extern      _GetModuleHandleA@4
extern      _GetD3D9Device@8
extern      _events_handle_keyboard
extern      _memory_tramp_hook
extern      _memory_patch
extern      _hook_end_scene

global      _MainThread@4
_MainThread@4:                                      ; 10002480: <_MainThread@4>:
    push    edi                                     ; 10002480: 57                     
    push    esi                                     ; 10002481: 56                     
    push    ebx                                     ; 10002482: 53                     
    sub     esp,0x200                               ; 10002483: 81 ec 00 02 00 00      
    mov     dword [esp],0x0                         ; 10002489: c7 04 24 00 00 00 00   
    call    _GetModuleHandleA@4                     ; 10002490: ff 15 c4 80 00 10      
    sub     esp,0x4                                 ; 10002496: 83 ec 04               
    lea     edx,[esp+0x24]                          ; 10002499: 8d 54 24 24            
    mov     [_g_module_base_addr], eax              ; 1000249d: a3 08 60 00 10         
    xor     eax,eax                                 ; 100024a2: 31 c0                  
    mov     word [esp+0x21],ax                      ; 100024a4: 66 89 44 24 21         
    mov     edi,edx                                 ; 100024a9: 89 d7                  
    xor     eax,eax                                 ; 100024ab: 31 c0                  
    mov     ecx,0x77                                ; 100024ad: b9 77 00 00 00         
    rep stosd   ;dword [edi], eax                   ; 100024b2: f3 ab                  
    mov     dword [esp+0x4],0x1dc                   ; 100024b4: c7 44 24 04 dc 01 00   
                                                    ; 100024bb: 00 
    mov     dword [esp],edx                         ; 100024bc: 89 14 24               
    mov     dword [esp+0x1d],0x0                    ; 100024bf: c7 44 24 1d 00 00 00   
                                                    ; 100024c6: 00 
    mov     byte [esp+0x23],0x0                     ; 100024c7: c6 44 24 23 00         
    xor     edi,edi                                 ; 100024cc: 31 ff                  
    call    _GetD3D9Device@8                        ; 100024ce: e8 fd eb ff ff         
    lea     ebx,[esp+0x1d]                          ; 100024d3: 8d 5c 24 1d            
    test    eax,eax                                 ; 100024d7: 85 c0                  
    jne     hook                                    ; 100024d9: 75 5d                  
    ;lea    esi,[esi+0x0]                           ; 100024db: 8d 74 26 00            
    nop
    nop
    nop
    nop
    nop
    nop                                             ; 100024df: 90                     
main_loop:
    call    _events_handle_keyboard                 ; 100024e0: e8 4b ef ff ff         
    test    eax,eax                                 ; 100024e5: 85 c0                  
    je      main_loop                               ; 100024e7: 74 f7                  
    nop
    nop
    nop
    nop
    nop
    nop
    nop
exit:
    mov     dword [esp+0x8],0x8000                  ; 100024e9: c7 44 24 08 00 80 00   
                                                    ; 100024f0: 00 
    mov     dword [esp+0x4],0xc                     ; 100024f1: c7 44 24 04 0c 00 00   
                                                    ; 100024f8: 00 
    mov     dword [esp],edi                         ; 100024f9: 89 3c 24               
    call    _VirtualFree@12                         ; 100024fc: ff 15 cc 80 00 10      
    sub     esp,0xc                                 ; 10002502: 83 ec 0c               
    mov     eax,dword [esp+0xcc]                    ; 10002505: 8b 84 24 cc 00 00 00   
    mov     dword [esp+0x4],ebx                     ; 1000250c: 89 5c 24 04            
    mov     dword [esp+0x8],0x7                     ; 10002510: c7 44 24 08 07 00 00   
                                                    ; 10002517: 00 
    mov     dword [esp],eax                         ; 10002518: 89 04 24               
    call    _memory_patch                           ; 1000251b: e8 f0 01 00 00         
    mov     ebx,dword [esp+0x210]                   ; 10002520: 8b 9c 24 10 02 00 00   
    mov     dword [esp+0x4],0x0                     ; 10002527: c7 44 24 04 00 00 00   
                                                    ; 1000252e: 00 
    mov     dword [esp],ebx                         ; 1000252f: 89 1c 24               
    call    _FreeLibraryAndExitThread@8             ; 10002532: ff 15 bc 80 00 10      
    nop
    nop
    nop
hook:
    mov     edx,dword [esp+0xcc]                    ; 10002538: 8b 94 24 cc 00 00 00   
    mov     ecx,0x7                                 ; 1000253f: b9 07 00 00 00         
    mov     esi,edx                                 ; 10002544: 89 d6                  
    mov     edi,ebx                                 ; 10002546: 89 df                  
    rep movsb   ;byte [edi], byte [esi]             ; 10002548: f3 a4                  
    mov     dword [esp+0x8],0x7                     ; 1000254a: c7 44 24 08 07 00 00   
                                                    ; 10002551: 00 
    mov     dword [esp+0x4], _hook_end_scene        ; 10002552: c7 44 24 04 50 10 00   
                                                    ; 10002559: 10 
    mov     dword [esp],edx                         ; 1000255a: 89 14 24               
    call    _memory_tramp_hook                      ; 1000255d: e8 9e 02 00 00         
    mov     [_oEndScene], eax                       ; 10002562: a3 04 60 00 10         
    mov     edi,eax                                 ; 10002567: 89 c7                  
    jmp     main_loop                               ; 10002569: e9 72 ff ff ff         
    nop                                             ; 1000256e: 90                     
    nop                                             ; 1000256f: 90                     
