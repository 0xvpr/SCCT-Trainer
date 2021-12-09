segment .text

global _healthDetour

_healthDetour:
    cmp    dword [edi], 0x110E8B50
    je     $ + 0x08
    xor    eax, eax
    mov    eax, eax
    mov    dword [ebx], eax
    mov    ebx, eax
    mov    eax, dword [esp + 0x14]
    pop    esi
    mov    dword [eax], ebx
    pop    ebx
    pop    ecx
    ret    0x8
