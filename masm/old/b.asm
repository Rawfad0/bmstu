.model small 
.stack 100h 

.data 
    video_mode equ 13h  

.code 
main proc 
    mov ax, @data 
    mov ds, ax 
 
    mov ax, video_mode 
    int 10h 
 
    mov ax, 0A000h    
    mov es, ax 

step1:
	mov cx, 320 * 200    
	xor di, di
fill_screen1: 
	mov word ptr es:[di], 66h
	add di, 1
	loop fill_screen1

	mov cx, 100    
	mov di, 320 * 5 + 100         
left_hand1: 
    mov word ptr es:[di], 0Ch
    add di, 319
    loop left_hand1
	
	mov cx, 100    
	mov di, 320 * 5 + 100         
right_hand1: 
    mov word ptr es:[di], 0Ch
    add di, 321
    loop right_hand1

	mov cx, 100    
	mov di, 320 * 0 + 100         
body1: 
    mov word ptr es:[di], 0Ch
    add di, 320
    loop body1
	
    mov cx, 100    
    mov di, 320 * 100 + 100            
left_leg1: 
    mov word ptr es:[di], 0Ch
    add di, 319
    loop left_leg1 
	
	mov cx, 100    
	mov di, 320 * 100 + 100         
right_leg1: 
    mov word ptr es:[di], 0Ch
    add di, 321
    loop right_leg1

	mov ah, 0
    int 16h
	cmp al, 71h
	je label_q
	cmp al, 71h
	jne step2	

step2:
	mov cx, 320 * 200    
	xor di, di
fill_screen2: 
	mov word ptr es:[di], 66h
	add di, 1
	loop fill_screen2

	mov cx, 100    
	mov di, 320 * 0 + 100         
body2: 
    mov word ptr es:[di], 0Ch
    add di, 320
    loop body2
	
	mov cx, 100    
	mov di, 320 * 5 + 100         
hand_l2: 
    mov word ptr es:[di], 0Ch
    add di, 319
    loop hand_l2
	
	mov cx, 100    
	mov di, 320 * 5 + 100         
right_hand2: 
    mov word ptr es:[di], 0Ch
    add di, 321
    loop right_hand2

	mov cx, 100    
	mov di, 320 * 100 + 100         
legs: 
    mov word ptr es:[di], 0Ch
    add di, 320
    loop legs        
	; ожидание нажатия клавиши
	mov ah, 0
    int 16h

	cmp al, 71h
	je label_q
	cmp al, 71h
	jne step1
; выход
label_q:
	mov ax, 3h           
    int 10h

    mov ax, 4C00h        
    int 21h 
main endp 
 
end main