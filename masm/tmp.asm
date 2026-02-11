vecSum proc far
    mov si, dx
    
    fld dword ptr [si + 0]
    fadd dword ptr [bx + 0]
    fstp result.x
    
    fld dword ptr [si + 4]
    fadd dword ptr [bx + 4]
    fstp result.y

    fld dword ptr [si + 8]
    fadd dword ptr [bx + 8]
    fstp result.z

    lea ax, result
    
    retf
vecSum endp