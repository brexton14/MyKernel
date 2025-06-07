#include "../include/types.h"
#include "../include/print.h"
#include "../include/kstdio.h"
#include "../include/stdlib.h"

// simplified kprintf for %s, %d, %c, %u, %x
void kprintf(const char* format, ...) {
    va_list args;
    va_start(args, format);

    for (size i = 0; format[i] != '\0'; i++) {
        if (format[i] == '%' && format[i + 1] != '\0') {
            i++;
            char buffer[32];

            switch (format[i]) {
                case 'c': {
                    char c = (char) va_arg(args, int);
                    putchar(c);
                    break;
                }
                case 's': {
                    const char* str = va_arg(args, const char*);
                    print(str);
                    break;
                }
                case 'd': {
                    s64 num = va_arg(args, int);
                    itoa(num, buffer);
                    print(buffer);
                    break;
                }
                case 'u': {
                    u64 num = va_arg(args, unsigned int);
                    utoa(num, buffer, 10);
                    print(buffer);
                    break;
                }
                case 'x': {
                    u64 num = va_arg(args, unsigned int);
                    print("0x");
                    utoa(num, buffer, 16);
                    print(buffer);
                    break;
                }
                case '%': {
                    putchar('%');
                    break;
                }
                default: {
                    putchar('%');
                    putchar(format[i]);
                    break;
                }
            }
        } else {
            putchar(format[i]);
        }
    }

    va_end(args);
}

void panic(const char* message) {
    print("\n\n!!! Kernel Panic !!!\n");
    print(message);
    print("\nSystem halted.\n");

    while (1) {
        __asm__ volatile ("cli; hlt");
    }
}
