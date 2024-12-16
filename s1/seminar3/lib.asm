%define SYS_READ 0
%define SYS_WRITE 1
%define SYS_EXIT 60

%define STD_IN 0
%define STD_OUT 1
%define ST_ERR 2


section .data
codes:
    db   '0123456789ABCDEF'

section .text
    global exit
    global print_hex
    
; Принимает код возврата и завершает текущий процесс
exit:
    ; код возвратаи так уже в rdi как аргумент
    mov rax, SYS_EXIT; 
    syscall

print_hex:
        ; number 1122... in hexadecimal format
    mov  rax, rdi

    mov  rdi, 1
    mov  rdx, 1
    mov  rcx, 64
    ; Each 4 bits should be output as one hexadecimal digit
    ; Use shift and bitwise AND to isolate them
    ; the result is the offset in 'codes' array
.loop:
    push rax
    sub  rcx, 4
    ; cl is a register, smallest part of rcx
    ; rax -- eax -- ax -- ah + al
    ; rcx -- ecx -- cx -- ch + cl
    sar  rax, cl
    and  rax, 0xf

    lea  rsi, [codes + rax]
    mov  rax, 1

    ; syscall leaves rcx and r11 changed
    push  rcx
    syscall
    pop  rcx

    pop  rax
    ; test can be used for the fastest 'is it a zero?' check
    ; see docs for 'test' command
    test rcx, rcx
    jnz .loop
    ret