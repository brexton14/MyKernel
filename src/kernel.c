#include "../include/print.h"
#include "../include/keyboard.h"
#include "../include/kstdio.h"

#ifdef __cplusplus                      //ensures c++ is not being used to compile
extern "C" {
#endif

void kernel_main();                     // tells linker the function exists

#ifdef __cplusplus                      // closes extern block c
}
#endif

void kernel_main(){
    clear_screen(); // Wipe the screen

    print("Welcome to BrextonOS!\n");
    kprintf("Kernel version: %d.%d\n", 0, 1);

    while (1){
        keyboard_handler();
    }   // Halt kernel forever
}