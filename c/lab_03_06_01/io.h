/**
* Модуль для ввода и вывода матрицы
*/

#ifndef __IO__H__
#define __IO__H__

// Директивы препроцессора
#include <stddef.h>
#include "consts.h"

// Объявления функций
int matrix_size_input(size_t *m, size_t *n);

void matrix_print(long int matrix[][N_MAX], size_t m, size_t n);

#endif // __IO__H__
