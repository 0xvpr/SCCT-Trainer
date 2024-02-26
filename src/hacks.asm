; --------------------------------------------------------------------------- ;
;                            Exported Functions                               ;
; --------------------------------------------------------------------------- ;

global      _hack_god_mode
global      _hack_ghost_mode
global      _hack_super_weapons
global      _hack_disable_alarms
global      _hack_unlock_all_doors

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

extern      _VirtualProtect@16

extern      _memory_nop
extern      _memory_patch
extern      _memory_detour
extern      _memory_find_dynamic_address

; --------------------------------------------------------------------------- ;
;                            Imported Variables                               ;
; --------------------------------------------------------------------------- ;

extern      _g_module_base_addr

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
_hack_god_mode:                                     ; 0001f30:   <_hack_god_mode>
    sub     esp,0x1c                                ; 0001f30:   83 ec 1c                
    mov     eax,OFFSET_HEALTH                       ; 0001f33:   a1 e0 31 00 10          
    mov     edx,dword [esp+0x20]                    ; 0001f38:   8b 54 24 20             
    add     eax,dword [_g_module_base_addr]         ; 0001f3c:   03 05 04 30 00 10       
    test    edx,edx                                 ; 0001f42:   85 d2                   
    mov     dword [esp+0x8],0x6                     ; 0001f44:   c7 44 24 08 06 00 00    
                                                    ; 0001f4b:   00 
    je      god_mode_disabled                       ; 0001f4c:   74 1a                   
god_mode_enabled:
    mov     dword [esp+0x4], health_detour          ; 0001f4e:   c7 44 24 04 e0 13 00    
                                                    ; 0001f55:   10 
    mov     dword [esp],eax                         ; 0001f56:   89 04 24                
    call    _memory_detour                          ; 0001f59:   e8 a9 f7 ff ff          
    add     esp,0x1c                                ; 0001f5e:   83 c4 1c                
    ret                                             ; 0001f61:   c3                      
    lea     esi,[esi+0x0]                           ; 0001f62:   8d b6 00 00 00 00       
god_mode_disabled:
    mov     dword [esp+0x4], health_original        ; 0001f68:   c7 44 24 04 d4 40 00    
                                                    ; 0001f6f:   10 
    mov     dword [esp],eax                         ; 0001f70:   89 04 24                
    call    _memory_patch                           ; 0001f73:   e8 27 f7 ff ff          
    add     esp,0x1c                                ; 0001f78:   83 c4 1c                
    ret                                             ; 0001f7b:   c3                      
    lea     esi,[esi+0x0]                           ; 0001f7c:   8d 74 26 00             
    nop
    nop

_hack_ghost_mode:                                   ; 10001f80:   <_hack_ghost_mode>
    push    ebp                                     ; 10001f80:   55                     
    push    edi                                     ; 10001f81:   57                     
    push    esi                                     ; 10001f82:   56                     
    push    ebx                                     ; 10001f83:   53                     
    sub     esp,0x2c                                ; 10001f84:   83 ec 2c               
    mov     ebx, dword [_g_module_base_addr]        ; 10001f87:   8b 1d 04 30 00 10      
    mov     esi, OFFSET_VISIBILITY                  ; 10001f8d:   8b 35 e8 31 00 10      
    mov     eax,dword [esp+0x40]                    ; 10001f93:   8b 44 24 40            
    add     esi,ebx                                 ; 10001f97:   01 de                  
    add     ebx, OFFSET_NOISE                       ; 10001f99:   03 1d e4 31 00 10      
    test    eax,eax                                 ; 10001f9f:   85 c0                  
    je      ghost_mode_disabled                     ; 10001fa1:   74 7d                  
