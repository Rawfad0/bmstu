bits 64
global main

%define GTK_WIN_POS_CENTER 1
%define GTK_WIN_WIDTH 600
%define GTK_WIN_HEIGHT 300

extern exit
extern gtk_init
extern gtk_main
extern gtk_main_quit

extern gtk_window_new
extern gtk_widget_show
extern gtk_widget_show_all
extern gtk_window_set_title
extern gtk_window_set_position
extern gtk_window_set_default_size

; extern gtk_settings_get_default
; extern gtk_widget_set_size_request

extern gtk_container_add

extern gtk_box_new

extern gtk_spin_button_new
extern gtk_spin_button_new_with_range
extern gtk_spin_button_set_digits
extern gtk_spin_button_get_value
extern gtk_spin_button_set_value

extern gtk_button_new_with_label
extern gtk_button_set_label

extern gtk_label_new
extern gtk_label_set_text

; extern g_signal_connect
extern g_signal_connect_data
extern g_free
extern g_strdup_printf

section .bss
    window: resq 1
    box:    resq 1

    input_a:    resq 1
    input_b:    resq 1
    input_i:    resq 1

    run_button:
        .handle: resq 1
        .label: resq 1

    ; res_label:
    ;     .handle:    resq 1
    ;     .default:   resq 1

    res_spin:   resq 1

    bot: resq 1
    top: resq 1
    iters: resq 1

    x: resq 1
    f: resq 1

section .data
    signal:
        .clicked: db "clicked", 0
    value: dq 9.9

    five: dq 5.0
    two: dq 2.0
    zero: dq 0.0

section .rodata
    destroy_text:       db "destroy", 0
    title:              db "lab_10", 0
    run_button_text:    db "run", 0

    double_format: db "%.16f", 0

