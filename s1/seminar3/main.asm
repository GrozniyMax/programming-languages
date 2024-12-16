%include "lib.inc"

section .text
global _start

_start:
    mov rdi, 0x1122
    call print_hex
    call exit
    ret