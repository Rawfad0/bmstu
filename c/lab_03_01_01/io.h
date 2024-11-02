/**
* Модуль для ввода матрицы и вывода массива
*/ 

#ifndef __IO__H__
#define __IO__H__

// Директивы препроцессора
#include <stddef.h>
#include "consts.h"

// Объявления функций
int matrix_input(long int matrix[][N_MAX], size_t *m, size_t *n);

void array_print(long int arr[], size_t n);

#endif // __IO__H__
