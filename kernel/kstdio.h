// kernel/kstdio.h
#ifndef KSTDIO_H
#define KSTDIO_H

#include <stdint.h>
#include <stddef.h>

// Tek karakter yazdır
void vga_putc(char c);

// String yazdır
void kputs(const char* s);

// Formatlı çıktı (%s, %d, %u, %p, %c)
void kprintf(const char* fmt, ...);

#endif // KSTDIO_H
