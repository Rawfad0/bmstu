#include <stdio.h>
#include "io.h"

#define EXIT_CODE_INCORRECT_INPUT 1         // ошибка ввода
#define EXIT_CODE_INCORRECT_N 2             // n > 10
#define EXIT_CODE_INCORRECT_M 3             // m > 10
#define EXIT_CODE_ELEMENT_AMOUNT_MISMATCH 4     // количество введенных элементов не соответствует m*n

/*!
 * \brief Принимает матрицу
 *
 * \param matrix матрица
 * \param m количество строк матрицы
 * \param n количество столбцов матрицы
 * \return код выхода
 *
 * Данная функция запрашивает количество строк и столбцов массива, 
 * которые являются целыми числами m и n и принадлежат отрезку [0, 10],
 * последовательность элементов этой матрицы по строкам,
 * которые являются целыми числами и возвращает код выхода.
 */
int matrix_input(long int matrix[][N_MAX], size_t *m, size_t *n)
{   
    long int x;
    int r;

    if (r = scanf("%zu", m), r != 1)
        return EXIT_CODE_INCORRECT_INPUT;

    if ((*m > 10) || (*m == 0))
        return EXIT_CODE_INCORRECT_M;

    if (r = scanf("%zu", n), r != 1)
        return EXIT_CODE_INCORRECT_INPUT;

    if ((*n > 10) || (*n == 0))
        return EXIT_CODE_INCORRECT_N;

    for (size_t i = 0; i < *m; i++)
        for (size_t j = 0; j < *n; j++)
            if (r = scanf("%ld", &x), r == 1)
                matrix[i][j] = x;
            else
                return EXIT_CODE_ELEMENT_AMOUNT_MISMATCH;

    return 0;
}

/*!
 * \brief Выводит матрицу
 *
 * \param matrix массив
 * \param m количество строк в матрице
 * \param n количество столбцов в матрице
 *
 * Данная функция выводит m*n элементов матрицы целых чисел arr через пробел.
 */
void matrix_print(long int matrix[][N_MAX], size_t m, size_t n)
{
    for (size_t i = 0; i < m; i++)
    {
        for (size_t j = 0; j < n; j++)
            printf("%ld ", matrix[i][j]);
        printf("\n"); 
    }
}