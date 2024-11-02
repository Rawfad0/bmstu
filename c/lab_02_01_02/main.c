/*!
 * \file
 * \brief Задача 1
 *
 * 2. Найти и вывести на экран среднее арифметическое
 * отрицательных элементов массива.
 */

#include <stdio.h>

#define MAX_N 10                        // количество элементов массива
#define MACHINE_EPS 0.00000001          // константа погрешности при сравнении дробного числа с нулем

#define EXIT_CODE_INCORRECT_INPUT 1     // ошибка ввода
#define EXIT_CODE_INCORRECT_N 2         // n < 0, n > 10
#define EXIT_CODE_N_MISMATCH 3          // количество введенных элементов не соответствует n
#define EXIT_CODE_ZERO_DIVISION 4       // деление на ноль

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
    size_t i = 0;
    int r;

    if (r = scanf("%lu", n), r != 1)
        return EXIT_CODE_INCORRECT_INPUT;

    if (*n > 10)
        return EXIT_CODE_INCORRECT_N;

    while (r = scanf("%ld", &arr[i]), r == 1)
        i++;

    if (*n != i)
        return EXIT_CODE_N_MISMATCH;

    return 0;
}

/*!
 * \brief Вычисляет среднее арифметическое отрицательных элементов массива
 *
 * \param a массив
 * \param n количество элементов массива
 * \return среднее арифметическое отрицательных элементов массива 
 *         или 0, если таких элементов нет
 *
 * Данная функция принимает массив *a, в котором находятся дробные числа, 
 * и число его элементов, которое является целым числом n, 
 * и возвращает среднее арифметическое отрицательных элементов этого массива.
 */
long double array_negative_num_mean(long int *a, size_t n)
{
    int counter = 0;
    long int sum = 0;
    
    for (size_t i = 0; i < n; i++)
    {
        if (a[i] < 0)
        {
            sum += a[i];
            counter++;
        }
    }

    if (counter == 0)
        return 0;
    else
        return (long double) sum / counter;
}

/*!
 * \brief Выводит на экран среднее арифметическое отрицательных элементов массива.
 *
 * Данная функция запрашивает количество элементов массива, 
 * которое является целым числом n и принадлежит отрезку [0, 10],
 * последовательность элементов этого массива, которые являются дробными числами,
 * и выводит среднее арифметическое отрицательных элементов этого массива, 
 * которое является дробным числом arr_mean.
 */
int main(void)
{
    long int arr[MAX_N] = { 0 };
    size_t n;
    long double arr_mean;
    int r;

    if (r = array_input(arr, &n), r != 0)
        return r;

    arr_mean = array_negative_num_mean(arr, n);

    if (arr_mean >= 0)
    {
        printf("B массиве нет отрицательных элементов.\n");
        return EXIT_CODE_ZERO_DIVISION;
    }

    printf("Среднее значение равно %Lf\n", arr_mean);

    return 0;
}
