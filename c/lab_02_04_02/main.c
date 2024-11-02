/*!
 * \file
 * \brief Задача 4
 *
 * 2. Упорядочить массив по возрастанию с помощью сортировки выбором 
 * (англ. Selection Sort) и вывести на экран.
 */

#include <stdio.h>
#include <math.h>

#define MAX_N 10                        // количество элементов массива
#define MACHINE_EPS 0.00000001          // константа погрешности при сравнении дробного числа с нулем


#define EXIT_CODE_INCORRECT_N 2         // n == 0
#define EXIT_CODE_ARRAY_FULL 100        // массив закончен, а концевой признак не наступил

/*!
 * \brief Принимает массив
 *
 * \param arr массив
 * \param n количество элементов массива
 * \return код выхода
 *
 * Данная функция запрашивает последовательность элементов массива arr, 
 * которые являются дробными числами и возвращает код выхода.
 */
int array_input(long int arr[], size_t *n)
{
    long int x;
    int r;

    while (r = scanf("%ld", &x), (r == 1) && (*n < 10))
    {
        arr[*n] = x;
        (*n)++;
    }

    if (*n == 0)
        return EXIT_CODE_INCORRECT_N;
    if ((*n == 10) && (r == 1))
    {
        printf("Произошло переполнение массива, будут записаны только первые десять элементов.\n");
        return EXIT_CODE_ARRAY_FULL;
    }

    return 0;
}

/*!
 * \brief Сортирует массив
 *
 * \param arr массив
 * \param n количество элементов массива
 *
 * Данная функция соритрует массив arr
 * с помощью сортировки выбором.
 */
void array_selection_sort(long int arr[], size_t n)
{
    size_t min_i;
    long int temp;

    for (size_t i = 0; i < n; i++)
    {
        min_i = i;
        for (size_t j = i; j < n; j++)
        {
            if (arr[j] < arr[min_i])
                min_i = j;
        }

        if (min_i != i)
        {
            temp = arr[min_i];
            arr[min_i] = arr[i];
            arr[i] = temp;
        }
    }
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
 * \brief Сортирует массив
 *
 * Данная функция использует функцию array_input, чтобы принять массив.
 * Затем, с помощью функции array_selection_sort сортирует массив arr.
 * После этого отсортированный массив выводится на экран функцией array_print.
 */
int main(void)
{
    long int arr[MAX_N] = { 0 };
    size_t n = 0;
    int r;

    if (r = array_input(arr, &n), (r != 0) && (r != EXIT_CODE_ARRAY_FULL))
        return r;

    array_selection_sort(arr, n);

    array_print(arr, n);

    return r;
}
