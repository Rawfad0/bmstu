/**
 * @file main.c
 * @brief Собственная реализация функции snprintf
 * 
 */

#ifndef MY_SNPRINTF_H_
#define MY_SNPRINTF_H_

#include <stddef.h>

int my_snprintf(char *restrict s, size_t n, const char *restrict format, ...);

#endif
