#ifndef TYPES_H
#define TYPES_H

// Unsigned types
typedef unsigned char      u8;
typedef unsigned short     u16;
typedef unsigned int       u32;
typedef unsigned long long u64;

// Signed types
typedef signed char        s8;
typedef signed short       s16;
typedef signed int         s32;
typedef signed long long   s64;

// Freestanding variadic macros
typedef __builtin_va_list va_list;
#define va_start(ap, last) __builtin_va_start(ap, last)
#define va_arg(ap, type)   __builtin_va_arg(ap, type)
#define va_end(ap)         __builtin_va_end(ap)

// Core types
#define NULL ((void*)0)
typedef u64 size;  // or typedef u64 usize;

#endif // TYPES_H