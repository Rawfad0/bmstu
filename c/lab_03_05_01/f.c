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
 * \brief Заполянет массив определенных элементов
 *
 * \param matrix матрица
 * \param m количество строк матрицы
 * \param n количество столбцов матрицы
 *
 * Данная функция принимает целочисленную матрицу matrix размера m на n,
 * затем с помощью функции digit_sum находит определенные элементы и 
 * заполняет ими массив array длины arr_len.
 */
void array_fill(long int matrix[][N_MAX], size_t m, size_t n, long int array[], size_t *arr_len)
{
    *arr_len = 0;
    for (size_t i = 0; i < m; i++)
        for (size_t j = 0; j < n; j++)
            if (digit_sum(matrix[i][j]) > 10)
                array[(*arr_len)++] = matrix[i][j];
}

/*!
 * \brief Сдвиг элементов массива влево
 *
 * \param array матрица
 * \param array_len длина элементов
 * \param shift сдвиг
 *
 * Данная функция принимает целочисленную массив array размера arr_len,
 * затем сдвигает все элементы массива на shift влево.
 */
void array_left_shift(long int array[], size_t arr_len, size_t shift)
{
    long int temp;
    // for (size_t i = 0; i < shift; )
    for (size_t i = 0; i < shift; i++)
    {   
        for (size_t j = 0; j < arr_len - 1; j++)
        {
            temp = array[j];
            array[j] = array[j + 1];
            array[j + 1] = temp;
        }
    }
}

/*!
 * \brief Вставляет определенные элементы обратно из списка
 *
 * \param matrix матрица
 * \param m количество строк матрицы
 * \param n количество столбцов матрицы
 * \param array массив определенных элементов
 *
 * Данная функция принимает целочисленную матрицу matrix размера m на n,
 * затем с помощью функции digit_sum находит определенные элементы и 
 * меняет их на соответствующие из массива array.
 */
void matrix_insert(long int matrix[][N_MAX], size_t m, size_t n, long int array[])
{
    size_t k = 0;
    for (size_t i = 0; i < m; i++)
        for (size_t j = 0; j < n; j++)
            if (digit_sum(matrix[i][j]) > 10)
                matrix[i][j] = array[k++];
}
