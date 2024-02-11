; --------------------------------------------------------------------------- ;
;                            Exported Functions                               ;
; --------------------------------------------------------------------------- ;

global      _events_handle_keyboard

; --------------------------------------------------------------------------- ;
;                            External Variables                               ;
; --------------------------------------------------------------------------- ;

extern      _g_hack_menu
extern      _g_maximized
extern      _g_resolution
extern      _g_coordinates

; --------------------------------------------------------------------------- ;
;                            External Functions                               ;
; --------------------------------------------------------------------------- ;

extern      _GetAsyncKeyState@4

extern      _hack_test
extern      _hack_no_clip
extern      _hack_god_mode
extern      _hack_ghost_mode
extern      _hack_super_weapons
extern      _hack_disable_alarms
extern      _hack_disable_enemies
extern      _hack_unlock_all_doors

; --------------------------------------------------------------------------- ;
;                             Executable Code                                 ;
; --------------------------------------------------------------------------- ;

section     .text
_events_handle_keyboard:                                     ; 10001d60:   <_events_handle_keyboard>
    push    ebx                                              ; 10001d60:   53                       
    sub     esp,0x18                                         ; 10001d61:   83 ec 18                 
    mov     dword [esp],0x61                                 ; 10001d64:   c7 04 24 61 00 00 00     
    mov     ebx, _GetAsyncKeyState@4                         ; 10001d6b:   8b 1d e8 70 00 10        
    call    ebx                                              ; 10001d71:   ff d3                    
    sub     esp,0x4                                          ; 10001d73:   83 ec 04                 
    test    al,0x1                                           ; 10001d76:   a8 01                    
    jne     numpad_1                                         ; 10001d78:   0f 85 ca 00 00 00        
    mov     dword [esp],0x62                                 ; 10001d7e:   c7 04 24 62 00 00 00     
    call    ebx                                              ; 10001d85:   ff d3                    
    sub     esp,0x4                                          ; 10001d87:   83 ec 04                 
    test    al,0x1                                           ; 10001d8a:   a8 01                    
    jne     numpad_2                                         ; 10001d8c:   0f 85 e4 00 00 00        
numpad_3_check:
    mov     dword [esp],0x63                                 ; 10001d92:   c7 04 24 63 00 00 00     
    call    ebx                                              ; 10001d99:   ff d3                    
    sub     esp,0x4                                          ; 10001d9b:   83 ec 04                 
    test    al,0x1                                           ; 10001d9e:   a8 01                    
    jne     numpad_3                                         ; 10001da0:   0f 85 fe 00 00 00        
numpad_4_check:
    mov     dword [esp],0x64                                 ; 10001da6:   c7 04 24 64 00 00 00     
    call    ebx                                              ; 10001dad:   ff d3                    
    sub     esp,0x4                                          ; 10001daf:   83 ec 04                 
    test    al,0x1                                           ; 10001db2:   a8 01                    
    jne     numpad_4                                         ; 10001db4:   0f 85 18 01 00 00        
numpad_5_check:
    mov     dword [esp],0x65                                 ; 10001dba:   c7 04 24 65 00 00 00     
    call    ebx                                              ; 10001dc1:   ff d3                    
    sub     esp,0x4                                          ; 10001dc3:   83 ec 04                 
    test    al,0x1                                           ; 10001dc6:   a8 01                    
    jne     numpad_5                                         ; 10001dc8:   0f 85 32 01 00 00        
numpad_6_check:
    mov     dword [esp],0x66                                 ; 10001dce:   c7 04 24 66 00 00 00     
    call    ebx                                              ; 10001dd5:   ff d3                    
    sub     esp,0x4                                          ; 10001dd7:   83 ec 04                 
    test    al,0x1                                           ; 10001dda:   a8 01                    
    jne     numpad_6                                         ; 10001ddc:   0f 85 4c 01 00 00        
