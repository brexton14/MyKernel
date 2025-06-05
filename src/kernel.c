#ifdef __cplusplus                      //ensures c++ is not being used to compile
extern "C" {
#endif

void kernel_main();                     // tells linker the function exists

#ifdef __cplusplus                      // closes extern block c
}
#endif

void kernel_main(){
    char *video = (char*)0xb8000;       // text buffer

    const char *msg = "Hello from the kernel";

    for (int i = 0; msg[i]; i++){   // loop through each character
        video[i * 2] = msg[i];      // write character to screen at position i
        video[i * 2 + 1] = 0x0F;    // colo attribute White on blue
    }

    while (1);     //endless loop so kernel does not return
}