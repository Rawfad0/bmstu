.386

BIN_LEN EQU 16
BIN_MASK EQU 1
NEW_LINE EQU 13, 10
NUM_LEN EQU 3

extern number: word

public get_pow_two

DATASEG SEGMENT PARA PUBLIC USE16 'DATA'
    pow dw 0
    output_pow_msg DB NEW_LINE, 'Power of two, which is a multiple of the entered number: $'
    buffer db NUM_LEN dup(0)
DATASEG ENDS

CODESEG SEGMENT PARA PUBLIC USE16 'CODE'
    assume cs:CODESEG, ds:DATASEG

convert_decimal_to_string proc
    mov bx, 10                

    lea di, [buffer + NUM_LEN] 
    mov byte ptr [di], "$"

    mov cx, NUM_LEN - 1
    convert_loop:
        xor dx, dx
        div bx
        add dl, '0'
        dec di
        mov [di], dl

        loop convert_loop
    ret
convert_decimal_to_string endp

show_pow proc near
    mov ah, 9
    lea dx, output_pow_msg
    int 21h

    mov ax, pow
    call convert_decimal_to_string

    mov ah, 9
    lea dx, buffer
    int 21h

    ret
show_pow endp

get_pow_two proc near
    bsf ax, number
    mov pow, ax
    call show_pow
    ret
get_pow_two endp

CODESEG ENDS
END