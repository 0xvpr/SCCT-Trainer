section     .text

extern      _VirtualProtect@16
extern      _VirtualAlloc@16
extern      _VirtualFree@12
extern      _memset
extern      _memcpy

global      _memory_find_dynamic_address
global      _memory_tramp_hook
global      _memory_detour
global      _memory_patch
global      _memory_nop

_memory_find_dynamic_address:
    push    esi                                              ; 100025d0:    56                       
    push    ebx                                              ; 100025d1:    53                       
    mov     esi,dword [esp+0x14]                             ; 100025d2:    8b 74 24 14              
    mov     ecx,dword [esp+0x10]                             ; 100025d6:    8b 4c 24 10              
    mov     eax,dword [esp+0xc]                              ; 100025da:    8b 44 24 0c              
    test    esi,esi                                          ; 100025de:    85 f6                    
    je      dynamic_exit                                     ; 100025e0:    0f 84 f3 00 00 00        
    mov     ebx,esi                                          ; 100025e6:    89 f3                    
    mov     eax,dword [eax]                                  ; 100025e8:    8b 00                    
    xor     edx,edx                                          ; 100025ea:    31 d2                    
    and     ebx,0x7                                          ; 100025ec:    83 e3 07                 
    je      one_depth                                        ; 100025ef:    74 7f                    
    cmp     ebx,0x1                                          ; 100025f1:    83 fb 01                 
    je      two_depth                                        ; 100025f4:    74 69                    
    cmp     ebx,0x2                                          ; 100025f6:    83 fb 02                 
    je      three_depth                                      ; 100025f9:    74 58                    
    cmp     ebx,0x3                                          ; 100025fb:    83 fb 03                 
    je      four_depth                                       ; 100025fe:    74 43                    
    cmp     ebx,0x4                                          ; 10002600:    83 fb 04                 
    je      five_depth                                       ; 10002603:    74 2e                    
    cmp     ebx,0x5                                          ; 10002605:    83 fb 05                 
    je      six_depth                                        ; 10002608:    74 19                    
    cmp     ebx,0x6                                          ; 1000260a:    83 fb 06                 
    jne     e0_exit                                          ; 1000260d:    0f 85 cd 00 00 00        
seven_depth:
    movzx   ebx,word [ecx+edx*2]                             ; 10002613:    0f b7 1c 51              
    mov     eax,dword [ebx+eax*1]                            ; 10002617:    8b 04 03                 
    test    eax,eax                                          ; 1000261a:    85 c0                    
    je      dynamic_exit                                     ; 1000261c:    0f 84 b7 00 00 00        
    inc     edx                                              ; 10002622:    42                       
six_depth:
    movzx   ebx,word [ecx+edx*2]                             ; 10002623:    0f b7 1c 51              
    mov     eax,dword [ebx+eax*1]                            ; 10002627:    8b 04 03                 
    test    eax,eax                                          ; 1000262a:    85 c0                    
    je      dynamic_exit                                     ; 1000262c:    0f 84 a7 00 00 00        
    inc     edx                                              ; 10002632:    42                       
five_depth:
    movzx   ebx,word [ecx+edx*2]                             ; 10002633:    0f b7 1c 51              
    mov     eax,dword [ebx+eax*1]                            ; 10002637:    8b 04 03                 
    test    eax,eax                                          ; 1000263a:    85 c0                    
    je      dynamic_exit                                     ; 1000263c:    0f 84 97 00 00 00        
    inc     edx                                              ; 10002642:    42                       
four_depth:
    movzx   ebx,word [ecx+edx*2]                             ; 10002643:    0f b7 1c 51              
    mov     eax,dword [ebx+eax*1]                            ; 10002647:    8b 04 03                 
    test    eax,eax                                          ; 1000264a:    85 c0                    
    je      dynamic_exit                                     ; 1000264c:    0f 84 87 00 00 00        
    inc     edx                                              ; 10002652:    42                       
