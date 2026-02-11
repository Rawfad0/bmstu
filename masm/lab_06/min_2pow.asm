.386

EXTRN number            : WORD
PUBLIC print_min_pow

DSEG SEGMENT para public USE16 'DATA'
    pow dw 0
DSEG ENDS

CSEG SEGMENT para public USE16 'CODE'
    assume CS:CSEG, DS:DSEG

print_min_pow:
    bsr ax, number
    mov pow, ax

    mov ah, 2

    xor bx, bx
    mov bx, pow

    cmp bx, 10
    jb no_dozen

    mov dl, '1'
    sub bx, 10
    no_dozen:
        mov dl, bl
        add dl, '0'
        int 21h

    ; mov ax, number
    ; mov dl, 0
    ; mov cl, 1   ; величина сдвига
    ; min_pow_loop:
    ;     cmp ax, 0   ; закончилось ли число
    ;     je quit
    ;     sar ax, cl  ; сдвиг вправо на 1 бит
    ;     inc dl
    ;     jmp min_pow_loop

    ; cmp ax, 10h
    ; je print_16

    ; cmp ax, 0Ah
    ; jge print_alph

    ; print_digit:
    ;     add dl, '0'
    ;     mov ah, 02
	;     int 21h
    ;     jmp quit

    ; print_alph:
    ;     add dl, 'A' - 10
    ;     mov ah, 02
	;     int 21h
    ;     jmp quit

    ; print_16:
    ;     mov ah, 02
	;     mov dl, '1'
	;     int 21h
	;     mov dl, '0'
	;     int 21h
	;     mov dl, 'h'
	;     int 21h
    ;     jmp quit

    quit:
        mov ah, 02
        mov dl, 0Ah         ; символ новой строки
        int 21h

    ret

; print_min_pow:
;     mov ax, number
;     xor dx, dx
;     bsr dx, ax

;     cmp dl, Ah
;     jge print_alph
;         add dl, '0'
;         jmp print_count

;     print_alph:
;         add dl, 'A' - 10
;         jmp print_count

;     print_count:
;         mov ah, 02h  ; команда вывода символа
;         int 21h
;         mov dl, 0Ah  ; символ новой строки
;         int 21h
;     ret

; print_min_pow:
;     mov ax, number

;     ; bsr dx, ax
;     ; bsr bx, ax
;     ; mov dx, 00s
;     ; add dl, 1      ; т.к. нужен следующий

;     mov dl, 0
;     mov cl, 1   ; величина сдвига
;     min_pow_loop:
;         cmp ax, 0   ; закончилось ли число
;         je quit
;         sar ax, cl  ; сдвиг вправо на 1 бит
;         inc dl
;         jmp min_pow_loop
    
;     quit:
    
;     cmp dl, Ah
;     jge print_alph
;         add dl, '0'
;         jmp print_count

;     print_alph:
;         add dl, 'A' - 10
;         jmp print_count

;     print_count:
;         mov ah, 02h  ; команда вывода символа
; 	    int 21h
;         xor dl, dl
;         mov dl, 0Ah  ; символ новой строки
;         int 21h
;     ret

CSEG ENDS
END