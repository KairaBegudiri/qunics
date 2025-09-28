// kernel/syscall.h
#ifndef SYSCALL_H
#define SYSCALL_H

#include <stdint.h>

int syscall_dispatch(int num, uint32_t a1, uint32_t a2, uint32_t a3);

#endif // SYSCALL_H
