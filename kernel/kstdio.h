// kernel/kstdio.h
#ifndef KSTDIO_H
#define KSTDIO_H

#include <stdint.h>
#include <stddef.h>

void vga_putc(char c);

void kputs(const char* s);

void kprintf(const char* fmt, ...);

#endif
