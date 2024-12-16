%macro m_push 2-*
    %rep %0
        push %1
        %rotate 1
    %endrep
%endmacro

%macro m_pop 2-*
    %rep %0
        pop %1
        %rotate 1
    %endrep
%endmacro


section .text
global _start
_start:
    mov rax, 1
    mov rdi, 2
    mov rdx, 3
    
    m_push rax, rdi, rdx
    
    m_pop rax, rdi, rdx
    
    mov rax, 60; 
    syscall
    
    