section .text

    f_x:
        fld qword[ x ]      ; [   <-x          => [x               положить x в стек
        fld qword[ five ]   ; [x   <-5         => [x, 5            положить 5 в стек
        faddp               ; [x, 5            => [x + 5
        fld qword[ x ]      ; [x + 5 <-x       => [x, x            положить x в стек
        fmulp               ; [x + 5, x        => [x^2 + 5*x       умножить x и x
        fsin                ; [x^2 + 5*x       => [sin(x^2 + 5x)
        fstp qword[ f ]     ; [sin(x^2 + 5*x)  => [ -> res    взять sin(x^2 + 5*x) из стека в res
        ret

    get_mid:
        fld qword[bot]
        fld qword[top]
        faddp
        fld qword[two]
        fdivp
        fstp qword[x]

        ; movq xmm0, [bot]
        ; movq xmm1, [top]
        ; addsd xmm0, xmm1
        ; movq xmm1, [two]
        ; divsd xmm0, xmm1
        ; movq [x], xmm0
        ; ret

    solve:
        mov rcx, iters

        midpoint_getter_loop:
            call get_mid    ; x:=(bot+top)/2
            call f_x        ; f:=f(x)

            fld qword[bot]
            fld qword[f]
            fmulp

            fldz
            fcom
            fstsw ax
            sahf

            je out
            ja a_to_mid
            jmp mid_to_b

            ; je out          ; если f=0, на выход
            ; jg mid_to_b     ; если f>0, a-b -> a-f
            ; movq xmm0, [x]
            ; jz mid_to_b
            a_to_mid:
                movq [bot], xmm0
                jmp to_end
            
            mid_to_b:
                movq [top], xmm0
            
            to_end:
                loop midpoint_getter_loop
        
        out:
            ret

    ; solve:
    ;     ; mov qword[ x ], 0
    ;     mov rdi, __float64__(1.0)
    ;     mov qword[ x ], rdi

    ;     call f_x
    ;     ret

    print_result:
        push rax
        push rdi
        push rsi

        mov     rdi, qword[ res_spin ] 
        movq    xmm0, [ f ] 
        call    gtk_spin_button_set_value

        pop rsi
        pop rdi
        pop rax
        ret

    run_handler:
        push rsi
        ; начало интервала
        mov rdi, qword[ input_a ]
        call gtk_spin_button_get_value
        movq [ bot ], xmm0 
        ; конец интервала
        mov rdi, qword[ input_b ]
        call gtk_spin_button_get_value
        movq [ top ], xmm0
        ; количество итераций
        mov rdi, qword[ input_i ]
        call gtk_spin_button_get_value
        movq [ iters ], xmm0

        call solve

        call print_result

        pop rsi
        ret

    _destroy_window:
        jmp     gtk_main_quit
    
    main:
        push    rbp
        mov     rbp, rsp
        ; init
        xor     rsi, rsi
        xor     rdi, rdi
        call    gtk_init
        ;
        xor     rdi, rdi
        call    gtk_window_new
        mov     qword [ rel window ], rax
        ; title
        mov     rdi, qword [ rel window ]
        mov     rsi, title
        call    gtk_window_set_title
        ; window size
        mov     rdi, qword [ rel window ]
        mov     rsi, GTK_WIN_WIDTH
        mov     rdx, GTK_WIN_HEIGHT
        call    gtk_window_set_default_size


        ; box 
        mov     rdi, 1
        mov     rsi, 1
        call    gtk_box_new
        mov     qword[box], rax

        ; a_spin
        mov     rdi, __float64__(-100.0)
        movq    XMM0, rdi
        mov     rsi, __float64__(100.0)
        movq    XMM1, rsi
        mov     rdx, __float64__(1.0)
        movq    XMM2, rdx
        call    gtk_spin_button_new_with_range
        mov     qword[input_a], rax

        mov     rdi, qword[input_a]
        mov     rsi, 6
        movq    XMM0, rsi
        call    gtk_spin_button_set_digits

        mov     rdi, qword[input_a]
        mov     rsi, __float64__(-0.2)
        movq    XMM0, rsi
        call    gtk_spin_button_set_value

        mov     rdi,qword[box]
        mov     rsi,qword[input_a]
        call    gtk_container_add

        ; b_spin
        mov     rdi, __float64__(-100.0)
        movq    XMM0, rdi
        mov     rsi, __float64__(100.0)
        movq    XMM1, rsi
        mov     rdx, __float64__(1.0)
        movq    XMM2, rdx
        call    gtk_spin_button_new_with_range
        mov     qword[input_b], rax

        mov     rdi, qword[input_b]
        mov     rsi, 6
        movq    XMM0, rsi
        call    gtk_spin_button_set_digits

        mov     rdi, qword[input_b]
        mov     rsi, __float64__(0.2)
        movq    XMM0, rsi
        call    gtk_spin_button_set_value

        mov     rdi,qword[box]
        mov     rsi,qword[input_b]
        call    gtk_container_add

        ; i_spin
        mov     rdi, __float64__(-100.0)
        movq    XMM0, rdi
        mov     rsi, __float64__(100.0)
        movq    XMM1, rsi
        mov     rdx, __float64__(1.0)
        movq    XMM2, rdx
        call    gtk_spin_button_new_with_range
        mov     qword[input_i], rax

        mov     rdi, qword[input_i]
        mov     rsi, __float64__(10.0)
        movq    XMM0, rsi
        call    gtk_spin_button_set_value

        mov     rdi, qword[input_i]
        mov     rsi, 6
        movq    XMM0, rsi
        call    gtk_spin_button_set_digits

        mov     rdi,qword[box]
        mov     rsi,qword[input_i]
        call    gtk_container_add

        ; button
        mov     rdi, run_button.label
        call    gtk_button_new_with_label
        mov     qword[run_button],rax

        mov     rdi, rax
        mov     rsi, run_button_text
        call    gtk_button_set_label

        mov     rdi,qword[box]
        mov     rsi,qword[run_button]
        call    gtk_container_add

        ; result spin
        mov     rdi, __float64__(-100.0)
        movq    XMM0, rdi
        mov     rsi, __float64__(100.0)
        movq    XMM1, rsi
        mov     rdx, __float64__(1.0)
        movq    XMM2, rdx
        call    gtk_spin_button_new_with_range
        mov     qword[res_spin], rax

        mov     rdi, qword[res_spin]
        mov     rsi, __float64__(0.0)
        movq    XMM0, rsi
        call    gtk_spin_button_set_value

        mov     rdi, qword[res_spin]
        mov     rsi, 6
        movq    XMM0, rsi
        call    gtk_spin_button_set_digits

        mov     rdi,qword[box]
        mov     rsi,qword[res_spin]
        call    gtk_container_add
        
        ; ; result label
        ; call    gtk_label_new
        ; mov     qword[res_label.handle], rax

        ; mov     rdi,qword[res_label.handle]
        ; mov     rsi,res_label.default
        ; call    gtk_label_set_text

        ; mov     rdi,qword[box]
        ; mov     rsi,qword[res_label.handle]
        ; call    gtk_container_add

        ; vbox
        mov     rdi,qword[window]
        mov     rsi,qword[box]
        call    gtk_container_add


        ; run_button signal
        mov     rdi, qword [ run_button.handle ]
        mov     rsi, signal.clicked
        mov     rdx, run_handler
        xor     rcx, rcx
        xor     r8d, r8d
        xor     r9d, r9d
        call    g_signal_connect_data

        ; destroy signal
        mov     rdi, qword [ rel window ]
        mov     rsi, destroy_text
        mov     rdx, _destroy_window
        xor     rcx, rcx
        xor     r8d, r8d
        xor     r9d, r9d
        call    g_signal_connect_data       
        

        ; show
        mov     rdi, qword [ rel window ]
        ; call  gtk_widget_show
        call    gtk_widget_show_all
        ; mainloop
        call    gtk_main
        xor     rdi, rdi
        call    exit
    ret