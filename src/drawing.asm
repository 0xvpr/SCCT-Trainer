; --------------------------------------------------------------------------- ;
;                            Exported Functions                               ;
; --------------------------------------------------------------------------- ;

global          _drawing_draw_border_box
global          _drawing_draw_filled_rect

; --------------------------------------------------------------------------- ;
;                             Executable Code                                 ;
; --------------------------------------------------------------------------- ;

section .text
_drawing_draw_border_box:
    push        ebp                             
    push        edi                             
    push        esi                             
    push        ebx                             
    sub         esp, 0x4c                       
    mov         esi, dword [esp+0x60]           
    mov         eax, dword [esp+0x64]           
    mov         edx, dword [esp+0x68]           
    mov         ebx, dword [esp+0x78]           
    mov         ecx, dword [esp+0x74]           
    lea         ebp, [esp+0x30]                 
    add         edx, esi                        
    mov         dword [esp+0x34], eax           
    add         eax, dword [esp+0x70]           
    mov         edi, dword [ebx]                
    mov         dword [esp+0x30], esi           
    mov         dword [esp+0x38], edx           
    mov         dword [esp+0x10], ecx           
    mov         dword [esp+0x8], ebp            
    mov         dword [esp], ebx                
    mov         dword [esp+0x3c], eax           
    mov         dword [esp+0x18], 0x0           
                                                
    mov         dword [esp+0x14], 0x0           
                                                
    mov         dword [esp+0xc], 0x7            
                                                
    mov         dword [esp+0x4], 0x1            
                                                
    mov         dword [esp+0x2c], edx           
    call        dword [edi+0xac]                
    sub         esp, 0x1c                       
    mov         edx, dword [esp+0x70]           
    mov         edi, dword [esp+0x64]           
    mov         eax, dword [esp+0x64]           
    mov         ecx, dword [esp+0x74]           
    add         edi, dword [esp+0x6c]           
    add         edx, esi                        
    mov         dword [esp+0x30], esi           
    mov         dword [esp+0x34], eax           
    mov         dword [esp+0x38], edx           
    mov         eax, dword [ebx]                
    mov         dword [esp+0x3c], edi           
    mov         dword [esp+0x10], ecx           
    mov         dword [esp+0x8], ebp            
    mov         dword [esp], ebx                
    mov         dword [esp+0x18], 0x0           
                                                
    mov         dword [esp+0x14], 0x0           
                                                
    mov         dword [esp+0xc], 0x7            
                                                
    mov         dword [esp+0x4], 0x1            
                                                
    call        dword [eax+0xac]                
    sub         esp, 0x1c                       
    mov         edx, dword [esp+0x2c]           
    mov         eax, dword [esp+0x64]           
    mov         ecx, dword [esp+0x74]           
    mov         dword [esp+0x30], edx           
    add         edx, dword [esp+0x70]           
    mov         dword [esp+0x34], eax           
    mov         dword [esp+0x38], edx           
    mov         eax, dword [ebx]                
    mov         dword [esp+0x3c], edi           
    mov         dword [esp+0x10], ecx           
    mov         dword [esp+0x8], ebp            
    mov         dword [esp], ebx                
    mov         dword [esp+0x18], 0x0           
                                                
    mov         dword [esp+0x14], 0x0           
                                                
    mov         dword [esp+0xc], 0x7            
                                                
    mov         dword [esp+0x4], 0x1            
                                                
    call        dword [eax+0xac]                
    sub         esp, 0x1c                       
    mov         edx, dword [esp+0x68]           
    mov         dword [esp+0x30], esi           
    add         edx, dword [esp+0x70]           
    add         esi, edx                        
    mov         dword [esp+0x38], esi           
    mov         esi, dword [esp+0x70]           
    mov         dword [esp+0x34], edi           
    add         esi, edi                        
    mov         edi, dword [esp+0x74]           
    mov         eax, dword [ebx]                
    mov         dword [esp+0x3c], esi           
    mov         dword [esp+0x10], edi           
    mov         dword [esp+0x8], ebp            
    mov         dword [esp], ebx                
    mov         dword [esp+0x18], 0x0           
                                                
    mov         dword [esp+0x14], 0x0           
                                                
    mov         dword [esp+0xc], 0x7            
                                                
    mov         dword [esp+0x4], 0x1            
                                                
    call        dword [eax+0xac]                
    sub         esp, 0x1c                       
    add         esp, 0x4c                       
    pop         ebx                             
    pop         esi                             
    pop         edi                             
    pop         ebp                             
    ret                                         
    lea         esi, [esi+0x0]                  
    lea         esi, [esi+0x0]                  
                                           
_drawing_draw_filled_rect:
    sub         esp, 0x3c                       
    mov         edx, dword [esp+0x40]           
    mov         eax, dword [esp+0x44]           
    mov         dword [esp+0x20], edx           
    add         edx, dword [esp+0x48]           
    mov         ecx, dword [esp+0x54]           
    mov         dword [esp+0x28], edx           
    mov         edx, dword [esp+0x50]           
    mov         dword [esp+0x24], eax           
    add         eax, dword [esp+0x4c]           
    mov         dword [esp+0x2c], eax           
    mov         eax, dword [ecx]                
    mov         dword [esp+0x10], edx           
    lea         edx, [esp+0x20]                 
    mov         dword [esp+0x18], 0x0           
                                                
    mov         dword [esp+0x14], 0x0           
                                                
    mov         dword [esp+0xc], 0x7            
                                                
    mov         dword [esp+0x8], edx            
    mov         dword [esp+0x4], 0x1            
                                                
    mov         dword [esp], ecx                
    call        dword [eax+0xac]                
    sub         esp, 0x1c                       
    add         esp, 0x3c                       
    ret                                         
    nop                                         
    nop                                         
    nop                                         
    nop                                         
    nop                                         
    nop                                         
    nop                                         
