/*!
 * \file
 * \brief Задача 3
 *
 * Упорядочить строки матрицы:
 * 1. по убыванию их наибольших элементов;
 */

#include "f.h"
#include "io.h"
#include "consts.h"

int main(void)
{
    long int matrix[M_MAX][N_MAX] = { 0 };
    size_t m, n;
    int r;

    if (r = matrix_input(matrix, &m, &n), r != 0)
        return r;

    matrix_sort_rows(matrix, m, n);
    matrix_print(matrix, m, n);

    return 0;
}
