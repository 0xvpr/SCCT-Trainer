section     .data
global      _g_resolution
global      _g_maximized
global      _g_coordinates
global      _g_hack_menu
global      _coordinates_x
global      _coordinates_y

_g_resolution:
    dd      0
_g_maximized:
    dd      1
_g_hack_menu:
    times   408 db 0
_g_coordinates:
_coordinates_x:
    dw      30
_coordinates_y:
    dw      25

section     .text
extern      _drawing_draw_filled_rect
extern      _drawing_draw_border_box

global      _render_menu@4
_render_menu@4:                                    ; 100028e0:    <_render_menu@4>
    push    ebp                                    ; 100028e0:    55                       
    push    edi                                    ; 100028e1:    57                       
    push    esi                                    ; 100028e2:    56                       
    push    ebx                                    ; 100028e3:    53                       
    sub     esp,0x2c                               ; 100028e4:    83 ec 2c                 
    mov     ecx,[_g_maximized]                     ; 100028e7:    8b 0d 54 30 00 10        
    mov     eax,ds:0x9d2a8                         ; 100028ed:    a1 a8 d2 09 00           
    mov     ebx,dword [esp+0x40]                   ; 100028f2:    8b 5c 24 40              
    test    ecx,ecx                                ; 100028f6:    85 c9                    
    mov     [_g_resolution], eax                   ; 100028f8:    a3 98 61 00 10           
    mov     dword [esp+0x14],ebx                   ; 100028fd:    89 5c 24 14              
    mov     dword [esp+0x10],0xff191919            ; 10002901:    c7 44 24 10 19 19 19     
                                                   ; 10002908:    ff 
    je      render_minimized                       ; 10002909:    0f 84 c1 01 00 00        
    movzx   ecx, word [_coordinates_y]             ; 1000290f:    0f b7 0d 52 30 00 10     S
    movzx   edi, word [_coordinates_x]             ; 10002916:    0f b7 3d 50 30 00 10     
    mov     dword [esp+0x4],ecx                    ; 1000291d:    89 4c 24 04              
    mov     dword [esp],edi                        ; 10002921:    89 3c 24                 
    mov     dword [esp+0xc],0x64                   ; 10002924:    c7 44 24 0c 64 00 00     
                                                   ; 1000292b:    00 
    mov     dword [esp+0x8],0x8c                   ; 1000292c:    c7 44 24 08 8c 00 00     
                                                   ; 10002933:    00 
    mov     edi,0x14                               ; 10002934:    bf 14 00 00 00           
    call    _drawing_draw_filled_rect              ; 10002939:    e8 29 ea ff ff           
    movzx   esi, word [_coordinates_y]             ; 1000293e:    0f b7 35 52 30 00 10     
    movzx   edx, word [_coordinates_x]             ; 10002945:    0f b7 15 50 30 00 10     
    mov     dword [esp+0x4],esi                    ; 1000294c:    89 74 24 04              
    mov     dword [esp+0x18],ebx                   ; 10002950:    89 5c 24 18              
    mov     dword [esp+0x14],0xff000000            ; 10002954:    c7 44 24 14 00 00 00     
                                                   ; 1000295b:    ff 
    mov     dword [esp+0x10],0x4                   ; 1000295c:    c7 44 24 10 04 00 00     
                                                   ; 10002963:    00 
    mov     dword [esp+0xc],0x64                   ; 10002964:    c7 44 24 0c 64 00 00     
                                                   ; 1000296b:    00 
    mov     dword [esp+0x8],0x8c                   ; 1000296c:    c7 44 24 08 8c 00 00     
                                                   ; 10002973:    00 
    mov     dword [esp],edx                        ; 10002974:    89 14 24                 
    mov     esi,_g_hack_menu                       ; 10002977:    be 00 60 00 10           
    mov     ebp,esi                                ; 1000297c:    89 f5                    
    call    _drawing_draw_border_box               ; 1000297e:    e8 5d e8 ff ff           
