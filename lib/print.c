#include "../include/types.h"

#define VGA_WIDTH 80
#define VGA_HEIGHT 25
#define VGA_ADDRESS 0xB8000
#define VGA_COLOR 0x0F

static size cursor_row = 0;
static size cursor_col = 0;

// Pointer to VGA memory buffer
static volatile u8* const video_memory = (u8*) VGA_ADDRESS;

static void scroll() {
    for (size row = 1; row < VGA_HEIGHT; row++) {
        for (size col = 0; col < VGA_WIDTH; col++) {
            size from = (row * VGA_WIDTH + col) * 2;
            size to = ((row - 1) * VGA_WIDTH + col) * 2;
            video_memory[to] = video_memory[from];
            video_memory[to + 1] = video_memory[from + 1];
        }
    }
    for (size col = 0; col < VGA_WIDTH; col++) {
        size index = ((VGA_HEIGHT - 1) * VGA_WIDTH + col) * 2;
        video_memory[index] = ' ';
        video_memory[index + 1] = VGA_COLOR;
    }
    cursor_row = VGA_HEIGHT - 1;
}

void clear_screen() {
    for (size row = 0; row < VGA_HEIGHT; row++) {
        for (size col = 0; col < VGA_WIDTH; col++) {
            size index = (row * VGA_WIDTH + col) * 2;
            video_memory[index] = ' ';
            video_memory[index + 1] = VGA_COLOR;
        }
    }
    cursor_row = 0;
    cursor_col = 0;
}

void putchar(char c) {
    if (c == '\n') {
        cursor_row++;
        cursor_col = 0;
    } else if (c == '\b') {
        if (cursor_col > 0) {
            cursor_col--;
        } else if (cursor_row > 0) {
            cursor_row--;
            cursor_col = VGA_WIDTH - 1;
        }
        size index = (cursor_row * VGA_WIDTH + cursor_col) * 2;
        video_memory[index] = ' ';
        video_memory[index + 1] = VGA_COLOR;
    } else {
        size index = (cursor_row * VGA_WIDTH + cursor_col) * 2;
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

void print(const char* str) {
    for (size i = 0; str[i] != '\0'; i++) {
        putchar(str[i]);
    }
}
