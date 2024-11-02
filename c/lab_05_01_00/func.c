#include "func.h"

/**
 * @brief Вывод положительного максимального элемента, находящегося после отрицательного
 * 
 * @param f файловая переменная
 * @return int код выхода
 */
int process(FILE *f)
{
    long max = 0;
    long num;
    long prev = 0;
    int r;
    
    while (r = fscanf(f, "%ld", &num), r == 1)
    {
        if (prev < 0 && num > max)
            max = num;
        prev = num;
    }

    if (max == 0)
        return EXIT_CODE_NO_MAX;
    
    printf("%ld\n", max);
    
    return 0;
}