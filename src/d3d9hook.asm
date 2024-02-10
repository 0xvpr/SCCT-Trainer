section     .data
g_window:
    dd      0

section     .text
extern      _EnumWindows@8
extern      _GetCurrentProcessId@0
extern      _GetWindowThreadProcessId@8
extern      _Direct3DCreate9@4
extern      _memcpy

global      _EnumWindowsCallback@8
global      _GetProcessWindow
global      _GetD3D9Device@8

_EnumWindowsCallback@8:
    push   ebx                                     ; 10001360:  53                 
    sub    esp,0x28                                ; 10001361:  83 ec 28           
    mov    ebx,dword [esp+0x30]                    ; 10001364:  8b 5c 24 30        
    lea    eax,[esp+0x1c]                          ; 10001368:  8d 44 24 1c        
    mov    dword [esp+0x4],eax                     ; 1000136c:  89 44 24 04        
    mov    dword [esp],ebx                         ; 10001370:  89 1c 24           
    call   _GetWindowThreadProcessId@8             ; 10001373:  ff 15 ec 80 00 10  
    sub    esp,0x8                                 ; 10001379:  83 ec 08           
    call   _GetCurrentProcessId@0                  ; 1000137c:  ff 15 c0 80 00 10  
    mov    edx,eax                                 ; 10001382:  89 c2              
    mov    eax,0x1                                 ; 10001384:  b8 01 00 00 00     
    cmp    edx,dword [esp+0x1c]                    ; 10001389:  3b 54 24 1c        
    jne    callback_exit                           ; 1000138d:  75 08              
    mov    dword [g_window],ebx                    ; 1000138f:  89 1d 00 60 00 10  
    xor    eax,eax                                 ; 10001395:  31 c0              
callback_exit:
    add    esp,0x28                                ; 10001397:  83 c4 28           
    pop    ebx                                     ; 1000139a:  5b                 
    ret    0x8                                     ; 1000139b:  c2 08 00           
    xchg   ax,ax                                   ; 1000139e:  66 90              

_GetProcessWindow:
    sub    esp,0x1c                                ; 100013a0:  83 ec 1c            
    mov    dword [esp+0x4],0x0                     ; 100013a3:  c7 44 24 04 00 00 00
                                                   ; 100013aa:  00 
    mov    dword [esp],_EnumWindowsCallback@8      ; 100013ab:  c7 04 24 60 13 00 10
    mov    dword [g_window],0x0                    ; 100013b2:  c7 05 00 60 00 10 00
                                                   ; 100013b9:  00 00 00 
    call   _EnumWindows@8                          ; 100013bc:  ff 15 e4 80 00 10   
    sub    esp,0x8                                 ; 100013c2:  83 ec 08            
    mov    eax,[g_window]                          ; 100013c5:  a1 00 60 00 10      
    add    esp,0x1c                                ; 100013ca:  83 c4 1c            
    ret                                            ; 100013cd:  c3                  
    xchg   ax,ax                                   ; 100013ce:  66 90               

_GetD3D9Device@8:
    push   ebp                                     ; 100013d0:   55                  
    push   edi                                     ; 100013d1:   57                  
    push   esi                                     ; 100013d2:   56                  
    push   ebx                                     ; 100013d3:   53                  
    sub    esp,0x6c                                ; 100013d4:   83 ec 6c            
    mov    esi,dword [esp+0x80]                    ; 100013d7:   8b b4 24 80 00 00 00
    test   esi,esi                                 ; 100013de:   85 f6               
    je     d3d9_exit                               ; 100013e0:   0f 84 15 01 00 00   
    mov    dword [esp],0x20                        ; 100013e6:   c7 04 24 20 00 00 00
    call   _Direct3DCreate9@4                      ; 100013ed:   e8 8e 18 00 00      
    sub    esp,0x4                                 ; 100013f2:   83 ec 04            
    mov    ebx,eax                                 ; 100013f5:   89 c3               
    test   eax,eax                                 ; 100013f7:   85 c0               
    je     d3d9_exit                               ; 100013f9:   0f 84 fc 00 00 00   
    lea    ebp,[esp+0x28]                          ; 100013ff:   8d 6c 24 28         
    xor    eax,eax                                 ; 10001403:   31 c0               
    mov    ecx,0xe                                 ; 10001405:   b9 0e 00 00 00      
    mov    edi,ebp                                 ; 1000140a:   89 ef               
    rep stosd; dword es:[edi],eax                  ; 1000140c:   f3 ab               
    mov    dword [esp+0x24],0x0                    ; 1000140e:   c7 44 24 24 00 00 00
                                                   ; 10001415:   00 
    mov    dword [esp+0x40],0x1                    ; 10001416:   c7 44 24 40 01 00 00
                                                   ; 1000141d:   00 
    lea    edi,[esp+0x24]                          ; 1000141e:   8d 7c 24 24         
    call   _GetProcessWindow                       ; 10001422:   e8 17 fc ff ff      
    mov    dword [esp+0x44],eax                    ; 10001427:   89 44 24 44         
    mov    edx,dword [ebx]                         ; 1000142b:   8b 13               
    mov    dword [esp+0x48],0x1                    ; 1000142d:   c7 44 24 48 01 00 00
                                                   ; 10001434:   00 
    mov    dword [esp+0x18],edi                    ; 10001435:   89 7c 24 18         
    mov    dword [esp+0x14],ebp                    ; 10001439:   89 6c 24 14         
    mov    dword [esp+0x10],0x20                   ; 1000143d:   c7 44 24 10 20 00 00
                                                   ; 10001444:   00 
    mov    dword [esp+0xc],eax                     ; 10001445:   89 44 24 0c         
    mov    dword [esp+0x8],0x1                     ; 10001449:   c7 44 24 08 01 00 00
                                                   ; 10001450:   00 
    mov    dword [esp+0x4],0x0                     ; 10001451:   c7 44 24 04 00 00 00
                                                   ; 10001458:   00 
    mov    dword [esp],ebx                         ; 10001459:   89 1c 24            
    call   dword [edx+0x40]                        ; 1000145c:   ff 52 40            
    sub    esp,0x1c                                ; 1000145f:   83 ec 1c            
    test   eax,eax                                 ; 10001462:   85 c0               
    je     clean_exit                              ; 10001464:   74 46               
    mov    eax,dword [esp+0x48]                    ; 10001466:   8b 44 24 48         
    xor    ecx,ecx                                 ; 1000146a:   31 c9               
    test   eax,eax                                 ; 1000146c:   85 c0               
    mov    eax,dword [ebx]                         ; 1000146e:   8b 03               
    mov    dword [esp+0x14],ebp                    ; 10001470:   89 6c 24 14         
    mov    ebp,dword [esp+0x44]                    ; 10001474:   8b 6c 24 44         
    sete   cl                                      ; 10001478:   0f 94 c1            
    mov    dword [esp+0x48],ecx                    ; 1000147b:   89 4c 24 48         
    mov    dword [esp+0x18],edi                    ; 1000147f:   89 7c 24 18         
    mov    dword [esp+0x10],0x20                   ; 10001483:   c7 44 24 10 20 00 00
                                                   ; 1000148a:   00 
    mov    dword [esp+0xc],ebp                     ; 1000148b:   89 6c 24 0c         
    mov    dword [esp+0x8],0x1                     ; 1000148f:   c7 44 24 08 01 00 00
                                                   ; 10001496:   00 
    mov    dword [esp+0x4],0x0                     ; 10001497:   c7 44 24 04 00 00 00
                                                   ; 1000149e:   00 
    mov    dword [esp],ebx                         ; 1000149f:   89 1c 24            
    call   dword [eax+0x40]                        ; 100014a2:   ff 50 40            
    sub    esp,0x1c                                ; 100014a5:   83 ec 1c            
    test   eax,eax                                 ; 100014a8:   85 c0               
    jne    d3d9_exit                               ; 100014aa:   75 44               
