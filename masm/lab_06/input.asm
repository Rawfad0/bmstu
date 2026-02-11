.386

PUBLIC number
PUBLIC read_action
PUBLIC read_binnum

DSEG SEGMENT para public USE16 'DATA'
    number dw 1
    sign db 0
    PROMPT_TEXT db "Signed binary num: ", "$"
DSEG ENDS

CSEG SEGMENT para public USE16 'CODE'
    assume CS:CSEG, DS:DSEG

reverse_number:
    mov dx, number
    not dx
    inc dx
    or dx, 8000h
    mov number, dx
    ret

read_binnum:
    mov ah, 09h         ; команда вывода текста
	lea dx, PROMPT_TEXT ; в регистр DX адрес текста приглашения
	int 21h             ; вывод приглашения к вводу

    mov number, 0       ; сброс числа
    mov sign, 0         ; сброс знака

    xor dx, dx          ; 16-разрядное число в регистре DX
    mov cx, 15          ; количество введенных двоичных цифр 16 - 1 (1 бит для знака)
    mov ah, 01h         ; команда чтения символа

    int 21h             ; чтение символа
        cmp al, '-'     ; если был введен минус
        je set_sign     ; установить знак
        jmp add_digit   ; иначе цифра
        
    set_sign:
        mov sign, 1 ; установка знака
        jmp read_digit ; следующий символ
        

    read_digit:
        int 21h
        add_digit:
            sub al, '0' ; из ascii в цифру
            push cx     ; кладем счетчик внешнего цикла в стек
            mov cl, 1   ; величина побитового сдвига      
            sal dx, cl  ; побитовый сдвиг введенной части влево на 1
            pop cx      ; достаем обратно
            add dl, al  ; добавление новой цифры
            loop read_digit ; следующий символ
    mov number, dx

    cmp sign, 1
    jne end_read
    call reverse_number ; если число отрицательное, то перевернуть его запись

    end_read:
    mov ah, 02
	mov dl, 0Ah         ; вывод символа новой строки
	int 21h

	ret

read_action:
	mov ah, 01h	; команда считывания символа
	int 21h		; вызов прерывания
	xor ah, ah	; очистка старшего байта
	sub al, '0'	; вычитание символа '0', чтобы перейти из ascii в число
	mov cl, 4	; умножение на два
	mul cl		; т.к. каждая команда в массиве занимает два байта
	mov si, ax	; помещение вычисленного сдвига в регистр индекса

    mov ah, 02
	mov dl, 0Ah ; вывод символа новой строки
	int 21h
	ret

CSEG ENDS
END