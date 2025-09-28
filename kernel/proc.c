// kernel/proc.c
#include "arch/i386/enter_user.h"
#include "kstdio.h"
#include "elf.h"
#include "vfs.h"
#include "paging.h"
#include "proc.h"

// Basit bir ELF process başlatıcı
int proc_exec_from_elf(const char *path) {
    int fd = vfs_open(path, 0);
    if (fd < 0) {
        kprintf("proc: cannot open %s\n", path);
        return -1;
    }

    // ELF dosyasını oku
    uint8_t buf[4096]; // küçük ELF dosyaları için yeterli
    int r = vfs_read(fd, buf, sizeof(buf));
    if (r <= 0) {
        kputs("proc: elf load failed\n");
        vfs_close(fd);
        return -1;
    }
    vfs_close(fd);

    uint32_t entry = 0;
    uint32_t *pdir = NULL;
    if (elf_load_and_map(buf, r, &entry, &pdir) != 0) {
        kputs("proc: elf parsing failed\n");
        return -1;
    }

    // Kullanıcı moduna geç
    kprintf("proc: jumping to user ELF entry at 0x%x...\n", entry);
    enter_user_mode(entry, pdir);

    return 0;
}
