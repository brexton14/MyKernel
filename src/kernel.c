#include "print.h"
#include "keyboard.h"

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
    print("Type something:\n> ");

    while (1){
        keyboard_handler();
    }   // Halt kernel forever
}