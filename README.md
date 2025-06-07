# Custom x86 Kernel (NASM + C) Brextons Kernel

This is a simple 32-bit operating system kernel built from scratch using NASM and C. It boots directly with QEMU and runs in protected mode without relying on any operating system or standard library.

---

## Features Implemented

- **Multiboot-Compliant Bootloader**  
  A minimal GRUB-compatible bootloader written in NASM that loads the kernel into 32-bit protected mode.

- **Custom Linker Script**  
  Uses a `linker.ld` file to control memory layout and ensure correct entry point and section mapping.

- **Raw VGA Text Output**  
  Directly writes to VGA memory (0xB8000) to display white-on-black text using low-level `putchar()` and `print()` functions.

- **Screen Clearing and Scrolling**  
  The `clear_screen()` function resets the terminal, and vertical scrolling is implemented when the text buffer overflows.

- **Backspace Support**  
  Basic backspace handling using `\\b` is included in the `putchar()` function to erase characters from the screen buffer.

- **Stack Initialization and C Runtime Support**  
  Sets up a proper stack in assembly and jumps into the C-defined `kernel_main()` function.

- **Keyboard Input Handler (WIP)**  
  A basic input loop has been started in `kernel_main()` calling `keyboard_handler()` continuously. Keyboard scancode handling logic is being integrated.

---

## How to Run

1. **Build your kernel binary** (ensure NASM, i686-elf GCC toolchain, and linker are set up)
2. Launch with QEMU:

```bash
qemu-system-i386 -kernel kernel.bin
