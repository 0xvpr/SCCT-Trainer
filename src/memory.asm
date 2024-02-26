; --------------------------------------------------------------------------- ;
;                              Exported Functions                             ;
; --------------------------------------------------------------------------- ;

global          _memory_find_dynamic_address
global          _memory_tramp_hook
global          _memory_detour
global          _memory_patch
global          _memory_nop

; --------------------------------------------------------------------------- ;
;                              Imported Functions                             ;
; --------------------------------------------------------------------------- ;

extern          _VirtualProtect@16
extern          _VirtualAlloc@16
extern          _VirtualFree@12
extern          _memset
extern          _memcpy

; --------------------------------------------------------------------------- ;
;                               Executable Code                               ;
; --------------------------------------------------------------------------- ;

section .text
_memory_find_dynamic_address:
    push        esi                                              
    push        ebx                                              
    mov         esi,dword [esp+0x14]                             
    mov         ecx,dword [esp+0x10]                             
    mov         eax,dword [esp+0xc]                              
    test        esi,esi                                          
    je          dynamic_exit                                     
    mov         ebx,esi                                          
    mov         eax,dword [eax]                                  
    xor         edx,edx                                          
    and         ebx,0x7                                          
    je          one_depth                                        
    cmp         ebx,0x1                                          
    je          two_depth                                        
    cmp         ebx,0x2                                          
    je          three_depth                                      
    cmp         ebx,0x3                                          
    je          four_depth                                       
    cmp         ebx,0x4                                          
    je          five_depth                                       
    cmp         ebx,0x5                                          
    je          six_depth                                        
    cmp         ebx,0x6                                          
    jne         e0_exit                                          
seven_depth:    
    movzx       ebx,word [ecx+edx*2]                             
    mov         eax,dword [ebx+eax*1]                            
    test        eax,eax                                          
    je          dynamic_exit                                     
    inc         edx                                              
six_depth:
    movzx       ebx,word [ecx+edx*2]                             
    mov         eax,dword [ebx+eax*1]                            
    test        eax,eax                                          
    je          dynamic_exit                                     
    inc         edx                                              
five_depth:
    movzx       ebx,word [ecx+edx*2]                             
    mov         eax,dword [ebx+eax*1]                            
    test        eax,eax                                          
    je          dynamic_exit                                     
    inc         edx                                              
four_depth:
    movzx       ebx,word [ecx+edx*2]                             
    mov         eax,dword [ebx+eax*1]                            
    test        eax,eax                                          
    je          dynamic_exit                                     
    inc         edx                                              
three_depth:    
    movzx       ebx,word [ecx+edx*2]                             
    mov         eax,dword [ebx+eax*1]                            
    test        eax,eax                                          
    je          dynamic_exit                                     
    inc         edx                                              
two_depth:
    movzx       ebx,word [ecx+edx*2]                             
    add         ebx,eax                                          
    mov         eax,dword [ebx]                                  
    test        eax,eax                                          
    je          dynamic_exit                                     
    inc         edx                                              
    cmp         esi,edx                                          
    je          pre_dynamic_exit                                 
one_depth:
    movzx       ebx,word [ecx+edx*2]                             
    mov         eax,dword [ebx+eax*1]                            
    test        eax,eax                                          
    je          dynamic_exit                                     
    movzx       ebx,word [ecx+edx*2+0x2]                         
    mov         eax,dword [ebx+eax*1]                            
    test        eax,eax                                          
    je          dynamic_exit                                     
    movzx       ebx,word [ecx+edx*2+0x4]                         
    mov         eax,dword [ebx+eax*1]                            
    test        eax,eax                                          
    je          dynamic_exit                                     
    movzx       ebx,word [ecx+edx*2+0x6]                         
    mov         eax,dword [ebx+eax*1]                            
    test        eax,eax                                          
    je          dynamic_exit                                     
    movzx       ebx,word [ecx+edx*2+0x8]                         
    mov         eax,dword [ebx+eax*1]                            
    test        eax,eax                                          
    je          dynamic_exit                                     
    movzx       ebx,word [ecx+edx*2+0xa]                         
    mov         eax,dword [ebx+eax*1]                            
    test        eax,eax                                          
    je          dynamic_exit                                     
    movzx       ebx,word [ecx+edx*2+0xc]                         
    mov         eax,dword [ebx+eax*1]                            
    test        eax,eax                                          
    je          dynamic_exit                                     
    movzx       ebx,word [ecx+edx*2+0xe]                         
    add         ebx,eax                                          
    mov         eax,dword [ebx]                                  
    test        eax,eax                                          
    je          dynamic_exit                                     
    add         edx,0x8                                          
    cmp         esi,edx                                          
    jne         one_depth                                        
