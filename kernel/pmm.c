#include "pmm.h"
#include <stdint.h>

static uintptr_t pmm_next = 0;
static uintptr_t pmm_end  = 0;

void pmm_init(uintptr_t free_start, uintptr_t free_end){
    pmm_next = (free_start + 0xFFF) & ~0xFFF;
    pmm_end = free_end & ~0xFFF;
}

void* pmm_alloc_page(void){
    if (pmm_next >= pmm_end) return 0;
    void* p = (void*)pmm_next;
    pmm_next += 0x1000;
    return p;
}
