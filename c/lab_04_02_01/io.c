#include "io.h"
#include <stdio.h>

/**
 * @brief Запрос строки
 * 
 * @param line строка для записи
 * @return код выхода
 *
 * Функция запрашивает строку длиной LINE_MAX+3 из входного потока
 */
int line_input(char *line)
{
    if (fgets(line, LINE_MAX+3, stdin))
        return 0;
    return EXIT_CODE_EMPTY_INPUT;
}

/**
 * @brief Вывод результата
 *
 * @param str_array массив строк
 * @param n размер массива
 *
 * Функция выводит строку Result: а затем массив строк через пробел.
 */

void print_str_array(char str_array[][WORD_MAX+1], size_t n)
{
    printf("Result: ");
    for (size_t i = 0; i < n; i++)
        printf("%s ", str_array[i]);
    printf("\n");
}