numpad_7_check:
    mov     dword [esp],0x67                                 ; 10001de2:   c7 04 24 67 00 00 00     
    call    ebx                                              ; 10001de9:   ff d3                    
    sub     esp,0x4                                          ; 10001deb:   83 ec 04                 
    test    al,0x1                                           ; 10001dee:   a8 01                    
    jne     numpad_7                                         ; 10001df0:   0f 85 51 01 00 00        
menu_max_q:
    mov     ecx, dword [_g_maximized]                        ; 10001df6:   8b 0d 10 30 00 10        
    test    ecx,ecx                                          ; 10001dfc:   85 c9                    
    jne     menu_minimized                                   ; 10001dfe:   0f 85 56 01 00 00        
menu_maximized:
    mov     dword [esp],0x71                                 ; 10001e04:   c7 04 24 71 00 00 00     
    call    ebx                                              ; 10001e0b:   ff d3                    
    sub     esp,0x4                                          ; 10001e0d:   83 ec 04                 
    test    al,0x1                                           ; 10001e10:   a8 01                    
    je      home_key                                         ; 10001e12:   74 12                    
    mov     edx,dword [_g_maximized]                         ; 10001e14:   8b 15 10 30 00 10        
    xor     eax,eax                                          ; 10001e1a:   31 c0                    
    test    edx,edx                                          ; 10001e1c:   85 d2                    
    sete    al                                               ; 10001e1e:   0f 94 c0                 
    mov     dword [_g_maximized],eax                         ; 10001e21:   a3 10 30 00 10           
home_key:
    mov     dword [esp],0x24                                 ; 10001e26:   c7 04 24 24 00 00 00     
    call    ebx                                              ; 10001e2d:   ff d3                    
    mov     ebx,eax                                          ; 10001e2f:   89 c3                    
    sub     esp,0x4                                          ; 10001e31:   83 ec 04                 
    xor     eax,eax                                          ; 10001e34:   31 c0                    
    test    bx,bx                                            ; 10001e36:   66 85 db                 
    jne     unload                                           ; 10001e39:   0f 85 a1 01 00 00        
    add     esp,0x18                                         ; 10001e3f:   83 c4 18                 
    pop     ebx                                              ; 10001e42:   5b                       
    ret                                                      ; 10001e43:   c3                       
    lea     esi,[esi+0x0]                                    ; 10001e44:   8d 74 26 00              
    nop
    nop
    nop
    nop
numpad_1:
    mov     edx, dword [_g_hack_menu+0x44*0]                 ; 10001e48:   8b 15 14 30 00 10        
    xor     eax,eax                                          ; 10001e4e:   31 c0                    
    test    edx,edx                                          ; 10001e50:   85 d2                    
    sete    al                                               ; 10001e52:   0f 94 c0                 
    mov     dword [esp],eax                                  ; 10001e55:   89 04 24                 
    mov     [_g_hack_menu+0x44*0],eax                        ; 10001e58:   a3 14 30 00 10           
    call    _hack_god_mode                                   ; 10001e5d:   e8 b6 f5 ff ff           
    mov     dword [esp],0x62                                 ; 10001e62:   c7 04 24 62 00 00 00     
    call    ebx                                              ; 10001e69:   ff d3                    
    sub     esp,0x4                                          ; 10001e6b:   83 ec 04                 
    test    al,0x1                                           ; 10001e6e:   a8 01                    
    je      numpad_3_check                                   ; 10001e70:   0f 84 1c ff ff ff        
numpad_2:
    mov     ecx, dword [_g_hack_menu+0x44*1]                 ; 10001e76:   8b 0d 58 30 00 10        
    xor     eax,eax                                          ; 10001e7c:   31 c0                    
    test    ecx,ecx                                          ; 10001e7e:   85 c9                    
    sete    al                                               ; 10001e80:   0f 94 c0                 
    mov     dword [esp],eax                                  ; 10001e83:   89 04 24                 
    mov     [_g_hack_menu+0x44*1],eax                        ; 10001e86:   a3 58 30 00 10           
    call    _hack_ghost_mode                                 ; 10001e8b:   e8 d4 f5 ff ff           
    mov     dword [esp],0x63                                 ; 10001e90:   c7 04 24 63 00 00 00     
    call    ebx                                              ; 10001e97:   ff d3                    
    sub     esp,0x4                                          ; 10001e99:   83 ec 04                 
    test    al,0x1                                           ; 10001e9c:   a8 01                    
    je      numpad_4_check                                   ; 10001e9e:   0f 84 02 ff ff ff        
