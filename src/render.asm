; --------------------------------------------------------------------------- ;
;                              Exported Functions                             ;
; --------------------------------------------------------------------------- ;

global          _render_menu@4

; --------------------------------------------------------------------------- ;
;                              Exported Variables                             ;
; --------------------------------------------------------------------------- ;

global          _g_resolution
global          _g_maximized
global          _g_coordinates
global          _g_hack_menu
global          _coordinates_x
global          _coordinates_y

; --------------------------------------------------------------------------- ;
;                              Imported Functions                             ;
; --------------------------------------------------------------------------- ;

extern          _drawing_draw_filled_rect
extern          _drawing_draw_border_box

; --------------------------------------------------------------------------- ;
;                                Local Variables                              ;
; --------------------------------------------------------------------------- ;

section .data
_g_resolution: dd 0
_g_maximized:  dd 1

_g_hack_menu:  times 408 db 0

_g_coordinates:
_coordinates_x: dw 30
_coordinates_y: dw 25

; --------------------------------------------------------------------------- ;
;                                Executable Code                            ;
; --------------------------------------------------------------------------- ;

section .text
_render_menu@4:                                    
    push        ebp                                    
    push        edi                                    
    push        esi                                    
    push        ebx                                    
    sub         esp,0x2c                               
    mov         ecx,[_g_maximized]                     
    mov         eax,ds:0x9d2a8                         
    mov         ebx,dword [esp+0x40]                   
    test        ecx,ecx                                
    mov         [_g_resolution], eax                   
    mov         dword [esp+0x14],ebx                   
    mov         dword [esp+0x10],0xff191919            
                                                       
    je          render_minimized                       
    movzx       ecx, word [_coordinates_y]             
    movzx       edi, word [_coordinates_x]             
    mov         dword [esp+0x4],ecx                    
    mov         dword [esp],edi                        
    mov         dword [esp+0xc],0x64                   
                                                       
    mov         dword [esp+0x8],0x8c                   
                                                       
    mov         edi,0x14                               
    call        _drawing_draw_filled_rect              
    movzx       esi, word [_coordinates_y]             
    movzx       edx, word [_coordinates_x]             
    mov         dword [esp+0x4],esi                    
    mov         dword [esp+0x18],ebx                   
    mov         dword [esp+0x14],0xff000000            
                                                       
    mov         dword [esp+0x10],0x4                   
                                                       
    mov         dword [esp+0xc],0x64                   
                                                       
    mov         dword [esp+0x8],0x8c                   
                                                       
    mov         dword [esp],edx                        
    mov         esi,_g_hack_menu                       
    mov         ebp,esi                                
    call        _drawing_draw_border_box               
top_menu_max:
    cmp         dword [ebp+0xcc],0x1                   
    sbb         eax,eax                                
    movzx       ecx, word [_coordinates_y]             
    movzx       edx, word [_coordinates_x]             
    and         eax,0x458846                           
    add         edx,edi                                
    sub         eax,0xf537f6                           
    add         ecx,0xf                                
    mov         dword [esp+0x10],eax                   
    mov         dword [esp+0x4],ecx                    
    mov         dword [esp],edx                        
    mov         dword [esp+0x14],ebx                   
    mov         dword [esp+0xc],0x14                   
                                                       
    mov         dword [esp+0x8],0x19                   
                                                       
    add         ebp,0x44                               
    call        _drawing_draw_filled_rect              
    movzx       eax, word [_coordinates_y]             
    movzx       ecx, word [_coordinates_x]             
    add         eax,0xf                                
    add         ecx,edi                                
    mov         dword [esp+0x18],ebx                   
    mov         dword [esp+0x14],0xff000000            
                                                       
    mov         dword [esp+0x10],0x2                   
                                                       
    mov         dword [esp+0xc],0x14                   
                                                       
    mov         dword [esp+0x8],0x19                   
                                                       
    mov         dword [esp+0x4],eax                    
    mov         dword [esp],ecx                        
    add         edi,0x28                               
    call        _drawing_draw_border_box               
    cmp         edi,0x8c                               
    jne         top_menu_max                           
    mov         ebp,0x14                               
