/* boot/start.s — Qunics kernel entry point */

.set STACK_SIZE, 0x4000       # 16 KB stack

.section .bss
.align 16
stack_bottom:
    .skip STACK_SIZE
stack_top:

.section .text
.global _start
.global multiboot_info_ptr

multiboot_info_ptr:
    .long 0

_start:
    movl %ebx, multiboot_info_ptr

    movl $stack_top, %esp

    call kernel_main

halt:
    cli
    hlt
    jmp halt
