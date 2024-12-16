%define O_RDONLY 0 
%define PROT_READ 0x1
%define MAP_PRIVATE 0x2
%define SYS_OPEN 2
%define SYS_MMAP 9
%define STR_LEN 12

section .data
; This is the file name. You are free to change it. **fname here**
fname: db 'hello.txt', 0

section .text
global _start
exit:
  mov rax, 60           ; use exit system call to shut down correctly
  xor rdi, rdi
  syscall
; These functions are used to print a null terminated string
print_string:
    push rdi
    call string_length
    pop rsi
    mov rdx, rax 
    mov rax, 1
    mov rdi, 1 
    syscall
    ret
string_length:
    xor rax, rax
.loop:
    cmp byte [rdi+rax], 0
    je .end 
    inc rax
    jmp .loop 
.end:
    ret

_start:

; Вызовите open и откройте fname в режиме read only.
mov rax, SYS_OPEN
mov rdi, fname
mov rsi, O_RDONLY    ; Open file read only
mov rdx, 0            ; We are not creating a file
                      ; so this argument has no meaning
syscall

  
; Вызовите mmap c правильными аргументами
; Дайте операционной системе самой выбрать, куда отобразить файл
; Размер области возьмите в размер страницы 
; Область не должна быть общей для нескольких процессов 
;  и должна выделяться только для чтения.

mov rdi, 0
mov rsi, STR_LEN
mov rdx, PROT_READ
mov r10, MAP_PRIVATE
mov r8, rax
mov r9, 0
mov rax, SYS_MMAP
syscall


; с помощью print_string теперь можно вывести его содержимое

mov rdi, rax
call print_string

call exit
