// kernel/main.c
#include "kstdio.h"
#include "ext2.h"
#include "vfs.h"
#include "proc.h"

extern uint32_t initrd_addr;
extern uint32_t initrd_size;

void kernel_main(void) {
    kprintf("Qunics POSIX-skeleton kernel booting...\n");

    kprintf("Initrd detected: %u bytes at %p\n", initrd_size, (void*)initrd_addr);

    if (ext2_mount((void*)initrd_addr, initrd_size) != 0) {
        kprintf("ext2 mount failed. Halting.\n");
        for (;;);
    }

    kprintf("System ready. Trying to exec /bin/hello...\n");

    if (proc_exec_from_elf("/bin/hello") != 0) {
        kprintf("No /bin/hello found in initrd.\n");
        for (;;);
    }

    for (;;);
}
