global main
section .data
    y: dq 8.0
    output_format: db "y = %lf", 10, 0  ; Формат строки с символом новой строки
    
    x: dq -4.0
    input_format: db "%lf", 0

section .text
    extern printf
    extern scanf
main:

.print:
    push rbp
    lea rdi, [input_format]    ; Указатель на строку формата
    lea rsi, [x]    ; Указатель на переменную для записи числа
    call scanf               ; Вызов scanf
    pop rbp
    ; Загружаем считанное значение из памяти в xmm0

    push rbp
    lea rdi, [output_format]            ; Адрес строки формата
    mov rax, 1                        
    call printf
    pop rbp
.error:
    ; Завершение программы
    mov rax, 60                   ; Системный вызов для выхода
    xor rdi, rdi                  ; Код возврата 0
    syscall                       ; Завершаем программу
