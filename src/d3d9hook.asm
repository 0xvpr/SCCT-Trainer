; --------------------------------------------------------------------------- ;
;                            Exported Functions                               ;
; --------------------------------------------------------------------------- ;

global          _GetD3D9Device@8

; --------------------------------------------------------------------------- ;
;                            Imported Functions                               ;
; --------------------------------------------------------------------------- ;

extern          _EnumWindows@8
extern          _GetCurrentProcessId@0
extern          _GetWindowThreadProcessId@8
extern          _Direct3DCreate9@4
extern          _memcpy

; --------------------------------------------------------------------------- ;
;                             Local Variables                                 ;
; --------------------------------------------------------------------------- ;

section .data
g_window:       dd 0

; --------------------------------------------------------------------------- ;
;                             Executable Code                                 ;
; --------------------------------------------------------------------------- ;

section .text
_EnumWindowsCallback@8:
    push        ebx                                     
    sub         esp,0x28                                
    mov         ebx,dword [esp+0x30]                    
    lea         eax,[esp+0x1c]                          
    mov         dword [esp+0x4],eax                     
    mov         dword [esp],ebx                         
    call        _GetWindowThreadProcessId@8             
    sub         esp,0x8                                 
    call        _GetCurrentProcessId@0                  
    mov         edx,eax                                 
    mov         eax,0x1                                 
    cmp         edx,dword [esp+0x1c]                    
    jne         callback_exit                           
    mov         dword [g_window],ebx                    
    xor         eax,eax                                 
callback_exit:
    add         esp,0x28                                
    pop         ebx                                     
    ret         0x8                                     
    xchg        ax,ax                                   

GetProcessWindow:
    sub         esp,0x1c                                
    mov         dword [esp+0x4],0x0                     
                                                            
    mov         dword [esp],_EnumWindowsCallback@8      
    mov         dword [g_window],0x0                    
                                                            
    call        _EnumWindows@8                          
    sub         esp,0x8                                 
    mov         eax,[g_window]                          
    add         esp,0x1c                                
    ret                                                 
    xchg        ax,ax                                   

_GetD3D9Device@8:
    push        ebp                                     
    push        edi                                     
    push        esi                                     
    push        ebx                                     
    sub         esp,0x6c                                
    mov         esi,dword [esp+0x80]                    
    test        esi,esi                                 
    je          d3d9_exit                               
    mov         dword [esp],0x20                        
    call        _Direct3DCreate9@4                      
    sub         esp,0x4                                 
    mov         ebx,eax                                 
    test        eax,eax                                 
    je          d3d9_exit                               
    lea         ebp,[esp+0x28]                          
    xor         eax,eax                                 
    mov         ecx,0xe                                 
    mov         edi,ebp                                 
    rep         stosd
    mov         dword [esp+0x24],0x0                    
                                                   
    mov         dword [esp+0x40],0x1                    
                                                   
    lea         edi,[esp+0x24]                          
    call        GetProcessWindow                        
    mov         dword [esp+0x44],eax                    
    mov         edx,dword [ebx]                         
    mov         dword [esp+0x48],0x1                    
                                                        
    mov         dword [esp+0x18],edi                    
    mov         dword [esp+0x14],ebp                    
    mov         dword [esp+0x10],0x20                   
                                                        
    mov         dword [esp+0xc],eax                     
    mov         dword [esp+0x8],0x1                     
                                                        
    mov         dword [esp+0x4],0x0                     
                                                        
    mov         dword [esp],ebx                         
    call        dword [edx+0x40]                        
    sub         esp,0x1c                                
    test        eax,eax                                 
    je          clean_exit                              
    mov         eax,dword [esp+0x48]                    
    xor         ecx,ecx                                 
    test        eax,eax                                 
    mov         eax,dword [ebx]                         
    mov         dword [esp+0x14],ebp                    
    mov         ebp,dword [esp+0x44]                    
    sete        cl                                      
    mov         dword [esp+0x48],ecx                    
    mov         dword [esp+0x18],edi                    
    mov         dword [esp+0x10],0x20                   
                                                        
    mov         dword [esp+0xc],ebp                     
    mov         dword [esp+0x8],0x1                     
                                                        
    mov         dword [esp+0x4],0x0                     
                                                        
    mov         dword [esp],ebx                         
    call        dword [eax+0x40]                        
    sub         esp,0x1c                                
    test        eax,eax                                 
    jne         d3d9_exit                               
clean_exit:
    mov         edi,dword [esp+0x24]                    
    mov         edx,dword [esp+0x84]                    
    mov         ecx,dword [edi]                         
    mov         dword [esp+0x8],edx                     
    mov         dword [esp+0x4],ecx                     
    mov         dword [esp],esi                         
    call        _memcpy                                 
    mov         esi,dword [edi]                         
    mov         dword [esp],edi                         
    call        dword [esi+0x8]                         
    sub         esp,0x4                                 
    mov         eax,dword [ebx]                         
    mov         dword [esp],ebx                         
    call        dword [eax+0x8]                         
    sub         esp,0x4                                 
    add         esp,0x6c                                
    pop         ebx                                     
    pop         esi                                     
    pop         edi                                     
    mov         eax,0x1                                 
    pop         ebp                                     
    ret                                                 
    lea         esi,[esi+0x0]                           
    mov         ebp,dword [ebx]                         
    mov         dword [esp],ebx                         
    call        dword [ebp+0x8]                         
    sub         esp,0x4                                 
d3d9_exit:
    add         esp,0x6c                                
    pop         ebx                                     
    pop         esi                                     
    pop         edi                                     
    xor         eax,eax                                 
    pop         ebp                                     
    ret                                            
    nop                                            
    nop                                            
    nop                                            
