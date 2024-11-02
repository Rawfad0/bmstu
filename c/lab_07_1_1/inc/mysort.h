/**
 * Модуль содержащий функцию сортировки и сравнения чисел
 */ 

#ifndef __MYSORT__H__
#define __MYSORT__H__

// Директивы препроцессора
#include "consts.h"
#include <string.h>

// Объявления функций
int compare_int(const void *p, const void *q);

void mysort(void *base, size_t nmemb, size_t size, int (*compar)(const void*, const void*));

#endif