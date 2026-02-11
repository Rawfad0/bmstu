SC1 SEGMENT para public 'CODE'
	assume CS:SC1

input_digit:	; ввод цифры
	mov ah, 01
	int 21h
	sub al, '0'
	ret

MAIN:
    LEN = 3

    mov bx, (LEN / 16) + 1
    mov ah, 48h
    int 21h
    mov es, ax

    mov cx, LEN
    lea si, es:0
    input:
        call input_digit
        mov [si], al
        inc bx
        inc si
        loop input
    
    mov ah, 02h
    mov dl, 0Ah
    int 21h

    mov cx, LEN
    lea si, es:0
    output:
        mov ah, 02h
        mov dl, [si]
        int 21h

        inc si
        loop output

    mov es, ax
    mov ah, 49h
    int 21h

    mov ax, 4C00h
    int 21h
SC1 ENDS

END MAIN
