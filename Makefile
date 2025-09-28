# QunicsOS Makefile

CROSS_COMPILE =
AS      = $(CROSS_COMPILE)as
CC      = $(CROSS_COMPILE)gcc
LD      = $(CROSS_COMPILE)ld
OBJCOPY = $(CROSS_COMPILE)objcopy

CFLAGS  = -ffreestanding -O2 -Wall -Wextra -m32 -Ikernel -Ikernel/arch/i386
LDFLAGS = -m elf_i386 -T linker.ld

OBJS = \
    boot/start.o \
    boot/multiboot_header.o \
    io.o \
    kernel/arch/i386/isr80.o \
    kernel/arch/i386/idt.o \
    kernel/arch/i386/gdt.o \
    kernel/arch/i386/gdt_flush.o \
    kernel/arch/i386/enter_user.o \
    kernel/pmm.o \
    kernel/paging.o \
    kernel/elf.o \
    kernel/proc.o \
    kernel/kstdio.o \
    kernel/syscall.o \
    kernel/ext2.o \
    kernel/vfs.o \
    kernel/timer.o \
    kernel/utils.o \
    kernel/main.o

KERNEL = kernel.bin
ISO    = qunics.iso
INITRD = ext2.img

all: $(KERNEL) iso

# Kernel link
$(KERNEL): $(OBJS)
	$(LD) $(LDFLAGS) -o $@ $(OBJS)

# Assembly
%.o: %.s
	$(AS) --32 -o $@ $<

# C files
%.o: %.c
	$(CC) -c $(CFLAGS) -o $@ $<

# ext2 image (initrd)
$(INITRD):
	dd if=/dev/zero of=$(INITRD) bs=1M count=8
	mkfs.ext2 -F -I 128 -L QUNICS $(INITRD)
	sudo mkdir -p /mnt/qunics
	sudo mount -o loop $(INITRD) /mnt/qunics
	sudo mkdir -p /mnt/qunics/bin
	sudo umount /mnt/qunics

# ISO image with GRUB
iso: $(KERNEL) $(INITRD)
	mkdir -p iso/boot/grub
	cp $(KERNEL) iso/boot/
	cp boot/grub/grub.cfg iso/boot/grub/
	cp $(INITRD) iso/boot/initrd.ext2
	grub2-mkrescue -o $(ISO) iso

run: all
	qemu-system-i386 -cdrom $(ISO)

clean:
	rm -rf *.o kernel/*.o kernel/arch/i386/*.o boot/*.o \
	       $(KERNEL) $(ISO) $(INITRD) iso user/hello
