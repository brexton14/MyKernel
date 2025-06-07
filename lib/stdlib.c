#include "../include/types.h"

int strcmp(const char* s1, const char* s2) {
    while (*s1 && (*s1 == *s2)) {
        s1++;
        s2++;
    }
    return *(const u8*)s1 - *(const u8*)s2;
}

void utoa(u64 value, char* buffer, int base) {
    const char* digits = "0123456789ABCDEF";
    char temp[32];
    int i = 0;

    if (value == 0) {
        buffer[0] = '0';
        buffer[1] = '\0';
        return;
    }

    while (value > 0) {
        temp[i++] = digits[value % base];
        value /= base;
    }

    for (int j = 0; j < i; j++) {
        buffer[j] = temp[i - j - 1];
    }
    buffer[i] = '\0';
}

void itoa(s64 value, char* buffer) {
    if (value < 0) {
        buffer[0] = '-';
        utoa((u64)(-value), buffer + 1, 10);
    } else {
        utoa((u64)value, buffer, 10);
    }
}
