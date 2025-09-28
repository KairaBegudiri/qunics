// kernel/proc.h
#ifndef PROC_H
#define PROC_H

#include <stdint.h>

int proc_exec_from_elf(const char *path);

// İleride eklenebilecekler:
// - process tablosu
// - PID yönetimi
// - fork(), exit(), wait()

#endif
