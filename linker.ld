ENTRY(_start)

SECTIONS {
    . = 0x100000; /* Loading address for Kernel at 1mb */

    .text : ALIGN(4K) {
        *(.multiboot) /* Multiboot header must be first required by GRUB*/
        *(.text*) /* All code is entered in here -boot.asm*/
    }

    .rodata : ALIGN(4K) {
        *(.rodata) /*read-only data*/
    }

    .data : ALIGN(4K) {
        *(.data*) /*Initialized data ex: int x =5;*/
    }

    .bss : ALIGN(4K) {
        *(.bss*) /*Zero-initialized data */
        *(COMMON)
    }
    .stack (NOLOAD) : ALIGN(16) { /*Address you should load into ESP at boot*/
        _stack_top = .;
        . = . + 0x4000; /* 16 KB stack */
        _stack_bottom = .; /*Marks the base of the stack*/
    }
    .heap (NOLOAD) : ALIGN(16) {/*Bounds for future memory allocator*/
        _heap_start = .;
        . = . + 0x100000; /* 1 MB heap */
        _heap_end = .;
    }
    /DISCARD/ : {
        *(.comment)
        *(.note*)
    }
}