#ifdef __cplusplus                      //ensures c++ is not being used to compile
extern "C" {
#endif

void kernel_main();                     // tells linker the function exists
void print(const char* str);
void clear_screen();

#ifdef __cplusplus                      // closes extern block c
}
#endif

void kernel_main(){
    clear_screen(); // Wipe the screen

    print("Welcome to BrextonOS!\n");

    while (1);     // Halt kernel forever
}