ghost_mode_enabled:
    lea     ebp,[esp+0x1c]                          ; 10001fa3:   8d 6c 24 1c            
    mov     dword [esp+0xc],ebp                     ; 10001fa7:   89 6c 24 0c            
    mov     dword [esp],esi                         ; 10001fab:   89 34 24               
    mov     dword [esp+0x8],0x80                    ; 10001fae:   c7 44 24 08 80 00 00   
                                                    ; 10001fb5:   00 
    mov     dword [esp+0x4],0x6                     ; 10001fb6:   c7 44 24 04 06 00 00   
                                                    ; 10001fbd:   00 
    mov     edi,_VirtualProtect@16                  ; 10001fbe:   8b 3d d0 70 00 10      
    mov     dword [esp+0x1c],0x0                    ; 10001fc4:   c7 44 24 1c 00 00 00   
                                                    ; 10001fcb:   00 
    call    edi                                     ; 10001fcc:   ff d7                  
    sub     esp,0x10                                ; 10001fce:   83 ec 10               
    mov     edx,dword [esp+0x1c]                    ; 10001fd1:   8b 54 24 1c            
    mov     dword [esi],0x90909090                  ; 10001fd5:   c7 06 90 90 90 90      
    mov     dword [esi+0x4],0x5d99090               ; 10001fdb:   c7 46 04 90 90 d9 05   
    mov     dword [esp+0xc],ebp                     ; 10001fe2:   89 6c 24 0c            
    mov     dword [esp+0x8],edx                     ; 10001fe6:   89 54 24 08            
    mov     dword [esp],esi                         ; 10001fea:   89 34 24               
    mov     dword [esp+0x4],0x6                     ; 10001fed:   c7 44 24 04 06 00 00   
                                                    ; 10001ff4:   00 
    call    edi                                     ; 10001ff5:   ff d7                  
    sub     esp,0x10                                ; 10001ff7:   83 ec 10               
    mov     dword [esp],ebx                         ; 10001ffa:   89 1c 24               
    mov     dword [esp+0x8],0x2                     ; 10001ffd:   c7 44 24 08 02 00 00   
                                                    ; 10002004:   00 
    mov     dword [esp+0x4],noise_patch             ; 10002005:   c7 44 24 04 c8 40 00   
                                                    ; 1000200c:   10 
    call    _memory_patch                           ; 1000200d:   e8 8d f6 ff ff         
    add     esp,0x2c                                ; 10002012:   83 c4 2c               
    pop     ebx                                     ; 10002015:   5b                     
    pop     esi                                     ; 10002016:   5e                     
    pop     edi                                     ; 10002017:   5f                     
    pop     ebp                                     ; 10002018:   5d                     
    ret                                             ; 10002019:   c3                     
    lea     esi,[esi]                               ; 1000201a:   8d b6 00 00 00 00      
    nop
    nop
    nop
    nop
ghost_mode_disabled:
    mov     dword [esp],esi                         ; 10002020:   89 34 24               
    mov     dword [esp+0x8],0x6                     ; 10002023:   c7 44 24 08 06 00 00   
                                                    ; 1000202a:   00 
    mov     dword [esp+0x4],visibility_original     ; 1000202b:   c7 44 24 04 cc 40 00   
                                                    ; 10002032:   10 
    call    _memory_patch                           ; 10002033:   e8 67 f6 ff ff         
    mov     dword [esp],ebx                         ; 10002038:   89 1c 24               
    mov     dword [esp+0x8],0x2                     ; 1000203b:   c7 44 24 08 02 00 00   
                                                    ; 10002042:   00 
    mov     dword [esp+0x4],noise_original          ; 10002043:   c7 44 24 04 ca 40 00   
                                                    ; 1000204a:   10 
    call    _memory_patch                           ; 1000204b:   e8 4f f6 ff ff         
    add     esp,0x2c                                ; 10002050:   83 c4 2c               
    pop     ebx                                     ; 10002053:   5b                     
    pop     esi                                     ; 10002054:   5e                     
    pop     edi                                     ; 10002055:   5f                     
    pop     ebp                                     ; 10002056:   5d                     
    ret                                             ; 10002057:   c3                     
    lea     esi,[esi+0x0]                           ; 10002058:   8d b4 26 00 00 00 00   
    nop
    nop
    nop
    nop

