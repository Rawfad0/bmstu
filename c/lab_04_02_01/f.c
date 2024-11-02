#include "f.h"
#include "string.h"

/**
 * @brief Является ли строка уникальной
 * 
 * @param str_array массив строк
 * @param n длина массива
 * @param str строка
 * @return 0/1
 *
 * Проверяет есть ли строка str в str_array, если есть возвращает 0, 
 * если нет, т.е. строка является уникальной то возвращает 1. 
 */
int is_str_uniq(char str_array[][WORD_MAX+1], size_t n, char str[])
{
    for (size_t i = 0; i < n; i++)
        if (strncmp(str_array[i], str, WORD_MAX+1) == 0)
            return 0;
    return 1;
}

/**
 * @brief Разделяет строку по словам на массив строк
 * 
 * @param line строка
 * @param str_array массив строк
 * @param n длина массива
 * @return код возврата
 *
 * Функция итерируется по символам строки и добавляет их в массив строк, пока не встретит разделяющий символ,
 * потом проверяет уникальности строки в массиве, и если не уникальна, то стирает её (ставит нулевой символ в начало),
 * а если уникальна, то переходит к заполнению следующей строки массива.
 */
int split_line_to_array(char *line, char str_array[][WORD_MAX+1], size_t *n)
{
    *n = 0;
    size_t j = 0;
    for (size_t i = 0; i < strlen(line); i++)
    {
        if (!strchr(SEPARATORS, line[i]))
        {
            str_array[*n][j] = line[i];
            j++;
            if (j > WORD_MAX)
                return EXIT_CODE_INCORRECT_WORD_SIZE;
        } 
        else 
        {
            if (j != 0)
            {
                str_array[*n][j] = '\0';
                if (is_str_uniq(str_array, *n, str_array[*n]) == 1)
                    (*n)++;
            }
            j = 0;
        }
    }
    if (j != 0)
    {
        str_array[*n][j] = '\0';
        if (is_str_uniq(str_array, *n, str_array[*n]) == 1)
            (*n)++;
    }
    return 0;
}

/**
 * @brief Лексико-графическая сортировка массива строк
 * 
 * @param str_array массив строк
 * @param n длина массива
 *
 * Упорядочивает массив строк в лексико-графическом порядке.
 */
void str_array_sort(char str_array[][WORD_MAX+1], size_t n)
{
    size_t min_i;
    char temp[WORD_MAX+1];
    for (size_t i = 0; i < n; i++)
    {
        min_i = i;
        for (size_t j = i; j < n; j++)
        {
            if (strncmp(str_array[min_i], str_array[j], WORD_MAX+1) > 0)
                min_i = j;
        }
        if (min_i != i)
        {
            strncpy(temp, str_array[min_i], WORD_MAX+1);
            strncpy(str_array[min_i], str_array[i], WORD_MAX+1);
            strncpy(str_array[i], temp, WORD_MAX+1);
        }
    }
}

int is_valid_line(char *line)
{
    if (strlen(line) > LINE_MAX+1)
        return EXIT_CODE_INCORRECT_LINE_SIZE;
    return 0;
}
