#ifndef MATRIX_H
#define MATRIX_H

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

typedef struct matrix
{
    double **data;
    size_t rows, cols;
} matrix_t;

typedef enum error
{
    /// При выполнении действия ошибок не возникло
    MATRIX_OK = 0,
    /// При вызове функции указаны неверные параметры
    MATRIX_INVALID_PARAM,
    /// При выполнении действия возникли ошибки при работе с памятью 
    MATRIX_MEM,
} matrix_error_t;

matrix_t *matrix_create(size_t rows, size_t cols);

void matrix_free(matrix_t **matrix);

matrix_error_t matrix_rand_fill(matrix_t *matrix, double rand_min, double rand_max);

matrix_error_t matrix_print(matrix_t *matrix);

// MATRIX MULT
matrix_error_t matrix_mult_standart(const matrix_t *a, const matrix_t *b, matrix_t **r);

matrix_error_t matrix_mult_winograd(const matrix_t *a, const matrix_t *b, matrix_t **r);

matrix_error_t matrix_mult_winograd_opt(const matrix_t *a, const matrix_t *b, matrix_t **r);

// Unsafe mult functions
void matrix_mult_standart_unsafe(const matrix_t *a, const matrix_t *b, matrix_t **r);

void matrix_mult_winograd_unsafe(const matrix_t *a, const matrix_t *b, matrix_t **r);

void matrix_mult_winograd_opt_unsafe(const matrix_t *a, const matrix_t *b, matrix_t **r);

#endif