three_depth:
    movzx   ebx,word [ecx+edx*2]                             ; 10002653:    0f b7 1c 51              
    mov     eax,dword [ebx+eax*1]                            ; 10002657:    8b 04 03                 
    test    eax,eax                                          ; 1000265a:    85 c0                    
    je      dynamic_exit                                     ; 1000265c:    74 7b                    
    inc     edx                                              ; 1000265e:    42                       
two_depth:
    movzx   ebx,word [ecx+edx*2]                             ; 1000265f:    0f b7 1c 51              
    add     ebx,eax                                          ; 10002663:    01 c3                    
    mov     eax,dword [ebx]                                  ; 10002665:    8b 03                    
    test    eax,eax                                          ; 10002667:    85 c0                    
    je      dynamic_exit                                     ; 10002669:    74 6e                    
    inc     edx                                              ; 1000266b:    42                       
    cmp     esi,edx                                          ; 1000266c:    39 d6                    
    je      pre_dynamic_exit                                 ; 1000266e:    74 67                    
one_depth:
    movzx   ebx,word [ecx+edx*2]                             ; 10002670:    0f b7 1c 51              
    mov     eax,dword [ebx+eax*1]                            ; 10002674:    8b 04 03                 
    test    eax,eax                                          ; 10002677:    85 c0                    
    je      dynamic_exit                                     ; 10002679:    74 5e                    
    movzx   ebx,word [ecx+edx*2+0x2]                         ; 1000267b:    0f b7 5c 51 02           
    mov     eax,dword [ebx+eax*1]                            ; 10002680:    8b 04 03                 
    test    eax,eax                                          ; 10002683:    85 c0                    
    je      dynamic_exit                                     ; 10002685:    74 52                    
    movzx   ebx,word [ecx+edx*2+0x4]                         ; 10002687:    0f b7 5c 51 04           
    mov     eax,dword [ebx+eax*1]                            ; 1000268c:    8b 04 03                 
    test    eax,eax                                          ; 1000268f:    85 c0                    
    je      dynamic_exit                                     ; 10002691:    74 46                    
    movzx   ebx,word [ecx+edx*2+0x6]                         ; 10002693:    0f b7 5c 51 06           
    mov     eax,dword [ebx+eax*1]                            ; 10002698:    8b 04 03                 
    test    eax,eax                                          ; 1000269b:    85 c0                    
    je      dynamic_exit                                     ; 1000269d:    74 3a                    
    movzx   ebx,word [ecx+edx*2+0x8]                         ; 1000269f:    0f b7 5c 51 08           
    mov     eax,dword [ebx+eax*1]                            ; 100026a4:    8b 04 03                 
    test    eax,eax                                          ; 100026a7:    85 c0                    
    je      dynamic_exit                                     ; 100026a9:    74 2e                    
    movzx   ebx,word [ecx+edx*2+0xa]                         ; 100026ab:    0f b7 5c 51 0a           
    mov     eax,dword [ebx+eax*1]                            ; 100026b0:    8b 04 03                 
    test    eax,eax                                          ; 100026b3:    85 c0                    
    je      dynamic_exit                                     ; 100026b5:    74 22                    
    movzx   ebx,word [ecx+edx*2+0xc]                         ; 100026b7:    0f b7 5c 51 0c           
    mov     eax,dword [ebx+eax*1]                            ; 100026bc:    8b 04 03                 
    test    eax,eax                                          ; 100026bf:    85 c0                    
    je      dynamic_exit                                     ; 100026c1:    74 16                    
    movzx   ebx,word [ecx+edx*2+0xe]                         ; 100026c3:    0f b7 5c 51 0e           
    add     ebx,eax                                          ; 100026c8:    01 c3                    
    mov     eax,dword [ebx]                                  ; 100026ca:    8b 03                    
    test    eax,eax                                          ; 100026cc:    85 c0                    
    je      dynamic_exit                                     ; 100026ce:    74 09                    
    add     edx,0x8                                          ; 100026d0:    83 c2 08                 
    cmp     esi,edx                                          ; 100026d3:    39 d6                    
    jne     one_depth                                        ; 100026d5:    75 99                    
