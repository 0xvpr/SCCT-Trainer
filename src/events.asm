; --------------------------------------------------------------------------- ;
;                            Exported Functions                               ;
; --------------------------------------------------------------------------- ;

global          _events_handle_keyboard

; --------------------------------------------------------------------------- ;
;                            External Variables                               ;
; --------------------------------------------------------------------------- ;

extern          _g_hack_menu
extern          _g_maximized
extern          _g_resolution
extern          _g_coordinates

; --------------------------------------------------------------------------- ;
;                            Imported Functions                               ;
; --------------------------------------------------------------------------- ;

extern          _GetAsyncKeyState@4

extern          _hack_test
extern          _hack_no_clip
extern          _hack_god_mode
extern          _hack_ghost_mode
extern          _hack_super_weapons
extern          _hack_disable_alarms
extern          _hack_disable_enemies
extern          _hack_unlock_all_doors

; --------------------------------------------------------------------------- ;
;                             Executable Code                                 ;
; --------------------------------------------------------------------------- ;

section .text
_events_handle_keyboard:                                     
    push        ebx                                              
    sub         esp,0x18                                         
    mov         dword [esp],0x61                                 
    mov         ebx, _GetAsyncKeyState@4                         
    call        ebx                                              
    sub         esp,0x4                                          
    test        al,0x1                                           
    jne         numpad_1                                         
    mov         dword [esp],0x62                                 
    call        ebx                                              
    sub         esp,0x4                                          
    test        al,0x1                                           
    jne         numpad_2                                         
numpad_3_check:
    mov         dword [esp],0x63                                 
    call        ebx                                              
    sub         esp,0x4                                          
    test        al,0x1                                           
    jne         numpad_3                                         
numpad_4_check:
    mov         dword [esp],0x64                                 
    call        ebx                                              
    sub         esp,0x4                                          
    test        al,0x1                                           
    jne         numpad_4                                         
numpad_5_check:
    mov         dword [esp],0x65                                 
    call        ebx                                              
    sub         esp,0x4                                          
    test        al,0x1                                           
    jne         numpad_5                                         
numpad_6_check:
    mov         dword [esp],0x66                                 
    call        ebx                                              
    sub         esp,0x4                                          
    test        al,0x1                                           
    jne         numpad_6                                         
numpad_7_check:
    mov         dword [esp],0x67                                 
    call        ebx                                              
    sub         esp,0x4                                          
    test        al,0x1                                           
    jne         numpad_7                                         
menu_max_q:
    mov         ecx, dword [_g_maximized]                        
    test        ecx,ecx                                          
    jne         menu_minimized                                   
menu_maximized:
    mov         dword [esp],0x71                                 
    call        ebx                                              
    sub         esp,0x4                                          
    test        al,0x1                                           
    je          home_key                                         
    mov         edx,dword [_g_maximized]                         
    xor         eax,eax                                          
    test        edx,edx                                          
    sete        al                                               
    mov         dword [_g_maximized],eax                         
home_key:
    mov         dword [esp],0x24                                 
    call        ebx                                              
    mov         ebx,eax                                          
    sub         esp,0x4                                          
    xor         eax,eax                                          
    test        bx,bx                                            
    jne         unload                                           
    add         esp,0x18                                         
    pop         ebx                                              
    ret                                                          
    lea         esi,[esi+0x0]                                    
    nop
    nop
    nop
    nop
numpad_1:
    mov         edx, dword [_g_hack_menu+0x44*0]                 
    xor         eax,eax                                          
    test        edx,edx                                          
    sete        al                                               
    mov         dword [esp],eax                                  
    mov         [_g_hack_menu+0x44*0],eax                        
    call        _hack_god_mode                                   
    mov         dword [esp],0x62                                 
    call        ebx                                              
    sub         esp,0x4                                          
    test        al,0x1                                           
    je          numpad_3_check                                   
numpad_2:
    mov         ecx, dword [_g_hack_menu+0x44*1]                 
    xor         eax,eax                                          
    test        ecx,ecx                                          
    sete        al                                               
    mov         dword [esp],eax                                  
    mov         [_g_hack_menu+0x44*1],eax                        
    call        _hack_ghost_mode                                 
    mov         dword [esp],0x63                                 
    call        ebx                                              
    sub         esp,0x4                                          
    test        al,0x1                                           
    je          numpad_4_check                                   
numpad_3:
    mov         edx, dword [_g_hack_menu+0x44*2]                 
    xor         eax,eax                                          
    test        edx,edx                                          
    sete        al                                               
    mov         dword [esp],eax                                  
    mov         [_g_hack_menu+0x44*2],eax                        
    call        _hack_super_weapons                              
    mov         dword [esp],0x64                                 
    call        ebx                                              
    sub         esp,0x4                                          
    test        al,0x1                                           
    je          numpad_5_check                                   
