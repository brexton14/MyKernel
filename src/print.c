#include <stddef.h>

#define VGA_WIDTH 80
#define VGA_HEIGHT 25
#define VGA_ADDRESS 0xB8000

static int cursor_row = 0;
static int cursor_col = 0;
static char* const video_memory = (char*) VGA_ADDRESS;

// write single character at current cursor
void putchar(char c) {
    if (c == '\n'){
        cursor_row++;
        cursor_col = 0;
    } else {
        int index = (cursor_row * VGA_WIDTH + cursor_col) * 2;
        video_memory[index] = c; // character
        video_memory[index + 1] = 0x0F;
        cursor_col++;
        if (cursor_col >= VGA_WIDTH) {
            cursor_col = 0;
            cursor_row++;
        }
    }
    // TODO: add scrolling if cursor_row >= VGA_HEIGHT
}

void print(const char* str){
    for (size_t i = 0; str[i] != '\0'; i++){
        putchar(str[i]);
    }
}