pre_dynamic_exit:
    mov     eax,ebx                                          ; 100026d7:    89 d8                    
dynamic_exit:
    pop     ebx                                              ; 100026d9:    5b                       
    pop     esi                                              ; 100026da:    5e                       
    ret                                                      ; 100026db:    c3                       
    lea     esi,[esi+0x0]                                    ; 100026dc:    8d 74 26 00              
e0_exit:
    movzx   edx,word [ecx]                                   ; 100026e0:    0f b7 11                 
    mov     eax,dword [edx+eax*1]                            ; 100026e3:    8b 04 02                 
    test    eax,eax                                          ; 100026e6:    85 c0                    
    je      dynamic_exit                                     ; 100026e8:    74 ef                    
    mov     edx,0x1                                          ; 100026ea:    ba 01 00 00 00           
    jmp     seven_depth                                      ; 100026ef:    e9 1f ff ff ff           
    lea     esi,[esi+0x0]                                    ; 100026f4:    8d b4 26 00 00 00 00     
    lea     esi,[esi+0x0]                                    ; 100026fb:    8d 74 26 00              
    nop                                                      ; 100026ff:    90                       

_memory_nop:                                                 ; 10002700:    <_memory_nop>
    push    ebp                                              ; 10002700:    55                       
    push    edi                                              ; 10002701:    57                       
    push    esi                                              ; 10002702:    56                       
    push    ebx                                              ; 10002703:    53                       
    sub     esp,0x2c                                         ; 10002704:    83 ec 2c                 
    mov     ebx,dword [esp+0x40]                             ; 10002707:    8b 5c 24 40              
    mov     esi,dword [esp+0x44]                             ; 1000270b:    8b 74 24 44              
    lea     ebp,[esp+0x1c]                                   ; 1000270f:    8d 6c 24 1c              
    mov     dword [esp+0xc],ebp                              ; 10002713:    89 6c 24 0c              
    mov     dword [esp+0x4],esi                              ; 10002717:    89 74 24 04              
    mov     dword [esp],ebx                                  ; 1000271b:    89 1c 24                 
    mov     dword [esp+0x8],0x80                             ; 1000271e:    c7 44 24 08 80 00 00     
                                                             ; 10002725:    00 
    mov     edi,_VirtualProtect@16                           ; 10002726:    8b 3d d0 80 00 10        
    call    edi                                              ; 1000272c:    ff d7                    
    sub     esp,0x10                                         ; 1000272e:    83 ec 10                 
    mov     dword [esp+0x8],esi                              ; 10002731:    89 74 24 08              
    mov     dword [esp],ebx                                  ; 10002735:    89 1c 24                 
    mov     dword [esp+0x4],0x90                             ; 10002738:    c7 44 24 04 90 00 00     
                                                             ; 1000273f:    00 
    call    _memset                                          ; 10002740:    e8 8b 05 00 00           
    mov     eax,dword [esp+0x1c]                             ; 10002745:    8b 44 24 1c              
    mov     dword [esp+0xc],ebp                              ; 10002749:    89 6c 24 0c              
    mov     dword [esp+0x4],esi                              ; 1000274d:    89 74 24 04              
    mov     dword [esp],ebx                                  ; 10002751:    89 1c 24                 
    mov     dword [esp+0x8],eax                              ; 10002754:    89 44 24 08              
    call    edi                                              ; 10002758:    ff d7                    
    sub     esp,0x10                                         ; 1000275a:    83 ec 10                 
    add     esp,0x2c                                         ; 1000275d:    83 c4 2c                 
    pop     ebx                                              ; 10002760:    5b                       
    pop     esi                                              ; 10002761:    5e                       
    pop     edi                                              ; 10002762:    5f                       
    pop     ebp                                              ; 10002763:    5d                       
    ret                                                      ; 10002764:    c3                       
    lea     esi,[esi+0x0]                                    ; 10002765:    8d b4 26 00 00 00 00     
    lea     esi,[esi+0x0]                                    ; 1000276c:    8d 74 26 00              

