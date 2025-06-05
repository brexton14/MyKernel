#ifndef PRINT_H
#define PRINT_H

#ifdef __cplusplus
extern "C" {
#endif

// Function declarations from print.c
void putchar(char c);                 // Print a single character to screen
void print(const char* str);          // Print a string to screen
void clear_screen();                  // Clears the VGA text screen

#ifdef __cplusplus
}
#endif

#endif