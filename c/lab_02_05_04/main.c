/*!
 * \file
 * \brief Задача 4
 *
 * 2. Найти и вывести на экран количество уникальных чисел в массиве.
 */

#include <stdio.h>
#include <math.h>

#define MAX_N 10                        // количество элементов массива
#define MACHINE_EPS 0.00000001          // константа погрешности при сравнении дробного числа с нулем

#define EXIT_CODE_INCORRECT_INPUT 1     // ошибка ввода
#define EXIT_CODE_INCORRECT_N 2         // n < 0, n > 10
#define EXIT_CODE_N_MISMATCH 3          // количество введенных элементов не соответствует n


/*!
 * \brief Принимает массив
 *
 * \param pa указатель на начало массива
 * \param pb указатель на указатель за последний элемент массива
 * \return код выхода
 *
 * Данная функция запрашивает количество элементов массива, 
 * которое является целым числом n и принадлежит отрезку [0, 10],
 * последовательность элементов этого массива, которые являются дробными числами
 * и возвращает код выхода.
 */
int array_input(long int *pa, long int **pb)
{   
    size_t n;
    int r;

    if (r = scanf("%lu", &n), r != 1)
        return EXIT_CODE_INCORRECT_INPUT;

    if ((n > 10) || (n == 0))
        return EXIT_CODE_INCORRECT_N;
    
    *pb = pa + n;
    for (long int *pi = pa; pi < *pb; pi++)
        r = scanf("%ld", pi);

    if (r != 1)
        return EXIT_CODE_INCORRECT_INPUT;

    return 0;
}

/*!
 * \brief Считает количество уникальных элементов
 *
 * \param pa указатель на начало массива
 * \param pb указатель за последний элемент массива
 *
 * Данная функция считает количество уникальных элементов counter
 * и выводит значение counter на экран.
 */
void array_count_uniq(long int *pa, long int *pb)
{   
    size_t counter = 0;
    for (long int *pi = pa; pi < pb; pi++)
    {   
        counter++;                                  // допустим он уникальный (не встречался ранее) -> записываем
        for (long int *pj = pa; pj < pi; pj++)
        {
            // встречался ли ранее этот элемент
            if (*pi == *pj)
            {
                counter--;                          // оказался неуникальным -> вычеркиваем
                break;
            }
        }
    }
    printf("%lu\n", counter);
}

/*!
 * \brief Ищет количество уникальных элементов.
 *
 * Данная функция использует функцию array_input, чтобы принять массив.
 * Затем, с помощью функции array_count_uniq считает 
 * количество уникальных элементов и выводит это количество.
 */
int main(void)
{
    long int arr[MAX_N] = { 0 };
    long int *pa;
    long int *pb;
    int r;

    pa = arr;
    pb = arr;
    if (r = array_input(pa, &pb), r != 0)
        return r;

    array_count_uniq(pa, pb);

    return 0;
}
