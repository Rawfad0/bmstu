.386

EXTRN number    : WORD
PUBLIC print_16_unsigned_num

DSEG SEGMENT para public USE16 'DATA'
    hex_number db 5 dup('$')
    HEX_MASK db 0Fh
    U16_TEXT db "Hexadecimal num: ", "$"
DSEG ENDS

CSEG SEGMENT para public USE16 'CODE'
    assume CS:CSEG, DS:DSEG

; print_hex_digit:
; 	mov ah, 02h
;     cmp dl, Ah
;     jg print_alph
;     add dl, '0'
;     jmp print_ret
;     print_alph:
;         add dl, 'A' - 10    ; F=16 => 16+'A'-10='A'+6='F' 
;     print_ret:
; 	    int 21h
; 	ret

hex_to_ansii:
    cmp dl, Ah
    jg to_alph
    add dl, '0'
    jmp hex_to_ansi_quit
    to_alph:
        add dl, 'A' - 10    ; F=16 => 16+'A'-10='A'+6='F' 
    hex_to_ansi_quit:
    ret


print_16_unsigned_num:
    mov ah, 09h         ; команда вывода текста
	lea dx, U16_TEXT    ; в регистр DX адрес текста сообщения
	int 21h             ; вывод

    mov bx, number
    mov cx, 4
    hex_num_to_ansi:
        mov dl, HEX_MASK
        and dl, bl

        ; call print_hex_digit
        call hex_to_ansii
        mov si, cx
        dec si
        mov hex_number[si], dl  ; hex[ci - 1] = hex_to_ansii(hex)

        push cx     ; кладем счетчик внешнего цикла в стек
        mov cl, 4   ; величина побитового сдвига      
        sar bx, cl  ; побитовый сдвиг числа вправо на 4
        pop cx      ; достаем обратно
        loop hex_num_to_ansi
    

    mov ah, 09h         ; команда вывода текста
	lea dx, hex_number  ; строка содержащая число в 16 с/с 
	int 21h

    mov ah, 02
	mov dl, 0Ah     ; символ новой строки
	int 21h
    ret

CSEG ENDS
END