clean_exit:
    mov    edi,dword [esp+0x24]                    ; 100014ac:   8b 7c 24 24         
    mov    edx,dword [esp+0x84]                    ; 100014b0:   8b 94 24 84 00 00 00
    mov    ecx,dword [edi]                         ; 100014b7:   8b 0f               
    mov    dword [esp+0x8],edx                     ; 100014b9:   89 54 24 08         
    mov    dword [esp+0x4],ecx                     ; 100014bd:   89 4c 24 04         
    mov    dword [esp],esi                         ; 100014c1:   89 34 24            
    call   _memcpy                                 ; 100014c4:   e8 07 18 00 00      
    mov    esi,dword [edi]                         ; 100014c9:   8b 37               
    mov    dword [esp],edi                         ; 100014cb:   89 3c 24            
    call   dword [esi+0x8]                         ; 100014ce:   ff 56 08            
    sub    esp,0x4                                 ; 100014d1:   83 ec 04            
    mov    eax,dword [ebx]                         ; 100014d4:   8b 03               
    mov    dword [esp],ebx                         ; 100014d6:   89 1c 24            
    call   dword [eax+0x8]                         ; 100014d9:   ff 50 08            
    sub    esp,0x4                                 ; 100014dc:   83 ec 04            
    add    esp,0x6c                                ; 100014df:   83 c4 6c            
    pop    ebx                                     ; 100014e2:   5b                  
    pop    esi                                     ; 100014e3:   5e                  
    pop    edi                                     ; 100014e4:   5f                  
    mov    eax,0x1                                 ; 100014e5:   b8 01 00 00 00      
    pop    ebp                                     ; 100014ea:   5d                  
    ret                                            ; 100014eb:   c3                  
    lea    esi,[esi+0x0]                           ; 100014ec:   8d 74 26 00         
    mov    ebp,dword [ebx]                         ; 100014f0:   8b 2b               
    mov    dword [esp],ebx                         ; 100014f2:   89 1c 24            
    call   dword [ebp+0x8]                         ; 100014f5:   ff 55 08            
    sub    esp,0x4                                 ; 100014f8:   83 ec 04            
d3d9_exit:
    add    esp,0x6c                                ; 100014fb:   83 c4 6c            
    pop    ebx                                     ; 100014fe:   5b                  
    pop    esi                                     ; 100014ff:   5e                  
    pop    edi                                     ; 10001500:   5f                  
    xor    eax,eax                                 ; 10001501:   31 c0               
    pop    ebp                                     ; 10001503:   5d                  
    ret                                            ; 10001504:   c3                  
    nop                                            ; 10001505:   90                  
    nop                                            ; 10001506:   90                  
    nop                                            ; 10001507:   90                  
    nop                                            ; 10001508:   90                  
    nop                                            ; 10001509:   90                  
    nop                                            ; 1000150a:   90                  
    nop                                            ; 1000150b:   90                  
    nop                                            ; 1000150c:   90                  
    nop                                            ; 1000150d:   90                  
    nop                                            ; 1000150e:   90                  
    nop                                            ; 1000150f:   90                  