_hack_super_weapons:                                ; 10002130:   <_hack_super_weapons>
    push   ebp                                      ; 10002130:   55                      
    push   edi                                      ; 10002131:   57                      
    push   esi                                      ; 10002132:   56                      
    push   ebx                                      ; 10002133:   53                      
    sub    esp,0x3c                                 ; 10002134:   83 ec 3c                
    mov    eax, dword [_g_module_base_addr]         ; 10002137:   a1 0c 30 00 10          
    mov    ebx, dword [recoil_base_1]               ; 1000213c:   8b 1d b8 31 00 10       
    mov    esi, dword [recoil_base_2]               ; 10002142:   8b 35 bc 31 00 10       
    add    ebx,eax                                  ; 10002148:   01 c3                   
    mov    dword [esp+0x1c],ebx                     ; 1000214a:   89 5c 24 1c             
    mov    ebx, dword [recoil_base_3]               ; 1000214e:   8b 1d c0 31 00 10       
    add    esi,eax                                  ; 10002154:   01 c6                   
    add    ebx,eax                                  ; 10002156:   01 c3                   
    mov    dword [esp+0x20],esi                     ; 10002158:   89 74 24 20             
    mov    dword [esp+0x24],ebx                     ; 1000215c:   89 5c 24 24             
    mov    ecx, dword [main_ammo_base]              ; 10002160:   8b 0d e0 31 00 10       
    mov    ebp, dword [shotgun_ammo_base]           ; 10002166:   8b 2d dc 31 00 10       
    mov    edx, dword [sniper_ammo_base]            ; 1000216c:   8b 15 d8 31 00 10       
    mov    edi, dword [rapid_fire_base]             ; 10002172:   8b 3d d4 31 00 10       
    mov    esi, dword [recoil_base_4]               ; 10002178:   8b 35 c4 31 00 10       
    mov    ebx, dword [recoil_base_5]               ; 1000217e:   8b 1d c8 31 00 10       
    add    edx,eax                                  ; 10002184:   01 c2                   
    add    ecx,eax                                  ; 10002186:   01 c1                   
    add    ebp,eax                                  ; 10002188:   01 c5                   
    add    edi,eax                                  ; 1000218a:   01 c7                   
    add    esi,eax                                  ; 1000218c:   01 c6                   
    add    ebx,eax                                  ; 1000218e:   01 c3                   
    add    eax, dword [recoil_base_6]               ; 10002190:   03 05 cc 31 00 10       
    cmp    dword [esp+0x50],0x0                     ; 10002196:   83 7c 24 50 00          
    mov    dword [esp+0x2c],eax                     ; 1000219b:   89 44 24 2c             
    mov    dword [esp+0x28],edx                     ; 1000219f:   89 54 24 28             
    je     super_weapons_disabled                   ; 100021a3:   0f 84 ff 00 00 00       
    mov    dword [esp],ecx                          ; 100021a9:   89 0c 24                
    mov    dword [esp+0x4],0x2                      ; 100021ac:   c7 44 24 04 02 00 00    
                                                    ; 100021b3:   00 
    call   _memory_nop                              ; 100021b4:   e8 ee f9 ff ff          
    mov    eax, dword [esp+0x28]                    ; 100021b9:   8b 44 24 28             
    mov    dword [esp+0x8],0xe                      ; 100021bd:   c7 44 24 08 0e 00 00    
                                                    ; 100021c4:   00 
    mov    dword [esp],eax                          ; 100021c5:   89 04 24                
    mov    dword [esp+0x4], sniper_ammo_patch       ; 100021c8:   c7 44 24 04 88 40 00    
                                                    ; 100021cf:   10 
    call   _memory_patch                            ; 100021d0:   e8 3a fa ff ff          
    mov    dword [esp],ebp                          ; 100021d5:   89 2c 24                
    mov    dword [esp+0x8],0xe                      ; 100021d8:   c7 44 24 08 0e 00 00    
                                                    ; 100021df:   00 
    mov    dword [esp+0x4], shotgun_ammo_patch      ; 100021e0:   c7 44 24 04 a8 40 00    
                                                    ; 100021e7:   10 
    call   _memory_patch                            ; 100021e8:   e8 22 fa ff ff          
    mov    dword [esp],edi                          ; 100021ed:   89 3c 24                
    mov    dword [esp+0x4],0x2                      ; 100021f0:   c7 44 24 04 02 00 00    
                                                    ; 100021f7:   00 
    call   _memory_nop                              ; 100021f8:   e8 aa f9 ff ff          
    mov    ecx, dword [esp+0x1c]                    ; 100021fd:   8b 4c 24 1c             
    mov    dword [esp+0x8],0x6                      ; 10002201:   c7 44 24 08 06 00 00    
                                                    ; 10002208:   00 
    mov    dword [esp],ecx                          ; 10002209:   89 0c 24                
    mov    dword [esp+0x4], recoil_patch_1          ; 1000220c:   c7 44 24 04 20 40 00    
                                                    ; 10002213:   10 
    call   _memory_patch                            ; 10002214:   e8 f6 f9 ff ff          
    mov    ebp, dword [esp+0x20]                    ; 10002219:   8b 6c 24 20             
    mov    dword [esp+0x8],0x6                      ; 1000221d:   c7 44 24 08 06 00 00    
                                                    ; 10002224:   00 
    mov    dword [esp],ebp                          ; 10002225:   89 2c 24                
    mov    dword [esp+0x4], recoil_patch_2          ; 10002228:   c7 44 24 04 26 40 00    
                                                    ; 1000222f:   10 
    call   _memory_patch                            ; 10002230:   e8 da f9 ff ff          
    mov    edx, dword [esp+0x24]                    ; 10002235:   8b 54 24 24             
    mov    dword [esp+0x8],0x6                      ; 10002239:   c7 44 24 08 06 00 00    
                                                    ; 10002240:   00 
    mov    dword [esp],edx                          ; 10002241:   89 14 24                
    mov    dword [esp+0x4], recoil_patch_3          ; 10002244:   c7 44 24 04 2c 40 00    
                                                    ; 1000224b:   10 
    call   _memory_patch                            ; 1000224c:   e8 be f9 ff ff          
    mov    dword [esp],esi                          ; 10002251:   89 34 24                
    mov    dword [esp+0x8],0x6                      ; 10002254:   c7 44 24 08 06 00 00    
                                                    ; 1000225b:   00 
    mov    dword [esp+0x4], recoil_patch_4          ; 1000225c:   c7 44 24 04 32 40 00    
                                                    ; 10002263:   10 
    call   _memory_patch                            ; 10002264:   e8 a6 f9 ff ff          
    mov    dword [esp],ebx                          ; 10002269:   89 1c 24                
    mov    dword [esp+0x8],0x6                      ; 1000226c:   c7 44 24 08 06 00 00    
                                                    ; 10002273:   00 
    mov    dword [esp+0x4], recoil_patch_5          ; 10002274:   c7 44 24 04 38 40 00    
                                                    ; 1000227b:   10 
    call   _memory_patch                            ; 1000227c:   e8 8e f9 ff ff          
    mov    esi, dword [esp+0x2c]                    ; 10002281:   8b 74 24 2c             
    mov    dword [esp+0x8],0x6                      ; 10002285:   c7 44 24 08 06 00 00    
                                                    ; 1000228c:   00 
    mov    dword [esp],esi                          ; 1000228d:   89 34 24                
    mov    dword [esp+0x4], recoil_patch_6          ; 10002290:   c7 44 24 04 3e 40 00    
                                                    ; 10002297:   10 
    call   _memory_patch                            ; 10002298:   e8 72 f9 ff ff          
    add    esp,0x3c                                 ; 1000229d:   83 c4 3c                
    pop    ebx                                      ; 100022a0:   5b                      
    pop    esi                                      ; 100022a1:   5e                      
    pop    edi                                      ; 100022a2:   5f                      
    pop    ebp                                      ; 100022a3:   5d                      
    ret                                             ; 100022a4:   c3                      
    lea    esi,[esi+0x0]                            ; 100022a5:   8d 76 00                
    nop
    nop
    nop
    nop
    nop
