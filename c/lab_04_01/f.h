/**
* Модуль с реализацией аналогов строковых функций
*/ 

#ifndef __F__H__
#define __F__H__

// Директивы препроцессора
#include "consts.h"

// Объявления функций 
char *my_strpbrk(const char *str1, const char *str2);

size_t my_strspn(const char *string1, const char *string2);

size_t my_strcspn(const char *string1, const char *string2);

char *my_strchr(const char *string, int symbol);

char *my_strrchr(const char *string, int symbol);

#endif // __F__H__
