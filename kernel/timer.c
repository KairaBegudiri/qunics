#include "timer.h"
#include "kstdio.h"
#include <stdint.h>

/* set PIT to ~100Hz */
void timer_init(void){
    uint32_t divisor = 1193182 / 100;
    /* command port 0x43, channel 0, access lobyte/hibyte, mode 3 */
    __asm__ volatile ("outb %0, %1"::"a"((uint8_t)0x36),"Nd"((uint16_t)0x43));
    uint8_t lo = divisor & 0xFF;
    uint8_t hi = (divisor >> 8) & 0xFF;
    __asm__ volatile ("outb %0, %1"::"a"(lo),"Nd"((uint16_t)0x40));
    __asm__ volatile ("outb %0, %1"::"a"(hi),"Nd"((uint16_t)0x40));
}
