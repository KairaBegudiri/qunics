// kernel/kstdio.c
#include "kstdio.h"
#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>

#define VGA_WIDTH  80
#define VGA_HEIGHT 25
#define VGA_ADDRESS 0xB8000

static uint16_t* vga_buffer = (uint16_t*) VGA_ADDRESS;
static int cursor_x = 0, cursor_y = 0;
static uint8_t vga_color = 0x07; 

static void vga_putentryat(char c, uint8_t color, int x, int y) {
    const size_t index = y * VGA_WIDTH + x;
    vga_buffer[index] = ((uint16_t)color << 8) | (uint8_t)c;
}

static void vga_scroll(void) {
    if (cursor_y < VGA_HEIGHT) return;
    for (size_t y = 1; y < VGA_HEIGHT; y++) {
        for (size_t x = 0; x < VGA_WIDTH; x++) {
            vga_buffer[(y-1)*VGA_WIDTH + x] = vga_buffer[y*VGA_WIDTH + x];
        }
    }
    for (size_t x = 0; x < VGA_WIDTH; x++) {
        vga_buffer[(VGA_HEIGHT-1)*VGA_WIDTH + x] = ((uint16_t)vga_color << 8) | ' ';
    }
    cursor_y = VGA_HEIGHT - 1;
}

void vga_putc(char c) {
    if (c == '\n') {
        cursor_x = 0;
        cursor_y++;
    } else {
        vga_putentryat(c, vga_color, cursor_x, cursor_y);
        if (++cursor_x == VGA_WIDTH) {
            cursor_x = 0;
            cursor_y++;
        }
    }
    vga_scroll();
}

void kputs(const char* s) {
    while (*s) {
        vga_putc(*s++);
    }
}

static void itoa_unsigned(unsigned int value, char *str, int base) {
    char *digits = "0123456789abcdef";
    char buf[32];
    int i = 0;

    if (value == 0) {
        str[0] = '0';
        str[1] = '\0';
        return;
    }

    while (value > 0) {
        buf[i++] = digits[value % base];
        value /= base;
    }

    for (int j = 0; j < i; j++) {
        str[j] = buf[i - j - 1];
    }
    str[i] = '\0';
}

void kprintf(const char* fmt, ...) {
    va_list args;
    va_start(args, fmt);

    for (const char* p = fmt; *p; p++) {
        if (*p == '%') {
            p++;
            if (*p == 's') {
                const char* s = va_arg(args, const char*);
                kputs(s);
            } else if (*p == 'd') {
                int v = va_arg(args, int);
                char buf[32];
                if (v < 0) {
                    vga_putc('-');
                    v = -v;
                }
                itoa_unsigned((unsigned)v, buf, 10);
                kputs(buf);
            } else if (*p == 'u') {
                unsigned int v = va_arg(args, unsigned int);
                char buf[32];
                itoa_unsigned(v, buf, 10);
                kputs(buf);
            } else if (*p == 'p') {
                void* v = va_arg(args, void*);
                char buf[32];
                kputs("0x");
                itoa_unsigned((uintptr_t)v, buf, 16);
                kputs(buf);
            } else if (*p == 'c') {
                char c = (char) va_arg(args, int);
                vga_putc(c);
            } else {
                vga_putc('%');
                vga_putc(*p);
            }
        } else {
            vga_putc(*p);
        }
    }

    va_end(args);
}
