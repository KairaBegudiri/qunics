#ifndef PAGING_H
#define PAGING_H
#include <stdint.h>

/* Flags for map_page */
#define PDE_PRESENT 0x1
#define PDE_RW      0x2
#define PDE_USER    0x4

void paging_init(uint32_t phys_end);
int map_page(uint32_t *pd, uint32_t va, uint32_t pa, uint32_t flags);
uint32_t* create_user_pdir(void);
void switch_pdir(uint32_t *pd);

#endif
