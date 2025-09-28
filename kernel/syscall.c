// kernel/syscall.c
#include "syscall.h"
#include "vfs.h"
#include "kstdio.h"

// Syscall numaraları
#define SYS_WRITE   1
#define SYS_OPEN    2
#define SYS_READ    3
#define SYS_CLOSE   4

int syscall_dispatch(int num, uint32_t a1, uint32_t a2, uint32_t a3) {
    switch (num) {
    case SYS_WRITE:
        // write(fd, buf, len)
        // Burada sadece fd = 1 (stdout) destekleniyor
        if ((int)a1 == 1) {
            const char* buf = (const char*)a2;
            for (uint32_t i = 0; i < a3; i++)
                vga_putc(buf[i]);
            return a3;
        }
        return -1;

    case SYS_OPEN:
        // open(path, flags)
        return vfs_open((const char*)a1, (int)a2);

    case SYS_READ:
        // read(fd, buf, len)
        return vfs_read((int)a1, (void*)a2, (uint32_t)a3);

    case SYS_CLOSE:
        // close(fd)
        return vfs_close((int)a1);

    default:
        kprintf("Unknown syscall %d\n", num);
        return -1;
    }
}
