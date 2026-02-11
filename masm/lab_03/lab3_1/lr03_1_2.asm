PUBLIC output_X
EXTRN X: byte

DS2 SEGMENT AT 0b800h
	CA LABEL byte
	ORG 80 * 2 * 2 + 2 * 2	; 3-я строка 3-й символ
	SYMB LABEL word
DS2 ENDS

CSEG SEGMENT PARA PUBLIC 'CODE'
	assume CS:CSEG, ES:DS2
output_X proc near
	mov ax, DS2
	mov es, ax
	mov ah, 10		; второй байт - атрибуты: 10 - 00001010:
												; 0 - нет мерцания
												; 000 - фон 
												; 1010 - цвет:
													; 1 - есть яркость
													; 010 - rGb - зеленый
	mov al, X		; первый байт - символ (в данном случае 'R')
	mov symb, ax
	ret
output_X endp
CSEG ENDS
END