bottom_menu_max:
    cmp         dword [esi],0x1                        
    sbb         edi,edi                                
    movzx       edx, word [_coordinates_y]             
    movzx       eax, word [_coordinates_x]             
    and         edi,0x458846                           
    add         eax,ebp                                
    add         edx,0x37                               
    sub         edi,0xf537f6                           
    mov         dword [esp+0x10],edi                   
    mov         dword [esp+0x4],edx                    
    mov         dword [esp],eax                        
    mov         dword [esp+0x14],ebx                   
    mov         dword [esp+0xc],0x14                   
                                                       
    mov         dword [esp+0x8],0x19                   
                                                       
    add         esi,0x44                               
    call        _drawing_draw_filled_rect              
    movzx       ecx, word [_coordinates_y]             
    movzx       edi, word [_coordinates_x]             
    add         ecx,0x37                               
    add         edi,ebp                                
    mov         dword [esp+0x18],ebx                   
    mov         dword [esp+0x14],0xff000000            
                                                       
    mov         dword [esp+0x10],0x2                   
                                                       
    mov         dword [esp+0xc],0x14                   
                                                       
    mov         dword [esp+0x8],0x19                   
                                                       
    mov         dword [esp+0x4],ecx                    
    mov         dword [esp],edi                        
    add         ebp,0x28                               
    call        _drawing_draw_border_box               
    cmp         ebp,0x8c                               
    jne         bottom_menu_max                        
not_a_clue:
    add         esp,0x2c                               
    pop         ebx                                    
    pop         esi                                    
    pop         edi                                    
    pop         ebp                                    
    ret         0x4                                    
    xchg        ax,ax                                  
render_minimized:
    mov         dword [esp+0xc],0x19                   
                                                       
    mov         dword [esp+0x8],0x23                   
                                                       
    mov         dword [esp+0x4],0x14                   
                                                       
    mov         dword [esp],0x1e                       
    mov         edi,0x10006000                         
    mov         ebp,edi                                
    call        _drawing_draw_filled_rect              
    mov         dword [esp+0x18],ebx                   
    mov         dword [esp+0x14],0xff000000            
                                                       
    mov         dword [esp+0x10],0x2                   
                                                       
    mov         dword [esp+0xc],0x19                   
                                                       
    mov         dword [esp+0x8],0x23                   
                                                       
    mov         dword [esp+0x4],0x14                   
                                                       
    mov         dword [esp],0x1e                       
    mov         esi,0x23                               
    call        _drawing_draw_border_box               
idek:
    mov         edx,dword [ebp+0xcc]                   
    mov         dword [esp+0x14],ebx                   
    test        edx,edx                                
    je          inactive_color                         
    mov         dword [esp+0x10],0xff0ac80a            
                                                       
jmp_2b52:
    mov         dword [esp],esi                        
    mov         dword [esp+0xc],0x5                    
                                                       
    mov         dword [esp+0x8],0x5                    
                                                       
    mov         dword [esp+0x4],0x19                   
                                                       
    add         ebp,0x44                               
    call        _drawing_draw_filled_rect              
    mov         dword [esp],esi                        
    mov         dword [esp+0x18],ebx                   
    mov         dword [esp+0x14],0xff000000            
                                                       
    mov         dword [esp+0x10],0x1                   
                                                       
    mov         dword [esp+0xc],0x5                    
                                                       
    mov         dword [esp+0x8],0x5                    
                                                       
    mov         dword [esp+0x4],0x19                   
                                                       
    add         esi,0xa                                
    call        _drawing_draw_border_box               
    cmp         esi,0x41                               
    jne         idek                                   
    mov         eax,dword [edi]                        
    mov         ebp,0x23                               
    test        eax,eax                                
    mov         dword [esp+0x14],ebx                   
    je          inactive_color_2                       
jmp_2bc0:
    mov         dword [esp+0x10],0xff0ac80a            
                                                       
jmp_2bc8:
    mov         dword [esp],ebp                        
    mov         dword [esp+0xc],0x5                    
                                                       
    mov         dword [esp+0x8],0x5                    
                                                       
    mov         dword [esp+0x4],0x23                   
                                                       
    add         edi,0x44                               
    call        _drawing_draw_filled_rect              
    mov         dword [esp],ebp                        
    mov         dword [esp+0x18],ebx                   
    mov         dword [esp+0x14],0xff000000            
                                                       
    mov         dword [esp+0x10],0x1                   
                                                       
    mov         dword [esp+0xc],0x5                    
                                                       
    mov         dword [esp+0x8],0x5                    
                                                       
    mov         dword [esp+0x4],0x23                   
                                                       
    add         ebp,0xa                                
    call        _drawing_draw_border_box               
    cmp         ebp,0x41                               
    je          not_a_clue                             
    mov         eax,dword [edi]                        
    mov         dword [esp+0x14],ebx                   
    test        eax,eax                                
    jne         jmp_2bc0                               
inactive_color_2:
    mov         dword [esp+0x10],0xff505050            
                                                   
    jmp         jmp_2bc8                               
    nop                                            
inactive_color:
    mov         dword [esp+0x10],0xff505050            
    jmp         jmp_2b52                               
    nop                                            
    nop                                            
    nop                                            