_memory_patch:                                               ; 10002770:    <_memory_patch>
    push    ebp                                              ; 10002770:    55                       
    push    edi                                              ; 10002771:    57                       
    push    esi                                              ; 10002772:    56                       
    push    ebx                                              ; 10002773:    53                       
    sub     esp,0x2c                                         ; 10002774:    83 ec 2c                 
    mov     ebx,dword [esp+0x40]                             ; 10002777:    8b 5c 24 40              
    mov     esi,dword [esp+0x48]                             ; 1000277b:    8b 74 24 48              
    lea     ebp,[esp+0x1c]                                   ; 1000277f:    8d 6c 24 1c              
    mov     dword [esp+0xc],ebp                              ; 10002783:    89 6c 24 0c              
    mov     dword [esp+0x4],esi                              ; 10002787:    89 74 24 04              
    mov     dword [esp],ebx                                  ; 1000278b:    89 1c 24                 
    mov     dword [esp+0x8],0x80                             ; 1000278e:    c7 44 24 08 80 00 00     
                                                             ; 10002795:    00 
    mov     edi,_VirtualProtect@16                           ; 10002796:    8b 3d d0 80 00 10        
    call    edi                                              ; 1000279c:    ff d7                    
    sub     esp,0x10                                         ; 1000279e:    83 ec 10                 
    mov     eax,dword [esp+0x44]                             ; 100027a1:    8b 44 24 44              
    mov     dword [esp+0x8],esi                              ; 100027a5:    89 74 24 08              
    mov     dword [esp],ebx                                  ; 100027a9:    89 1c 24                 
    mov     dword [esp+0x4],eax                              ; 100027ac:    89 44 24 04              
    call    _memcpy                                          ; 100027b0:    e8 23 05 00 00           
    mov     edx,dword [esp+0x1c]                             ; 100027b5:    8b 54 24 1c              
    mov     dword [esp+0xc],ebp                              ; 100027b9:    89 6c 24 0c              
    mov     dword [esp+0x4],esi                              ; 100027bd:    89 74 24 04              
    mov     dword [esp],ebx                                  ; 100027c1:    89 1c 24                 
    mov     dword [esp+0x8],edx                              ; 100027c4:    89 54 24 08              
    call    edi                                              ; 100027c8:    ff d7                    
    sub     esp,0x10                                         ; 100027ca:    83 ec 10                 
    add     esp,0x2c                                         ; 100027cd:    83 c4 2c                 
    pop     ebx                                              ; 100027d0:    5b                       
    pop     esi                                              ; 100027d1:    5e                       
    pop     edi                                              ; 100027d2:    5f                       
    pop     ebp                                              ; 100027d3:    5d                       
    ret                                                      ; 100027d4:    c3                       
    lea     esi,[esi+0x0]                                    ; 100027d5:    8d b4 26 00 00 00 00     
    lea     esi,[esi+0x0]                                    ; 100027dc:    8d 74 26 00              

