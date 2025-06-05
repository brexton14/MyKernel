#ifdef __cplusplus                      //ensures c++ is not being used to compile
extern "C" {
#endif

void kernel_main();                     // tells linker the function exists
void print(const char* str);            // new print function!!
#ifdef __cplusplus                      // closes extern block c
}
#endif

void kernel_main(){
    print("Hello from print()!\nThis is line 2.\nAnd line 3.");
    while (1);     //endless loop so kernel does not return
}