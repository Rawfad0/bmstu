SSTK SEGMENT para STACK 'STACK'
    db 200 dup(0)
SSTK ENDS

LEN = 5

DSEG SEGMENT PARA PUBLIC 'DATA'
	ARR DW 0
DSEG ENDS

SC1 SEGMENT para public 'CODE'
	assume CS:SC1, DS:DSEG, SS:SSTK

print_new_line proc near
    mov ah, 02h
    mov dl, 13
    int 21h
    mov dl, 10
    int 21h
    pop ax
    jmp ax
print_new_line endp

print_space proc near
    mov ah, 02h
    mov dl, ' '
    int 21h
    ret
print_space endp

get_sym proc near
    mov ah, 01h
    int 21h
    ret
get_sym endp

get_num proc near
    call get_sym
    sub al, '0'
    ret
get_num endp

show_sym proc near
    mov ah, 02h
    int 21h
    ret
show_sym endp

get_mtr proc near
    lea si, es:0
    mov cx, LEN

    input_mtr:
        call get_sym
        mov [si], al
        inc si
        call print_space

        loop input_mtr
    
    ret
get_mtr endp

print_mtr proc near
    lea si, es:LEN
    mov cx, LEN

    output_mtr:
        dec si
        mov dl, [si]
        call show_sym
        call print_space

        loop output_mtr
    ret
print_mtr endp

main:
    mov ax, DSEG
    mov ds, ax

    mov bx, (LEN / 16) + 1
    mov ah, 48h
    int 21h

    mov es, ax

    call get_mtr

    call print_new_line
    call print_mtr

    mov ah, 49h
    int 21h

    mov ax, 4C00h
    int 21h
SC1 ENDS
END main