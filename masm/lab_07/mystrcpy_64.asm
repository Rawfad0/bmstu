section .text

global asm_strncpy

; Соглашение elf64:
; Входные:  1: dst -> rdi
;           2: src -> rsi
;           3: n   -> rdx
; Выходные: ret - в rax

asm_strncpy:
    mov rbx, rdi
    mov rcx, rdx    ; n в rcx - счётчик повторений для команде rep movsb
    
    ; сравнение *dst и *src
    cmp rdi, rsi
    jbe copy        ; если dst <= src, то копирование

    mov rax, rdi
    sub rax, rsi
    cmp rax, rcx
    ja copy         ; если dst - src > len, то копирование
    
    add rdi, rcx
    dec rdi
    add rsi, rcx
    dec rsi         ; поставили rsi и rdi в концы строк, на которые они указывали
    std             ; установка флага направления DF (для команд обработки строк) 
    ; если 1, то строки обрабатываются в сторону уменьшения адресов, 
    ; если 0, то наоборот

copy:
    rep movsb       ; цикл копирования строки
    cld             ; сброс флага направления в 0
    mov rax, rbx    ; кладём в rax возвращаемое значение (указатель dst), который мы в самом начале сохранили в rbx
ret