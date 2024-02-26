; --------------------------------------------------------------------------- ;
;                            Exported Functions                               ;
; --------------------------------------------------------------------------- ;

global              _hack_god_mode
global              _hack_ghost_mode
global              _hack_super_weapons
global              _hack_disable_alarms
global              _hack_disable_enemies
global              _hack_unlock_all_doors
global              _hack_no_clip
global              _hack_test

; --------------------------------------------------------------------------- ;
;                                Definitions                                  ;
; --------------------------------------------------------------------------- ;

TYPE_NPC            EQU 0x110F88D8
TYPE_DOOR           EQU 0x110FDDD8
TYPE_PLAYER         EQU 0x110E8B50

OFFSET_ALARMS       EQU 0x0009BC61
OFFSET_HEALTH       EQU 0x003F07C8
OFFSET_NOISE        EQU 0x00417E5D
OFFSET_VISIBILITY   EQU 0x0027F12C

; --------------------------------------------------------------------------- ;
;                            Imported Functions                               ;
; --------------------------------------------------------------------------- ;

extern              _VirtualProtect@16

extern              _memory_nop
extern              _memory_patch
extern              _memory_detour
extern              _memory_find_dynamic_address

; --------------------------------------------------------------------------- ;
;                            Imported Variables                               ;
; --------------------------------------------------------------------------- ;

extern              _g_module_base_addr

; --------------------------------------------------------------------------- ;
;                                Variables                                    ;
; --------------------------------------------------------------------------- ;
section     .data
game_world_base:
    dd      0x00A0DFEC
game_world_offsets:
    dw      0x78
    dw      0x5E4

primary_weapons_base:
    dd      0x00A0F434
primary_weapons_offsets:
    dw      0x84
    dw      0x6E0
    dw      0x434

main_ammo_base:
    dd      0x002F9E4A
shotgun_ammo_base:
    dd      0x002FCFF0
sniper_ammo_base:
    dd      0x002FBC58
rapid_fire_base:
    dd      0x00178FA2

recoil_base_1:
    dd      0x002F83BE
recoil_base_2:
    dd      0x002F8409
recoil_base_3:
    dd      0x002F845B
recoil_base_4:
    dd      0x002F855E
recoil_base_5:
    dd      0x002F84D5
recoil_base_6:
    dd      0x002F8578

; --------------------------------------------------------------------------- ;
;                             Local Executable Code                           ;
; --------------------------------------------------------------------------- ;
section     .text
health_original:
    sub     eax, edx
    mov     dword [ebx], eax
    mov     ebx, eax

health_detour:
    cmp     dword [edi], TYPE_PLAYER
    je      skip_player
    xor     eax, eax
    mov     eax, eax
    mov     dword [ebx], eax
    mov     ebx, eax
skip_player:
    mov     eax, dword [esp + 0x14]
    pop     esi
    mov     dword [eax], ebx
    pop     ebx
    pop     ecx
    ret     0x8

visibility_original:
    mov     eax, dword [esi + 0x1518]

noise_original:
    cmp     edi, eax

noise_patch:
    cmp     eax, eax

alarm_original:
    jne     $ + 0x33B

alarm_patch:
    jmp     $ + 0x33B
    nop

main_ammo_original:
    dec     ebx
    dec     edi

shotgun_ammo_original:
    dec     ecx
    mov     dword [edi + 0x41C], ecx
    mov     ecx, dword [edi + 0x3FC]                                        
    dec     eax

shotgun_ammo_patch:
    nop
    mov     dword [edi + 0x41C], ecx
    mov     ecx, dword [edi + 0x3FC]                                        
    nop

sniper_ammo_original:
    dec     eax
    mov     dword [esi + 0x454], eax
    mov     eax, dword [esi + 0x45C]
    dec     eax

sniper_ammo_patch:
    nop
    mov     dword [esi + 0x454], eax
    mov     eax, dword [esi + 0x45C]
    nop

rapid_fire_original:
    jne     $ + 0x49

recoil_original_1:
    fstp    dword [esi + 0x52C]
recoil_original_2:
    fstp    dword [esi + 0x52C]
recoil_original_3:
    fstp    dword [esi + 0x52C]
recoil_original_4:
    fstp    dword [esi + 0x530]
recoil_original_5:
    mov     dword [esi + 0x530], edx
recoil_original_6:
    mov     dword [esi + 0x534], ecx

recoil_patch_1:
    mov     dword [esi + 0x52C], ecx
recoil_patch_2:
    mov     dword [esi + 0x52C], ecx
