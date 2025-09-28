#include "ext2.h"
#include "kstdio.h"
#include <stdint.h>

static const void *ext2_image = 0;
static uint32_t ext2_size = 0;

/* ==== STUB IMPLEMENTASYON ==== */

int ext2_mount(const void *image, uint32_t size) {
    ext2_image = image;
    ext2_size = size;

    kprintf("[ext2] mounted at %p, size=%u bytes\n", image, size);
    return 0; /* başarı */
}

int ext2_lookup(const char *path, uint32_t *ino_out) {
    if (!path || !ino_out) return -1;

    if (path[0] == '/' && path[1] == 'b' && path[2] == 'i' &&
        path[3] == 'n' && path[4] == '/' &&
        path[5] == 'h' && path[6] == 'e' && path[7] == 'l' &&
        path[8] == 'l' && path[9] == 'o' && path[10] == '\0') 
    {
        *ino_out = 2;
        return 0;
    }

    kprintf("[ext2] lookup failed: %s\n", path);
    return -1;
}

uint32_t ext2_get_size(uint32_t ino) {
    (void)ino;
    return 64;
}

int ext2_read(uint32_t ino, uint32_t offset, void *buf, uint32_t len) {
    (void)ino;

    static const char fake_data[] = "Hello from Qunics stub ext2!\n";

    if (offset >= sizeof(fake_data))
        return 0;

    uint32_t to_copy = sizeof(fake_data) - offset;
    if (to_copy > len) to_copy = len;

    for (uint32_t i = 0; i < to_copy; i++) {
        ((char*)buf)[i] = fake_data[offset + i];
    }

    return to_copy;
}
