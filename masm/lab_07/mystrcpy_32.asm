section .text

global asm_strncpy

asm_strncpy:
    push ebp
    mov ebp, esp

    mov eax, [ebp + 8]
    mov ecx, [ebp + 12]
    mov edx, [ebp + 16]

    mov edi, eax
    mov esi, ecx
    mov ecx, edx
    cmp edi, esi
    jbe copy

    mov eax, edi
    sub eax, esi
    cmp eax, ecx
    ja copy
    ; dst > src  dst - src < len
    add edi, ecx
    dec edi
    add esi, ecx
    dec esi
    std

copy:
    rep movsb       
    cld
    mov eax, ebx
    pop ebp
ret
