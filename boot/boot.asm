[bits 32]               ;NASM 32-bit protected mode

section .multiboot      ; Required by GRUB to recongize and load kernel
align 4
    dd 0X1BADB002       ; Magic number to identift as a multiboot
    dd 0                ; Flags (no requesting memory map)
    dd -(0X1BADB002)    ; Checksum: magic + flags + checksum = 0

section .text
global _start           ; Make _start visible to linker
extern kernel_main      ; Declare kernel_main() from C code
extern _stack_top       ; Import stack top symbol from linker.ld

_start:
    mov esp, _stack_top ; Set up for stack pointer for kernel C code
    call kernel_main    ; Jump into kernel main

.hang:
    jmp .hang           ; infinite loop to avoid returning