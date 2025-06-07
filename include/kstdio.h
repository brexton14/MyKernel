#ifndef KSTDIO_H
#define KSTDIO_H


void kprintf(const char* format, ...);  // Like printf
void panic(const char* message);        // Kernel panic with halt


#endif