top_menu_max:
    cmp     dword [ebp+0xcc],0x1                   ; 10002983:    83 bd cc 00 00 00 01     
    sbb     eax,eax                                ; 1000298a:    19 c0                    
    movzx   ecx, word [_coordinates_y]             ; 1000298c:    0f b7 0d 52 30 00 10     
    movzx   edx, word [_coordinates_x]             ; 10002993:    0f b7 15 50 30 00 10     
    and     eax,0x458846                           ; 1000299a:    25 46 88 45 00           
    add     edx,edi                                ; 1000299f:    01 fa                    
    sub     eax,0xf537f6                           ; 100029a1:    2d f6 37 f5 00           
    add     ecx,0xf                                ; 100029a6:    83 c1 0f                 
    mov     dword [esp+0x10],eax                   ; 100029a9:    89 44 24 10              
    mov     dword [esp+0x4],ecx                    ; 100029ad:    89 4c 24 04              
    mov     dword [esp],edx                        ; 100029b1:    89 14 24                 
    mov     dword [esp+0x14],ebx                   ; 100029b4:    89 5c 24 14              
    mov     dword [esp+0xc],0x14                   ; 100029b8:    c7 44 24 0c 14 00 00     
                                                   ; 100029bf:    00 
    mov     dword [esp+0x8],0x19                   ; 100029c0:    c7 44 24 08 19 00 00     
                                                   ; 100029c7:    00 
    add     ebp,0x44                               ; 100029c8:    83 c5 44                 
    call    _drawing_draw_filled_rect              ; 100029cb:    e8 97 e9 ff ff           
    movzx   eax, word [_coordinates_y]             ; 100029d0:    0f b7 05 52 30 00 10     
    movzx   ecx, word [_coordinates_x]             ; 100029d7:    0f b7 0d 50 30 00 10     
    add     eax,0xf                                ; 100029de:    83 c0 0f                 
    add     ecx,edi                                ; 100029e1:    01 f9                    
    mov     dword [esp+0x18],ebx                   ; 100029e3:    89 5c 24 18              
    mov     dword [esp+0x14],0xff000000            ; 100029e7:    c7 44 24 14 00 00 00     
                                                   ; 100029ee:    ff 
    mov     dword [esp+0x10],0x2                   ; 100029ef:    c7 44 24 10 02 00 00     
                                                   ; 100029f6:    00 
    mov     dword [esp+0xc],0x14                   ; 100029f7:    c7 44 24 0c 14 00 00     
                                                   ; 100029fe:    00 
    mov     dword [esp+0x8],0x19                   ; 100029ff:    c7 44 24 08 19 00 00     
                                                   ; 10002a06:    00 
    mov     dword [esp+0x4],eax                    ; 10002a07:    89 44 24 04              
    mov     dword [esp],ecx                        ; 10002a0b:    89 0c 24                 
    add     edi,0x28                               ; 10002a0e:    83 c7 28                 
    call    _drawing_draw_border_box               ; 10002a11:    e8 ca e7 ff ff           
    cmp     edi,0x8c                               ; 10002a16:    81 ff 8c 00 00 00        
    jne     top_menu_max                           ; 10002a1c:    0f 85 61 ff ff ff        
    mov     ebp,0x14                               ; 10002a22:    bd 14 00 00 00           
bottom_menu_max:
    cmp     dword [esi],0x1                        ; 10002a27:    83 3e 01                 
    sbb     edi,edi                                ; 10002a2a:    19 ff                    
    movzx   edx, word [_coordinates_y]             ; 10002a2c:    0f b7 15 52 30 00 10     
    movzx   eax, word [_coordinates_x]             ; 10002a33:    0f b7 05 50 30 00 10     
    and     edi,0x458846                           ; 10002a3a:    81 e7 46 88 45 00        
    add     eax,ebp                                ; 10002a40:    01 e8                    
    add     edx,0x37                               ; 10002a42:    83 c2 37                 
    sub     edi,0xf537f6                           ; 10002a45:    81 ef f6 37 f5 00        
    mov     dword [esp+0x10],edi                   ; 10002a4b:    89 7c 24 10              
    mov     dword [esp+0x4],edx                    ; 10002a4f:    89 54 24 04              
    mov     dword [esp],eax                        ; 10002a53:    89 04 24                 
    mov     dword [esp+0x14],ebx                   ; 10002a56:    89 5c 24 14              
    mov     dword [esp+0xc],0x14                   ; 10002a5a:    c7 44 24 0c 14 00 00     
                                                   ; 10002a61:    00 
    mov     dword [esp+0x8],0x19                   ; 10002a62:    c7 44 24 08 19 00 00     
                                                   ; 10002a69:    00 
    add     esi,0x44                               ; 10002a6a:    83 c6 44                 
    call    _drawing_draw_filled_rect              ; 10002a6d:    e8 f5 e8 ff ff           
    movzx   ecx, word [_coordinates_y]             ; 10002a72:    0f b7 0d 52 30 00 10     
    movzx   edi, word [_coordinates_x]             ; 10002a79:    0f b7 3d 50 30 00 10     
    add     ecx,0x37                               ; 10002a80:    83 c1 37                 
    add     edi,ebp                                ; 10002a83:    01 ef                    
    mov     dword [esp+0x18],ebx                   ; 10002a85:    89 5c 24 18              
    mov     dword [esp+0x14],0xff000000            ; 10002a89:    c7 44 24 14 00 00 00     
                                                   ; 10002a90:    ff 
    mov     dword [esp+0x10],0x2                   ; 10002a91:    c7 44 24 10 02 00 00     
                                                   ; 10002a98:    00 
    mov     dword [esp+0xc],0x14                   ; 10002a99:    c7 44 24 0c 14 00 00     
                                                   ; 10002aa0:    00 
    mov     dword [esp+0x8],0x19                   ; 10002aa1:    c7 44 24 08 19 00 00     
                                                   ; 10002aa8:    00 
    mov     dword [esp+0x4],ecx                    ; 10002aa9:    89 4c 24 04              
    mov     dword [esp],edi                        ; 10002aad:    89 3c 24                 
    add     ebp,0x28                               ; 10002ab0:    83 c5 28                 
    call    _drawing_draw_border_box               ; 10002ab3:    e8 28 e7 ff ff           
    cmp     ebp,0x8c                               ; 10002ab8:    81 fd 8c 00 00 00        
    jne     bottom_menu_max                        ; 10002abe:    0f 85 63 ff ff ff        
