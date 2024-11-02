/*!
 * \file
 * \brief Задача 4
 *
 * 1. Поменять местами элементы, расположенные в показанной в примере области.
 * Первая строка меняется с последней, вторая — с предпоследней и т. д. 
 * Элементы, расположенные на главной и побочных диагоналях, включены в обмен.
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

    matrix_swap_triangles(matrix, m, n);
    matrix_print(matrix, m, n);

    return 0;
}