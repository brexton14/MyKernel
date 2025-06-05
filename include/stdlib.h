#ifndef STDLIB_H
#define STDLIB_H

#ifdef __cplusplus
extern "C" {
#endif

void itoa(int value, char* buffer);
void utoa(unsigned int value, char* buffer, int base);
int strcmp(const char* s1, const char* s2);

#ifdef __cplusplus
}
#endif

#endif