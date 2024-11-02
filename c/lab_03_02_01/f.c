#include "f.h"
#include <stdlib.h>

/*!
 * \brief Сумма цифр числа
 *
 * \param num число
 * \return сумма цифр числа
 *
 * Данная функция принимает целое число num и 
 * возвращает sum - сумму цифр числа num.
 */
int digit_sum(long int num)
{   
    int sum = 0;
    num = labs(num);
    while (num != 0)
    {
        sum += num % 10;
        num /= 10;
    }
    return sum;
}

/*!
 * \brief Удаление строки и столбца матрицы
 *
 * \param matrix матрица
 * \param m количество строк матрицы
 * \param n количество столбцов матрицы
 * \param arr масиив симетричности строк матрицы
 *
 * Данная функция принимает целочисленную матрицу matrix размера m на n,
 * затем сдвигает все строки и столбцы начиная с row_i и column_i соответственно,
 * количество строк и столбцов уменьшается на 1.
 */
void delete_row_and_column(long int matrix[][N_MAX], size_t *m, size_t *n, size_t row_i, size_t column_i)
{
    (*m)--;
    for (size_t i = row_i; i < *m; i++)
        for (size_t j = 0; j < *n; j++)
            matrix[i][j] = matrix[i + 1][j];
    (*n)--;
    for (size_t i = 0; i < *m; i++)
        for (size_t j = column_i; j < *n; j++)
            matrix[i][j] = matrix[i][j + 1];
}

/*!
 * \brief Удаление строки и столбца матрицы содержащих элемент матрицы с минимальной суммой цифр.
 *
 * \param matrix матрица
 * \param m количество строк матрицы
 * \param n количество столбцов матрицы
 *
 * Данная функция принимает целочисленную матрицу matrix размера m на n,
 * затем с помощью функции digit_sum вычисляет сумму цифр элемента и
 * и с помощью функции delete_row_and_column удаляет строку и столбец матрицы
 * на пересечении элемента матрицы с наименьшей суммой цифр.
 */
void find_min_digit_sum_and_delete(long int matrix[][N_MAX], size_t *m, size_t *n)
{
    size_t row_i = 0, column_i = 0;
    for (size_t i = 0; i < *m; i++)
        for (size_t j = 0; j < *n; j++)
            if (digit_sum(matrix[i][j]) < digit_sum(matrix[row_i][column_i]))
            {
                row_i = i;
                column_i = j;
            }
    delete_row_and_column(matrix, m, n, row_i, column_i);
}