not_a_clue:
    add     esp,0x2c                               ; 10002ac4:    83 c4 2c                 
    pop     ebx                                    ; 10002ac7:    5b                       
    pop     esi                                    ; 10002ac8:    5e                       
    pop     edi                                    ; 10002ac9:    5f                       
    pop     ebp                                    ; 10002aca:    5d                       
    ret     0x4                                    ; 10002acb:    c2 04 00                 
    xchg    ax,ax                                  ; 10002ace:    66 90                    
render_minimized:
    mov     dword [esp+0xc],0x19                   ; 10002ad0:    c7 44 24 0c 19 00 00     
                                                   ; 10002ad7:    00 
    mov     dword [esp+0x8],0x23                   ; 10002ad8:    c7 44 24 08 23 00 00     
                                                   ; 10002adf:    00 
    mov     dword [esp+0x4],0x14                   ; 10002ae0:    c7 44 24 04 14 00 00     
                                                   ; 10002ae7:    00 
    mov     dword [esp],0x1e                       ; 10002ae8:    c7 04 24 1e 00 00 00     
    mov     edi,0x10006000                         ; 10002aef:    bf 00 60 00 10           
    mov     ebp,edi                                ; 10002af4:    89 fd                    
    call    _drawing_draw_filled_rect              ; 10002af6:    e8 6c e8 ff ff           
    mov     dword [esp+0x18],ebx                   ; 10002afb:    89 5c 24 18              
    mov     dword [esp+0x14],0xff000000            ; 10002aff:    c7 44 24 14 00 00 00     
                                                   ; 10002b06:    ff 
    mov     dword [esp+0x10],0x2                   ; 10002b07:    c7 44 24 10 02 00 00     
                                                   ; 10002b0e:    00 
    mov     dword [esp+0xc],0x19                   ; 10002b0f:    c7 44 24 0c 19 00 00     
                                                   ; 10002b16:    00 
    mov     dword [esp+0x8],0x23                   ; 10002b17:    c7 44 24 08 23 00 00     
                                                   ; 10002b1e:    00 
    mov     dword [esp+0x4],0x14                   ; 10002b1f:    c7 44 24 04 14 00 00     
                                                   ; 10002b26:    00 
    mov     dword [esp],0x1e                       ; 10002b27:    c7 04 24 1e 00 00 00     
    mov     esi,0x23                               ; 10002b2e:    be 23 00 00 00           
    call    _drawing_draw_border_box               ; 10002b33:    e8 a8 e6 ff ff           
idek:
    mov     edx,dword [ebp+0xcc]                   ; 10002b38:    8b 95 cc 00 00 00        
    mov     dword [esp+0x14],ebx                   ; 10002b3e:    89 5c 24 14              
    test    edx,edx                                ; 10002b42:    85 d2                    
    je      inactive_color                         ; 10002b44:    0f 84 f6 00 00 00        
    mov     dword [esp+0x10],0xff0ac80a            ; 10002b4a:    c7 44 24 10 0a c8 0a     
                                                   ; 10002b51:    ff 
