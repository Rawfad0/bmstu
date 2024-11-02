#include "f.h"

/**
 * @brief Заполнение бинарного файла случайными числами
 * 
 * @param f файловая переменная
 * @param num количество чисел
 */
void fill_random_int_bin_file(FILE *f, size_t num)
{
    int rand_num;
    srand(time(NULL));
    for (size_t i = 0; i < num; i++)
    {
        rand_num = rand();
        fwrite(&rand_num, sizeof(int), 1, f);
    }
}

/**
 * @brief Вывод целых чисел из бинарного файла
 * 
 * @param f файловая переменная
 * @return int код выхода
 */
int print_int_bin_file(FILE *f)
{
    size_t size;
    int num;
    int r;

    r = bin_file_size(f, &size);
    if (r == 0 && size % sizeof(int) == 0)
    {
        for (size_t i = 0; i < size / sizeof(int); i++)
        {
            fread(&num, sizeof(int), 1, f);
            printf("%d\n", num);
        }
    }
    else
        return EXIT_CODE_INCORRECT_SIZE;
    return 0;
}

/**
 * @brief Сортировка целых чисел по возрастанию из бинарного файла
 * 
 * @param f файловая переменная
 * @return int код выхода
 */
int sort_int_bin_file(FILE *f)
{
    size_t size;
    size_t min_i;
    int num1, num2;
    int r;

    r = bin_file_size(f, &size);
    if (r != 0 || size % sizeof(int) != 0)
        return EXIT_CODE_INCORRECT_SIZE;

    for (size_t i = 0; i < size / sizeof(int); i++)
    {
        min_i = i;
        for (size_t j = i; j < size / sizeof(int); j++)
        {
            if (r = get_number_by_pos(f, j, &num1), r != 0)
                return r;
            if (r = get_number_by_pos(f, min_i, &num2), r != 0)
                return r;
            if (num1 < num2)
                min_i = j;
        }

        if (min_i != i)
        {
            if (r = get_number_by_pos(f, min_i, &num1), r != 0)
                return r;
            if (r = get_number_by_pos(f, i, &num2), r != 0)
                return r;
            if (r = put_number_by_pos(f, min_i, &num2), r != 0)
                return r;
            if (r = put_number_by_pos(f, i, &num1), r != 0)
                return r;
        }
    }
    return 0;
}