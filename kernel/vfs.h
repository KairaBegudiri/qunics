#ifndef VFS_H
#define VFS_H

#include <stdint.h>

/* Sanal dosya sistemi arayüzü */
void vfs_init();

int  vfs_open(const char *path, int flags);   /* fd veya -1 döner */
int  vfs_read(int fd, void *buf, uint32_t len);
int  vfs_close(int fd);

#endif
