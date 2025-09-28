#include "elf.h"
#include "pmm.h"
#include "paging.h"
#include <stdint.h>
#include <string.h>

/* Minimal ELF32 loader for PT_LOAD segments. Assumes ELF is 32-bit little-endian. */

struct elf32_hdr {
    unsigned char e_ident[16];
    uint16_t e_type, e_machine;
    uint32_t e_version, e_entry, e_phoff, e_shoff;
    uint32_t e_flags;
    uint16_t e_ehsize, e_phentsize, e_phnum, e_shentsize, e_shnum, e_shstrndx;
};

struct elf32_phdr {
    uint32_t p_type, p_offset, p_vaddr, p_paddr, p_filesz, p_memsz, p_flags, p_align;
};

#define PT_LOAD 1

static uint32_t* alloc_pd(void){
    return (uint32_t*)pmm_alloc_page();
}

int elf_load_and_map(const void *elf_addr, uint32_t elf_size, uint32_t *entry_out, uint32_t **pdir_out){
    if(!elf_addr) return -1;
    const struct elf32_hdr *eh = (const struct elf32_hdr*)elf_addr;
    if(eh->e_ident[0] != 0x7f || eh->e_ident[1] != 'E' || eh->e_ident[2] != 'L' || eh->e_ident[3] != 'F')
        return -2;
    uint32_t phoff = eh->e_phoff;
    uint16_t phnum = eh->e_phnum;
    uint32_t *pdir = alloc_pd();
    if(!pdir) return -3;
    memset(pdir,0,0x1000);

    for(uint16_t i=0;i<phnum;i++){
        const struct elf32_phdr *ph = (const struct elf32_phdr*)((const uint8_t*)elf_addr + phoff + i * eh->e_phentsize);
        if(ph->p_type != PT_LOAD) continue;
        uint32_t va = ph->p_vaddr & ~0xFFF;
        uint32_t file_off = ph->p_offset;
        uint32_t filesz = ph->p_filesz;
        uint32_t memsz = ph->p_memsz;
        uint32_t tocopy = filesz;
        uint32_t pages = ((memsz + 0xFFF) / 0x1000);
        for(uint32_t p=0;p<pages;p++){
            void *phys = pmm_alloc_page();
            if(!phys) return -4;
            uint32_t pa = (uint32_t)phys;
            uint32_t cur_va = va + p*0x1000;
            map_page(pdir, cur_va, pa, PDE_RW | PDE_USER);
            memset((void*)pa, 0, 0x1000);
            uint32_t page_file_off = p*0x1000 - (ph->p_vaddr & 0xFFF);
            if((int)page_file_off < (int)filesz){
                uint32_t copy = (filesz - page_file_off);
                if(copy > 0x1000) copy = 0x1000;
                memcpy((void*)(pa + (ph->p_vaddr & 0xFFF ? (ph->p_vaddr & 0xFFF) : 0)), (const uint8_t*)elf_addr + file_off + page_file_off, copy);
            }
        }
    }

    *entry_out = eh->e_entry;
    *pdir_out = pdir;
    return 0;
}
