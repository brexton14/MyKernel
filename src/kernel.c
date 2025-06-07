#include "../include/print.h"
#include "../include/keyboard.h"
#include "../include/kstdio.h"


void kernel_main(){
    clear_screen(); // Wipe the screen

    print("Welcome to RexOS!\n");
    kprintf("Kernel version: %d.%d\n", 0, 1);
    print("> "); // Initial shell prompt
    while (1){
        keyboard_handler();
    }   // Halt kernel forever
}