// kernel/proc.h
#ifndef PROC_H
#define PROC_H

#include <stdint.h>

// Basit process exec API'si
// ELF dosyasını açar, memory map yapar ve kullanıcı modunda çalıştırır.
int proc_exec_from_elf(const char *path);

// İleride eklenebilecekler:
// - process tablosu
// - PID yönetimi
// - fork(), exit(), wait()

#endif
