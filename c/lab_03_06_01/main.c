/*!
 * \file
 * \brief Задача 6
 *
 * 1. Приняв с клавиатуры число строк и столбцов матрицы, 
 * заполнить квадратную целочисленную матрицу по спирали 
 * по часовой стрелке. Матрицу вывести на экран. 
 */

#include "f.h"
#include "io.h"
#include "consts.h"

int main(void)
{
    long int matrix[M_MAX][N_MAX] = { 0 };
    size_t m, n;
    int r;

    if (r = matrix_size_input(&m, &n), r != 0)
        return r;

    matrix_spiral_fill(matrix, n);

    matrix_print(matrix, m, n);

    return 0;
}