// Mini version of strcmp (no stdlib)
int strcmp(const char* s1, const char* s2) {
    while (*s1 && (*s1 == *s2)) {
        s1++;
        s2++;
    }
    return *(const unsigned char*)s1 - *(const unsigned char*)s2;
}

void utoa(unsigned int value, char* buffer, int base){
    const char* digits = "0123456789ABCDEF";
    char temp[32];
    int i = 0;

    if (value == 0){
        buffer[0] = '0';
        buffer[1] = '\0';
        return;
    }

    while (value > 0){
        temp[i++] = digits[value % base];
        value /= base;
    }

    for (int j = 0; j < i; j++) {
        buffer[j] = temp[i - j - 1];  // Reverse the digits
    }
    buffer[i] = '\0';
}

// simple int to str (base 10)
void itoa(int value, char* buffer) {
    if (value < 0) {
        buffer[0] = '-';
        utoa(-value, buffer + 1, 10);  // convert positive part
    } else {
        utoa(value, buffer, 10);
    }
}
