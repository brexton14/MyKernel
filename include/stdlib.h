#ifndef STDLIB_H
#define STDLIB_H
#include "../include/types.h"


void utoa(u64 value, char* buffer, int base);
void itoa(s64 value, char* buffer);
int strcmp(const char* s1, const char* s2);


#endif