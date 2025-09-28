#define SYS_write 1
#define SYS_exit  2

static inline int syscall(int num, int a1, int a2, int a3) {
    int ret;
    asm volatile("int $0x80"
                 : "=a"(ret)
                 : "a"(num), "b"(a1), "c"(a2), "d"(a3));
    return ret;
}

void _start(void) {
    const char msg[] = "Hello kernel!\n";
    syscall(SYS_write, 1, (int)msg, sizeof(msg)-1);
    syscall(SYS_exit, 0, 0, 0);
    for(;;); 
}
