#ifndef PMM_H
#define PMM_H
#include <stdint.h>
void pmm_init(uintptr_t free_start, uintptr_t free_end);
void* pmm_alloc_page(void);
#endif
