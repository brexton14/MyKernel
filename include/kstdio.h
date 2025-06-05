#ifndef KSTDIO_H
#define KSTDIO_H

#ifdef __cplusplus
extern "C" {
#endif

void kprintf(const char* format, ...);  // Like printf
void panic(const char* message);        // Kernel panic with halt

#ifdef __cplusplus
}
#endif

#endif
