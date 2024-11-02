/*!
 * \file
 * \brief Задача 2
 *
 * 2. Сформировать и вывести на экран новый массив, 
 * в который скопировать элементы исходного массива, 
 * которые начинаются и заканчиваются на одну и ту же цифру.
 */

#include <stdio.h>
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
 * \brief Формирует новый массив
 *
 * \param arr массив
 * \param n количество элементов массива
 * \param new_arr новый массив
 * \param new_arr_n количество элементов нового массива
 *
 * Данная функция формирует новый массив new_arr,
 * в который копируются элементы исходного массива arr, 
 * которые начинаются и заканчиваются на одну и ту же цифру.
 */
void fill_new_array(long int arr[], size_t n, long int new_arr[], size_t *new_arr_n)
{   
    int x;

    for (size_t i = 0; i < n; i++)
    {
        x = labs(arr[i]);
        while (x >= 10)
        {
            x /= 10;
        }
        if (x == (labs(arr[i]) % 10))
        {
            new_arr[*new_arr_n] = arr[i];
            *new_arr_n += 1;
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
    {
        printf("%ld ", arr[i]);
    }
    printf("\n");
}


/*!
 * \brief Выводит на экран элементы массива у которых совпадает первая и последняя цифра.
 *
 * Данная функция использует функцию array_input, чтобы принять массив.
 * Затем, с помощью функции fill_new_array, формирует новый массив,
 * в который копируются элементы исходного массива, 
 * которые начинаются и заканчиваются на одну и ту же цифру.
 * После этого новый массив выводится на экран функцией array_print.
 */
int main(void)
{
    long int arr[MAX_N] = { 0 };
    long int new_arr[MAX_N] = { 0 };
    size_t n;
    size_t new_arr_n = 0;
    int r;

    if (r = array_input(arr, &n), r != 0)
        return r;

    fill_new_array(arr, n, new_arr, &new_arr_n);

    if (new_arr_n == 0)
    {
        printf("B массиве нет таких элементов.\n");
        return EXIT_CODE_NO_ELEMENTS;
    }

    array_print(new_arr, new_arr_n);

    return 0;
}
