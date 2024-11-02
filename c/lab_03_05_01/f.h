/**
* Модуль для основных вычислений программы
*/ 

#ifndef __F__H__
#define __F__H__

// Директивы препроцессора
#include <stddef.h>
#include "consts.h"

// Объявления функций 
void array_fill(long int matrix[][N_MAX], size_t m, size_t n, long int array[], size_t *arr_len);

void array_left_shift(long int array[], size_t arr_len, size_t shift);

void matrix_insert(long int matrix[][N_MAX], size_t m, size_t n, long int array[]);

#endif // __F__H__
