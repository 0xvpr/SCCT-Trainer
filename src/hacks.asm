; -----------------------------------------------------------------------------
;                                Definitions
; -----------------------------------------------------------------------------

TYPE_PLAYER         EQU 0x110E8B50
OFFSET_HEALTH       EQU 0x003F07C8
OFFSET_VISIBILITY   EQU 0x0027F12C
OFFSET_NOISE        EQU 0x00417E5D
OFFSET_ALARMS       EQU 0x0009BC61

; -----------------------------------------------------------------------------
;                            External Variables
; -----------------------------------------------------------------------------

extern      _g_module_base_addr

; -----------------------------------------------------------------------------
;                            External Functions
; -----------------------------------------------------------------------------

extern      _VirtualProtect@16

extern      _memory_patch
extern      _memory_detour

; -----------------------------------------------------------------------------
;                              Executable Code
; -----------------------------------------------------------------------------
section     .text
global      _hack_god_mode
global      _hack_ghost_mode
global      _hack_disable_alarms

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
    jne     $ + 0x33b

alarm_patch:
    jmp     $ + 0x33b
    nop

_hack_god_mode:                                     ; 0001f30:   <_hack_god_mode>:
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

_hack_ghost_mode:                                   ; 10001f80    <_hack_ghost_mode>:
    push    ebp                                     ; 10001f80:   55                     
    push    edi                                     ; 10001f81:   57                     
    push    esi                                     ; 10001f82:   56                     
    push    ebx                                     ; 10001f83:   53                     
    sub     esp,0x2c                                ; 10001f84:   83 ec 2c               
    mov     ebx,dword [_g_module_base_addr]         ; 10001f87:   8b 1d 04 30 00 10      
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

