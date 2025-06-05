#include <stddef.h>

#define VGA_WIDTH 80
#define VGA_HEIGHT 25
#define VGA_ADDRESS 0xB8000

#define VGA_COLOR 0x0F

// Global cursor position
static size_t cursor_row = 0;
static size_t cursor_col = 0;

// Pointer to VGA memory buffer
static char* const video_memory = (char*) VGA_ADDRESS;

void putchar(char c) {
    if (c == '\n') {
        // Move to start of next row on newline
        cursor_row++;
        cursor_col = 0;
    } else {
        // Compute index into VGA memory (2 bytes per character cell)
        size_t index = (cursor_row * VGA_WIDTH + cursor_col) * 2;

        video_memory[index] = c;          // Character byte
        video_memory[index + 1] = VGA_COLOR; // Color/attribute byte

        // Move cursor forward
        cursor_col++;

        // Wrap to next line if end of row is reached
        if (cursor_col >= VGA_WIDTH) {
            cursor_col = 0;
            cursor_row++;
        }
    }

    // TODO: Add scrolling if cursor_row >= VGA_HEIGHT
}
/**
 * Writes a null-terminated string to the screen starting at the current cursor.
 */
void print(const char* str) {
    for (size_t i = 0; str[i] != '\0'; i++) {
        putchar(str[i]);
    }
}