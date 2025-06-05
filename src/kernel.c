#ifdef __cplusplus                      //ensures c++ is not being used to compile
extern "C" {
#endif

void kernel_main();                     // tells linker the function exists
void print(const char* str);
#ifdef __cplusplus                      // closes extern block c
}
#endif

void kernel_main(){
    print("Welcome to BrextonOS!\n");
    print("Printing is now clean and modular.\n");
    while (1);     //endless loop so kernel does not return
}