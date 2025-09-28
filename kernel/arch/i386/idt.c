#include "idt.h"
#include <stdint.h>

struct idt_entry {
    uint16_t base_low;
    uint16_t sel;
    uint8_t  always0;
    uint8_t  flags;
    uint16_t base_high;
} __attribute__((packed));

struct idt_ptr {
    uint16_t limit;
    uint32_t base;
} __attribute__((packed));

#define IDT_SIZE 256
static struct idt_entry idt[IDT_SIZE];
static struct idt_ptr idtp;

extern void isr80_handler(void);

static void idt_set_gate(uint8_t num, uint32_t base, uint16_t sel, uint8_t flags) {
    idt[num].base_low = base & 0xFFFF;
    idt[num].sel = sel;
    idt[num].always0 = 0;
    idt[num].flags = flags;
    idt[num].base_high = (base >> 16) & 0xFFFF;
}

static inline void lidt(void* base, uint16_t size) {
    struct {
        uint16_t length;
        uint32_t base;
    } __attribute__((packed)) IDTR = { size, (uint32_t) base };
    __asm__ volatile("lidt %0" : : "m"(IDTR));
}

void idt_init(void) {
    for (int i = 0; i < IDT_SIZE; i++) {
        idt_set_gate(i, 0, 0, 0);
    }

    /* Int 0x80 → isr80_handler, selector = 0x08 (kernel code), flags = 0xEE:
       - Present
       - DPL=3 (user space erişebilir)
       - 32-bit interrupt gate (0xE) */
    idt_set_gate(0x80, (uint32_t)isr80_handler, 0x08, 0xEE);

    idtp.limit = sizeof(idt) - 1;
    idtp.base = (uint32_t)&idt;

    lidt(&idt, sizeof(idt) - 1);
}