recoil_patch_3:
    mov     dword [esi + 0x52C], ecx
recoil_patch_4:
    mov     dword [esi + 0x530], ecx
recoil_patch_5:
    mov     dword [esi + 0x530], ecx
recoil_patch_6:
    mov     dword [esi + 0x534], edi

; --------------------------------------------------------------------------- ;
;                            Global Executable Code                           ;
; --------------------------------------------------------------------------- ;
_hack_god_mode:                                     
    sub     esp,0x1c                                
    mov     eax,OFFSET_HEALTH                       
    mov     edx,dword [esp+0x20]                    
    add     eax,dword [_g_module_base_addr]         
    test    edx,edx                                 
    mov     dword [esp+0x8],0x6                     
                                                    
    je      god_mode_disabled                       
god_mode_enabled:
    mov     dword [esp+0x4], health_detour          
                                                    
    mov     dword [esp],eax                         
    call    _memory_detour                          
    add     esp,0x1c                                
    ret                                             
    lea     esi,[esi+0x0]                           
god_mode_disabled:
    mov     dword [esp+0x4], health_original        
                                                    
    mov     dword [esp],eax                         
    call    _memory_patch                           
    add     esp,0x1c                                
    ret                                             
    lea     esi,[esi+0x0]                           
    nop
    nop

_hack_ghost_mode:                                   
    push    ebp                                     
    push    edi                                     
    push    esi                                     
    push    ebx                                     
    sub     esp,0x2c                                
    mov     ebx, dword [_g_module_base_addr]        
    mov     esi, OFFSET_VISIBILITY                  
    mov     eax,dword [esp+0x40]                    
    add     esi,ebx                                 
    add     ebx, OFFSET_NOISE                       
    test    eax,eax                                 
    je      ghost_mode_disabled                     
ghost_mode_enabled:
    lea     ebp,[esp+0x1c]                          
    mov     dword [esp+0xc],ebp                     
    mov     dword [esp],esi                         
    mov     dword [esp+0x8],0x80                    
                                                    
    mov     dword [esp+0x4],0x6                     
                                                    
    mov     edi,_VirtualProtect@16                  
    mov     dword [esp+0x1c],0x0                    
                                                    
    call    edi                                     
    sub     esp,0x10                                
    mov     edx,dword [esp+0x1c]                    
    mov     dword [esi],0x90909090                  
    mov     dword [esi+0x4],0x5d99090               
    mov     dword [esp+0xc],ebp                     
    mov     dword [esp+0x8],edx                     
    mov     dword [esp],esi                         
    mov     dword [esp+0x4],0x6                     
                                                    
    call    edi                                     
    sub     esp,0x10                                
    mov     dword [esp],ebx                         
    mov     dword [esp+0x8],0x2                     
                                                    
    mov     dword [esp+0x4],noise_patch             
                                                    
    call    _memory_patch                           
    add     esp,0x2c                                
    pop     ebx                                     
    pop     esi                                     
    pop     edi                                     
    pop     ebp                                     
    ret                                             
    lea     esi,[esi]                               
    nop
    nop
    nop
    nop
ghost_mode_disabled:
    mov     dword [esp],esi                         
    mov     dword [esp+0x8],0x6                     
                                                    
    mov     dword [esp+0x4],visibility_original     
                                                    
    call    _memory_patch                           
    mov     dword [esp],ebx                         
    mov     dword [esp+0x8],0x2                     
                                                    
    mov     dword [esp+0x4],noise_original          
                                                    
    call    _memory_patch                           
    add     esp,0x2c                                
    pop     ebx                                     
    pop     esi                                     
    pop     edi                                     
    pop     ebp                                     
    ret                                             
    lea     esi,[esi+0x0]                           
    nop
    nop
    nop
    nop

_hack_super_weapons:                                
    push   ebp                                      
    push   edi                                      
    push   esi                                      
    push   ebx                                      
    sub    esp,0x3c                                 
    mov    eax, dword [_g_module_base_addr]         
    mov    ebx, dword [recoil_base_1]               
    mov    esi, dword [recoil_base_2]               
    add    ebx,eax                                  
    mov    dword [esp+0x1c],ebx                     
    mov    ebx, dword [recoil_base_3]               
    add    esi,eax                                  
    add    ebx,eax                                  
    mov    dword [esp+0x20],esi                     
    mov    dword [esp+0x24],ebx                     
    mov    ecx, dword [main_ammo_base]              
    mov    ebp, dword [shotgun_ammo_base]           
    mov    edx, dword [sniper_ammo_base]            
    mov    edi, dword [rapid_fire_base]             
    mov    esi, dword [recoil_base_4]               
    mov    ebx, dword [recoil_base_5]               
    add    edx,eax                                  
    add    ecx,eax                                  
    add    ebp,eax                                  
    add    edi,eax                                  
    add    esi,eax                                  
    add    ebx,eax                                  
    add    eax, dword [recoil_base_6]               
    cmp    dword [esp+0x50],0x0                     
    mov    dword [esp+0x2c],eax                     
    mov    dword [esp+0x28],edx                     
    je     super_weapons_disabled                   
