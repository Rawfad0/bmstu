.386

EXTRN number                : WORD
PUBLIC print_10_signed_num

DSEG SEGMENT para public USE16 'DATA'
    ; dec_number db 6 dup(0)  ; -32k to +32k
    dec_number db 4 dup('$')  ; -32 to 31
    ; sign db 1
    MASK_TO_CHAR dw 00FFh
    S10_TEXT db "Signed decimal num: ", "$"
DSEG ENDS

CSEG SEGMENT para public USE16 'CODE'
    assume CS:CSEG, DS:DSEG

hex_to_dec_str:
    mov bx, 10          ; деление на 10
    mov cx, 0           ; счетчик цифр
    hex_to_dec:       
        mov dx, 0       ; для деления
        div bx          ; AX = AX / 10 (остаток в DX).
        push dx         ; в стек
        inc cx          ; счетчик кол-ва цифр увеличивается
        cmp ax, 0       ; закончилось ли число
        jne hex_to_dec  ; не закончилось => еще раз
        lea si, dec_number
    to_str:
        pop dx          ; достаем из стека
        add dl, '0'     ; цифра в ascii
        mov [si], dl
        inc si
        loop to_str
    ret

print_10_signed_num:
    mov ah, 09h         ; команда вывода текста
	lea dx, S10_TEXT    ; в регистр DX адрес текста сообщения
	int 21h             ; вывод 

    mov ax, number
    and ax, 00FFh       ; MASK_TO_CHAR

    mov bx, 0080h       ; первый бит второго байта - бит знака
    and bx, ax          ; узнать знак числа
    jz pass             ; если 0 - далее
                        ; если не 0 - учесть знак
    
    not al
    inc al
    ; and al, 007Fh       ; 0111.1111 - первый бит из восьми занулить
    push ax
    mov ah, 02h         ; команда вывода
    mov dl, '-'         ; символ знака
    int 21h             ; вывод знака
    pop ax

    pass:
    call hex_to_dec_str ; перевод hex числа в dec число
    
    mov ah, 09h         ; команда вывода текста
	lea dx, dec_number  ; строка содержащая число в 16 с/с 
	int 21h

    mov ah, 02
	mov dl, 0Ah         ; символ новой строки
	int 21h

    ret

CSEG ENDS
END