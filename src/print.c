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

void scroll(){
    // deletes top row and moves rows all up by one
    for (size_t row = 1; row < VGA_HEIGHT; row++){
        for (size_t col = 0; col < VGA_WIDTH; col++){
            size_t from = (row * VGA_WIDTH + col) * 2;
            size_t to = ((row - 1) * VGA_WIDTH + col) * 2;
            video_memory[to] = video_memory[from];
            video_memory[to + 1] = video_memory[from + 1];
        }
    }

    for (size_t col = 0; col < VGA_WIDTH; col++) {
        size_t index = ((VGA_HEIGHT - 1) * VGA_WIDTH + col) * 2;
        video_memory[index] = ' ';
        video_memory[index + 1] = VGA_COLOR;
    }

    cursor_row = VGA_HEIGHT - 1;
}

void clear_screen(){
    for (size_t row = 0; row < VGA_HEIGHT; row++){
        for(size_t col = 0; col < VGA_WIDTH; col++){
            size_t index = (row * VGA_WIDTH + col) * 2;
            video_memory[index] = ' ';
            video_memory[index + 1] = VGA_COLOR;
        }
    }
    cursor_row = 0;
    cursor_col = 0;
}
void putchar(char c) {
    if (c == '\n') {
        // Move to start of next row on newline
        cursor_row++;
        cursor_col = 0;
    } else if (c == '\b') {
        if (cursor_col > 0) {
            cursor_col--;
        } else if (cursor_row > 0) {
            cursor_row--;
            cursor_col = VGA_WIDTH - 1;
        }
        size_t index = (cursor_row * VGA_WIDTH + cursor_col) * 2;
        video_memory[index] = ' ';
        video_memory[index + 1] = VGA_COLOR;
    } else {
        size_t index = (cursor_row * VGA_WIDTH + cursor_col) * 2;
        video_memory[index] = c;
        video_memory[index + 1] = VGA_COLOR;
        cursor_col++;
        if (cursor_col >= VGA_WIDTH) {
            cursor_col = 0;
            cursor_row++;
        }
    }

    if (cursor_row >= VGA_HEIGHT) {
        scroll();
    }
}
/**
 * Writes a null-terminated string to the screen starting at the current cursor.
 */
void print(const char* str) {
    for (size_t i = 0; str[i] != '\0'; i++) {
        putchar(str[i]);
    }
}