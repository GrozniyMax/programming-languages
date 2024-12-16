global find_word
%include "lib.inc"

%ifndef NULL                    ;Установим NULL
    %define NULL 0
%endif

%ifndef LINK_OFFSET            ;Установим последний элемент
    %define LINK_OFFSET 8
%endif


section .text
; rdi - Ссылка на строку
; rsi - ссылка на словарь
find_word:
    mov  r9, rsi
    push rdi
    .loop:
        mov rdi, qword[r9]
        mov rsi, qword[rsp]                 ;Подгружаем ссылку на строку
        call string_equals
        cmp rax, 1
        jne .loop_end
        .equals:
            mov rax, qword[r9+LINK_OFFSET] ;Нашли нужный элемент
            jmp .end
    .loop_end:  
        cmp qword[r9+2*LINK_OFFSET], NULL  ;Дошли до конца словаря
        je .not_found
        mov r9, qword[r9+2*LINK_OFFSET]
        jmp .loop
    .not_found:
        xor rax, rax
    .end:
        pop rdi
        ret
