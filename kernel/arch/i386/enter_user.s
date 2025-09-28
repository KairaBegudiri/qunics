/* enter_user_mode(entry, user_stack, pd_phys) */

.code32
.text
.global enter_user_mode

enter_user_mode:
    mov 4(%esp), %eax   # entry
    mov 8(%esp), %ebx   # user_stack
    mov 12(%esp), %ecx  # pd_phys

    mov %ecx, %cr3

    pushl $0x23
    pushl %ebx
    pushfl
    pushl $0x1B
    pushl %eax
    iret