_memory_detour:                                              ; 100027e0:    <_memory_detour>
    push    ebp                                              ; 100027e0:    55                       
    xor     eax,eax                                          ; 100027e1:    31 c0                    
    push    edi                                              ; 100027e3:    57                       
    push    esi                                              ; 100027e4:    56                       
    push    ebx                                              ; 100027e5:    53                       
    sub     esp,0x2c                                         ; 100027e6:    83 ec 2c                 
    mov     esi,dword [esp+0x48]                             ; 100027e9:    8b 74 24 48              
    mov     ebx,dword [esp+0x40]                             ; 100027ed:    8b 5c 24 40              
    cmp     esi,0x4                                          ; 100027f1:    83 fe 04                 
    jbe     detour_exit                                      ; 100027f4:    76 62                    
    lea     ebp,[esp+0x1c]                                   ; 100027f6:    8d 6c 24 1c              
    mov     dword [esp+0xc],ebp                              ; 100027fa:    89 6c 24 0c              
    mov     dword [esp+0x8],0x40                             ; 100027fe:    c7 44 24 08 40 00 00     
                                                             ; 10002805:    00 
    mov     dword [esp+0x4],esi                              ; 10002806:    89 74 24 04              
    mov     dword [esp],ebx                                  ; 1000280a:    89 1c 24                 
    mov     edi,_VirtualProtect@16                           ; 1000280d:    8b 3d d0 80 00 10        
    call    edi                                              ; 10002813:    ff d7                    
    sub     esp,0x10                                         ; 10002815:    83 ec 10                 
    mov     dword [esp+0x8],esi                              ; 10002818:    89 74 24 08              
    mov     dword [esp+0x4],0x90                             ; 1000281c:    c7 44 24 04 90 00 00     
                                                             ; 10002823:    00 
    mov     dword [esp],ebx                                  ; 10002824:    89 1c 24                 
    call    _memset                                          ; 10002827:    e8 a4 04 00 00           
    mov     eax,dword [esp+0x44]                             ; 1000282c:    8b 44 24 44              
    mov     edx,dword [esp+0x1c]                             ; 10002830:    8b 54 24 1c              
    sub     eax,0x5                                          ; 10002834:    83 e8 05                 
    sub     eax,ebx                                          ; 10002837:    29 d8                    
    mov     byte [ebx],0xe9                                  ; 10002839:    c6 03 e9                 
    mov     dword [ebx+0x1],eax                              ; 1000283c:    89 43 01                 
    mov     dword [esp+0xc],ebp                              ; 1000283f:    89 6c 24 0c              
    mov     dword [esp+0x8],edx                              ; 10002843:    89 54 24 08              
    mov     dword [esp+0x4],esi                              ; 10002847:    89 74 24 04              
    mov     dword [esp],ebx                                  ; 1000284b:    89 1c 24                 
    call    edi                                              ; 1000284e:    ff d7                    
    sub     esp,0x10                                         ; 10002850:    83 ec 10                 
    mov     eax,0x1                                          ; 10002853:    b8 01 00 00 00           
detour_exit:
    add     esp,0x2c                                         ; 10002858:    83 c4 2c                 
    pop     ebx                                              ; 1000285b:    5b                       
    pop     esi                                              ; 1000285c:    5e                       
    pop     edi                                              ; 1000285d:    5f                       
    pop     ebp                                              ; 1000285e:    5d                       
    ret                                                      ; 1000285f:    c3                       

