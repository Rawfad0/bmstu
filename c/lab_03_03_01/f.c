#include "f.h"
#include <stdlib.h>

/*!
 * \brief Максимальный элемент массива
 *
 * \param array массив
 * \param n количество элементов в массиве
 *
 * Данная функция принимает массив array размера n,
 * затем находит максимальный элемент в этом массиве.
 */
long int array_max(long int array[], size_t n)
{
    long int max = array[0];
    for (size_t i = 1; i < n; i++)
        if (array[i] > max)
            max = array[i];
    return max;
}

/*!
 * \brief Меняет две строки матрицы местами
 *
 * \param line1 первая строка
 * \param line2 вторая строка
 * \param n количество элементов в строке
 *
 * Данная функция принимает две строки матрицы line1 line2 размера n,
 * затем меняет соответствующие элементы строк местами.
 */
void matrix_swap_rows(long int line1[], long int line2[], size_t n)
{   
    long int temp;
    for (size_t i = 0; i < n; i++)
    {
        temp = line1[i];
        line1[i] = line2[i];
        line2[i] = temp;
    }
}

/*!
 * \brief Сортирует строки матрицы по убыванию их наибольших элементов
 *
 * \param matrix матрица
 * \param m количество строк матрицы
 * \param n количество столбцов матрицы
 *
 * Данная функция принимает целочисленную матрицу matrix размера m на n,
 * затем с помощью функции array_max находит максимальный элемент в строке и
 * и с помощью функции matrix_swap_rows, меняющей две строки местами,
 * сортирует строки матрицы элементом с помощью с помощью сортировки выбором.
 */
void matrix_sort_rows(long int matrix[][N_MAX], size_t m, size_t n)
{   
    size_t max_i;
    long int max, line_max;
    for (size_t i = 0; i < m; i++)
    {   
        max_i = i;
        max = array_max(matrix[i], n);
        for (size_t j = i; j < m; j++)
        {
            line_max = array_max(matrix[j], n);
            if (line_max > max)
            {
                max_i = j;
                max = line_max;
            }
        }

        if (max_i != i)
        {
            matrix_swap_rows(matrix[i], matrix[max_i], n);
        }
    }
}
