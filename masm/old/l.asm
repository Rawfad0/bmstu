DS1 SEGMENT AT 0b800h
	CA LABEL byte
	SYMB LABEL word
DS1 ENDS

CSEG SEGMENT PARA PUBLIC 'CODE'
	assume CS:CSEG, DS:DS1
main:
	mov ax, DS1
	mov ds, ax
	
	mov ah, 64
	mov al, 0
	mov symb, ax
	
	mov ax, 4c00h
	int 21h
CSEG ENDS
END main

.286
.model tiny
.CODE
org 100h
start:  mov ax, 600h
    mov bx, 0F000h
    xor cx,cx
    mov dx, 850h
    int 10h
    sub bh,60h
    add ch,8
    add dh,8
    int 10h
    add bh,30h
    add ch,8
    add dh,8
    int 10h
    mov ah,0
    int 16h
    ret
end start
bh=90 red
bh=B0 blue
bh=F0 white