section     .text

global      _drawing_draw_border_box
global      _drawing_draw_filled_rect

_drawing_draw_border_box:
    push    ebp                             ; 0 : 55                   
    push    edi                             ; 1 : 57                   
    push    esi                             ; 2 : 56                   
    push    ebx                             ; 3 : 53                   
    sub     esp, 0x4c                       ; 4 : 83 ec 4c             
    mov     esi, dword [esp+0x60]           ; 7 : 8b 74 24 60          
    mov     eax, dword [esp+0x64]           ; b : 8b 44 24 64          
    mov     edx, dword [esp+0x68]           ; f : 8b 54 24 68          
    mov     ebx, dword [esp+0x78]           ; 13 : 8b 5c 24 78          
    mov     ecx, dword [esp+0x74]           ; 17 : 8b 4c 24 74          
    lea     ebp, [esp+0x30]                 ; 1b : 8d 6c 24 30          
    add     edx, esi                        ; 1f : 01 f2                
    mov     dword [esp+0x34], eax           ; 21 : 89 44 24 34          
    add     eax, dword [esp+0x70]           ; 25 : 03 44 24 70          
    mov     edi, dword [ebx]                ; 29 : 8b 3b                
    mov     dword [esp+0x30], esi           ; 2b : 89 74 24 30          
    mov     dword [esp+0x38], edx           ; 2f : 89 54 24 38          
    mov     dword [esp+0x10], ecx           ; 33 : 89 4c 24 10          
    mov     dword [esp+0x8], ebp            ; 37 : 89 6c 24 08          
    mov     dword [esp], ebx                ; 3b : 89 1c 24             
    mov     dword [esp+0x3c], eax           ; 3e : 89 44 24 3c          
    mov     dword [esp+0x18], 0x0           ; 42 : c7 44 24 18 00 00 00 
                                            ; 49 : 00 
    mov     dword [esp+0x14], 0x0           ; 4a : c7 44 24 14 00 00 00 
                                            ; 51 : 00 
    mov     dword [esp+0xc], 0x7            ; 52 : c7 44 24 0c 07 00 00 
                                            ; 59 : 00 
    mov     dword [esp+0x4], 0x1            ; 5a : c7 44 24 04 01 00 00 
                                            ; 61 : 00 
    mov     dword [esp+0x2c], edx           ; 62 : 89 54 24 2c          
    call    dword [edi+0xac]                ; 66 : ff 97 ac 00 00 00    
    sub     esp, 0x1c                       ; 6c : 83 ec 1c             
    mov     edx, dword [esp+0x70]           ; 6f : 8b 54 24 70          
    mov     edi, dword [esp+0x64]           ; 73 : 8b 7c 24 64          
    mov     eax, dword [esp+0x64]           ; 77 : 8b 44 24 64          
    mov     ecx, dword [esp+0x74]           ; 7b : 8b 4c 24 74          
    add     edi, dword [esp+0x6c]           ; 7f : 03 7c 24 6c          
    add     edx, esi                        ; 83 : 01 f2                
    mov     dword [esp+0x30], esi           ; 85 : 89 74 24 30          
    mov     dword [esp+0x34], eax           ; 89 : 89 44 24 34          
    mov     dword [esp+0x38], edx           ; 8d : 89 54 24 38          
    mov     eax, dword [ebx]                ; 91 : 8b 03                
    mov     dword [esp+0x3c], edi           ; 93 : 89 7c 24 3c          
    mov     dword [esp+0x10], ecx           ; 97 : 89 4c 24 10          
    mov     dword [esp+0x8], ebp            ; 9b : 89 6c 24 08          
    mov     dword [esp], ebx                ; 9f : 89 1c 24             
    mov     dword [esp+0x18], 0x0           ; a2 : c7 44 24 18 00 00 00 
                                            ; a9 : 00 
    mov     dword [esp+0x14], 0x0           ; aa : c7 44 24 14 00 00 00 
                                            ; b1 : 00 
    mov     dword [esp+0xc], 0x7            ; b2 : c7 44 24 0c 07 00 00 
                                            ; b9 : 00 
    mov     dword [esp+0x4], 0x1            ; ba : c7 44 24 04 01 00 00 
                                            ; c1 : 00 
    call    dword [eax+0xac]                ; c2 : ff 90 ac 00 00 00    
    sub     esp, 0x1c                       ; c8 : 83 ec 1c             
    mov     edx, dword [esp+0x2c]           ; cb : 8b 54 24 2c          
    mov     eax, dword [esp+0x64]           ; cf : 8b 44 24 64          
    mov     ecx, dword [esp+0x74]           ; d3 : 8b 4c 24 74          
    mov     dword [esp+0x30], edx           ; d7 : 89 54 24 30          
    add     edx, dword [esp+0x70]           ; db : 03 54 24 70          
    mov     dword [esp+0x34], eax           ; df : 89 44 24 34          
    mov     dword [esp+0x38], edx           ; e3 : 89 54 24 38          
    mov     eax, dword [ebx]                ; e7 : 8b 03                
    mov     dword [esp+0x3c], edi           ; e9 : 89 7c 24 3c          
    mov     dword [esp+0x10], ecx           ; ed : 89 4c 24 10          
    mov     dword [esp+0x8], ebp            ; f1 : 89 6c 24 08          
    mov     dword [esp], ebx                ; f5 : 89 1c 24             
    mov     dword [esp+0x18], 0x0           ; f8 : c7 44 24 18 00 00 00 
                                            ; ff : 00 
    mov     dword [esp+0x14], 0x0           ; 100 : c7 44 24 14 00 00 00 
                                            ; 107 : 00 
    mov     dword [esp+0xc], 0x7            ; 108 : c7 44 24 0c 07 00 00 
                                            ; 10f : 00 
    mov     dword [esp+0x4], 0x1            ; 110 : c7 44 24 04 01 00 00 
                                            ; 117 : 00 
    call    dword [eax+0xac]                ; 118 : ff 90 ac 00 00 00    
    sub     esp, 0x1c                       ; 11e : 83 ec 1c             
    mov     edx, dword [esp+0x68]           ; 121 : 8b 54 24 68          
    mov     dword [esp+0x30], esi           ; 125 : 89 74 24 30          
    add     edx, dword [esp+0x70]           ; 129 : 03 54 24 70          
    add     esi, edx                        ; 12d : 01 d6                
    mov     dword [esp+0x38], esi           ; 12f : 89 74 24 38          
    mov     esi, dword [esp+0x70]           ; 133 : 8b 74 24 70          
    mov     dword [esp+0x34], edi           ; 137 : 89 7c 24 34          
    add     esi, edi                        ; 13b : 01 fe                
    mov     edi, dword [esp+0x74]           ; 13d : 8b 7c 24 74          
    mov     eax, dword [ebx]                ; 141 : 8b 03                
    mov     dword [esp+0x3c], esi           ; 143 : 89 74 24 3c          
    mov     dword [esp+0x10], edi           ; 147 : 89 7c 24 10          
    mov     dword [esp+0x8], ebp            ; 14b : 89 6c 24 08          
    mov     dword [esp], ebx                ; 14f : 89 1c 24             
    mov     dword [esp+0x18], 0x0           ; 152 : c7 44 24 18 00 00 00 
                                            ; 159 : 00 
    mov     dword [esp+0x14], 0x0           ; 15a : c7 44 24 14 00 00 00 
                                            ; 161 : 00 
    mov     dword [esp+0xc], 0x7            ; 162 : c7 44 24 0c 07 00 00 
                                            ; 169 : 00 
    mov     dword [esp+0x4], 0x1            ; 16a : c7 44 24 04 01 00 00 
                                            ; 171 : 00 
    call    dword [eax+0xac]                ; 172 : ff 90 ac 00 00 00    
    sub     esp, 0x1c                       ; 178 : 83 ec 1c             
    add     esp, 0x4c                       ; 17b : 83 c4 4c             
    pop     ebx                             ; 17e : 5b                   
    pop     esi                             ; 17f : 5e                   
    pop     edi                             ; 180 : 5f                   
    pop     ebp                             ; 181 : 5d                   
    ret                                     ; 182 : c3                   
    lea     esi, [esi+0x0]                  ; 183 : 8d b4 26 00 00 00 00 
    lea     esi, [esi+0x0]                  ; 18a : 8d b6 00 00 00 00    
                                       
