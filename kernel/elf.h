#ifndef ELF_H
#define ELF_H
#include <stdint.h>
int elf_load_and_map(const void *elf_addr, uint32_t elf_size, uint32_t *entry_out, uint32_t **pdir_out);
#endif
