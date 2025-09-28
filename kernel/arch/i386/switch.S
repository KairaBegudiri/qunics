/* minimal switch_to: load CR3 (pdir), set esp, iret is used elsewhere */
.global switch_to
/* arg: pointer to proc struct in eax? we use C wrapper; keep minimal placeholder */
switch_to:
    ret