super_weapons_disabled:
    mov    dword [esp],ecx                          ; 100022a8:   89 0c 24                
    mov    dword [esp+0x8],0x2                      ; 100022ab:   c7 44 24 08 02 00 00    
                                                    ; 100022b2:   00 
    mov    dword [esp+0x4], main_ammo_original      ; 100022b3:   c7 44 24 04 c6 40 00    
                                                    ; 100022ba:   10 
    call   _memory_patch                            ; 100022bb:   e8 4f f9 ff ff          
    mov    eax, dword [esp+0x28]                    ; 100022c0:   8b 44 24 28             
    mov    dword [esp+0x8],0xe                      ; 100022c4:   c7 44 24 08 0e 00 00    
                                                    ; 100022cb:   00 
    mov    dword [esp],eax                          ; 100022cc:   89 04 24                
    mov    dword [esp+0x4], sniper_ammo_original    ; 100022cf:   c7 44 24 04 98 40 00    
                                                    ; 100022d6:   10 
    call   _memory_patch                            ; 100022d7:   e8 33 f9 ff ff          
    mov    dword [esp],ebp                          ; 100022dc:   89 2c 24                
    mov    dword [esp+0x8],0xe                      ; 100022df:   c7 44 24 08 0e 00 00    
                                                    ; 100022e6:   00 
    mov    dword [esp+0x4], shotgun_ammo_original   ; 100022e7:   c7 44 24 04 b8 40 00    
                                                    ; 100022ee:   10 
    call   _memory_patch                            ; 100022ef:   e8 1b f9 ff ff          
    mov    dword [esp],edi                          ; 100022f4:   89 3c 24                
    mov    dword [esp+0x8],0x2                      ; 100022f7:   c7 44 24 08 02 00 00    
                                                    ; 100022fe:   00 
    mov    dword [esp+0x4], rapid_fire_original     ; 100022ff:   c7 44 24 04 84 40 00    
                                                    ; 10002306:   10 
    call   _memory_patch                            ; 10002307:   e8 03 f9 ff ff          
    mov    ecx, dword [esp+0x1c]                    ; 1000230c:   8b 4c 24 1c             
    mov    dword [esp+0x8],0x6                      ; 10002310:   c7 44 24 08 06 00 00    
                                                    ; 10002317:   00 
    mov    dword [esp],ecx                          ; 10002318:   89 0c 24                
    mov    dword [esp+0x4], recoil_original_1       ; 1000231b:   c7 44 24 04 60 40 00    
                                                    ; 10002322:   10 
    call   _memory_patch                            ; 10002323:   e8 e7 f8 ff ff          
    mov    ebp, dword [esp+0x20]                    ; 10002328:   8b 6c 24 20             
    mov    dword [esp+0x8],0x6                      ; 1000232c:   c7 44 24 08 06 00 00    
                                                    ; 10002333:   00 
    mov    dword [esp],ebp                          ; 10002334:   89 2c 24                
    mov    dword [esp+0x4], recoil_original_2       ; 10002337:   c7 44 24 04 66 40 00    
                                                    ; 1000233e:   10 
    call   _memory_patch                            ; 1000233f:   e8 cb f8 ff ff          
    mov    edx, dword [esp+0x24]                    ; 10002344:   8b 54 24 24             
    mov    dword [esp+0x8],0x6                      ; 10002348:   c7 44 24 08 06 00 00    
                                                    ; 1000234f:   00 
    mov    dword [esp],edx                          ; 10002350:   89 14 24                
    mov    dword [esp+0x4], recoil_original_3       ; 10002353:   c7 44 24 04 6c 40 00    
                                                    ; 1000235a:   10 
    call   _memory_patch                            ; 1000235b:   e8 af f8 ff ff          
    mov    dword [esp],esi                          ; 10002360:   89 34 24                
    mov    dword [esp+0x8],0x6                      ; 10002363:   c7 44 24 08 06 00 00    
                                                    ; 1000236a:   00 
    mov    dword [esp+0x4], recoil_original_4       ; 1000236b:   c7 44 24 04 72 40 00    
                                                    ; 10002372:   10 
    call   _memory_patch                            ; 10002373:   e8 97 f8 ff ff          
    mov    dword [esp],ebx                          ; 10002378:   89 1c 24                
    mov    dword [esp+0x8],0x6                      ; 1000237b:   c7 44 24 08 06 00 00    
                                                    ; 10002382:   00 
    mov    dword [esp+0x4], recoil_original_5       ; 10002383:   c7 44 24 04 78 40 00    
                                                    ; 1000238a:   10 
    call   _memory_patch                            ; 1000238b:   e8 7f f8 ff ff          
    mov    edi, dword [esp+0x2c]                    ; 10002390:   8b 7c 24 2c             
    mov    dword [esp+0x8],0x6                      ; 10002394:   c7 44 24 08 06 00 00    
                                                    ; 1000239b:   00 
    mov    dword [esp],edi                          ; 1000239c:   89 3c 24                
    mov    dword [esp+0x4], recoil_original_6       ; 1000239f:   c7 44 24 04 7e 40 00    
                                                    ; 100023a6:   10 
    call   _memory_patch                            ; 100023a7:   e8 63 f8 ff ff          
    add    esp,0x3c                                 ; 100023ac:   83 c4 3c                
    pop    ebx                                      ; 100023af:   5b                      
    pop    esi                                      ; 100023b0:   5e                      
    pop    edi                                      ; 100023b1:   5f                      
    pop    ebp                                      ; 100023b2:   5d                      
    ret                                             ; 100023b3:   c3                      
