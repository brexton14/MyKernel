# Custom x86 Kernel (NASM + C)

This is a simple 32-bit operating system kernel built from scratch using NASM and C. It boots directly with QEMU and runs in protected mode without relying on any operating system or standard library.

---

## Features so far

- Multiboot-compliant kernel with custom linker script
- Raw VGA text output using direct memory access
- Stack setup and C runtime environment
- `kernel_main()` executed from custom bootloader

---

## Latest Update

**Added `print()` function**  
A low-level function that prints strings to the VGA screen with newline `\n` support and white-on-black text formatting.

---

## Run It

download and then run:
qemu-system-i386 -kernel kernel.bin
