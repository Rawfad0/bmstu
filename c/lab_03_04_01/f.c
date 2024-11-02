#include "f.h"
#include <stdlib.h>

/*!
 * \brief Меняет два элемента матрицы местами
 *
 * \param matrix матрица
 * \param i1 номер строки матрицы с первым элементом
 * \param j1 номер первого элемента в строке
 * \param i2 номер строки матрицы со вторым элементом
 * \param j2 номер второго элемента в строке
 *
 * Данная функция принимает целочисленную матрицу matrix размера m на n,
 * затем меняет два элемента матрицы местами.
 */
void matrix_swap_elements(long int *x, long int *y)
{
    long int temp = *x;
    *x = *y;
    *y = temp;
}

/*!
 * \brief Меняет треугольные участки матрицы местами
 *
 * \param matrix матрица
 * \param m количество строк матрицы
 * \param n количество столбцов матрицы
 *
 * Данная функция принимает целочисленную матрицу matrix размера m на n,
 * затем с помощью функции matrix_swap_elements меняет соответствующие элементы
 * треугольных участков матрицы местами.
 */
void matrix_swap_triangles(long int matrix[][N_MAX], size_t m, size_t n)
{
    for (size_t i = 0; i < (m / 2); i++)
        for (size_t j = i; j < n - i; j++)
        {   
            matrix_swap_elements(&matrix[i][j], &matrix[n - 1 - i][j]);
        }
}
