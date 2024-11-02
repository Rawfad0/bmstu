/*!
 * \file
 * \brief Задача 3
 *
 * 2. Удалить из исходного массива все элементы, 
 * которые являются полными квадратами. Ситуацию, 
 * когда массив после операции не изменился, 
 * ошибочной не считать.
 */

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define MAX_N 10                        // количество элементов массива
#define MACHINE_EPS 0.00000001          // константа погрешности при сравнении дробного числа с нулем

#define EXIT_CODE_INCORRECT_INPUT 1     // ошибка ввода
#define EXIT_CODE_INCORRECT_N 2         // n < 0, n > 10
#define EXIT_CODE_N_MISMATCH 3          // количество введенных элементов не соответствует n
#define EXIT_CODE_NO_ELEMENTS 4         // новый массив пуст, т.е. таких чисел нет


/*!
 * \brief Принимает массив
 *
 * \param arr массив
 * \param n количество элементов массива
 * \return код выхода
 *
 * Данная функция запрашивает количество элементов массива, 
 * которое является целым числом n и принадлежит отрезку [0, 10],
 * последовательность элементов этого массива, которые являются дробными числами
 * и возвращает код выхода.
 */
int array_input(long int arr[], size_t *n)
{
    long int x;
    size_t i = 0;
    int r;

    if (r = scanf("%lu", n), r != 1)
        return EXIT_CODE_INCORRECT_INPUT;

    if ((*n > 10) || (*n == 0))
        return EXIT_CODE_INCORRECT_N;

    while (r = scanf("%ld", &x), r == 1)
    {
        if (i == *n)
            return EXIT_CODE_N_MISMATCH;
        arr[i] = x;
        i++;        
    }

    if (*n != i)
        return EXIT_CODE_N_MISMATCH;

    return 0;
}

/*!
 * \brief Удаляет квадраты из массива
 *
 * \param arr массив
 * \param n количество элементов массива
 *
 * Данная функция удаляет все элементы массива arr,
 * которые являются полными квадратами.
 */
void array_sq_del(long int arr[], size_t *n)
{   
    size_t shift = 0;
    for (size_t i = 0; i < *n; i++)
    {
        if (fabsl(fmodl((long double) sqrtl(arr[i]), 1)) < MACHINE_EPS)
        {
            shift++;
        }
        else
            arr[i - shift] = arr[i];
    }
    *n -= shift;
}

/*!
 * \brief Выводит массив
 *
 * \param arr массив
 * \param n количество элементов массива
 *
 * Данная функция выводит n элементов массива дробных чисел arr через пробел.
 */
void array_print(long int arr[], size_t n)
{
    for (size_t i = 0; i < n; i++)
        printf("%ld ", arr[i]);
    printf("\n");
}


/*!
 * \brief Удаляет элементы-квадраты из массива.
 *
 * Данная функция использует функцию array_input, чтобы принять массив.
 * Затем, с помощью функции array_sq_del удаляет все элементы массива arr,
 * которые являются полными квадратами.
 * После этого новый массив выводится на экран функцией array_print.
 */
int main(void)
{
    long int arr[MAX_N] = { 0 };
    size_t n;
    int r;

    if (r = array_input(arr, &n), r != 0)
        return r;

    array_sq_del(arr, &n);

    if (n == 0)
    {
        printf("Bce элементы массива оказались квадратами, массив пуст.\n");
        return EXIT_CODE_NO_ELEMENTS;
    }

    array_print(arr, n);

    return 0;
}
