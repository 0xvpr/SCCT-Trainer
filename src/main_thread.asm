; --------------------------------------------------------------------------- ;
;                              Exported Functions                             ;
; --------------------------------------------------------------------------- ;

global          _MainThread@4

; --------------------------------------------------------------------------- ;
;                              Exported Variables                             ;
; --------------------------------------------------------------------------- ;

global          _g_module_base_addr

; --------------------------------------------------------------------------- ;
;                              Imported Functions                             ;
; --------------------------------------------------------------------------- ;

extern          _GetD3D9Device@8

extern          _VirtualFree@12
extern          _GetModuleHandleA@4
extern          _FreeLibraryAndExitThread@8

extern          _events_handle_keyboard

extern          _memory_tramp_hook
extern          _memory_patch

extern          _render_menu@4

; --------------------------------------------------------------------------- ;
;                                  Variables                                  ;
; --------------------------------------------------------------------------- ;

section .data
_g_module_base_addr: dd 0
_oEndScene:          dd 0

; --------------------------------------------------------------------------- ;
;                               Executable Code                               ;
; --------------------------------------------------------------------------- ;

section .text
_hook_end_scene:
    push        dword [esp + 0x4]
    call        _render_menu@4
    jmp         [_oEndScene]

_MainThread@4:                                      
    push        edi                                     
    push        esi                                     
    push        ebx                                     
    sub         esp,0x200                               
    mov         dword [esp],0x0                         
    call        _GetModuleHandleA@4                     
    sub         esp,0x4                                 
    lea         edx,[esp+0x24]                          
    mov         [_g_module_base_addr], eax              
    xor         eax,eax                                 
    mov         word [esp+0x21],ax                      
    mov         edi,edx                                 
    xor         eax,eax                                 
    mov         ecx,0x77                                
    rep         stosd
    mov         dword [esp+0x4],0x1dc                   
                                                        
    mov         dword [esp],edx                         
    mov         dword [esp+0x1d],0x0                    
                                                        
    mov         byte [esp+0x23],0x0                     
    xor         edi,edi                                 
    call        _GetD3D9Device@8                        
    lea         ebx,[esp+0x1d]                          
    test        eax,eax                                 
    jne         hook                                    
    nop
    nop
    nop
    nop
    nop
    nop                                                 
main_loop:
    call        _events_handle_keyboard                 
    test        eax,eax                                 
    je          main_loop                               
    nop
    nop
    nop
    nop
    nop
    nop
    nop
exit:
    mov         dword [esp+0x8],0x8000                  
                                                        
    mov         dword [esp+0x4],0xc                     
                                                        
    mov         dword [esp],edi                         
    call        _VirtualFree@12                         
    sub         esp,0xc                                 
    mov         eax,dword [esp+0xcc]                    
    mov         dword [esp+0x4],ebx                     
    mov         dword [esp+0x8],0x7                     
                                                        
    mov         dword [esp],eax                         
    call        _memory_patch                           
    mov         ebx,dword [esp+0x210]                   
    mov         dword [esp+0x4],0x0                     
                                                        
    mov         dword [esp],ebx                         
    call        _FreeLibraryAndExitThread@8             
    nop
    nop
    nop
hook:
    mov         edx,dword [esp+0xCC]
    mov         ecx,0x7                                 
    mov         esi,edx                                 
    mov         edi,ebx                                 
    rep         movsb
    mov         dword [esp+0x8],0x7                     
                                                        
    mov         dword [esp+0x4], _hook_end_scene        
                                                        
    mov         dword [esp],edx                         
    call        _memory_tramp_hook                      
    mov         [_oEndScene], eax                       
    mov         edi,eax                                 
    jmp         main_loop                               
    nop                                                 
    nop                                                 