super_weapons_enabled:
    mov    dword [esp],ecx                          
    mov    dword [esp+0x4],0x2                      
                                                    
    call   _memory_nop                              
    mov    eax, dword [esp+0x28]                    
    mov    dword [esp+0x8],0xe                      
                                                    
    mov    dword [esp],eax                          
    mov    dword [esp+0x4], sniper_ammo_patch       
                                                    
    call   _memory_patch                            
    mov    dword [esp],ebp                          
    mov    dword [esp+0x8],0xe                      
                                                    
    mov    dword [esp+0x4], shotgun_ammo_patch      
                                                    
    call   _memory_patch                            
    mov    dword [esp],edi                          
    mov    dword [esp+0x4],0x2                      
                                                    
    call   _memory_nop                              
    mov    ecx, dword [esp+0x1c]                    
    mov    dword [esp+0x8],0x6                      
                                                    
    mov    dword [esp],ecx                          
    mov    dword [esp+0x4], recoil_patch_1          
                                                    
    call   _memory_patch                            
    mov    ebp, dword [esp+0x20]                    
    mov    dword [esp+0x8],0x6                      
                                                    
    mov    dword [esp],ebp                          
    mov    dword [esp+0x4], recoil_patch_2          
                                                    
    call   _memory_patch                            
    mov    edx, dword [esp+0x24]                    
    mov    dword [esp+0x8],0x6                      
                                                    
    mov    dword [esp],edx                          
    mov    dword [esp+0x4], recoil_patch_3          
                                                    
    call   _memory_patch                            
    mov    dword [esp],esi                          
    mov    dword [esp+0x8],0x6                      
                                                    
    mov    dword [esp+0x4], recoil_patch_4          
                                                    
    call   _memory_patch                            
    mov    dword [esp],ebx                          
    mov    dword [esp+0x8],0x6                      
                                                    
    mov    dword [esp+0x4], recoil_patch_5          
                                                    
    call   _memory_patch                            
    mov    esi, dword [esp+0x2c]                    
    mov    dword [esp+0x8],0x6                      
                                                    
    mov    dword [esp],esi                          
    mov    dword [esp+0x4], recoil_patch_6          
                                                    
    call   _memory_patch                            
    add    esp,0x3c                                 
    pop    ebx                                      
    pop    esi                                      
    pop    edi                                      
    pop    ebp                                      
    ret                                             
    lea    esi,[esi+0x0]                            
    nop
    nop
    nop
    nop
    nop
super_weapons_disabled:
    mov    dword [esp],ecx                          
    mov    dword [esp+0x8],0x2                      
                                                    
    mov    dword [esp+0x4], main_ammo_original      
                                                    
    call   _memory_patch                            
    mov    eax, dword [esp+0x28]                    
    mov    dword [esp+0x8],0xe                      
                                                    
    mov    dword [esp],eax                          
    mov    dword [esp+0x4], sniper_ammo_original    
                                                    
    call   _memory_patch                            
    mov    dword [esp],ebp                          
    mov    dword [esp+0x8],0xe                      
                                                    
    mov    dword [esp+0x4], shotgun_ammo_original   
                                                    
    call   _memory_patch                            
    mov    dword [esp],edi                          
    mov    dword [esp+0x8],0x2                      
                                                    
    mov    dword [esp+0x4], rapid_fire_original     
                                                    
    call   _memory_patch                            
    mov    ecx, dword [esp+0x1c]                    
    mov    dword [esp+0x8],0x6                      
                                                    
    mov    dword [esp],ecx                          
    mov    dword [esp+0x4], recoil_original_1       
                                                    
    call   _memory_patch                            
    mov    ebp, dword [esp+0x20]                    
    mov    dword [esp+0x8],0x6                      
                                                    
    mov    dword [esp],ebp                          
    mov    dword [esp+0x4], recoil_original_2       
                                                    
    call   _memory_patch                            
    mov    edx, dword [esp+0x24]                    
    mov    dword [esp+0x8],0x6                      
                                                    
    mov    dword [esp],edx                          
    mov    dword [esp+0x4], recoil_original_3       
                                                    
    call   _memory_patch                            
    mov    dword [esp],esi                          
    mov    dword [esp+0x8],0x6                      
                                                    
    mov    dword [esp+0x4], recoil_original_4       
                                                    
    call   _memory_patch                            
    mov    dword [esp],ebx                          
    mov    dword [esp+0x8],0x6                      
                                                    
    mov    dword [esp+0x4], recoil_original_5       
                                                    
    call   _memory_patch                            
    mov    edi, dword [esp+0x2c]                    
    mov    dword [esp+0x8],0x6                      
                                                    
    mov    dword [esp],edi                          
    mov    dword [esp+0x4], recoil_original_6       
                                                    
    call   _memory_patch                            
    add    esp,0x3c                                 
    pop    ebx                                      
    pop    esi                                      
    pop    edi                                      
    pop    ebp                                      
    ret                                             
    nop
    nop
    nop
    nop

