#include "func.h"

/**
 * @brief Нахождение минимума и максимума в файле
 * 
 * @param f файловая переменная
 * @param min минимум 
 * @param max максимум
 * @return int код выхода
 */
int find_min_max(FILE *f, long double *min, long double *max)
{
    long double num;

    if (feof(f) || fscanf(f, "%Lf", min) != 1)
        return EXIT_CODE_INCORRECT_INPUT;
    *max = *min;
    while (!feof(f))
    {
        if (fscanf(f, "%Lf", &num) != 1)
            return EXIT_CODE_INCORRECT_INPUT;
        if (num < *min)
            *min = num;
        if (num > *max)
            *max = num;
    }
    if (*max - *min < EPS)
        return EXIT_CODE_NO_MEAN;
    rewind(f);
    return 0;
}

/**
 * @brief Среднее значение чисел, расположенных между минимальным и максимальным числами
 * 
 * @param f файловая переменная
 * @param mean среднее
 * @return int код выхода
 */
int between_minmax_mean(FILE *f, long double *mean)
{
    long double num;
    long double min;
    long double max;
    long double sum = 0;
    size_t counter = 0;
    int r;

    if (r = find_min_max(f, &min, &max), r != 0)
        return r;

    while (!feof(f))
    {
        if (fscanf(f, "%Lf", &num) != 1)
            return EXIT_CODE_INCORRECT_INPUT;
        if (fabsl(num - min) < EPS && counter != 0)
            break;           // условие конца
        if (counter != 0)
        {
            sum += num;
            counter++;
        }
        if (fabsl(num - min) < EPS)
        {
            min = max;
            counter++;
        }
        if (fabsl(num - max) < EPS)
        {
            max = min;
            counter++;
        }
    }
    counter--;  // так как был дополнительный ++ при условии начала, обозначающий начало суммирования
    if (counter == 0)
        return EXIT_CODE_NO_MEAN;
    *mean = sum / counter;

    return 0;
}