pre_dynamic_exit:
    mov         eax,ebx                                          
dynamic_exit:
    pop         ebx                                              
    pop         esi                                              
    ret                                                          
    lea         esi,[esi+0x0]                                    
e0_exit:
    movzx       edx,word [ecx]                                   
    mov         eax,dword [edx+eax*1]                            
    test        eax,eax                                          
    je          dynamic_exit                                     
    mov         edx,0x1                                          
    jmp         seven_depth                                      
    lea         esi,[esi+0x0]                                    
    lea         esi,[esi+0x0]                                    
    nop                                                          

_memory_nop:                                                     
    push        ebp                                              
    push        edi                                              
    push        esi                                              
    push        ebx                                              
    sub         esp,0x2c                                         
    mov         ebx,dword [esp+0x40]                             
    mov         esi,dword [esp+0x44]                             
    lea         ebp,[esp+0x1c]                                   
    mov         dword [esp+0xc],ebp                              
    mov         dword [esp+0x4],esi                              
    mov         dword [esp],ebx                                  
    mov         dword [esp+0x8],0x80                             
                                                                 
    mov         edi,_VirtualProtect@16                           
    call        edi                                              
    sub         esp,0x10                                         
    mov         dword [esp+0x8],esi                              
    mov         dword [esp],ebx                                  
    mov         dword [esp+0x4],0x90                             
                                                                 
    call        _memset                                          
    mov         eax,dword [esp+0x1c]                             
    mov         dword [esp+0xc],ebp                              
    mov         dword [esp+0x4],esi                              
    mov         dword [esp],ebx                                  
    mov         dword [esp+0x8],eax                              
    call        edi                                              
    sub         esp,0x10                                         
    add         esp,0x2c                                         
    pop         ebx                                              
    pop         esi                                              
    pop         edi                                              
    pop         ebp                                              
    ret                                                          
    lea         esi,[esi+0x0]                                    
    lea         esi,[esi+0x0]                                    

_memory_patch:                                               
    push        ebp                                              
    push        edi                                              
    push        esi                                              
    push        ebx                                              
    sub         esp,0x2c                                         
    mov         ebx,dword [esp+0x40]                             
    mov         esi,dword [esp+0x48]                             
    lea         ebp,[esp+0x1c]                                   
    mov         dword [esp+0xc],ebp                              
    mov         dword [esp+0x4],esi                              
    mov         dword [esp],ebx                                  
    mov         dword [esp+0x8],0x80                             
                                                                 
    mov         edi,_VirtualProtect@16                           
    call        edi                                              
    sub         esp,0x10                                         
    mov         eax,dword [esp+0x44]                             
    mov         dword [esp+0x8],esi                              
    mov         dword [esp],ebx                                  
    mov         dword [esp+0x4],eax                              
    call        _memcpy                                          
    mov         edx,dword [esp+0x1c]                             
    mov         dword [esp+0xc],ebp                              
    mov         dword [esp+0x4],esi                              
    mov         dword [esp],ebx                                  
    mov         dword [esp+0x8],edx                              
    call        edi                                              
    sub         esp,0x10                                         
    add         esp,0x2c                                         
    pop         ebx                                              
    pop         esi                                              
    pop         edi                                              
    pop         ebp                                              
    ret                                                          
    lea         esi,[esi+0x0]                                    
    lea         esi,[esi+0x0]                                    