_hack_disable_enemies:                             
    push    ebx
    sub     esp,0x1C                                
    mov     eax, dword [game_world_base]            
    mov     dword [esp+0x8],0x2                    
    add     eax, dword [_g_module_base_addr]     
    mov     dword [esp+0x4], game_world_offsets 
    mov     dword [esp],eax                   
    call    _memory_find_dynamic_address     
    test    eax,eax                         
    jz      disable_enemies_exit
    xor     ecx, ecx
    mov     edx, dword [eax+0x4]                    ; n_entities
    mov     eax, dword [eax]
    xor     dword [esp + 0x24], 0x1                 ; flip bEnabled
disable_enemies_main_loop:
    cmp     ecx,edx
    je      disable_enemies_exit
    lea     ebx, [eax+ecx*0x4]
    mov     ebx, dword [ebx+0x0]
    cmp     dword [ebx], TYPE_NPC                   ; Check type
    jne     not_npc
    imul    edi, dword [esp + 0x24], 0x96           ; !bEnabled * 150
    mov     dword [ebx + 0x420], edi
not_npc:
    inc     ecx
    jmp     disable_enemies_main_loop
disable_enemies_exit:
    xor     eax, eax
    xor     ecx, eax
    add     esp, 0x1c
    pop     ebx
    ret

_hack_unlock_all_doors:                             
    push    ebx
    sub     esp,0x1c                                
    mov     eax, dword [game_world_base]            
    mov     dword [esp+0x8],0x2                    
    add     eax, dword [_g_module_base_addr]     
    mov     dword [esp+0x4], game_world_offsets 
    mov     dword [esp],eax                   
    call    _memory_find_dynamic_address     
    test    eax,eax                         
    jz      unlock_all_doors_exit
    xor     ecx, ecx
    mov     edx, dword [eax+0x4]                    ; n_entities
    mov     eax, dword [eax]
unlock_all_doors_main_loop:
    cmp     ecx,edx
    je      unlock_all_doors_exit
    lea     ebx, [eax+ecx*0x4]
    mov     ebx, dword [ebx+0x0]
    cmp     dword [ebx], TYPE_DOOR                  ; Check type
    jne     not_door
    cmp     dword [ebx + 0x4B8], 0
    jne     not_door
    mov     dword [ebx + 0x4B8], 0x4                ; set door access to 4
not_door:
    inc     ecx
    jmp     unlock_all_doors_main_loop
unlock_all_doors_exit:
    xor     eax, eax
    xor     ecx, eax
    add     esp, 0x1c
    pop     ebx
    ret

_hack_disable_alarms:                               
    sub     esp,0x1c                                
    mov     eax, OFFSET_ALARMS                      
    mov     edx,dword [esp+0x20]                    
    add     eax,dword [_g_module_base_addr]         
    test    edx,edx                                 
    mov     dword [esp+0x8],0x6                     
                                                    
    je      alarms_disabled                         
alarms_enabled:
    mov     dword [esp+0x4],alarm_patch             
                                                    
    mov     dword [esp],eax                         
    call    _memory_patch                           
    add     esp,0x1c                                
    ret                                             
    lea     esi,[esi]                               
    nop
    nop
    nop
    nop
alarms_disabled:
    mov     dword [esp+0x4],alarm_original          
                                                    
    mov     dword [esp],eax                         
    call    _memory_patch                           
    add     esp,0x1c                                
    ret                                             
    lea     esi,[esi]                               
    nop
    nop
    nop
    nop

_hack_no_clip:
    ret
    nop
    nop
    nop

_hack_test:
    ret
    nop
    nop
    nop