_drawing_draw_filled_rect:
    sub     esp, 0x3c                       ; 190 : 83 ec 3c             
    mov     edx, dword [esp+0x40]           ; 193 : 8b 54 24 40          
    mov     eax, dword [esp+0x44]           ; 197 : 8b 44 24 44          
    mov     dword [esp+0x20], edx           ; 19b : 89 54 24 20          
    add     edx, dword [esp+0x48]           ; 19f : 03 54 24 48          
    mov     ecx, dword [esp+0x54]           ; 1a3 : 8b 4c 24 54          
    mov     dword [esp+0x28], edx           ; 1a7 : 89 54 24 28          
    mov     edx, dword [esp+0x50]           ; 1ab : 8b 54 24 50          
    mov     dword [esp+0x24], eax           ; 1af : 89 44 24 24          
    add     eax, dword [esp+0x4c]           ; 1b3 : 03 44 24 4c          
    mov     dword [esp+0x2c], eax           ; 1b7 : 89 44 24 2c          
    mov     eax, dword [ecx]                ; 1bb : 8b 01                
    mov     dword [esp+0x10], edx           ; 1bd : 89 54 24 10          
    lea     edx, [esp+0x20]                 ; 1c1 : 8d 54 24 20          
    mov     dword [esp+0x18], 0x0           ; 1c5 : c7 44 24 18 00 00 00 
                                            ; 1cc : 00 
    mov     dword [esp+0x14], 0x0           ; 1cd : c7 44 24 14 00 00 00 
                                            ; 1d4 : 00 
    mov     dword [esp+0xc], 0x7            ; 1d5 : c7 44 24 0c 07 00 00 
                                            ; 1dc : 00 
    mov     dword [esp+0x8], edx            ; 1dd : 89 54 24 08          
    mov     dword [esp+0x4], 0x1            ; 1e1 : c7 44 24 04 01 00 00 
                                            ; 1e8 : 00 
    mov     dword [esp], ecx                ; 1e9 : 89 0c 24             
    call    dword [eax+0xac]                ; 1ec : ff 90 ac 00 00 00    
    sub     esp, 0x1c                       ; 1f2 : 83 ec 1c             
    add     esp, 0x3c                       ; 1f5 : 83 c4 3c             
    ret                                     ; 1f8 : c3                   
    nop                                     ; 1f9 : 90                   
    nop                                     ; 1fa : 90                   
    nop                                     ; 1fb : 90                   
    nop                                     ; 1fc : 90                   
    nop                                     ; 1fd : 90                   
    nop                                     ; 1fe : 90                   
    nop                                     ; 1ff : 90                   