_memory_detour:                                              
    push        ebp                                              
    xor         eax,eax                                          
    push        edi                                              
    push        esi                                              
    push        ebx                                              
    sub         esp,0x2c                                         
    mov         esi,dword [esp+0x48]                             
    mov         ebx,dword [esp+0x40]                             
    cmp         esi,0x4                                          
    jbe         detour_exit                                      
    lea         ebp,[esp+0x1c]                                   
    mov         dword [esp+0xc],ebp                              
    mov         dword [esp+0x8],0x40                             
                                                                 
    mov         dword [esp+0x4],esi                              
    mov         dword [esp],ebx                                  
    mov         edi,_VirtualProtect@16                           
    call        edi                                              
    sub         esp,0x10                                         
    mov         dword [esp+0x8],esi                              
    mov         dword [esp+0x4],0x90                             
                                                                 
    mov         dword [esp],ebx                                  
    call        _memset                                          
    mov         eax,dword [esp+0x44]                             
    mov         edx,dword [esp+0x1c]                             
    sub         eax,0x5                                          
    sub         eax,ebx                                          
    mov         byte [ebx],0xe9                                  
    mov         dword [ebx+0x1],eax                              
    mov         dword [esp+0xc],ebp                              
    mov         dword [esp+0x8],edx                              
    mov         dword [esp+0x4],esi                              
    mov         dword [esp],ebx                                  
    call        edi                                              
    sub         esp,0x10                                         
    mov         eax,0x1                                          
detour_exit:    
    add         esp,0x2c                                         
    pop         ebx                                              
    pop         esi                                              
    pop         edi                                              
    pop         ebp                                              
    ret                                                      

_memory_tramp_hook:                                          
    push        ebp                                               
    push        edi                                               
    push        esi                                               
    push        ebx                                               
    xor         ebx,ebx                                           
    sub         esp,0x1c                                          
    mov         esi,dword [esp+0x38]                              
    mov         edi,dword [esp+0x30]                              
    cmp         esi,0x4                                           
    jbe         tramp_exit                                        
    lea         ebp,[esi+0x5]                                     
    mov         dword [esp+0xc],0x40                              
                                                                  
    mov         dword [esp+0x8],0x3000                            
                                                                  
    mov         dword [esp+0x4],ebp                               
    mov         dword [esp],0x0                                   
    call        _VirtualAlloc@16                                  
    sub         esp,0x10                                          
    mov         dword [esp+0x8],esi                               
    mov         dword [esp+0x4],edi                               
    mov         dword [esp],eax                                   
    mov         ebx,eax                                           
    call        _memcpy                                           
    mov         eax,edi                                           
    sub         eax,ebx                                           
    mov         edx,dword [esp+0x34]                              
    sub         eax,0x5                                           
    mov         byte [ebx+esi*1],0xe9                             
    mov         dword [ebx+esi*1+0x1],eax                         
    mov         dword [esp+0x8],esi                               
    mov         dword [esp+0x4],edx                               
    mov         dword [esp],edi                                   
    call        _memory_detour                                    
    test        eax,eax                                           
    je          detour_fail_exit                                  
tramp_exit:
    add         esp,0x1c                                          
    mov         eax,ebx                                           
    pop         ebx                                               
    pop         esi                                               
    pop         edi                                               
    pop         ebp                                               
    ret                                                      
detour_fail_exit:
    mov         dword [esp+0x4],ebp                               
    mov         dword [esp],ebx                                   
    mov         dword [esp+0x8],0x8000                            
                                                                  
    xor         ebx,ebx                                           
    call        _VirtualFree@12                                   
    sub         esp,0xc                                           
    add         esp,0x1c                                          
    mov         eax,ebx                                           
    pop         ebx                                               
    pop         esi                                               
    pop         edi                                               
    pop         ebp                                               
    ret                                                      
    nop                                                      
    nop                                                      
    nop                                                      
    nop                                                      
    nop                                                      
    nop                                                      
    nop                                                      
    nop                                                      
    nop                                                      
    nop                                                      
    nop                                                      
    nop                                                      
