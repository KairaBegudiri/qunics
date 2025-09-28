/* kernel/arch/i386/isr80.s — syscall interrupt handler (int 0x80) */

.code32
.text
.global isr80_handler
.extern syscall_dispatch

isr80_handler:
    pusha
    push %ds
    push %es
    push %fs
    push %gs

    mov $0x10, %ax
    mov %ax, %ds
    mov %ax, %es
    mov %ax, %fs
    mov %ax, %gs

    push %edx
    push %ecx
    push %ebx
    push %eax
    call syscall_dispatch
    add $16, %esp

    pop %gs
    pop %fs
    pop %es
    pop %ds
    popa
    iret