numpad_4:
    mov         ecx, dword [_g_hack_menu+0x44*3]                 
    xor         eax,eax                                          
    test        ecx,ecx                                          
    sete        al                                               
    mov         dword [esp],eax                                  
    mov         [_g_hack_menu+0x44*3],eax                        
    call        _hack_disable_alarms                             
    mov         dword [esp],0x65                                 
    call        ebx                                              
    sub         esp,0x4                                          
    test        al,0x1                                           
    je          numpad_6_check                                   
numpad_5:
    mov         edx, dword [_g_hack_menu+0x44*4]                 
    xor         eax,eax                                          
    test        edx,edx                                          
    sete        al                                               
    mov          dword [esp],eax                                 
    mov         [_g_hack_menu+0x44*4],eax                        
    call        _hack_disable_enemies                            
    mov          dword [esp],0x66                                
    call        ebx                                              
    sub         esp,0x4                                          
    test        al,0x1                                           
    je          numpad_7_check                                   
numpad_6:
    call        _hack_unlock_all_doors                           
    mov          dword [esp],0x67                                
    call        ebx                                              
    sub         esp,0x4                                          
    test        al,0x1                                           
    je          menu_max_q                                       
numpad_7:
    call        _hack_test                                       
    mov         ecx, dword [_g_maximized]                        
    test        ecx,ecx                                          
    je          menu_maximized                                   
menu_minimized:
    mov         dword [esp],0x25                                 
    call        ebx                                              
    sub         esp,0x4                                          
    test        al,0x1                                           
    jne         arrow_left                                       
arrow_right_check:
    mov         dword [esp],0x27                                 
    call        ebx                                              
    sub         esp,0x4                                          
    test        al,0x1                                           
    jne         arrow_right                                      
arrow_up_check:
    mov         dword [esp],0x26                                 
    call        ebx                                              
    sub         esp,0x4                                          
    test        al,0x1                                           
    jne         arrow_up                                         
arrow_down_check:
    mov         dword [esp],0x28                                 
    call        ebx                                              
    sub         esp,0x4                                          
    test        al,0x1                                           
    jne         coordinate_check_y                               
f3_check:
    mov         ecx,dword [_g_maximized]                         
    test        ecx,ecx                                          
    je          menu_maximized                                   
    mov         dword [esp],0x72                                 
    call        ebx                                              
    sub         esp,0x4                                          
    test        al,0x1                                           
    je          menu_maximized                                   
    mov         dword [_g_coordinates],0x19001e                  
                                                                 
    jmp         menu_maximized                                   
    lea         esi,[esi+0x0]                                    
    nop                                                          
    nop                                                          
    nop                                                          
    nop                                                          
    nop                                                          
unload:
    mov         dword [esp],0x0                                  
    call        _hack_god_mode                                   
    mov         dword [esp],0x0                                  
    call        _hack_ghost_mode                                 
    mov         dword [esp],0x0                                  
    call        _hack_super_weapons                              
    mov         dword [esp],0x0                                  
    call        _hack_disable_alarms                             
    mov         dword [esp],0x0                                  
    call        _hack_disable_enemies                            
    add         esp,0x18                                         
    mov         eax,0x1                                          
    pop         ebx                                              
    ret                                                          
    lea         esi,[esi+0x0]                                    
    nop
    nop
    nop
    nop
    lea         esi,[esi+0x0]                                    
coordinate_check_y:
    movzx       eax, word [_g_resolution+0x2]                    
    movzx       ecx, word [_g_coordinates+0x2]                   
    sub         eax,0x78                                         
    mov         edx,ecx                                          
    cmp         ecx,eax                                          
    jge         f3_check                                         
    add         edx,0x5                                          
    mov         word [_g_coordinates+0x2],dx                     
    jmp         f3_check                                         
    lea         esi,[esi+0x0]                                    
arrow_up:
    movzx       ecx,word [_g_coordinates+0x2]                    
    cmp         cx,0x1e                                          
    jbe         arrow_down_check                                 
    sub         ecx,0x5                                          
    mov         word [_g_coordinates+0x2],cx                     
    jmp         arrow_down_check                                 
arrow_right:    
    movzx       eax,word [_g_resolution]                         
    movzx       ecx,word [_g_coordinates]                        
    sub         eax,0xaf                                         
    mov         edx,ecx                                          
    cmp         ecx,eax                                          
    jge         arrow_up_check                                   
    add         edx,0x5                                          
    mov         word [_g_coordinates],dx                         
    jmp         arrow_up_check                                   
    lea         esi,[esi+0x0]                                    
    nop
    nop
    nop
    nop
arrow_left:
    movzx       eax,word [_g_coordinates]                        
    cmp         ax,0x23                                          
    jbe         arrow_right_check                                
    sub         eax,0x5                                          
    mov         word [_g_coordinates],ax                         
    jmp         arrow_right_check                                
    nop                                                          
