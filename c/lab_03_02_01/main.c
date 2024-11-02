/*!
 * \file
 * \brief Задача 2
 *
 * 1. Удалить строку и столбец, на пересечении которых 
 * расположен элемент матрицы, сумма цифр которого минимальна. 
 * При обнаружении нескольких подходящих элементов 
 * считать целевым первый при обходе по строкам.
 */

#include "f.h"
#include "io.h"
#include "consts.h"

#define EXIT_CODE_EMPTY_MATRIX 5            // пустая матрица

int main(void)
{
    long int matrix[M_MAX][N_MAX] = { 0 };
    size_t m, n;
    int r;

    if (r = matrix_input(matrix, &m, &n), r != 0)
        return r;

    find_min_digit_sum_and_delete(matrix, &m, &n);
    if (m == 0 || n == 0)
        return EXIT_CODE_EMPTY_MATRIX;
    matrix_print(matrix, m, n);

    return 0;
}