#include <stdarg.h>
#include <stddef.h>
#include "../include/print.h"
#include "../include/kstdio.h"
#include "../include/stdlib.h"

// simplified kprintf for %s, %d, %c
void kprintf(const char* format, ...){
    va_list args;
    va_start(args, format);

    for (size_t i = 0; format[i] != '\0'; i++) {
        if (format[i] == '%' && format[i + 1] != '\0') {
            i++;  // move to format specifier
            char buffer[32];  // local temporary buffer

            switch (format[i]) {
                case 'c': {
                    char c = (char) va_arg(args, int);
                    putchar(c);
                    break;
                }
                case 's': {
                    char* str = va_arg(args, char*);
                    print(str);
                    break;
                }
                case 'd': {
                    int num = va_arg(args, int);
                    itoa(num, buffer);
                    print(buffer);
                    break;
                }
                case 'u': {
                    unsigned int num = va_arg(args, unsigned int);
                    utoa(num, buffer, 10);
                    print(buffer);
                    break;
                }
                case 'x': {
                    unsigned int num = va_arg(args, unsigned int);
                    utoa(num, buffer, 16);
                    print("0x");           // standard hex prefix
                    print(buffer);
                    break;
                }
                case '%': {
                    putchar('%');
                    break;
                }
                default: {
                    putchar('%');
                    putchar(format[i]);  // fallback
                    break;
                }
            }
        } else {
            putchar(format[i]);
        }
    }
    va_end(args);

}
// Panic function: prints message and halts
void panic(const char* message) {
    print("\n\n!!! Kernel Panic !!!\n");
    print(message);
    print("\nSystem halted.\n");

    // Infinite loop to simulate halt
    while (1) {
        __asm__ volatile ("cli; hlt");  // Disable interrupts and halt CPU
    }
}
