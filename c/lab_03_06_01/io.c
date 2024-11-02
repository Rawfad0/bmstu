#include <stdio.h>
#include "io.h"

#define EXIT_CODE_INCORRECT_INPUT 1         // ошибка ввода
#define EXIT_CODE_INCORRECT_N 2             // n > 10
#define EXIT_CODE_INCORRECT_M 3             // m > 10
#define EXIT_CODE_MATRIX_NOT_SQUARE 4       // матрица не квадратная

int matrix_size_input(size_t *m, size_t *n)
{
    int r;

    if (r = scanf("%zu", m), r != 1)
        return EXIT_CODE_INCORRECT_INPUT;

    if ((*m > 10) || (*m == 0))
        return EXIT_CODE_INCORRECT_M;

    if (r = scanf("%zu", n), r != 1)
        return EXIT_CODE_INCORRECT_INPUT;

    if ((*n > 10) || (*n == 0))
        return EXIT_CODE_INCORRECT_N;
    
    if (*n != *m)
        return EXIT_CODE_MATRIX_NOT_SQUARE;

    return 0;
}

void matrix_print(long int matrix[][N_MAX], size_t m, size_t n)
{
    for (size_t i = 0; i < m; i++)
    {
        for (size_t j = 0; j < n; j++)
            printf("%ld ", matrix[i][j]);
        printf("\n"); 
    }
}