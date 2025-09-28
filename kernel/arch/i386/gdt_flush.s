/* kernel/arch/i386/gdt_flush.s — load GDT and reset segments */

.code32
.text
.global gdt_flush

gdt_flush:
    movl 4(%esp), %eax    
    lgdt (%eax)

    ljmp $0x08, $flush_cs

flush_cs:
    mov $0x10, %ax
    mov %ax, %ds
    mov %ax, %es
    mov %ax, %fs
    mov %ax, %gs
    mov %ax, %ss
    ret