numpad_3:
    mov     edx, dword [_g_hack_menu+0x44*2]                 ; 10001ea4:   8b 15 9c 30 00 10        
    xor     eax,eax                                          ; 10001eaa:   31 c0                    
    test    edx,edx                                          ; 10001eac:   85 d2                    
    sete    al                                               ; 10001eae:   0f 94 c0                 
    mov     dword [esp],eax                                  ; 10001eb1:   89 04 24                 
    mov     [_g_hack_menu+0x44*2],eax                        ; 10001eb4:   a3 9c 30 00 10           
    call    _hack_super_weapons                              ; 10001eb9:   e8 12 02 00 00           
    mov     dword [esp],0x64                                 ; 10001ebe:   c7 04 24 64 00 00 00     
    call    ebx                                              ; 10001ec5:   ff d3                    
    sub     esp,0x4                                          ; 10001ec7:   83 ec 04                 
    test    al,0x1                                           ; 10001eca:   a8 01                    
    je      numpad_5_check                                   ; 10001ecc:   0f 84 e8 fe ff ff        
numpad_4:
    mov     ecx, dword [_g_hack_menu+0x44*3]                 ; 10001ed2:   8b 0d e0 30 00 10        
    xor     eax,eax                                          ; 10001ed8:   31 c0                    
    test    ecx,ecx                                          ; 10001eda:   85 c9                    
    sete    al                                               ; 10001edc:   0f 94 c0                 
    mov     dword [esp],eax                                  ; 10001edf:   89 04 24                 
    mov     [_g_hack_menu+0x44*3],eax                        ; 10001ee2:   a3 e0 30 00 10           
    call    _hack_disable_alarms                             ; 10001ee7:   e8 54 f6 ff ff           
    mov     dword [esp],0x65                                 ; 10001eec:   c7 04 24 65 00 00 00     
    call    ebx                                              ; 10001ef3:   ff d3                    
    sub     esp,0x4                                          ; 10001ef5:   83 ec 04                 
    test    al,0x1                                           ; 10001ef8:   a8 01                    
    je      numpad_6_check                                   ; 10001efa:   0f 84 ce fe ff ff        
numpad_5:
    mov     edx, dword [_g_hack_menu+0x44*4]                 ; 10001f00:   8b 15 24 31 00 10        
    xor     eax,eax                                          ; 10001f06:   31 c0                    
    test    edx,edx                                          ; 10001f08:   85 d2                    
    sete    al                                               ; 10001f0a:   0f 94 c0                 
    mov      dword [esp],eax                                 ; 10001f0d:   89 04 24                 
    mov     [_g_hack_menu+0x44*4],eax                        ; 10001f10:   a3 24 31 00 10           
    call    _hack_disable_enemies                            ; 10001f15:   e8 46 04 00 00           
    mov      dword [esp],0x66                                ; 10001f1a:   c7 04 24 66 00 00 00     
    call    ebx                                              ; 10001f21:   ff d3                    
    sub     esp,0x4                                          ; 10001f23:   83 ec 04                 
    test    al,0x1                                           ; 10001f26:   a8 01                    
    je      numpad_7_check                                   ; 10001f28:   0f 84 b4 fe ff ff        
numpad_6:
    call    _hack_unlock_all_doors                           ; 10001f2e:   e8 bd 09 00 00           
    mov      dword [esp],0x67                                ; 10001f33:   c7 04 24 67 00 00 00     
    call    ebx                                              ; 10001f3a:   ff d3                    
    sub     esp,0x4                                          ; 10001f3c:   83 ec 04                 
    test    al,0x1                                           ; 10001f3f:   a8 01                    
    je      menu_max_q                                       ; 10001f41:   0f 84 af fe ff ff        