_memory_tramp_hook:                                          ; 10002830:    <_memory_tramp_hook>:
    push   ebp                                               ; 10002830:    55                      
    push   edi                                               ; 10002831:    57                      
    push   esi                                               ; 10002832:    56                      
    push   ebx                                               ; 10002833:    53                      
    xor    ebx,ebx                                           ; 10002834:    31 db                   
    sub    esp,0x1c                                          ; 10002836:    83 ec 1c                
    mov    esi,dword [esp+0x38]                              ; 10002839:    8b 74 24 38             
    mov    edi,dword [esp+0x30]                              ; 1000283d:    8b 7c 24 30             
    cmp    esi,0x4                                           ; 10002841:    83 fe 04                
    jbe    tramp_exit                                        ; 10002844:    76 60                   
    lea    ebp,[esi+0x5]                                     ; 10002846:    8d 6e 05                
    mov    dword [esp+0xc],0x40                              ; 10002849:    c7 44 24 0c 40 00 00    
                                                             ; 10002850:    00
    mov    dword [esp+0x8],0x3000                            ; 10002851:    c7 44 24 08 00 30 00    
                                                             ; 10002858:    00
    mov    dword [esp+0x4],ebp                               ; 10002859:    89 6c 24 04             
    mov    dword [esp],0x0                                   ; 1000285d:    c7 04 24 00 00 00 00    
    call   _VirtualAlloc@16                                  ; 10002864:    ff 15 c8 80 00 10       
    sub    esp,0x10                                          ; 1000286a:    83 ec 10                
    mov    dword [esp+0x8],esi                               ; 1000286d:    89 74 24 08             
    mov    dword [esp+0x4],edi                               ; 10002871:    89 7c 24 04             
    mov    dword [esp],eax                                   ; 10002875:    89 04 24                
    mov    ebx,eax                                           ; 10002878:    89 c3                   
    call   _memcpy                                           ; 1000287a:    e8 29 04 00 00          
    mov    eax,edi                                           ; 1000287f:    89 f8                   
    sub    eax,ebx                                           ; 10002881:    29 d8                   
    mov    edx,dword [esp+0x34]                              ; 10002883:    8b 54 24 34             
    sub    eax,0x5                                           ; 10002887:    83 e8 05                
    mov    byte [ebx+esi*1],0xe9                             ; 1000288a:    c6 04 33 e9             
    mov    dword [ebx+esi*1+0x1],eax                         ; 1000288e:    89 44 33 01             
    mov    dword [esp+0x8],esi                               ; 10002892:    89 74 24 08             
    mov    dword [esp+0x4],edx                               ; 10002896:    89 54 24 04             
    mov    dword [esp],edi                                   ; 1000289a:    89 3c 24                
    call   _memory_detour                                    ; 1000289d:    e8 3e ed ff ff          
    test   eax,eax                                           ; 100028a2:    85 c0                   
    je     detour_fail_exit                                  ; 100028a4:    74 0a                   
tramp_exit:
    add    esp,0x1c                                          ; 100028a6:    83 c4 1c                
    mov    eax,ebx                                           ; 100028a9:    89 d8                   
    pop    ebx                                               ; 100028ab:    5b                      
    pop    esi                                               ; 100028ac:    5e                      
    pop    edi                                               ; 100028ad:    5f                      
    pop    ebp                                               ; 100028ae:    5d                      
    ret                                                      ; 100028af:    c3                      
detour_fail_exit:
    mov    dword [esp+0x4],ebp                               ; 100028b0:    89 6c 24 04             
    mov    dword [esp],ebx                                   ; 100028b4:    89 1c 24                
    mov    dword [esp+0x8],0x8000                            ; 100028b7:    c7 44 24 08 00 80 00    
                                                             ; 100028be:    00
    xor    ebx,ebx                                           ; 100028bf:    31 db                   
    call   _VirtualFree@12                                   ; 100028c1:    ff 15 cc 80 00 10       
    sub    esp,0xc                                           ; 100028c7:    83 ec 0c                
    add    esp,0x1c                                          ; 100028ca:    83 c4 1c                
    mov    eax,ebx                                           ; 100028cd:    89 d8                   
    pop    ebx                                               ; 100028cf:    5b                      
    pop    esi                                               ; 100028d0:    5e                      
    pop    edi                                               ; 100028d1:    5f                      
    pop    ebp                                               ; 100028d2:    5d                      
    ret                                                      ; 100028d3:    c3                      
    nop                                                      ; 100028d4:    90                      
    nop                                                      ; 100028d5:    90                      
    nop                                                      ; 100028d6:    90                      
    nop                                                      ; 100028d7:    90                      
    nop                                                      ; 100028d8:    90                      
    nop                                                      ; 100028d9:    90                      
    nop                                                      ; 100028da:    90                      
    nop                                                      ; 100028db:    90                      
    nop                                                      ; 100028dc:    90                      
    nop                                                      ; 100028dd:    90                      
    nop                                                      ; 100028de:    90                      
    nop                                                      ; 100028df:    90                      
