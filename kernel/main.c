// kernel/main.c
#include "kstdio.h"
#include "ext2.h"
#include "vfs.h"
#include "proc.h"

// Bunlar linker tarafından sağlanıyor (boot/start.s içinde)
extern uint32_t initrd_addr;
extern uint32_t initrd_size;

void kernel_main(void) {
    kprintf("Qunics POSIX-skeleton kernel booting...\n");

    // Initrd bilgisi
    kprintf("Initrd detected: %u bytes at %p\n", initrd_size, (void*)initrd_addr);

    // EXT2 mount etmeyi dene
    if (ext2_mount((void*)initrd_addr, initrd_size) != 0) {
        kprintf("ext2 mount failed. Halting.\n");
        for (;;); // sonsuza kadar bekle
    }

    kprintf("System ready. Trying to exec /bin/hello...\n");

    // İlk kullanıcı sürecini başlat
    if (proc_exec_from_elf("/bin/hello") != 0) {
        kprintf("No /bin/hello found in initrd.\n");
        for (;;); // hata durumunda kilitlen
    }

    // Kernel burada idle moda girer
    for (;;);
}