numpad_7:
    call    _hack_test                                       ; 10001f47:   e8 f4 0c 00 00           
    mov     ecx, dword [_g_maximized]                        ; 10001f4c:   8b 0d 10 30 00 10        
    test    ecx,ecx                                          ; 10001f52:   85 c9                    
    je      menu_maximized                                   ; 10001f54:   0f 84 aa fe ff ff        
menu_minimized:
    mov     dword [esp],0x25                                 ; 10001f5a:   c7 04 24 25 00 00 00     
    call    ebx                                              ; 10001f61:   ff d3                    
    sub     esp,0x4                                          ; 10001f63:   83 ec 04                 
    test    al,0x1                                           ; 10001f66:   a8 01                    
    jne     arrow_left                                       ; 10001f68:   0f 85 42 01 00 00        
arrow_right_check:
    mov     dword [esp],0x27                                 ; 10001f6e:   c7 04 24 27 00 00 00     
    call    ebx                                              ; 10001f75:   ff d3                    
    sub     esp,0x4                                          ; 10001f77:   83 ec 04                 
    test    al,0x1                                           ; 10001f7a:   a8 01                    
    jne     arrow_right                                      ; 10001f7c:   0f 85 fe 00 00 00        
arrow_up_check:
    mov     dword [esp],0x26                                 ; 10001f82:   c7 04 24 26 00 00 00     
    call    ebx                                              ; 10001f89:   ff d3                    
    sub     esp,0x4                                          ; 10001f8b:   83 ec 04                 
    test    al,0x1                                           ; 10001f8e:   a8 01                    
    jne     arrow_up                                         ; 10001f90:   0f 85 ca 00 00 00        
arrow_down_check:
    mov     dword [esp],0x28                                 ; 10001f96:   c7 04 24 28 00 00 00     
    call    ebx                                              ; 10001f9d:   ff d3                    
    sub     esp,0x4                                          ; 10001f9f:   83 ec 04                 
    test    al,0x1                                           ; 10001fa2:   a8 01                    
    jne     coordinate_check_y                               ; 10001fa4:   0f 85 86 00 00 00        
f3_check:
    mov     ecx,dword [_g_maximized]                         ; 10001faa:   8b 0d 10 30 00 10        
    test    ecx,ecx                                          ; 10001fb0:   85 c9                    
    je      menu_maximized                                   ; 10001fb2:   0f 84 4c fe ff ff        
    mov     dword [esp],0x72                                 ; 10001fb8:   c7 04 24 72 00 00 00     
    call    ebx                                              ; 10001fbf:   ff d3                    
    sub     esp,0x4                                          ; 10001fc1:   83 ec 04                 
    test    al,0x1                                           ; 10001fc4:   a8 01                    
    je      menu_maximized                                   ; 10001fc6:   0f 84 38 fe ff ff        
    mov     dword [_g_coordinates],0x19001e                  ; 10001fcc:   c7 05 ac 31 00 10 1e     
                                                             ; 10001fd3:   00 19 00 
    jmp     menu_maximized                                   ; 10001fd6:   e9 29 fe ff ff           
    lea     esi,[esi+0x0]                                    ; 10001fdb:   8d 74 26 00              
    nop                                                      ; 10001fdf:   90                       
    nop                                                      ; 10001fdf:   90                       
    nop                                                      ; 10001fdf:   90                       
    nop                                                      ; 10001fdf:   90                       
    nop                                                      ; 10001fdf:   90                       
