SSEG SEGMENT para stack 'STACK'
	db 200h dup(0)
SSEG ENDS

DSEG SEGMENT para public 'DATA'
	N LABEL BYTE 
		dw 1
	M LABEL BYTE 
		dw 1
	matrix LABEL BYTE 
		db 9*9 dup(0)
DSEG ENDS

CSEG SEGMENT para 'CODE'
	assume CS:CSEG, DS:DSEG
	MAX_SIZE EQU 9				; максимальный размер матрицы - 9

print_space:	; вывод пробельного символа
	mov ah, 02
	mov dl, 20h 
	int 21h
	ret

print_new_line:	; вывод символа новой строки
	mov ah, 02
	mov dl, 0Ah
	int 21h
	ret

print_digit:	; вывод цифры
	add dl, '0'
	mov ah, 02
	int 21h
	ret

input_digit:	; ввод цифры
	mov ah, 01
	int 21h
	sub al, '0'
	ret

input_n_m:		; ввод размерности матрицы
	call input_digit
	mov N, al
	call print_new_line
	call input_digit
	mov M, al
	call print_new_line
	ret

input_matrix:
	xor cx, cx							; счетчик строк
	xor si, si							; счетчик строк умноженный на 9
	input_matrix_column_loop:
		xor bx, bx						; сброс регистра счетчика пройденных элементов строки
		input_matrix_row_loop:
			call input_digit			; чтение цифры
			mov matrix[si + bx], al		; запись цифры в матрицу по индексу si + bx = MAX_SIZE*cx + bx
			call print_space			; вывод пробельного символа
			inc bx						; увеличение счетчика пройденных столбцов
			cmp bl, N					; сравнение числа пройденных элементов строки и числа столбцов матрицы
			jl input_matrix_row_loop	; если меньше, то чтение следующего символа строки
		call print_new_line				; вывод символа новой строки
		add si, MAX_SIZE				; увеличение регистра счетчика на MAX_SIZE - количество столбцов матрицы
		inc cx							; увеличение счетчика пройденных строк
		cmp cl, M						; сравнение числа пройденных строк и числа строк матрицы
		jl input_matrix_column_loop		; если меньше, то чтение следующей строки матрицы
	ret

print_matrix:
	call print_new_line
	xor cx, cx
	xor si, si
	print_matrix_column_loop:
		xor bx, bx						; сброс регистра счетчика пройденных элементов строки
		print_matrix_row_loop:
			mov dl, matrix[si + bx]		; запись цифры из матрицы в регистр для вывода
			call print_digit			; вывод цифры
			call print_space			; вывод пробельного символа
			inc bx						; увеличение счетчика пройденных столбцов
			cmp bl, N					; сравнение числа пройденных элементов строки и числа столбцов матрицы
			; cmp bl, MAX_SIZE
			jl print_matrix_row_loop	; если меньше, то вывод следующего символа строки
		call print_new_line				; вывод символа новой строки
		add si, MAX_SIZE				; увеличение регистра счетчика на MAX_SIZE - количество столбцов матрицы
		inc cx							; увеличение счетчика пройденных строк
		cmp cl, M						; сравнение числа пройденных строк и числа строк матрицы
		; cmp cl, MAX_SIZE
		jl print_matrix_column_loop		; если меньше, то вывод следующей строки матрицы
	ret

sub_down_elem:
	mov cx, 1							; тут 1, а не 0, потому что нужно остановиться на одну строку раньше
	xor si, si
	sub_down_elem_column_loop:
		xor bx, bx						; сброс регистра счетчика пройденных элементов строки
		sub_down_elem_row_loop:
			mov dl, matrix[si + bx]					; считывание текущего элемента в регистр
			cmp dl, matrix[si + MAX_SIZE + bx]		; сравнение текущего элемента и следующего в столбце элемента
			jl elem_zero							; если следующий больше, то переход	на метку обнуления, иначе вычитание
													; если следующий меньше или равен,
				sub dl, matrix[si + MAX_SIZE + bx]	; то вычитание следующего из текущего
				mov matrix[si + bx], dl				; запись результата вычитания
				jmp pass							; далее

			elem_zero:								; если следующий больше,
				mov matrix[si + bx], 0				; то записать ноль
			pass:
			inc bx						; увеличение счетчика пройденных столбцов
			cmp bl, N					; сравнение числа пройденных элементов строки и числа столбцов матрицы
			jl sub_down_elem_row_loop	; если меньше, то к следующему символу строки
		add si, MAX_SIZE				; увеличение регистра счетчика на MAX_SIZE - количество столбцов матрицы
		inc cx							; увеличение счетчика пройденных строк
		cmp cl, M						; сравнение числа пройденных строк и числа строк матрицы
		jl sub_down_elem_column_loop	; если меньше, то к следующей строки матрицы
	ret

main:
	mov ax, DSEG
	mov ds, ax

	call input_n_m
	call input_matrix
	call sub_down_elem
	call print_matrix
	
	mov ax, 4c00h
	int 21h
CSEG ENDS
END main