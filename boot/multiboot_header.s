/* Multiboot v1 header */
    .section .multiboot,"a",@progbits
    .align 4
    .long 0x1BADB002
    .long 0x0
    .long -(0x1BADB002 + 0x0)
