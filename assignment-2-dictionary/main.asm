%include "lib.inc"
%include "dict.inc"
%include "colon.inc"
%include "words.inc"

section .data
buffer: times 256 db 0  ;255 символов и нуль-терминатор
error_msg: db "Not found",0
input_msg: db "Enter a word to found: ",0


section .text
    global _start

_start:
    mov rdi, input_msg
    call print_string
    
    mov rdi, buffer     ; Читаем слово
    mov rsi, 256
    call read_word
    
    
    mov rdi, rax
    mov rsi, first_word
    call find_word      ; Ищем слово
    
    push 0
    test rax, rax
    jnz .output
    mov qword[rsp], 1
    mov rdi, error_msg
    call print_error
    jmp .new_line
    .output:
    mov rdi, rax        ; Выводим слово
    call print_string
    .new_line:
    call print_newline
    pop rdi
    call exit
    
    
    
    
