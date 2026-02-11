DSEG SEGMENT para public 'DATA'
	buf LABEL byte
	db 100 dup('$')
DSEG ENDS

CSEG SEGMENT para public 'CODE'
	assume CS:CSEG, DS:DSEG
main:
	mov ax, DSEG
	mov ds, ax
	; из stdin в DS:DX
	mov ah, 0Ah
	lea dx, buf
	int 21h
	; \n
	mov ah, 02h
	mov dl, 0Ah
	int 21h
	
	; сложение чисел в регистре dl 
	mov dl,buf+1+2		; помещение ascii символа в регистр dl
	sub dl, '0'			; вычитание основания 30h=0, чтобы получить цифру
	add dl,buf+1+4		; добавление второго ascii символа как сумму основания 30h и цифры
						; итого <цифра> + 30h + <цифра> = ascii символ суммы цифр
	; вывод символа
	mov ah, 02h
	int 21h
	;
	mov ah, 4ch
	int 21h
CSEG ENDS
END main