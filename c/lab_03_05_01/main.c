/*!
 * \file
 * \brief Задача 5
 *
 * 1. Элементы матрицы, сумма цифр которых больше 10, 
 * в порядке обхода матрицы по строкам поместить в одномерный массив, 
 * циклически сдвинуть элементы этого массива влево на три позиции, 
 * и вернуть элементы из массива в матрицу в том же порядке, 
 * в котором они помещались в массив. Если в матрице нет чисел, 
 * сумма цифр которых больше 10, считать ситуацию ошибочной.
 */

#include "f.h"
#include "io.h"
#include "consts.h"

#define EXIT_CODE_NO_ELEMENTS 5     // в матрице нет чисел, сумма цифр которых больше 10

int main(void)
{
    long int matrix[M_MAX][N_MAX] = { 0 };
    long int array[N_MAX*M_MAX] = { 0 };
    size_t m, n, arr_len;
    int r;

    if (r = matrix_input(matrix, &m, &n), r != 0)
        return r;


    array_fill(matrix, m, n, array, &arr_len);
    if (arr_len == 0)
        return EXIT_CODE_NO_ELEMENTS;

    array_left_shift(array, arr_len, 3);
    matrix_insert(matrix, m, n, array);
    matrix_print(matrix, m, n);

    return 0;
}