;   lea    esi,[esi+eiz*1+0x0]                      ; 100023b4:   8d b4 26 00 00 00 00    
;   lea    esi,[esi+eiz*1+0x0]                      ; 100023bb:   8d 74 26 00             
    nop
    nop
    nop
    nop

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

_hack_disable_alarms:                               ; 100022f0:   <_hack_disable_alarms>
    sub     esp,0x1c                                ; 100022f0:   83 ec 1c               
    mov     eax, OFFSET_ALARMS                      ; 100022f3:   a1 dc 31 00 10         
    mov     edx,dword [esp+0x20]                    ; 100022f8:   8b 54 24 20            
    add     eax,dword [_g_module_base_addr]         ; 100022fc:   03 05 04 30 00 10      
    test    edx,edx                                 ; 10002302:   85 d2                  
    mov     dword [esp+0x8],0x6                     ; 10002304:   c7 44 24 08 06 00 00   
                                                    ; 1000230b:   00 
    je      alarms_disabled                         ; 1000230c:   74 1a                  
alarms_enabled:
    mov     dword [esp+0x4],alarm_patch             ; 1000230e:   c7 44 24 04 00 40 00   
                                                    ; 10002315:   10 
    mov     dword [esp],eax                         ; 10002316:   89 04 24               
    call    _memory_patch                           ; 10002319:   e8 81 f3 ff ff         
    add     esp,0x1c                                ; 1000231e:   83 c4 1c               
    ret                                             ; 10002321:   c3                     
    lea     esi,[esi]                               ; 10002322:   8d b6 00 00 00 00      
    nop
    nop
    nop
    nop
alarms_disabled:
    mov     dword [esp+0x4],alarm_original          ; 10002328:   c7 44 24 04 08 40 00   
                                                    ; 1000232f:   10 
    mov     dword [esp],eax                         ; 10002330:   89 04 24               
    call    _memory_patch                           ; 10002333:   e8 67 f3 ff ff         
    add     esp,0x1c                                ; 10002338:   83 c4 1c               
    ret                                             ; 1000233b:   c3                     
    lea     esi,[esi]                               ; 1000233c:   8d 74 26 00            
    nop
    nop
    nop
    nop
