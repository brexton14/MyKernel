#include <stdint.h>
#include "print.h"

#define KEYBOARD_PORT 0x60
#define KEYBOARD_STATUS_PORT 0x64
#define BUFFER_SIZE 256

// input buffer
char input_buffer[BUFFER_SIZE];
int buffer_index = 0;

// shift press and caps lock
int shift_pressed = 0;
int capslock_enabled = 0;

// US QWERTY layout(lowercase)
const unsigned char scancode_to_ascii[] = {
        0,  27, '1','2','3','4','5','6','7','8','9','0','-','=','\b', // 0x0 - 0x0F
        '\t','q','w','e','r','t','y','u','i','o','p','[',']','\n',    // 0x10 - 0x1D
        0,  'a','s','d','f','g','h','j','k','l',';','\'','`',         // 0x1E - 0x29
        0,  '\\','z','x','c','v','b','n','m',',','.','/', 0, '*', 0,  // 0x2A - 0x38
        ' ' // space
};

// US QWERTY layout(uppercase)
const unsigned char scancode_to_ascii_shift[] = {
        0,  27, '!', '@', '#', '$', '%', '^', '&', '*', '(', ')', '_', '+', '\b',
        '\t','Q','W','E','R','T','Y','U','I','O','P','{','}','\n',
        0,  'A','S','D','F','G','H','J','K','L',':','"','~',
        0,  '|','Z','X','C','V','B','N','M','<','>','?', 0, '*', 0,
        ' '
};

#define SCANCODE_MAP_SIZE (sizeof(scancode_to_ascii) / sizeof(scancode_to_ascii[0]))

// Read byte from I/O port
uint8_t inb(uint16_t port) {
    uint8_t ret;
    __asm__ __volatile__ ("inb %1, %0" : "=a"(ret) : "Nd"(port));
    return ret;
}
// Check keyboard status port
uint8_t inb_status(uint16_t port) {
    uint8_t ret;
    __asm__ __volatile__ ("inb %1, %0" : "=a"(ret) : "Nd"(port));
    return ret;
}

// Mini version of strcmp (no stdlib)
int strcmp(const char* s1, const char* s2) {
    while (*s1 && (*s1 == *s2)) {
        s1++;
        s2++;
    }
    return *(const unsigned char*)s1 - *(const unsigned char*)s2;
}
// Simple shell command handler
void handle_command(const char* input) {
    if (strcmp(input, "clear") == 0) {
        clear_screen();
        print("> ");
    } else if (strcmp(input, "help") == 0) {
        print("Available commands: help, clear\n> ");
    } else {
        print("Unknown command\n> ");
    }
}

// Keyboard input handler
void keyboard_handler() {
    uint8_t status = inb_status(KEYBOARD_STATUS_PORT);
    if ((status & 0x01) == 0) {
        return; // no data ready
    }

    uint8_t scancode = inb(KEYBOARD_PORT);
    // --- Special key handling ---

    // Shift pressed
    if (scancode == 0x2A || scancode == 0x36) {
        shift_pressed = 1;
        return;
    }

    // Shift released
    if (scancode == 0xAA || scancode == 0xB6) {
        shift_pressed = 0;
        return;
    }

    // Caps Lock toggled
    if (scancode == 0x3A) {
        capslock_enabled = !capslock_enabled;
        return;
    }

    // Ignore release scancodes, extended scancodes, and invalid range
    if ((scancode & 0x80) || scancode == 0xE0 || scancode >= SCANCODE_MAP_SIZE)
        return;


    // --- Character translation ---

    // Choose correct table
    char c = (char)(shift_pressed ? scancode_to_ascii_shift[scancode]
                                  : scancode_to_ascii[scancode]);

    // Apply CapsLock logic to letters
    if (c >= 'a' && c <= 'z') {
        if (capslock_enabled ^ shift_pressed) {
            c -= 32; // convert to uppercase
        }
    }

    // Skip unmapped characters
    if (!c) return;


    if (c == '\b') {
        if (buffer_index > 0) {
            buffer_index--;
            input_buffer[buffer_index] = '\0';

            // Erase character from screen visually
            putchar('\b');
            putchar(' ');
            putchar('\b');
        }
    }

    else if (c == '\n'){
        // Handle enter key
        putchar('\n');
        handle_command(input_buffer);
        putchar('\n'); // Clear the buffer for next input

        // reset buffer
        buffer_index = 0;
        input_buffer[0] = '\0';

        print("> "); // Show new input prompt
    }

    else {
        // Normal printable character
        if (buffer_index < BUFFER_SIZE - 1) {
            input_buffer[buffer_index++] = c;
            input_buffer[buffer_index] = '\0';
            putchar(c);
        }
    }
}