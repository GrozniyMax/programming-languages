global main
section .data
x: dq -4.0
input_format: db "%lf", 0

y: dq 0.0
output_format: db "y = %lf", 10, 0  ; Формат строки с символом новой строки

error_msg: db "Out of range", 10, 0

x1: dq -4.0
x2: dq -2.0
x3: dq 4.0
x4: dq 6.0
x5: dq 10.0

y0: dq 0.0
y1: dq 3.0
y2: dq -0.5
y3: dq -2.0
yl1: dq -1.0    ; Коэффиценты для итогового уравнения
yl2: dq -60.0
yl3: dq 16.0
yl4: dq -2.0
 
section .text
    extern printf
    extern scanf
    
; Принимает указатель на нуль-терминированную строку, возвращает её длину
string_length:
    xor rax, rax                ; Очистить rax
    .loop:
        cmp byte[rdi+rax], `\0`
        je .end
        inc rax
        jmp .loop
     .end:
        ret

; Принимает указатель на нуль-терминированную строку, выводит её в stdout
print_string:
    xor rax, rax                ; Сбрасываем фла
    push rdi
    call string_length
    mov rdx, rax
    pop rsi
    mov rdi, 1            ; то положим его на стек, и получим через rsp
    mov rax, 1
    syscall
    ret    
    
main:

    push rbp
    lea rdi, qword[input_format]    ; Указатель на строку формата
    lea rsi, qword[x]    ; Указатель на переменную для записи числа
    call scanf               ; Вызов scanf
    pop rbp
    ;xmm15 - регистр для сравнений
    
   
    movsd xmm15, qword[x]  ; x<=-4
    cmpltsd xmm15, qword[x1]  ;
    cvtsd2si rax, xmm15  ; преобразуем число из xmm0 в целое число и помещаем в rax
    test rax, rax
    jnz .error
    
    movsd xmm15, qword[x]      ; помещаем в регистр xmm0 число x
    cmplesd xmm15, qword[x2]  ; x<=-2
    cvtsd2si rax, xmm15  ; преобразуем число из xmm0 в целое число и помещаем в rax
    test rax, rax
    jz .next1
    
    movq xmm1, qword[y1]
    addsd xmm1, [x]
    movsd [y], xmm1
    jmp .print
    
.next1:
    movsd xmm15, qword[x]      ; помещаем в регистр xmm0 число x
    cmplesd xmm15, qword[x3]  ; x<=4
    cvtsd2si rax, xmm15  ; преобразуем число из xmm0 в целое число и помещаем в rax
    test rax, rax
    jz .next2
    movq xmm1, [x]     ; y = x
    mulsd xmm1, qword[y2]          ; y = x*-0.5
    movsd qword[y], xmm1
    jmp .print
    
.next2:
    movsd xmm15, qword[x]      ; помещаем в регистр xmm0 число x
    cmplesd xmm15, qword[x4]  ; x<=6
    cvtsd2si rax, xmm15  ; преобразуем число из xmm0 в целое число и помещаем в rax
    test rax, rax
    jz .next3
    movq xmm1, qword[y3]     ; y = 2
    movsd qword[y], xmm1
    jmp .print
    
.next3:
    movsd xmm15, qword[x]     ; помещаем в регистр xmm0 число x
    cmplesd xmm15, qword[x5]  ; x<=10
    cvtsd2si rax, xmm15  ; преобразуем число из xmm0 в целое число и помещаем в rax
    test rax, rax
    jz .next4
    
    movsd xmm2, qword[x]     ; xmm2=-(x*x)
    mulsd xmm2, qword[x]
    mulsd xmm2, qword[yl1]
    
    
    movsd xmm3, qword[x]     ; xmm3=16x
    mulsd xmm3, qword[yl3]
    
    
    movsd xmm1, qword[yl2]   ; y = -60
    addsd xmm1, xmm2    ; y = y - x^2
    addsd xmm1, xmm3    ; y = y + 16*x
    
    
    sqrtsd xmm1, xmm1   ; y = sqrt(y)
    
    addsd xmm1, qword[yl4]    ; y = y-2
    
    movsd qword[y], xmm1
    jmp .print

.next4:
    jmp .error
    
.print:
    ; Подготавливаем аргументы для printf
    movsd xmm0, [y]
    push rbp
    lea rdi, [output_format]            ; Адрес строки формата
    lea rsi, [y]
    mov rax, 1                        
    call printf
    pop rbp
    jmp .end
.error:
    ; Принимает указатель на нуль-терминированную строку, выводит её в stdout
    mov rdi, error_msg
    call print_string
.end:
    mov rax, 60
    syscall