/**
 * Модуль содержащий методы работы с матрицами
 */ 

#ifndef __KEY__H__
#define __KEY__H__

// Директивы препроцессора
#include "consts.h"
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <stdio.h>

typedef struct
{
    double **matrix;
    size_t n, m;
} matrix_t;

// Объявления функций

double **allocate_matrix(size_t n, size_t m);

void matrix_addition(matrix_t matrix1, matrix_t matrix2, matrix_t *matrix_res);

void matrix_multiplication(matrix_t matrix1, matrix_t matrix2, matrix_t *matrix_res);

int matrix_solve(matrix_t matrix, matrix_t *matrix_res);

#endif