jmp_2b52:
    mov     dword [esp],esi                        ; 10002b52:    89 34 24                 
    mov     dword [esp+0xc],0x5                    ; 10002b55:    c7 44 24 0c 05 00 00     
                                                   ; 10002b5c:    00 
    mov     dword [esp+0x8],0x5                    ; 10002b5d:    c7 44 24 08 05 00 00     
                                                   ; 10002b64:    00 
    mov     dword [esp+0x4],0x19                   ; 10002b65:    c7 44 24 04 19 00 00     
                                                   ; 10002b6c:    00 
    add     ebp,0x44                               ; 10002b6d:    83 c5 44                 
    call    _drawing_draw_filled_rect              ; 10002b70:    e8 f2 e7 ff ff           
    mov     dword [esp],esi                        ; 10002b75:    89 34 24                 
    mov     dword [esp+0x18],ebx                   ; 10002b78:    89 5c 24 18              
    mov     dword [esp+0x14],0xff000000            ; 10002b7c:    c7 44 24 14 00 00 00     
                                                   ; 10002b83:    ff 
    mov     dword [esp+0x10],0x1                   ; 10002b84:    c7 44 24 10 01 00 00     
                                                   ; 10002b8b:    00 
    mov     dword [esp+0xc],0x5                    ; 10002b8c:    c7 44 24 0c 05 00 00     
                                                   ; 10002b93:    00 
    mov     dword [esp+0x8],0x5                    ; 10002b94:    c7 44 24 08 05 00 00     
                                                   ; 10002b9b:    00 
    mov     dword [esp+0x4],0x19                   ; 10002b9c:    c7 44 24 04 19 00 00     
                                                   ; 10002ba3:    00 
    add     esi,0xa                                ; 10002ba4:    83 c6 0a                 
    call    _drawing_draw_border_box               ; 10002ba7:    e8 34 e6 ff ff           
    cmp     esi,0x41                               ; 10002bac:    83 fe 41                 
    jne     idek                                   ; 10002baf:    75 87                    
    mov     eax,dword [edi]                        ; 10002bb1:    8b 07                    
    mov     ebp,0x23                               ; 10002bb3:    bd 23 00 00 00           
    test    eax,eax                                ; 10002bb8:    85 c0                    
    mov     dword [esp+0x14],ebx                   ; 10002bba:    89 5c 24 14              
    je      inactive_color_2                       ; 10002bbe:    74 75                    
jmp_2bc0:
    mov     dword [esp+0x10],0xff0ac80a            ; 10002bc0:    c7 44 24 10 0a c8 0a     
                                                   ; 10002bc7:    ff 
jmp_2bc8:
    mov     dword [esp],ebp                        ; 10002bc8:    89 2c 24                 
    mov     dword [esp+0xc],0x5                    ; 10002bcb:    c7 44 24 0c 05 00 00     
                                                   ; 10002bd2:    00 
    mov     dword [esp+0x8],0x5                    ; 10002bd3:    c7 44 24 08 05 00 00     
                                                   ; 10002bda:    00 
    mov     dword [esp+0x4],0x23                   ; 10002bdb:    c7 44 24 04 23 00 00     
                                                   ; 10002be2:    00 
    add     edi,0x44                               ; 10002be3:    83 c7 44                 
    call    _drawing_draw_filled_rect              ; 10002be6:    e8 7c e7 ff ff           
    mov     dword [esp],ebp                        ; 10002beb:    89 2c 24                 
    mov     dword [esp+0x18],ebx                   ; 10002bee:    89 5c 24 18              
    mov     dword [esp+0x14],0xff000000            ; 10002bf2:    c7 44 24 14 00 00 00     
                                                   ; 10002bf9:    ff 
    mov     dword [esp+0x10],0x1                   ; 10002bfa:    c7 44 24 10 01 00 00     
                                                   ; 10002c01:    00 
    mov     dword [esp+0xc],0x5                    ; 10002c02:    c7 44 24 0c 05 00 00     
                                                   ; 10002c09:    00 
    mov     dword [esp+0x8],0x5                    ; 10002c0a:    c7 44 24 08 05 00 00     
                                                   ; 10002c11:    00 
    mov     dword [esp+0x4],0x23                   ; 10002c12:    c7 44 24 04 23 00 00     
                                                   ; 10002c19:    00 
    add     ebp,0xa                                ; 10002c1a:    83 c5 0a                 
    call    _drawing_draw_border_box               ; 10002c1d:    e8 be e5 ff ff           
    cmp     ebp,0x41                               ; 10002c22:    83 fd 41                 
    je      not_a_clue                             ; 10002c25:    0f 84 99 fe ff ff        
    mov     eax,dword [edi]                        ; 10002c2b:    8b 07                    
    mov     dword [esp+0x14],ebx                   ; 10002c2d:    89 5c 24 14              
    test    eax,eax                                ; 10002c31:    85 c0                    
    jne     jmp_2bc0                               ; 10002c33:    75 8b                    
inactive_color_2:
    mov     dword [esp+0x10],0xff505050            ; 10002c35:    c7 44 24 10 50 50 50     
                                                   ; 10002c3c:    ff 
    jmp     jmp_2bc8                               ; 10002c3d:    eb 89                    
    nop                                            ; 10002c3f:    90                       
inactive_color:
    mov     dword [esp+0x10],0xff505050            ; 10002c40:    c7 44 24 10 50 50 50     
                                                   ; 10002c47:    ff 
    jmp     jmp_2b52                               ; 10002c48:    e9 05 ff ff ff           
    nop                                            ; 10002c4d:    90                       
    nop                                            ; 10002c4e:    90                       
    nop                                            ; 10002c4f:    90                       
