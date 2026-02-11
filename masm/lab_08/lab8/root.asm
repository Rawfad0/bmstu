section .text
    global root

; берёт значение из xmm0
; возврщает значение в xmm0
func:
    sub rsp, 8
    movsd qword [rsp], xmm0
    fld qword [rsp]

    ; x * 5
    mov rax, 5
    push rax
    fild qword [rsp]
    fmulp
    pop rax
    
    ; x ** 2
    fld qword [rsp]
    fld qword [rsp]
    fmulp

    ; x**2 + 5*x
    faddp

    ; sin(x**2 + 5*x)
    fsin

    ; return value
    fstp qword [rsp]
    movsd xmm0, qword[rsp]
    add rsp, 8
ret

; a - xmm0
; b - xmm1
; return xmm2
mid:
    sub rsp, 16
    movsd qword [rsp], xmm0
    fld qword [rsp]

    movsd qword [rsp + 8], xmm1
    fld qword [rsp + 8]

    faddp

    push rax
    mov rax, 2
    push rax
    fild qword [rsp]
    fdivp
    pop rax
    pop rax

    fstp qword [rsp]
    movsd xmm2, qword[rsp]
    add rsp, 16
ret

; a - xmm0
; b - xmm1
; res - xmm2
mul:
    sub rsp, 16
    movsd qword [rsp], xmm0
    fld qword [rsp]

    movsd qword [rsp + 8], xmm1
    fld qword [rsp + 8]

    fmulp

    fstp qword [rsp]
    movsd xmm2, qword[rsp]
    add rsp, 16
ret

; a - xmm0
; b - xmm1
; count - rdi
; return xmm2
bi:
    mov rcx, 0
    call mid

    get_root:
        cmp rdi, rcx
        jle end_get_root

        movsd xmm4, xmm2 ; xmm4 - mid
        movsd xmm5, xmm1 ; xmm5 - b
        movsd xmm6, xmm0 ; xmm6 - a

        movsd xmm0, xmm2 ; xmm0 - mid
        call func
        movsd xmm2, xmm0 ; xmm2 - f(mid)
        movsd xmm0, xmm6 ; xmm0 - a
        call func ; xmm0 - f(a)
        
        movsd xmm1, xmm2 ; xmm1 - f(mid)
        call mul ; xmm2 - f(a) * f(mid)

        xorps xmm1, xmm1
        comisd xmm1, xmm2
        jl root_less
        jg root_upper
        jmp end_get_root

        root_less:
            movsd xmm1, xmm4 ; b - mid
            movsd xmm0, xmm6 ; a - a
            jmp after_root

        root_upper:
            movsd xmm0, xmm4 ;a - mid
            movsd xmm1, xmm5 ;b - b
            jmp after_root

        after_root:
            call mid ; xmm2 - mid
            inc rcx
            jmp get_root
        
    end_get_root:
ret

root:
    push rbp
    mov rbp, rsp
    push rbx

    call bi
    movsd xmm0, xmm2

    pop rbx
    pop rbp
ret