;_hack_super_weapons                                ; 10002060 <_hack_super_weapons>:
;    push    ebp                                    ; 10002060:   55                     
;    push    edi                                    ; 10002061:   57                     
;    push    esi                                    ; 10002062:   56                     
;    push    ebx                                    ; 10002063:   53                     
;    sub     esp,0x3c                               ; 10002064:   83 ec 3c               
;    mov     eax,[_g_module_base_addr]              ; 10002067:   a1 04 30 00 10         
;    mov     ebx,DWORD PTR ds:0x100031b0            ; 1000206c:   8b 1d b0 31 00 10      
;    mov     esi,DWORD PTR ds:0x100031b4            ; 10002072:   8b 35 b4 31 00 10      
;    add     ebx,eax                                ; 10002078:   01 c3                  
;    mov     DWORD PTR [esp+0x1c],ebx               ; 1000207a:   89 5c 24 1c            
;    mov     ebx,DWORD PTR ds:0x100031b8            ; 1000207e:   8b 1d b8 31 00 10      
;    add     esi,eax                                ; 10002084:   01 c6                  
;    add     ebx,eax                                ; 10002086:   01 c3                  
;    mov     DWORD PTR [esp+0x20],esi               ; 10002088:   89 74 24 20            
;    mov     DWORD PTR [esp+0x24],ebx               ; 1000208c:   89 5c 24 24            
;    mov     ecx,DWORD PTR ds:0x100031d8            ; 10002090:   8b 0d d8 31 00 10      
;    mov     ebp,DWORD PTR ds:0x100031d4            ; 10002096:   8b 2d d4 31 00 10      
;    mov     edx,DWORD PTR ds:0x100031d0            ; 1000209c:   8b 15 d0 31 00 10      
;    mov     edi,DWORD PTR ds:0x100031cc            ; 100020a2:   8b 3d cc 31 00 10      
;    mov     esi,DWORD PTR ds:0x100031bc            ; 100020a8:   8b 35 bc 31 00 10      
;    mov     ebx,DWORD PTR ds:0x100031c0            ; 100020ae:   8b 1d c0 31 00 10      
;    add     edx,eax                                ; 100020b4:   01 c2                  
;    add     ecx,eax                                ; 100020b6:   01 c1                  
;    add     ebp,eax                                ; 100020b8:   01 c5                  
;    add     edi,eax                                ; 100020ba:   01 c7                  
;    add     esi,eax                                ; 100020bc:   01 c6                  
;    add     ebx,eax                                ; 100020be:   01 c3                  
;    add     eax,DWORD PTR ds:0x100031c4            ; 100020c0:   03 05 c4 31 00 10      
;    cmp     DWORD PTR [esp+0x50],0x0               ; 100020c6:   83 7c 24 50 00         
;    mov     DWORD PTR [esp+0x2c],eax               ; 100020cb:   89 44 24 2c            
;    mov     DWORD PTR [esp+0x28],edx               ; 100020cf:   89 54 24 28            
;    je      100021d8 <_hack_super_weapons+0x178>   ; 100020d3:   0f 84 ff 00 00 00      
;    mov     DWORD PTR [esp],ecx                    ; 100020d9:   89 0c 24               
;    mov     DWORD PTR [esp+0x4],0x2                ; 100020dc:   c7 44 24 04 02 00 00   
;                                                   ; 100020e3:   00 
;    call    10001637 <_memory_nop>                 ; 100020e4:   e8 4e f5 ff ff         
;    mov     eax,DWORD PTR [esp+0x28]               ; 100020e9:   8b 44 24 28            
;    mov     DWORD PTR [esp+0x8],0xe                ; 100020ed:   c7 44 24 08 0e 00 00   
;                                                   ; 100020f4:   00 
;    mov     DWORD PTR [esp],eax                    ; 100020f5:   89 04 24               
;    mov     DWORD PTR [esp+0x4],0x10004088         ; 100020f8:   c7 44 24 04 88 40 00   
;                                                   ; 100020ff:   10 
;    call    1000169f <_memory_patch>               ; 10002100:   e8 9a f5 ff ff         
;    mov     DWORD PTR [esp],ebp                    ; 10002105:   89 2c 24               
;    mov     DWORD PTR [esp+0x8],0xe                ; 10002108:   c7 44 24 08 0e 00 00   
;                                                   ; 1000210f:   00 
;    mov     DWORD PTR [esp+0x4],0x100040a8         ; 10002110:   c7 44 24 04 a8 40 00   
;                                                   ; 10002117:   10 
;    call    1000169f <_memory_patch>               ; 10002118:   e8 82 f5 ff ff         
;    mov     DWORD PTR [esp],edi                    ; 1000211d:   89 3c 24               
;    mov     DWORD PTR [esp+0x4],0x2                ; 10002120:   c7 44 24 04 02 00 00   
;                                                   ; 10002127:   00 
;    call    10001637 <_memory_nop>                 ; 10002128:   e8 0a f5 ff ff         
;    mov     ecx,DWORD PTR [esp+0x1c]               ; 1000212d:   8b 4c 24 1c            
;    mov     DWORD PTR [esp+0x8],0x6                ; 10002131:   c7 44 24 08 06 00 00   
;                                                   ; 10002138:   00 
;    mov     DWORD PTR [esp],ecx                    ; 10002139:   89 0c 24               
;    mov     DWORD PTR [esp+0x4],0x10004020         ; 1000213c:   c7 44 24 04 20 40 00   
;                                                   ; 10002143:   10 
;    call    1000169f <_memory_patch>               ; 10002144:   e8 56 f5 ff ff         
;    mov     ebp,DWORD PTR [esp+0x20]               ; 10002149:   8b 6c 24 20            
;    mov     DWORD PTR [esp+0x8],0x6                ; 1000214d:   c7 44 24 08 06 00 00   
;                                                   ; 10002154:   00 
;    mov     DWORD PTR [esp],ebp                    ; 10002155:   89 2c 24               
;    mov     DWORD PTR [esp+0x4],0x10004026         ; 10002158:   c7 44 24 04 26 40 00   
;                                                   ; 1000215f:   10 
;    call    1000169f <_memory_patch>               ; 10002160:   e8 3a f5 ff ff         
;    mov     edx,DWORD PTR [esp+0x24]               ; 10002165:   8b 54 24 24            
;    mov     DWORD PTR [esp+0x8],0x6                ; 10002169:   c7 44 24 08 06 00 00   
;                                                   ; 10002170:   00 
;    mov     DWORD PTR [esp],edx                    ; 10002171:   89 14 24               
;    mov     DWORD PTR [esp+0x4],0x1000402c         ; 10002174:   c7 44 24 04 2c 40 00   
;                                                   ; 1000217b:   10 
;    call    1000169f <_memory_patch>               ; 1000217c:   e8 1e f5 ff ff         
;    mov     DWORD PTR [esp],esi                    ; 10002181:   89 34 24               
;    mov     DWORD PTR [esp+0x8],0x6                ; 10002184:   c7 44 24 08 06 00 00   
;                                                   ; 1000218b:   00 
;    mov     DWORD PTR [esp+0x4],0x10004032         ; 1000218c:   c7 44 24 04 32 40 00   
;                                                   ; 10002193:   10 
;    call    1000169f <_memory_patch>               ; 10002194:   e8 06 f5 ff ff         
;    mov     DWORD PTR [esp],ebx                    ; 10002199:   89 1c 24               
;    mov     DWORD PTR [esp+0x8],0x6                ; 1000219c:   c7 44 24 08 06 00 00   
;                                                   ; 100021a3:   00 
;    mov     DWORD PTR [esp+0x4],0x10004038         ; 100021a4:   c7 44 24 04 38 40 00   
;                                                   ; 100021ab:   10 
;    call    1000169f <_memory_patch>               ; 100021ac:   e8 ee f4 ff ff         
;    mov     esi,DWORD PTR [esp+0x2c]               ; 100021b1:   8b 74 24 2c            
;    mov     DWORD PTR [esp+0x8],0x6                ; 100021b5:   c7 44 24 08 06 00 00   
;                                                   ; 100021bc:   00 
;    mov     DWORD PTR [esp],esi                    ; 100021bd:   89 34 24               
;    mov     DWORD PTR [esp+0x4],0x1000403e         ; 100021c0:   c7 44 24 04 3e 40 00   
;                                                   ; 100021c7:   10 
;    call    1000169f <_memory_patch>               ; 100021c8:   e8 d2 f4 ff ff         
;    add     esp,0x3c                               ; 100021cd:   83 c4 3c               
;    pop     ebx                                    ; 100021d0:   5b                     
;    pop     esi                                    ; 100021d1:   5e                     
;    pop     edi                                    ; 100021d2:   5f                     
;    pop     ebp                                    ; 100021d3:   5d                     
;    ret                                            ; 100021d4:   c3                     
;    lea     esi,[esi+0x0]                          ; 100021d5:   8d 76 00               
;    mov     DWORD PTR [esp],ecx                    ; 100021d8:   89 0c 24               
;    mov     DWORD PTR [esp+0x8],0x2                ; 100021db:   c7 44 24 08 02 00 00   
;                                                   ; 100021e2:   00 
;    mov     DWORD PTR [esp+0x4],0x100040c6         ; 100021e3:   c7 44 24 04 c6 40 00   
;                                                   ; 100021ea:   10 
;    call    1000169f <_memory_patch>               ; 100021eb:   e8 af f4 ff ff         
;    mov     eax,DWORD PTR [esp+0x28]               ; 100021f0:   8b 44 24 28            
;    mov     DWORD PTR [esp+0x8],0xe                ; 100021f4:   c7 44 24 08 0e 00 00   
;                                                   ; 100021fb:   00 
;    mov     DWORD PTR [esp],eax                    ; 100021fc:   89 04 24               
;    mov     DWORD PTR [esp+0x4],0x10004098         ; 100021ff:   c7 44 24 04 98 40 00   
;                                                   ; 10002206:   10 
;    call    1000169f <_memory_patch>               ; 10002207:   e8 93 f4 ff ff         
;    mov     DWORD PTR [esp],ebp                    ; 1000220c:   89 2c 24               
;    mov     DWORD PTR [esp+0x8],0xe                ; 1000220f:   c7 44 24 08 0e 00 00   
;                                                   ; 10002216:   00 
;    mov     DWORD PTR [esp+0x4],0x100040b8         ; 10002217:   c7 44 24 04 b8 40 00   
;                                                   ; 1000221e:   10 
;    call    1000169f <_memory_patch>               ; 1000221f:   e8 7b f4 ff ff         
;    mov     DWORD PTR [esp],edi                    ; 10002224:   89 3c 24               
;    mov     DWORD PTR [esp+0x8],0x2                ; 10002227:   c7 44 24 08 02 00 00   
;                                                   ; 1000222e:   00 
;    mov     DWORD PTR [esp+0x4],0x10004084         ; 1000222f:   c7 44 24 04 84 40 00   
;                                                   ; 10002236:   10 
;    call    1000169f <_memory_patch>               ; 10002237:   e8 63 f4 ff ff         
;    mov     ecx,DWORD PTR [esp+0x1c]               ; 1000223c:   8b 4c 24 1c            
;    mov     DWORD PTR [esp+0x8],0x6                ; 10002240:   c7 44 24 08 06 00 00   
;                                                   ; 10002247:   00 
;    mov     DWORD PTR [esp],ecx                    ; 10002248:   89 0c 24               
;    mov     DWORD PTR [esp+0x4],0x10004060         ; 1000224b:   c7 44 24 04 60 40 00   
;                                                   ; 10002252:   10 
;    call    1000169f <_memory_patch>               ; 10002253:   e8 47 f4 ff ff         
;    mov     ebp,DWORD PTR [esp+0x20]               ; 10002258:   8b 6c 24 20            
;    mov     DWORD PTR [esp+0x8],0x6                ; 1000225c:   c7 44 24 08 06 00 00   
;                                                   ; 10002263:   00 
;    mov     DWORD PTR [esp],ebp                    ; 10002264:   89 2c 24               
;    mov     DWORD PTR [esp+0x4],0x10004066         ; 10002267:   c7 44 24 04 66 40 00   
;                                                   ; 1000226e:   10 
;    call    1000169f <_memory_patch>               ; 1000226f:   e8 2b f4 ff ff         
;    mov     edx,DWORD PTR [esp+0x24]               ; 10002274:   8b 54 24 24            
;    mov     DWORD PTR [esp+0x8],0x6                ; 10002278:   c7 44 24 08 06 00 00   
;                                                   ; 1000227f:   00 
;    mov     DWORD PTR [esp],edx                    ; 10002280:   89 14 24               
;    mov     DWORD PTR [esp+0x4],0x1000406c         ; 10002283:   c7 44 24 04 6c 40 00   
;                                                   ; 1000228a:   10 
;    call    1000169f <_memory_patch>               ; 1000228b:   e8 0f f4 ff ff         
;    mov     DWORD PTR [esp],esi                    ; 10002290:   89 34 24               
;    mov     DWORD PTR [esp+0x8],0x6                ; 10002293:   c7 44 24 08 06 00 00   
;                                                   ; 1000229a:   00 
;    mov     DWORD PTR [esp+0x4],0x10004072         ; 1000229b:   c7 44 24 04 72 40 00   
;                                                   ; 100022a2:   10 
;    call    1000169f <_memory_patch>               ; 100022a3:   e8 f7 f3 ff ff         
;    mov     DWORD PTR [esp],ebx                    ; 100022a8:   89 1c 24               
;    mov     DWORD PTR [esp+0x8],0x6                ; 100022ab:   c7 44 24 08 06 00 00   
;                                                   ; 100022b2:   00 
;    mov     DWORD PTR [esp+0x4],0x10004078         ; 100022b3:   c7 44 24 04 78 40 00   
;                                                   ; 100022ba:   10 
;    call    1000169f <_memory_patch>               ; 100022bb:   e8 df f3 ff ff         
;    mov     edi,DWORD PTR [esp+0x2c]               ; 100022c0:   8b 7c 24 2c            
;    mov     DWORD PTR [esp+0x8],0x6                ; 100022c4:   c7 44 24 08 06 00 00   
;                                                   ; 100022cb:   00 
;    mov     DWORD PTR [esp],edi                    ; 100022cc:   89 3c 24               
;    mov     DWORD PTR [esp+0x4],0x1000407e         ; 100022cf:   c7 44 24 04 7e 40 00   
;                                                   ; 100022d6:   10 
;    call    1000169f <_memory_patch>               ; 100022d7:   e8 c3 f3 ff ff         
;    add     esp,0x3c                               ; 100022dc:   83 c4 3c               
;    pop     ebx                                    ; 100022df:   5b                     
;    pop     esi                                    ; 100022e0:   5e                     
;    pop     edi                                    ; 100022e1:   5f                     
;    pop     ebp                                    ; 100022e2:   5d                     
;    ret                                            ; 100022e3:   c3                     
;    lea     esi,[esi+eiz*1+0x0]                    ; 100022e4:   8d b4 26 00 00 00 00   
;    lea     esi,[esi+eiz*1+0x0]                    ; 100022eb:   8d 74 26 00            
;    nop                                            ; 100022ef:   90                     

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
