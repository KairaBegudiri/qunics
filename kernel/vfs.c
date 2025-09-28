#include "vfs.h"
#include "ext2.h"
#include "utils.h"
#include "kstdio.h"

#define MAX_FD 32   /* aynı anda açılabilecek en fazla dosya */

struct file {
    int used;
    uint32_t ino;
    uint32_t pos;
    uint32_t size;
};

static struct file ftab[MAX_FD];

/* Basit file table reset */
void vfs_init() {
    for (int i = 0; i < MAX_FD; i++) {
        ftab[i].used = 0;
    }
}

/* Dosya açma */
int vfs_open(const char *path, int flags) {
    (void)flags; /* şimdilik kullanılmıyor */
    uint32_t ino;

    if (ext2_lookup(path, &ino) != 0) {
        kprintf("vfs_open: '%s' bulunamadı\n", path);
        return -1;
    }

    for (int fd = 0; fd < MAX_FD; fd++) {
        if (!ftab[fd].used) {
            ftab[fd].used = 1;
            ftab[fd].ino  = ino;
            ftab[fd].pos  = 0;
            ftab[fd].size = ext2_get_size(ino);
            return fd;
        }
    }

    kprintf("vfs_open: fd tablosu dolu!\n");
    return -1;
}

/* Dosya okuma */
int vfs_read(int fd, void *buf, uint32_t len) {
    if (fd < 0 || fd >= MAX_FD || !ftab[fd].used) {
        kprintf("vfs_read: geçersiz fd %d\n", fd);
        return -1;
    }

    int r = ext2_read(ftab[fd].ino, ftab[fd].pos, buf, len);
    if (r > 0) {
        ftab[fd].pos += r;
    }
    return r;
}

/* Dosya kapatma */
int vfs_close(int fd) {
    if (fd < 0 || fd >= MAX_FD || !ftab[fd].used) {
        return -1;
    }
    ftab[fd].used = 0;
    return 0;
}
