#include "paging.h"
#include "pmm.h"
#include <string.h>
#include <stdint.h>

#define PDE_PRESENT 0x1
#define PDE_RW      0x2
#define PDE_USER    0x4
#define PTE_PRESENT PDE_PRESENT

static uint32_t *alloc_pt(void){
    void *p = pmm_alloc_page();
    if (!p) return 0;
    memset(p,0,0x1000);
    return (uint32_t*)p;
}

/* identity-map first N MB (phys_end bytes) and enable paging */
void paging_init(uint32_t phys_end){
    uint32_t *pd = alloc_pt();
    if(!pd) return;
    /* identity map first phys_end */
    for(uint32_t addr = 0; addr < phys_end; addr += 0x1000){
        uint32_t pdi = (addr >> 22);
        uint32_t pti = (addr >> 12) & 0x3FF;
        uint32_t *pt;
        if(!(pd[pdi] & PDE_PRESENT)){
            pt = alloc_pt();
            pd[pdi] = ((uint32_t)pt) | PDE_PRESENT | PDE_RW;
        } else {
            pt = (uint32_t*)(pd[pdi] & ~0xFFF);
        }
        pt[pti] = (addr & ~0xFFF) | PTE_PRESENT | PDE_RW;
    }
    /* load pd (CR3) and enable paging */
    __asm__ volatile("mov %0, %%cr3"::"r"(pd));
    uint32_t cr0; __asm__ volatile("mov %%cr0, %0":"=r"(cr0));
    cr0 |= 0x80000000;
    __asm__ volatile("mov %0, %%cr0"::"r"(cr0));
}

/* map single page into supplied page directory (pd is physical pointer)
   flags: PDE_RW | PDE_USER bits */
int map_page(uint32_t *pd, uint32_t va, uint32_t pa, uint32_t flags){
    uint32_t pdi = (va >> 22);
    uint32_t pti = (va >> 12) & 0x3FF;
    uint32_t *pt;
    if(!(pd[pdi] & PDE_PRESENT)){
        pt = alloc_pt();
        if(!pt) return -1;
        pd[pdi] = ((uint32_t)pt) | PDE_PRESENT | (flags & PDE_RW ? PDE_RW : 0) | (flags & PDE_USER ? PDE_USER : 0);
    } else {
        pt = (uint32_t*)(pd[pdi] & ~0xFFF);
    }
    pt[pti] = (pa & ~0xFFF) | (flags & 0xFFF) | PTE_PRESENT;
    return 0;
}

/* create minimal user page directory (copy nothing) */
uint32_t* create_user_pdir(void){
    uint32_t *pd = alloc_pt();
    return pd;
}

void switch_pdir(uint32_t *pd){
    __asm__ volatile("mov %0, %%cr3"::"r"(pd));
}