unload:
    mov     dword [esp],0x0                                  ; 10001fe0:   c7 04 24 00 00 00 00     
    call    _hack_god_mode                                   ; 10001fe7:   e8 2c f4 ff ff           
    mov     dword [esp],0x0                                  ; 10001fec:   c7 04 24 00 00 00 00     
    call    _hack_ghost_mode                                 ; 10001ff3:   e8 6c f4 ff ff           
    mov     dword [esp],0x0                                  ; 10001ff8:   c7 04 24 00 00 00 00     
    call    _hack_super_weapons                              ; 10001fff:   e8 cc 00 00 00           
    mov     dword [esp],0x0                                  ; 10002004:   c7 04 24 00 00 00 00     
    call    _hack_disable_alarms                             ; 1000200b:   e8 30 f5 ff ff           
    mov     dword [esp],0x0                                  ; 10002010:   c7 04 24 00 00 00 00     
    call    _hack_disable_enemies                            ; 10002017:   e8 44 03 00 00           
    add     esp,0x18                                         ; 1000201c:   83 c4 18                 
    mov     eax,0x1                                          ; 1000201f:   b8 01 00 00 00           
    pop     ebx                                              ; 10002024:   5b                       
    ret                                                      ; 10002025:   c3                       
    lea     esi,[esi+0x0]                                    ; 10002026:   8d b4 26 00 00 00 00     
    nop
    nop
    nop
    nop
    lea     esi,[esi+0x0]                                    ; 1000202d:   8d 76 00                 
coordinate_check_y:
    movzx   eax, word [_g_resolution+0x2]                    ; 10002030:   0f b7 05 0e 30 00 10     
    movzx   ecx, word [_g_coordinates+0x2]                   ; 10002037:   0f b7 0d ae 31 00 10     
    sub     eax,0x78                                         ; 1000203e:   83 e8 78                 
    mov     edx,ecx                                          ; 10002041:   89 ca                    
    cmp     ecx,eax                                          ; 10002043:   39 c1                    
    jge     f3_check                                         ; 10002045:   0f 8d 5f ff ff ff        
    add     edx,0x5                                          ; 1000204b:   83 c2 05                 
    mov     word [_g_coordinates+0x2],dx                     ; 1000204e:   66 89 15 ae 31 00 10     
    jmp     f3_check                                         ; 10002055:   e9 50 ff ff ff           
    lea     esi,[esi+0x0]                                    ; 1000205a:   8d b6 00 00 00 00        
arrow_up:
    movzx   ecx,word [_g_coordinates+0x2]                    ; 10002060:   0f b7 0d ae 31 00 10     
    cmp     cx,0x1e                                          ; 10002067:   66 83 f9 1e              
    jbe     arrow_down_check                                 ; 1000206b:   0f 86 25 ff ff ff        
    sub     ecx,0x5                                          ; 10002071:   83 e9 05                 
    mov     word [_g_coordinates+0x2],cx                     ; 10002074:   66 89 0d ae 31 00 10     
    jmp     arrow_down_check                                 ; 1000207b:   e9 16 ff ff ff           
arrow_right:
    movzx   eax,word [_g_resolution]                         ; 10002080:   0f b7 05 0c 30 00 10     
    movzx   ecx,word [_g_coordinates]                        ; 10002087:   0f b7 0d ac 31 00 10     
    sub     eax,0xaf                                         ; 1000208e:   2d af 00 00 00           
    mov     edx,ecx                                          ; 10002093:   89 ca                    
    cmp     ecx,eax                                          ; 10002095:   39 c1                    
    jge     arrow_up_check                                   ; 10002097:   0f 8d e5 fe ff ff        
    add     edx,0x5                                          ; 1000209d:   83 c2 05                 
    mov     word [_g_coordinates],dx                         ; 100020a0:   66 89 15 ac 31 00 10     
    jmp     arrow_up_check                                   ; 100020a7:   e9 d6 fe ff ff           
    lea     esi,[esi+0x0]                                    ; 100020ac:   8d 74 26 00              
    nop
    nop
    nop
    nop
arrow_left:
    movzx   eax,word [_g_coordinates]                        ; 100020b0:   0f b7 05 ac 31 00 10     
    cmp     ax,0x23                                          ; 100020b7:   66 83 f8 23              
    jbe     arrow_right_check                                ; 100020bb:   0f 86 ad fe ff ff        
    sub     eax,0x5                                          ; 100020c1:   83 e8 05                 
    mov     word [_g_coordinates],ax                         ; 100020c4:   66 a3 ac 31 00 10        
    jmp     arrow_right_check                                ; 100020ca:   e9 9f fe ff ff           
    nop                                                      ; 100020cf:   90                       
