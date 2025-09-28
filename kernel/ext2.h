#ifndef EXT2_H
#define EXT2_H

#include <stdint.h>

/* ==== Ext2 Superblock ==== */
struct ext2_superblock {
    uint32_t inodes_count;
    uint32_t blocks_count;
    uint32_t log_block_size;
    uint32_t inode_size;
    uint32_t inodes_per_group;
    uint32_t magic;
};

/* ==== Ext2 Inode ==== */
struct ext2_inode {
    uint32_t size;
    uint32_t blocks;
    uint32_t block[15];
};

/* ==== Ext2 API ==== */

int ext2_mount(const void *image, uint32_t size);

int ext2_lookup(const char *path, uint32_t *ino_out);

uint32_t ext2_get_size(uint32_t ino);

int ext2_read(uint32_t ino, uint32_t offset, void *buf, uint32_t len);

#endif
